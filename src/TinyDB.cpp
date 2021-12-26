#include "TinyDB.h"

void TinyDB::begin(FS &fs) {
  this->fs = &fs;
}

bool TinyDB::contains(const String &key, const String &ext) {
  File file = fs->open(validate(key, ext).c_str(), FILE_READ);
  if (file && !file.isDirectory()) {
    file.close();
    return true;
  }
  return false;
}

bool TinyDB::remove(const String &key, const String &ext) {
  return fs->remove(validate(key, ext).c_str());
}

std::vector<String> TinyDB::listFile(const String &ext) {
  std::vector<String> v;
  String type(ext);
  type.toLowerCase();
  File root = fs->open("/", FILE_READ);
  root.rewindDirectory();
  File entry = root.openNextFile();
  while (entry) {
    String str(entry.name());
    str.toLowerCase();
    str.replace("/", "");
    if (type.equals("*")) {
      v.push_back(str);
    } else {
      if (str.indexOf("." + type) == str.length() - (type.length() + 1)) {
        if (str.indexOf("." + type) > 0) v.push_back(str);
      }
    }
    entry.close();
    entry = root.openNextFile();
  }
  root.close();
  return v;
}


/*--- Setter Method ---*/
bool TinyDB::putString(const String &key, const String &content, const String &ext) {
  return write(key, content, ext);
}

bool TinyDB::putInt(const String &key, const int &content, const String &ext) {
  return write(key, String(content), ext);
}

bool TinyDB::putFloat(const String &key, const float &content, const String &ext) {
  return write(key, doubleToString(content), ext);
}

bool TinyDB::putDouble(const String &key, const double &content, const String &ext) {
  return write(key, doubleToString(content), ext);
}

bool TinyDB::putBoolean(const String &key, const boolean &content, const String &ext) {
  return write(key, String(content), ext);
}

bool TinyDB::putListString(const String &key, const std::vector<String> &content, const String &ext) {
  if (!isWritable(key, ext)) {
    return false;
  }
  File file = fs->open(validate(key, ext).c_str(), FILE_APPEND);
  if (!file || file.isDirectory()) {
    return false;
  }
  for (int i = 0; i < content.size(); i++) {
    int res = file.println(content[i]);
    if (!res) {
      file.close();
      return false;
    }
  }
  file.close();
  return true;
}

bool TinyDB::putListInt(const String &key, const std::vector<int> &content, const String &ext) {
  if (!isWritable(key, ext)) {
    return false;
  }
  File file = fs->open(validate(key, ext).c_str(), FILE_APPEND);
  if (!file || file.isDirectory()) {
    return false;
  }
  for (int i = 0; i < content.size(); i++) {
    int res = file.println(String(content[i]));
    if (!res) {
      file.close();
      return false;
    }
  }
  file.close();
  return true;
}

bool TinyDB::putListFloat(const String &key, const std::vector<float> &content, const String &ext) {
  if (!isWritable(key, ext)) {
    return false;
  }
  File file = fs->open(validate(key, ext).c_str(), FILE_APPEND);
  if (!file || file.isDirectory()) {
    return false;
  }
  for (int i = 0; i < content.size(); i++) {
    int res = file.println(doubleToString(content[i]));
    if (!res) {
      file.close();
      return false;
    }
  }
  file.close();
  return true;
}

bool TinyDB::putListDouble(const String &key, const std::vector<double> &content, const String &ext) {
  if (!isWritable(key, ext)) {
    return false;
  }
  File file = fs->open(validate(key, ext).c_str(), FILE_APPEND);
  if (!file || file.isDirectory()) {
    return false;
  }
  for (int i = 0; i < content.size(); i++) {
    int res = file.println(doubleToString(content[i]));
    if (!res) {
      file.close();
      return false;
    }
  }
  file.close();
  return true;
}

bool TinyDB::putListBoolean(const String &key, const std::vector<boolean> &content, const String &ext) {
  if (!isWritable(key, ext)) {
    return false;
  }
  File file = fs->open(validate(key, ext).c_str(), FILE_APPEND);
  if (!file || file.isDirectory()) {
    return false;
  }
  for (int i = 0; i < content.size(); i++) {
    int res = file.println(String(content[i]));
    if (!res) {
      file.close();
      return false;
    }
  }
  file.close();
  return true;
}


/*--- Setter Method ---*/
String TinyDB::getString(const String &key, const String &ext) {
  return read(key, ext);
}

int TinyDB::getInt(const String &key, const String &ext) {
  return read(key, ext).toInt();
}

float TinyDB::getFloat(const String &key, const String &ext) {
  return read(key, ext).toFloat();
}

