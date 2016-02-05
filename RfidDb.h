#ifndef RFID_DB_H
#define RFID_DB_H

#include "Arduino.h"
#include "EEPROM.h"

// A database designed to store a number of RFIDs of 32 bits up to a fixed
// size. The database is stored in EEPROM and requires (N * 4) + 2 bytes of 
// storage where n is the maximum number of entries.
//
// Identifiers can be added, removed and checked for existence.
//
// Performance of insert, remove and contains is O(N).
// Performance of get at index is O(1)
class RfidDb {
  public:
    // Creates an RFID database.
    // Parameters:
    //   maxSize: The maximum number of ids that the database can hold
    //   eepromOffset: the byte offset from 0 where the databse resides
    //       in EEPROM
    RfidDb(uint8_t maxSize, uint16_t eepromOffset);

    // Initialises the database in EEPROM if the location at EEPROM
    // offset does not contain the magic number.
    void begin();

    // Returns the maximum number of identifiers that the database can
    // contain.
    uint8_t maxSize();

    // Returns the number of identifiers currently in the database.
    uint8_t count();

    // Inserts the identifier in the database. Returns true if the indentifier
    // was successfully inserted or already existed in the database. Returns
    // false if the database is at maximum capacity.
    bool insert(uint32_t id);

    // Removes the identifier from the database, if it exists. 
    void remove(uint32_t id);

    // Returns the identfier it the given position. Callers should check
    // the return value before using the identifier. Returns true if
    // the position is less than the count and writes the identifier value
    // at the given address.
    // Returns false if pos >= count
    bool get(uint8_t pos, uint32_t &id);

    // Returns whether the database contains the given identifier.
    bool contains(uint32_t id);

  private:
    uint16_t _eepromOffset;
    uint8_t _maxSize;

    bool hasMagic();
    void initDb();
    uint16_t countOffset();
    uint16_t dataOffset();
    uint16_t entryOffset(uint8_t pos);
    int16_t posOf(uint32_t id);
    uint32_t getId(uint8_t pos);
};

#endif
