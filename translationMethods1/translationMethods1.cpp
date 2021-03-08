#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Operator {
   public:
      char getName();

   private: 
      char name;

   Operator() = default;

   Operator(char symbol) : name(symbol){}
   Operator(string symbol) : name(symbol[0]){}

   bool operator < (Operator& b) const {
      return name < b.getName();
   }

   bool operator > (Operator& b) const {
      return name > b.getName();
   }

   bool operator == (Operator b) {
      return name == b.getName();
   }
};

char Operator::getName() {
   return name;
}

class AlphabetUnit {
   public:
      char getName();

   private: 
      char name;

   AlphabetUnit() = default;

   AlphabetUnit(char symbol) : name(symbol) {}
   AlphabetUnit(string symbol) : name(symbol[0]) {}


   bool operator < (AlphabetUnit& b) const {
      return name < b.getName();
   }

   bool operator > (AlphabetUnit& b) const {
      return name > b.getName();
   }

   bool operator == (AlphabetUnit b) {
      return name == b.getName();
   }
};

char AlphabetUnit::getName() {
   return name;
}

class Separator {
   public:
      char getName();

   private:
      char name;

   Separator() = default;

   Separator(char symbol) : name(symbol) {}
   Separator(string symbol) : name(symbol[0]) {}

   bool operator < (Separator& b) const {
      return name < b.getName();
   }

   bool operator > (Separator& b) const {
      return name > b.getName();
   }

   bool operator == (Separator b) {
      return name == b.getName();
   }
};

char Separator::getName() {
   return name;
}

struct ReservedWord {
   public:
      string getName();

   private:
      string name;

   ReservedWord() = default;

   ReservedWord(string _name) {
      name = _name;
   }

   bool operator < (ReservedWord& b) const {
      return name < b.getName();
   }

   bool operator > (ReservedWord& b) const {
      return name > b.getName();
   }

   bool operator == (ReservedWord b) {
      return name == b.getName();
   }
};

string ReservedWord::getName() {
   return name;
}

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
      return name == b.name && value == b.value;
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
      return name == b.name && value == b.value;
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
\ 
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
   //ImmutableTable<Separator> separatorTable = ImmutableTable<Separator>("Separators.txt");

   //ImmutableTable<ReservedWord> wordsTable = ImmutableTable<ReservedWord>("ReservedWords.txt");
   //ReservedWord w;
   //cout << (wordsTable.isExist(w) ? "true" : "false");
   //cout << endl;
   //w = ReservedWord("fasfd");
   //cout << (wordsTable.isExist(w) ? "true" : "false");


   /*ReservedWord w;
   int id = 2;
   if (wordsTable.getElementById(id, w)) cout << id << " " << w.name;
   id = 5;
   if (wordsTable.getElementById(id, w)) cout << id << " " << w.name;
   return 0;*/

   /*ReservedWord w = ReservedWord("void");
   int id;
   if (wordsTable.getIdByElement(w, id)) cout << w.name << " " << id;
   w = ReservedWord("voidsad");
   if (wordsTable.getIdByElement(w, id)) cout << w.name << " " << id;*/


   //MutableTable<Int> intTable = MutableTable<Int>("Int.txt");
   MutableTable<Constant> constTable = MutableTable<Constant>("Constant.txt");

   Constant c = Constant("c", 777);
   constTable.addElement(c);

   //int id = 4;
   //if (constTable.getElementById(id, c)) cout << id << " " << c.name;
   //id = 777;
   //if (constTable.getElementById(id, c)) cout << id << " " << c.name;

   //c = Constant("c", 777);
   //int id;
   //if (constTable.getIdByElement(c, id)) cout << c.name << " " << id;
   //c = Constant("c", 43);
   //if (constTable.getIdByElement(c, id)) cout << c.name << " " << id;

   c = Constant("name1", 1);
   if (constTable.isExist(c)) cout << "true" << endl;
   else cout << "false";
   c = Constant("vasdas", 2);
   if (constTable.isExist(c)) cout << "true";
   else cout << "false";

   return 0;
   //string name = "asdasdas";
   //Constant c = Constant(name, "4");
   //Constant b = Constant(name, 4);
   //constTable.addElement(c);
   //constTable.addElement(b);
   //constTable.getElementById(1, c);
   //int A;
   //constTable.getIdByElement(c, A);
   
}
