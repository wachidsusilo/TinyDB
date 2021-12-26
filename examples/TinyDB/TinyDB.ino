#include "Person.h"
#include "TinyDB.h"
#include "SPIFFS.h"

TinyDB db;

void setup() {
  Serial.begin(115200);
  delay(1000);
  SPIFFS.begin(true);
  db.begin(SPIFFS);

  db.putString("test", "Hello World");
  String str = db.getString("test");
  Serial.println("Result: " + str);

  Person person("Anindia", 26, Person::Male);
  db.putObject("test", person);
  Serial.println(person.toString());

  Person newPerson = db.getObject<Person>("test");
  Serial.println(newPerson.toString());
}

void loop() {
  // put your main code here, to run repeatedly:

}
