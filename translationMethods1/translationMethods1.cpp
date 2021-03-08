#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include <sstream>

using namespace std;

class Operator {
   public:
      char getName() {
         return name;
      }
      
      Operator() = default;

      Operator(char symbol) : name(symbol) {} 
      Operator(string symbol) : name(symbol[0]) {}

      bool operator < (Operator & b) const {
         return name < b.getName();
      }

      bool operator > (Operator & b) const {
         return name > b.getName();
      }

      bool operator == (Operator b) {
         return name == b.getName();
      }

   private: 
      char name;
};

class AlphabetUnit {
   public:
      char getName() {
         return name;
      }
      
      AlphabetUnit() = default;

      AlphabetUnit(char symbol) : name(symbol) {}
      AlphabetUnit(string symbol) : name(symbol[0]) {}


      bool operator < (AlphabetUnit & b) const {
         return name < b.getName();
      }

      bool operator > (AlphabetUnit & b) const {
         return name > b.getName();
      }

      bool operator == (AlphabetUnit b) {
         return name == b.getName();
      }

   private: 
      char name;
};

class Separator {
   public:
      char getName() {
         return name;
      }

      Separator() = default;

      Separator(char symbol) : name(symbol) {}
      Separator(string symbol) : name(symbol[0]) {}

      bool operator < (Separator & b) const {
         return name < b.getName();
      }

      bool operator > (Separator & b) const {
         return name > b.getName();
      }

      bool operator == (Separator b) {
         return name == b.getName();
      }

   private:
      char name;
};

class ReservedWord {
   public:
      string getName() {
         return name;
      }

      ReservedWord() = default;

      ReservedWord(char _name) {
         name = _name;
      }
      ReservedWord(string _name) {
         name = _name;
      }

      bool operator < (ReservedWord & b) const {
         return name < b.getName();
      }

      bool operator > (ReservedWord & b) const {
         return name > b.getName();
      }

      bool operator == (ReservedWord b) {
         return name == b.getName();
      }

   private:
      string name;
};

class Constant {
   public:
      string getName() {
         return name;
      }

      int getValue() {
         return value;
      }

      Constant() = default;

      Constant(string _name, string _value) {
         name = _name;
         value = atoi(_value.c_str());
      }

      Constant(string _name, int _value) {
         name = _name;
         value = _value;
      }

      Constant(string _name) {
         name = _name;
         value = INT_MIN;
      }

      bool operator < (Constant& b) const {
         return name < b.getName();
      }

      bool operator > (Constant& b) const {
         return name > b.getName();
      }

      bool operator == (Constant b) {
         return name == b.getName() && value == b.getValue();
      }

   private:
      string name;
      int value;
};

class Int {
   public:
      string getName() {
         return name;
      }

      int getValue() {
         return value;
      }

      bool getIsInit() {
         return isInit;
      }

      Int() = default;

      Int(string _name, string _value) {
         name = _name;
         value = atoi(_value.c_str());
         isInit = (value != INT_MIN) ? true : false;
      }

      Int(string _name, int _value) {
         name = _name;
         value = _value;
         isInit = (value != INT_MIN) ? true : false;
      }

      Int(string _name) {
         name = _name;
         value = INT_MIN;
         isInit = false;
      }

      bool operator < (Int& b) const {
         return name < b.getName();
      }

      bool operator > (Int& b) const {
         return name > b.getName();
      }

      bool operator == (Int b) {
         return name == b.getName() && value == b.getValue();
      }

   private:
      string name;
      int value;
      bool isInit;
};

