#include "EEPROM.h"
#include "RfidDb.h"

RfidDb db = RfidDb(4, 0, 4);

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

  Serial.print("Inserting id1 = ");
  Serial.println(db.insert(id1, "AAA"));
  dumpState();
  dumpContains();
  
  Serial.print("Inserting id2 = ");
  Serial.println(db.insert(id2, "BBB"));
  dumpState();
  dumpContains();

  Serial.print("Inserting id3 = ");
  Serial.println(db.insert(id3, "CCC"));
  dumpState();
  dumpContains();

  Serial.print("Inserting id4 = ");
  Serial.println(db.insert(id4, "DDD"));
  dumpState();
  dumpContains();

  Serial.print("Inserting id5 = ");
  Serial.println(db.insert(id5, "EEE"));
  dumpState();
  dumpContains();

  Serial.println("Removing id5");
  db.remove(id5);
  dumpState();
  dumpContains();

  Serial.println("Removing id1");
  db.remove(id1);
  dumpState();
  dumpContains();

  Serial.println("Removing id3");
  db.remove(id3);
  dumpState();
  dumpContains();

  Serial.println("Removing id2");
  db.remove(id2);
  dumpState();
  dumpContains();

  Serial.println("Removing id4");
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
  char name[db.maxNameLength()];
  for (int i = 0; i < count; i++) {
    if (db.getId(i, id)) {
      Serial.print(id);
      if (db.getName(i, name)) {
        Serial.print(":");        
        Serial.print(name);
      }
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