double TinyDB::getDouble(const String &key, const String &ext) {
  return read(key, ext).toDouble();
}

bool TinyDB::getBoolean(const String &key, const String &ext) {
  return read(key, ext).toInt();
}

std::vector<String> TinyDB::getListString(const String &key, const String &ext) {
  std::vector<String> v;
  File file = fs->open(validate(key, ext).c_str(), FILE_READ);
  String str = file.readStringUntil('\n');
  str.trim();
  while (str.length() > 0) {
    v.push_back(str);
    str = file.readStringUntil('\n');
    str.trim();
  }
  file.close();
  return v;
}

std::vector<int> TinyDB::getListInt(const String &key, const String &ext) {
  std::vector<int> v;
  File file = fs->open(validate(key, ext).c_str(), FILE_READ);
  String str = file.readStringUntil('\n');
  str.trim();
  while (str.length() > 0) {
    v.push_back(str.toInt());
    str = file.readStringUntil('\n');
    str.trim();
  }
  file.close();
  return v;
}

std::vector<float> TinyDB::getListFloat(const String &key, const String &ext) {
  std::vector<float> v;
  File file = fs->open(validate(key, ext).c_str(), FILE_READ);
  String str = file.readStringUntil('\n');
  str.trim();
  while (str.length() > 0) {
    v.push_back(str.toFloat());
    str = file.readStringUntil('\n');
    str.trim();
  }
  file.close();
  return v;
}

std::vector<double> TinyDB::getListDouble(const String &key, const String &ext) {
  std::vector<double> v;
  File file = fs->open(validate(key, ext).c_str(), FILE_READ);
  String str = file.readStringUntil('\n');
  str.trim();
  while (str.length() > 0) {
    v.push_back(str.toDouble());
    str = file.readStringUntil('\n');
    str.trim();
  }
  file.close();
  return v;
}

std::vector<bool> TinyDB::getListBoolean(const String &key, const String &ext) {
  std::vector<bool> v;
  File file = fs->open(validate(key, ext).c_str(), FILE_READ);
  String str = file.readStringUntil('\n');
  str.trim();
  while (str.length() > 0) {
    v.push_back(str.toInt());
    str = file.readStringUntil('\n');
    str.trim();
  }
  file.close();
  return v;
}


/*--- Private Method ---*/
String TinyDB::validate(const String &key, const String &ext) {
  String s(key);
  if (!s.startsWith("/")) {
    s = "/" + s;
    if (s.length() > ext.length() + 1) {
      if (s.indexOf("." + ext) != s.length() - (ext.length() + 1)) {
        s = s + "." + ext;
      }
    } else {
      s = s + "." + ext;
    }
  } else {
    if (s.length() > ext.length() + 1) {
      if (s.indexOf("." + ext) != s.length() - (ext.length() + 1)) {
        s = s + "." + ext;
      }
    } else {
      s = s + "." + ext;
    }
  }
  return s;
}

bool TinyDB::write(const String &key, String content, const String &ext) {
  File file = fs->open(validate(key, ext).c_str(), FILE_WRITE);
  if (!file || file.isDirectory()) {
    return false;
  }
  int res = file.print(content);
  file.close();
  return res;
}

bool TinyDB::append(const String &key, String content, const String &ext) {
  File file = fs->open(validate(key, ext).c_str(), FILE_APPEND);
  if (!file || file.isDirectory()) {
    return false;
  }
  int res = file.print(content);
  file.close();
  return res;
}

String TinyDB::read(const String &key, const String &ext) {
  File file = fs->open(validate(key, ext).c_str(), FILE_READ);
  if (!file || file.isDirectory()) {
    return "";
  }
  String res = file.readString();
  file.close();
  return res;
}

bool TinyDB::isWritable(const String &key, const String &ext) {
  File file = fs->open(validate(key, ext).c_str(), FILE_READ);
  if (file && !file.isDirectory()) {
    file.close();
    return fs->remove(validate(key, ext).c_str());
  }
  return true;
}

String TinyDB::doubleToString(const double &content) {
  char buffer[33];
  memset(buffer, 0, sizeof(buffer));
  snprintf(buffer, sizeof(buffer), "%f", content);
  buffer[32] = 0;
  return String(buffer);
}

std::vector<String> TinyDB::split(const String &content, const String &delimiter) {
  char* cstr = const_cast<char*>(content.c_str());
  char* current;
  std::vector<String> v;
  current = strtok(cstr, delimiter.c_str());
  while (current != NULL) {
    v.push_back(String(current));
    current = strtok(NULL, delimiter.c_str());
  }
  return v;
}
