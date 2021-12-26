#ifndef PERSON_H
#define PERSON_H

#include <vector>

#include "Arduino.h"

class Person {
   public:
    enum Gender {
        Male,
        Female,
        Undefined
    };

    Person(String name, int age, Gender gender)
        : name(name), age(age), gender(gender) {}

    Person(std::vector<String> v) {
        if (v.size() >= 3) {
            name = v[0];
            age = v[1].toInt();
            gender = intToGender(v[2].toInt());
        }
    }

    String toString() const {
        return name + "," + age + "," + genderToInt(gender);
    }

   private:
    String name;
    int age;
    Gender gender;

    int genderToInt(Gender gender) const {
        switch (gender) {
            case Male:
                return 0;
            case Female:
                return 1;
            default:
                return 2;
        }
    }

    Gender intToGender(int gender) const {
        switch (gender) {
            case 0:
                return Male;
            case 1:
                return Female;
            default:
                return Undefined;
        }
    }
};

#endif
