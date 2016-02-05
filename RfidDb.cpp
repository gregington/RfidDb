#include "Arduino.h"
#include "RfidDb.h"

// Magic number to verify RFID database in EEPROM
#define RFID_DB_MAGIC 0x75

// returns the EEPROM location of the number of items in the database
#define countOffset() (_eepromOffset + 1)

// returns the EEPROM location of the first id in the database
#define dataOffset() (countOffset() + 1)

// returns the EEPROM location of the Ith id in the database
#define entryOffset(I) (dataOffset() + ((I) * sizeof(uint32_t)))

RfidDb::RfidDb(uint8_t maxSize, uint16_t eepromOffset) {
  _eepromOffset = eepromOffset;
  _maxSize = maxSize;
}

void RfidDb::begin() {
  if (!hasMagic()) {
    initDb();
  }
}

uint8_t RfidDb::maxSize() {
  return _maxSize;
}

uint8_t RfidDb::count() {
  return EEPROM.read(countOffset());
}

bool RfidDb::insert(uint32_t id) {
  // if already exists in the database, we return success for insert
  if (posOf(id) != -1) {
    return true;
  }
  uint8_t c = count();
  // no room in database, return false
  if (c >= _maxSize) {
    return false;
  }
  // we know there is room for the id
  EEPROM.put(entryOffset(c), id);
  EEPROM.write(countOffset(), c + 1);
}

void RfidDb::remove(uint32_t id) {
  uint8_t originalCount = count();  
  if (originalCount == 0) {
    return;
  }
  int16_t posToRemove = posOf(id);
  if (posToRemove == -1) {
    return;
  }
  uint8_t newCount = originalCount - 1;
  if (newCount > 0 || newCount == posToRemove) {
    uint32_t idToMove = getId(newCount);
    EEPROM.put(entryOffset(posToRemove), idToMove);
  }
  EEPROM.write(countOffset(), newCount);
}

bool RfidDb::get(uint8_t pos, uint32_t &id) {
  if (pos >= count()) {
    return false;
  }
  id = getId(pos);
  return true;
}

bool RfidDb::contains(uint32_t id) {
  return posOf(id) != -1;
}

// Returns whether the EEPROM location at the EEPROM base address
// contains the magic number
bool RfidDb::hasMagic() {
  return EEPROM.read(_eepromOffset) == RFID_DB_MAGIC;
}

// Initialises the database by writing the magic number to the base
// EEPROM address, followed by a zero count.
void RfidDb::initDb() {
  EEPROM.write(_eepromOffset, RFID_DB_MAGIC);
  EEPROM.write(countOffset(), 0);
}

// Returns the position of given id in the database or -1
// if the id is not in the database
int16_t RfidDb::posOf(uint32_t id) {
  for (uint8_t i = 0, n = count(); i < n; i++) {
    if (id == getId(i)) {
      return i;
    }
  }
  return -1;
}

// Returns the id at the given position
uint32_t RfidDb::getId(uint8_t pos) {
  uint32_t id;
  EEPROM.get(entryOffset(pos), id);
  return id;
}
