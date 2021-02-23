#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct Operator {
   char name;

   Operator() = default;

   Operator(char symbol) : name(symbol){}
   Operator(string symbol) : name(symbol[0]){}

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

   AlphabetUnit() = default;

   AlphabetUnit(char symbol) : name(symbol) {}
   AlphabetUnit(string symbol) : name(symbol[0]) {}


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

   Separator() = default;

   Separator(char symbol) : name(symbol) {}
   Separator(string symbol) : name(symbol[0]) {}

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

   ReservedWord() = default;

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
   int value;

   Constant() = default;

   Constant(string _name, string _value) {
      name = _name;
      value = atoi(_value.c_str());
   }
      
   Constant(string _name, int _value) {
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
   int value;
   bool isInit;

   Int() = default;

   Int(string _name, string _value) {
      name = _name;
      value = atoi(_value.c_str());
      isInit = (value != -858993460) ? true : false;
   }

   Int(string _name, int _value) {
      name = _name;
      value = _value;
      isInit = (value != -858993460) ? true : false;
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

   ImmutableTable(string filename) {
      int size;
      T elem;
      string buf;
      ifstream fIn(filename);

      fIn >> size;
      data.resize(size);

      for (int i = 0; i < size; i++) {
         fIn >> buf;
         elem = T(buf);
         data[i] = elem;
      }
      
      fIn.close();
   }

   bool getElementById(int id, T &result) {
      
      if (data.size() > id) {
         result = data[id];
         return true;
      }

      return false;
   }

   bool isExist(T element) {

      if (find(data.begin(), data.end(), element) != data.end()) {
         return true;
      }

      return false;
   }

   bool getIdByElement(T element, int &result) {

      if (isExist(element)) {
         for (int i = 0; i < data.size(); i++) {
            if (data[i] == element) {
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

   MutableTable(string filename) {
      int size;
      string name, value;
      T elem;
      ifstream fIn(filename);

      fIn >> size;

      for (int i = 0; i < size; i++) {
         fIn >> name >> value;
         elem = T(name, value);
         data.push_back(elem);
      }

      fIn.close();
   }

   bool addElement(T element) {
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

   bool getElementById(int id, T &result) {
      if (data.size() > id) {
         result = data[id];
         return true;
      }

      return false;
   }

   bool isExist(T element) {

      if (find(data.begin(), data.end(), element) != data.end()) {
         return true;
      }

      return false;
   }

   bool getIdByElement(T element, int& result) {

      if (isExist(element)) {
         for (int i = 0; i < data.size(); i++) {
            if (data[i] == element) {
               result = i;
               break;
            }
         }
         return true;
      }

      return false;
   }
     
};

int main()
{
   //ImmutableTable<Operator> operatorTable = ImmutableTable<Operator>("Operators.txt");
   //ImmutableTable<AlphabetUnit> alphabetTable = ImmutableTable<AlphabetUnit>("AlphabetUnit.txt");
   ImmutableTable<Separator> separatorTable = ImmutableTable<Separator>("Separators.txt");
   ImmutableTable<ReservedWord> wordsTable = ImmutableTable<ReservedWord>("ReservedWords.txt");
   //MutableTable<Int> intTable = MutableTable<Int>("Int.txt");
   MutableTable<Constant> constTable = MutableTable<Constant>("Constant.txt");

   string name = "asdasdas";
   Constant c = Constant(name, "4");
   Constant b = Constant(name, 4);
   constTable.addElement(c);
   constTable.addElement(b);
   constTable.getElementById(1, c);
   int A;
   constTable.getIdByElement(c, A);
   
}
