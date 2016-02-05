#include "EEPROM.h"
#include "RfidDb.h"

RfidDb db = RfidDb(4, 0);

uint32_t id1 = 1000000001;
uint32_t id2 = 1000000002;
uint32_t id3 = 1000000003;
uint32_t id4 = 1000000004;
uint32_t id5 = 1000000005;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }

  EEPROM.put(0, 0);
  db.begin();

  Serial.println("Empty database");
  dumpState();

  Serial.print("Inserting id 1 = ");
  Serial.println(db.insert(id1));
  dumpState();
  dumpContains();
  
  Serial.print("Inserting id 2 = ");
  Serial.println(db.insert(id2));
  dumpState();
  dumpContains();

  Serial.print("Inserting id 3 = ");
  Serial.println(db.insert(id3));
  dumpState();
  dumpContains();

  Serial.print("Inserting id 4 = ");
  Serial.println(db.insert(id4));
  dumpState();
  dumpContains();

  Serial.print("Inserting id 5 = ");
  Serial.println(db.insert(id5));
  dumpState();
  dumpContains();

  Serial.println("Removing id 5");
  db.remove(id5);
  dumpState();
  dumpContains();

  Serial.println("Removing id 1");
  db.remove(id1);
  dumpState();
  dumpContains();

  Serial.println("Removing id 3");
  db.remove(id3);
  dumpState();
  dumpContains();

  Serial.println("Removing id 2");
  db.remove(id2);
  dumpState();
  dumpContains();

  Serial.println("Removing id 4");
  db.remove(id4);
  dumpState();
  dumpContains();
}

void loop() {
  // put your main code here, to run repeatedly:

}

void dumpState() {
  uint8_t count = db.count();
  Serial.print("count = ");
  Serial.print(count);
  Serial.print(" [");
  uint32_t id;
  for (int i = 0; i < count; i++) {
    if (db.get(i, id)) {
      Serial.print(id);
      if (i < count - 1) {
        Serial.print(", ");
      }
    }
  }
  Serial.println("]");
}

void dumpContains() {
  Serial.print("Contains id1 = ");
  Serial.println(db.contains(id1));
  Serial.print("Contains id2 = ");
  Serial.println(db.contains(id2));
  Serial.print("Contains id3 = ");
  Serial.println(db.contains(id3));
  Serial.print("Contains id4 = ");
  Serial.println(db.contains(id4));
  Serial.print("Contains id5 = ");
  Serial.println(db.contains(id5));  
}

