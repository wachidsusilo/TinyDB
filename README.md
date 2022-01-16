## TinyDB
An easy to use `FS` wrapper for Arduino, ESP8266, and ESP32. Support any `FS` based storage, i.e. `SPIFFS`, `LittleFS`, and `SD`.

## Examples
This library can be used to store any _Stringable_ data type into `FS` based storage.
### 1. Common Data Type
````c++
#include "SPIFFS.h"
#include "TinyDB.h"

TinyDB db;

void setup() {
    Serial.begin(115200);
    delay(1000);  //make sure Serial has been initialized

    SPIFFS.begin(true);
    db.begin(SPIFFS);

    db.putString("str1", "Hello World");  //Store String value with key "str1"
    String str = db.getString("str1");    //Retrieve String value with key "str1"
    Serial.println("String: " + str);

    db.putInt("int1", 2021);    //Store Int value with key "int1"
    int i = db.getInt("int1");  //Retrieve Int value with key "int1"
    Serial.println("Int: " + i);

    db.putDouble("double1", 3.14);       //Store Double value with key "double1"
    double d = db.getDouble("double1");  //Retrieve Double value with key "double1"
    Serial.println("Double: " + String(d));
}

void loop() {}
````

### 2. Common List
````c++
#include "SPIFFS.h"
#include "TinyDB.h"

TinyDB db;

void setup() {
    Serial.begin(115200);
    delay(1000);  //make sure Serial has been initialized

    SPIFFS.begin(true);
    db.begin(SPIFFS);

    std::vector<String> strList;
    strList.push_back("List 1");
    strList.push_back("List 2");
    strList.push_back("List 3");

    db.putListString("list1", strList);                    //Store list of string with key "list1"
    std::vector<String> list = db.getListString("list1");  //Retrieve list of string with key "list1"

    Serial.println("String List: ");
    for (auto& s : list) {
        Serial.println(s);
    }
}

void loop() {
    // put your main code here, to run repeatedly:
}
````

### 3. Custom Object
````c++
#include "SPIFFS.h"
#include "TinyDB.h"

TinyDB db;

struct Person {
    String name;
    int age;

    Person(String name, int age)
        : name(name), age(age) {}

    //This kind of constructor MUST exist
    //This constructor is used to rebuild object from a String
    Person(String value) {
        std::vector<String> v = TinyDB::split(value, ",");
        if (v.size() >= 2) {
            name = v[0];
            age = v[1].toInt();
        }
    }

    //This method MUST exist
    //Members MUST be separated using a separator, in this case we use comma
    String toString() const {
        return name + "," + age;
    }
};

void setup() {
    Serial.begin(115200);
    delay(1000);  //make sure Serial has been initialized

    SPIFFS.begin(true);
    db.begin(SPIFFS);

    Person p("John Doe", 35);

    db.putObject("obj1", p); //Store custom object with key "obj1"
    Person obj = db.getObject<Person>("obj1"); //Retrieve custom object with key "obj1"

    Serial.println("Person: " + obj.toString());
}

void loop() {}
````