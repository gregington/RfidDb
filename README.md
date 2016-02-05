# RfidDb
RfidDb provides a database that contains 32 bit identifiers which can be used
with an RFID reader to control access to a resource. The Ids are stored in
EEPROM and will persist across restarts.

## Creating and initialising RfidDb
An RfidDb must be created with the maximum size of the database and the
EEPROM location at which the database starts.

The size of the database in EEPROM is equal to the maximum number of entries
multiplied by 4, plust two bytes. For example, a database which can hold
a maximum of 16 entries takes 66 bytes (16 * 4 + 2).

The database must be initialised by calling the begin() method prior to use.
This is generally done in the setup method. For example

```c++
RfidDb db = RfidDb(16, 0);

void setup() {
  db.begin();
}
```

## Database Methods
The public methods available on the RfidDb are described below.

### maxSize
Returns the maximum number of identifiers that can be held in the database.

```c++
db.maxSize();
```

### count
Returns the number of identifiers currently in the database.

```c++
db.count();
```

### insert
Inserts a 32 bit identifier into the database. Returns true if the insert
was successful, or the identifier already existed in the database and false
if the identifier could not be inserted due to a full database.

```c++
if (db.insert(10042)) {
  Serial.println("Inserted or already existed");
} else {
  Serial.println("Insert failed");
}
```

### remove
Removes a 32 bit identifier from the database. If the database is empty or
the identifier was not in the database then this method does not alter
the database.

```c++
db.remove(10042);
```

### get
Returns the identifier at the specified zero-based position. The caller must
provide an unsigned 32-bit integer which this function will populate with
the identifier value. The method returns true if the get was successful and
false if the get was unsuccessful due to the postion being out of range.

```c++
uint32_t id;
if (db.get(4, id)) {
  Serial.print("Get successful. id = ");
  Serial.println(id);
} else {
  Serial.println("Get unsuccessful");
}
```

### contains
Returns true if the database contains the given identifier, false otherwise.

```c++
if (db.contains(10042)) {
  Serial.println("In database");
} else {
  Serial.println("Not in database");
}
```