template<typename T> class ImmutableTable {

   public:
      ImmutableTable() = default;
     
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

      bool getElementById(int id, T& result) {

         if (data.size() > id) {
            result = data[id];
            return true;
         }

         return false;
      }

      bool isExist(T& element) {

         if (find(data.begin(), data.end(), element) != data.end()) {
            return true;
         }

         return false;
      }

      bool isExist(char name) {

         T templateVar = T(name);

         if (find(data.begin(), data.end(), templateVar) != data.end()) {
            return true;
         }

         return false;
      }

      bool isExist(string name) {

         T templateVar = T(name);

         if (find(data.begin(), data.end(), templateVar) != data.end()) {
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

   private:
      vector<T> data;
};

template<typename T> class MutableTable {

   public:
      MutableTable() = default;

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

      bool getElementById(int id, T& result) {
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

      bool getIdByElement(string name, int value, int& result) {

         T element = T(name, value);

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

   private:
      vector<T> data;
};

class Translator {
   private:
      ImmutableTable<AlphabetUnit> alphabet; 
      ImmutableTable<Operator> operators; 
      ImmutableTable<ReservedWord> words; 
      ImmutableTable<Separator> separators; 
      MutableTable<Int> integers;
      MutableTable<Constant> constants;

      ifstream fIn;
      ofstream fOutToken, fOutError;

      bool analyzeString(string str) {
         trim(str);
         bool isErrorFound = false;
         if (str.size() > 0) {
            char symbol0 = str[0], symbol1 = str[1];
            string str1, str2;
            stringstream stringStream;
            stringStream << symbol0;
            str1 = stringStream.str();

            stringStream << symbol1;

            str2 = stringStream.str();
            int symbol_type = -1;

            if (alphabet.isExist(symbol0)) {
               symbol_type = 0;
            }

            if (isdigit(symbol0) || symbol0 == '-') {
               symbol_type = 1;
            }

            if (operators.isExist(str1) || operators.isExist(str2)) {
               symbol_type = 2;
            }

            if (separators.isExist(symbol0)) {
               symbol_type = 3;
            }

            switch (symbol_type) {
               case 0: {
                  string name = str;
                  int i;
                  bool isFound = false;

                  for (i = 1; i < name.size() && !isFound; i++) {
                     isFound = !(alphabet.isExist(str[i]) || alphabet.isExist(str[i]));
                  }

                  if (isFound) {
                     name.erase(i - 1);
                     str.erase(0, i - 1);
                  }
                  else {
                     str.erase(0);
                  }

                  trim(name);
                  trim(str);

                  if (words.isExist(name)) {
                     if (words.getIdByElement(name, i)) {
                        fOutToken << 3 << '\t' << i << '\t' << -1 << endl;
                     }
                  }
                  else {
                     integers.addElement(name);
                     int tableId, chain;
                     integers.getIdByElement(name, tableId, chain);
                     fOutToken << 5 << '\t' << tableId << '\t' << chain << endl;
                  }

                  return analyzeString(str);
               }
               break;
               case 1: {
                  string constant = str;
                  int i;
                  bool isFound = false;
                  string str0, str1;
                  stringstream str_stream_t;

                  for (i = 1; i < constant.size() && !isFound; i++) {
                     isFound = !(alphabet.isExist(str[i]) || str[i] == '.' || str[i] == ' ');
                  }
                
                  str_stream_t << str[i - 1];
                  str0 = str_stream_t.str();
                  str_stream_t << str[i];
                  str1 = str_stream_t.str();

                  if (!operators.isExist(str0) && !operators.isExist(str1) && !separators.isExist(str[i - 1])) {
                     fOutError << "Error: incorrect constant" << endl;
                     cout << "Error: incorrect constant" << endl;
                     return false;
                  }

                  if (isFound) {
                     constant.erase(i - 1);
                     str.erase(0, i - 1);
                  }
                  else {
                     str.erase(0);
                  }

                  trim(constant);
                  trim(str);

                  if (constant.find_last_of('.') - constant.find_first_of('.') != 0) {
                     fOutError << "Error: incorrect constant" << endl;
                     cout << "Error: incorrect constant" << endl;
                     return false;
                  }
                  else {
                     constants.addElement(constant);
                     int tableId, chain;
                     integers.getIdByElement(constant, tableId, chain);
                     fOutToken << 6 << '\t'  << tableId << '\t' << chain << '\t' << endl;
                  }

                  return analyzeString(str);
               }
               break;
               case 2: {

                  int tableId;

                  if (operators.isExist(str2)) {
                     operators.getIdByElement(str2, tableId);
                     fOutToken << 4 << '\t' << tableId << '\t' << -1 << endl;
                     str.erase(0, 2);
                     trim(str);
                     return analyzeString(str);
                  }

                  if (operators.isExist(str1)) {
                     operators.getIdByElement(str1, tableId);
                     fOutToken << 4 << '\t' << tableId << '\t' << -1 << endl;
                     str.erase(0, 1);
                     trim(str);
                     return analyzeString(str);
                  }
               }
               break;
               case 3: {
                  int tableId;
                  separators.getIdByElement((const char)str[0], tableId);
                  fOutToken << 4 << '\t' << tableId << '\t' << -1 << endl;
                  str.erase(0, 1);
                  trim(str);
                  return analyzeString(str);
               }
               break;
               default: {
                  fOutError << "Error: can`t determine symbol \"" << str1 << "\"" << endl;
                  cout << "Error: can`t determine symbol \"" << str1 << "\"" << endl;
                  return false;
               }
               break;
               }
         }
         return !isErrorFound;
      }

      bool decommentString(string& str, bool is_changed) {
         if (str.size() > 0) {
            bool isChanged = false;
            size_t commentIndex = str.find("//"), commentIndex1 = str.find("/*"), commentIndex2;

            if (commentIndex != string::npos && commentIndex < commentIndex1) {
               str.erase(commentIndex);
               isChanged = true;
            }

            commentIndex1 = str.find("/*");
            commentIndex2 = str.find("*/");

            if (commentIndex2 < commentIndex1) {
               fOutError << "Error: incorrect comment" << endl;
               cout << "Error: incorrect comment" << endl;
               return false;

            }

            while (commentIndex1 != string::npos && commentIndex2 != string::npos) {
               string tmpstr = str;
               str.erase(commentIndex1);
               tmpstr.erase(0, commentIndex2 + 2);
               str += tmpstr;
               commentIndex1 = str.find("/*");
               commentIndex2 = str.find("*/");
               isChanged = true;
            }

            commentIndex1 = str.find("/*");
            commentIndex2 = str.find("*/");

            if (commentIndex1 != string::npos && commentIndex2 == string::npos) {
               str.erase(commentIndex1);
               string tmpstr;
               if (!fIn.eof()) {
                  getline(fIn, tmpstr);
                  stringIncement++;

               }
               else {
                  fOutError << "Error: incorrect comment" << endl;
                  cout << "Error: incorrect comment" << endl;
                  return false;
               }

               while (tmpstr.find("*/") == string::npos) {
                  if (!fIn.eof()) {
                     getline(fIn, tmpstr);
                     stringIncement++;

                  }
                  else {
                     fOutError << "Error: incorrect comment" << endl;
                     cout << "Error: incorrect comment" << endl;
                     return false;

                  }
               }

               commentIndex2 = tmpstr.find("*/");
               tmpstr.erase(0, commentIndex2 + 2);
               str += " " + tmpstr;
               isChanged = true;
            }

            commentIndex1 = str.find("/*");
            commentIndex2 = str.find("*/");

            if (commentIndex1 != string::npos && commentIndex2 == string::npos ||
               commentIndex1 == string::npos && commentIndex2 != string::npos)  {
               fOutError << "Error: incorrect comment" << endl;
               cout << "Error: incorrect comment" << endl;
               return false;
            }

            if (is_changed) {
               return decommentString(str, isChanged);
            }

         }
         return true;
      }

      int stringNumber, stringIncement;

      static inline void trim(string& out_)
      {
         int notwhite = out_.find_first_not_of(" \t\n");
         out_.erase(0, notwhite);
         int notwhite = out_.find_last_not_of(" \t\n");
         out_.erase(notwhite + 1);
      }

   public:
      Translator() {
         alphabet = ImmutableTable<AlphabetUnit>("files/table_letters.txt");
         operators = ImmutableTable<Operator>("files/table_letters.txt");
         words = ImmutableTable<ReservedWord>("files/table_letters.txt");
         separators = ImmutableTable<Separator>("files/table_letters.txt");
         integers = MutableTable<Int>("files/table_letters.txt");
         constants = MutableTable<Constant>("files/table_letters.txt");
      }

      bool scanFile(string sourceFile, string tokenFile, string errorFile) {
         bool isErrorFound = false;
         string str;

         fIn.open(sourceFile.c_str(), ios::in);
         fOutToken.open(tokenFile.c_str(), ios::out);
         fOutError.open(errorFile.c_str(), ios::out);
         stringNumber = 1;

         while (!fIn.eof() && !isErrorFound) {
            getline(fIn, str);

            if (!fIn.eof()) {
               stringIncement = 0;
               string strold = str;
               if (!decommentString(str, true)) {
                  fOutError << "Error in string " << stringNumber << ": " << strold << endl;
                  cout << "Error in string " << stringNumber << ": " << strold << endl;
                  return false;
               }

               stringNumber += stringIncement;
               isErrorFound = !analyzeString(str);

               if (isErrorFound) {
                  fOutError << "Error in string " << stringNumber << ": " << str << endl;
                  cout << "Error in string " << stringNumber << ": " << str << endl;
               }
               stringNumber++;
            }
         }
         fIn.close();
         fOutToken.close();
         fOutError.close();
         return !isErrorFound;
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

   ReservedWord wew = ReservedWord('c');

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
