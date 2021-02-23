#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Operator {
   char name;

   bool operator < (const Operator& b) const {
      return name < b.name;
   }

   bool operator > (const Operator& b) const {
      return name > b.name;
   }

   bool operator == (Operator b) {
      return name == b.name;
   }
};

struct Separator {
   char name;

   bool operator < (const Operator& b) const {
      return name < b.name;
   }

   bool operator > (const Operator& b) const {
      return name > b.name;
   }

   bool operator == (Operator b) {
      return name == b.name;
   }
};

struct ReservedWord {
   string name;
   bool operator < (const ReservedWord& b) const {
      return name < b.name;
   }

   bool operator > (const ReservedWord& b) const {
      return name > b.name;
   }

   bool operator == (ReservedWord b) {
      return name == b.name;
   }
};

template<typename T> struct ImmutableTable {
   vector<T> data;

   ImmutableTable(int dataSize) {
      data.resize(dataSize);
   }

   bool getElementById(int id, string &result) {
      
      if (data.size() < id) {
         result = data[id];
         return true;
      }

      return false;
   }

   bool isExist(string dataString) {

      if (find(data.begin(), data.end(), dataString) != data.end()) {
         return true;
      }

      return false;
   }

   bool getIdByElement(string elementName, int &result) {

      if (isExist(dataString)) {
         for (int i = 0; i < data.size(); i++) {
            if (data[i] == elementName) {
               result = i;
               break;
            }
         }
         return true;
      }

      return false;
   }

};

struct Constant {
   string name; 
   int id; 
   string value; 

   bool operator < (const Constant& b) const {
      return name < b.name;
   }

   bool operator > (const Constant& b) const {
      return name > b.name;
   }

   bool operator == (Constant b) {
      return name == b.name;
   }
};

struct Int {
   string name;
   int id;
   string value;
   bool isInit;

   bool operator < (const Int& b) const {
      return name < b.name;
   }

   bool operator > (const Int& b) const {
      return name > b.name;
   }

   bool operator == (Int b) {
      return name == b.name;
   }
};

template<typename T> struct MutableTable {
   vector<T> data;

   bool addElement(string element, bool value) {
      try
      {
         data.push_back(element);
      }
      catch (const exception&)
      {
         cerr << "Ошибка добавления";
         return false; 
      }

      return true;
   }

   bool getElementById(int id, string &result) {
      if (data.size() < id) {
         result = data[id];
         return true;
      }

      return false;
   }

   bool isExist(string dataString) {

      if (find(data.begin(), data.end(), dataString) != data.end()) {
         return true;
      }

      return false;
   }

   bool getIdByElement(string elementName, int& result) {

      if (isExist(dataString)) {
         for (int i = 0; i < data.size(); i++) {
            if (data[i] == elementName) {
               result = i;
               break;
            }
         }
         return true;
      }

      return false;
   }


   bool getIsInitById(int id, string& result) {
      if (data.size() < id) {
         result = isInitWithValue[id];
         return true;
      }

      return false;
   }
     
};

int main()
{
    std::cout << "Hello World!\n";
}
