#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct Operator {
   char name;

   Operator(char symbol) : name(symbol){}

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

struct AlphabetUnit {
   char name;

   AlphabetUnit(char symbol) : name(symbol) {}

   bool operator < (const AlphabetUnit& b) const {
      return name < b.name;
   }

   bool operator > (const AlphabetUnit& b) const {
      return name > b.name;
   }

   bool operator == (AlphabetUnit b) {
      return name == b.name;
   }
};

struct Separator {
   char name;

   Separator(char symbol) : name(symbol) {}

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

   ReservedWord(string _name) {
      name = _name;
   }

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

struct Constant {
   string name;
   string value;

   Constant(string _name, string _value) {
      name = _name;
      value = _value;
   }

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

   Int(string _name, string _value, bool _isInit) {
      name = _name;
      value = _value;
      isInit = _isInit;
   }

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

template<typename T> struct ImmutableTable {
   vector<T> data;

   ImmutableTable<Operator>(string filename) {
      int size;
      string buf;
      Operator elem;
      ifstream fIn(filename);

      f >> size;
      data.resize(size);

      for (int i = 0; i < size; i++) {
         f >> buf;
         elem = Operator(buf)
         data[i] = elem;
      }
      
      fIn.close();
   }

   ImmutableTable<Separator>(string filename) {
      int size;
      string buf;
      Separator elem;
      ifstream fIn(filename);

      f >> size;
      data.resize(size);

      for (int i = 0; i < size; i++) {
         f >> buf;
         elem = Separator(buf)
         data[i] = elem;
      }

      fIn.close();
   }

   ImmutableTable<ReservedWord>(string filename) {
      int size;
      string buf;
      ReservedWord elem;
      ifstream fIn(filename);

      f >> size;
      data.resize(size);

      for (int i = 0; i < size; i++) {
         f >> buf;
         elem = ReservedWord(buf)
            data[i] = elem;
      }

      fIn.close();
   }

   ImmutableTable<AlphabetUnit>(string filename) {
      int size;
      string buf;
      AlphabetUnit elem;
      ifstream fIn(filename);

      f >> size;
      data.resize(size);

      for (int i = 0; i < size; i++) {
         f >> buf;
         elem = AlphabetUnit(buf)
            data[i] = elem;
      }

      fIn.close();
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

template<typename T> struct MutableTable {
   vector<T> data;

   MutableTable<Constant>(string filename) {
      int size;
      string name, value;
      Constant elem;
      ifstream fIn(filename);

      f >> size;

      for (int i = 0; i < size; i++) {
         f >> name >> value;
         elem = Constant(name, value)
            data.push_back(elem)
      }

      fIn.close();
   }

   MutableTable<Int>(string filename) {
      int size;
      string name, value;
      bool isInit;
      Int elem;
      ifstream fIn(filename);

      f >> size;

      for (int i = 0; i < size; i++) {
         f >> name >> value >> isInit;
         elem = Int(name, value)
            data.push_back(elem)
      }

      fIn.close();
   }

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
   ImmutableTable<Operator> operatorTable = ImmutableTable<Operator>("Operators.txt");
   ImmutableTable<AlphabetUnit> alphabetTable = ImmutableTable<AlphabetUnit>("AlphabetUnit.txt");
   ImmutableTable<Separator> separatorTable = ImmutableTable<Separator>("Separator.txt");
   ImmutableTable<ReservedWord> wordsTable = ImmutableTable<ReservedWord>("ReservedWord.txt");

   

}
