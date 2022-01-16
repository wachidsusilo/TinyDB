#include "Person.h"
#include "SPIFFS.h"
#include "TinyDB.h"

TinyDB db;

void setup() {
    Serial.begin(115200);
    delay(1000);
    SPIFFS.begin(true);
    db.begin(SPIFFS);

    db.putString("test", "Hello World");
    String str = db.getString("test");
    Serial.println("Result: " + str);

    Person person("Anindia", 26, Person::Female);
    db.putObject("test", person);
    Serial.println(person.toString());

    Person newPerson = db.getObject<Person>("test");
    Serial.println(newPerson.toString());

    db.remove("test");
}

void loop() {}
