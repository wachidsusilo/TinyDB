#ifndef TINYDB_H
#define TINYDB_H

#include <vector>

#include "Arduino.h"
#include "FS.h"

#ifndef FILE_WRITE
#define FILE_WRITE "w"
#endif

#ifndef FILE_READ
#define FILE_READ "r"
#endif

#ifndef FILE_APPEND
#define FILE_APPEND "a"
#endif

class TinyDB {
   public:
    TinyDB() {}
    ~TinyDB() {}

    void begin(FS &fs);
    bool contains(const String &key, const String &ext = "txt");
    bool remove(const String &key, const String &ext = "txt");
    std::vector<String> listFile(const String &ext = "*");

    bool putString(const String &key, const String &content, const String &ext = "txt");
    bool putInt(const String &key, const int &content, const String &ext = "txt");
    bool putFloat(const String &key, const float &content, const String &ext = "txt");
    bool putDouble(const String &key, const double &content, const String &ext = "txt");
    bool putBoolean(const String &key, const boolean &content, const String &ext = "txt");

    bool putListString(const String &key, const std::vector<String> &content, const String &ext = "txt");
    bool putListInt(const String &key, const std::vector<int> &content, const String &ext = "txt");
    bool putListFloat(const String &key, const std::vector<float> &content, const String &ext = "txt");
    bool putListDouble(const String &key, const std::vector<double> &content, const String &ext = "txt");
    bool putListBoolean(const String &key, const std::vector<boolean> &content, const String &ext = "txt");

    String getString(const String &key, const String &ext = "txt");
    int getInt(const String &key, const String &ext = "txt");
    float getFloat(const String &key, const String &ext = "txt");
    double getDouble(const String &key, const String &ext = "txt");
    bool getBoolean(const String &key, const String &ext = "txt");

    std::vector<String> getListString(const String &key, const String &ext = "txt");
    std::vector<int> getListInt(const String &key, const String &ext = "txt");
    std::vector<float> getListFloat(const String &key, const String &ext = "txt");
    std::vector<double> getListDouble(const String &key, const String &ext = "txt");
    std::vector<bool> getListBoolean(const String &key, const String &ext = "txt");

    template <typename T>
    bool putObject(const String &key, const T &content, const String &ext = "txt") {
        return write(key, content.toString(), ext);
    }

    template <typename T>
    bool putListObject(const String &key, const std::vector<T> &content, const String &ext = "txt") {
        if (!isWritable(key, ext)) {
            return false;
        }
        File file = fs->open(validate(key, ext).c_str(), FILE_APPEND);
        if (!file || file.isDirectory()) {
            return false;
        }
        for (int i = 0; i < content.size(); i++) {
            int res = file.println(content[i].toString());
            if (!res) {
                file.close();
                return false;
            }
        }
        file.close();
        return true;
    }

    template <typename T>
    T getObject(const String &key, const String &ext = "txt") {
        return T(split(read(key, ext), ","));
    }

    template <typename T>
    std::vector<T> getListObject(const String &key, const String &ext = "txt") {
        std::vector<T> v;
        File file = fs->open(validate(key, ext).c_str(), FILE_READ);
        String str = file.readStringUntil('\n');
        str.trim();
        while (str.length() > 0) {
            v.emplace_back(T(split(str, ",")));
            str = file.readStringUntil('\n');
            str.trim();
        }
        file.close();
        return v;
    }

   private:
    fs::FS *fs;
    String validate(const String &key, const String &ext = "txt");
    bool write(const String &key, String content, const String &ext = "txt");
    bool append(const String &key, String content, const String &ext = "txt");
    String read(const String &key, const String &ext = "txt");
    bool isWritable(const String &key, const String &ext = "txt");
    String doubleToString(const double &content);
    std::vector<String> split(const String &content, const String &delimiter);
};

#endif
