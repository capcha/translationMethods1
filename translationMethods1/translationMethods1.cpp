﻿#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <sstream>
#include <stack>
#include <queue>

using namespace std;

class Operator {
   public:
      string getName() {
         return name;
      }
      
      Operator() = default;

      Operator(string symbol) : name(symbol) {}

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
      string name;
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
      string getValue() {
         return value;
      }

      Constant() = default;

      Constant(string _value) {
         value = _value;
      }

      bool operator < (Constant& b) const {
         return value < b.getValue();
      }

      bool operator > (Constant& b) const {
         return value > b.getValue();
      }

      bool operator == (Constant b) {
         return value == b.getValue();
      }

   private:
      string value;
};

class Int {
   public:
      string getName() {
         return name;
      }
      
      void setIsInit(bool value) {
         isInit = value;
      }

      void setValue(int _value) {
         value = _value;
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

class Token {
   public: 
      int getTableId() {
         return tableId;
      }

      int getRowNumber() {
         return rowNumber;
      }

      int getChainNumber() {
         return chainNumber;
      }

      Token() = default;

      Token(int _tableId, int _rowNumber, int _chainNumber) {
         tableId = _tableId;
         rowNumber = _rowNumber;
         chainNumber = _chainNumber;
      }

   private:
      int tableId;
      int rowNumber;
      int chainNumber; 
};

class StateTableRow {
   public:
      vector<string> getTerminal() {
         return terminal;
      }

      int getJump() {
         return jump;
      }

      bool getAccept() {
         return accept;
      }

      bool getStack() {
         return stack;
      }

      bool getReturnState() {
         return returnState;
      }

      bool getError() {
         return error;
      }

      void setJump(int _jump) {
         jump = _jump;
      }

      void setAccept(int acc) {
         accept = acc;
      }

      void setStack(int _stack) {
         stack = _stack;
      }

      void setReturn(int ret) {
         returnState = ret;
      }

      void setError(int err) {
         error = err;
      }

      void pushTerminal(string str) {
         terminal.push_back(str);
      }

   private:
      vector<string> terminal;
      int jump;
      bool accept;
      bool stack;
      bool returnState;
      bool error;

};

class PostfixElem {
   public:
      string id;
      int type;
      int table;

      PostfixElem()
      {
         id = "", type = 0, table = -1;
      }

      PostfixElem(string id_, int type_, int table_)
      {
         id = id_, type = type_, table = table_;
      }

      PostfixElem(string id_, int type_)
      {
         id = id_, type = type_, table = -1;
      }

      PostfixElem(string id_)
      {
         id = id_, type = 1, table = -1;
      }

      friend bool operator == (const PostfixElem& f, const PostfixElem& l)
      {
         if (f.type == l.type && f.table == l.table && f.id == l.id) return true;
         return false;
      }

      friend ostream& operator << (ostream& ostream_, const PostfixElem& pe_)
      {
         ostream_ << pe_.id;
         return ostream_;
      }
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
         if (isExist(element)) {
              return false;
         }
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
      
      void setElementById(int id, T element) {
         data.at(id) = element;
      }

      int getTableSize() {
         return data.size();
      }

      bool getElementByValue(string value, T& result) {
         for (int i = 0; i < data.size(); i++) {
            if (data[i].getValue() == value) {
               result = data[i];
               return true;
            }
         }

         return false;
      }

      bool getElementByName(string name, T& result) {
         for (int i = 0; i < data.size(); i++) {
            if (data[i].getName() == name) {
               result = data[i];
               return true;
            }
         }

         return false;
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

      bool getIdByElement(string name, int& result) {

         T element = T(name);

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
      ImmutableTable<AlphabetUnit> alphabet; // 1
      ImmutableTable<Operator> operators;    // 2
      ImmutableTable<ReservedWord> words;    // 3
      ImmutableTable<Separator> separators;  // 4
      MutableTable<Int> integers;            // 5
      MutableTable<Constant> constants;      // 6

      ifstream fIn, fInToken;
      ofstream fOutToken, fOutError;

      int m = 1; // метка

      vector<StateTableRow> newTable; 
      stack<int> parseStack; 

      struct TreeElement {
         TreeElement *left, *right; 

         TreeElement() {	
            left = 0;
            right = 0;
         }

         int type; //0 - знак операции(или присваивания)
                  //1 - переменная

         string id; 
      };

      TreeElement *treeRoot; 
      TreeElement *currentNode;

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
            int symbolType = -1;

            if (alphabet.isExist(symbol0)) {
               symbolType = 0;
            }

            if (isdigit(symbol0) || symbol0 == '-') {
               symbolType = 1;
            }

            if (operators.isExist(str1) || operators.isExist(str2)) {
               symbolType = 2;
            }

            if (separators.isExist(symbol0)) {
               symbolType = 3;
            }

            switch (symbolType) {
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
                     Int newInt = Int(name);
                     integers.addElement(newInt);
                     int tableId;
                     integers.getIdByElement(newInt, tableId);
                     fOutToken << 5 << '\t' << tableId << '\t' << newInt.getIsInit() << endl;
                  }

                  return analyzeString(str);
               }
               break;
               case 1: {
                  string constant = str;
                  int i;
                  bool isFound = false;
                  string str0, str1;
                  stringstream sStream;

                  for (i = 1; i < constant.size() && !isFound; i++) {
                     isFound = !(alphabet.isExist(str[i]) || str[i] == '.' || str[i] == ' ');
                  }
                
                  sStream << str[i - 1];
                  str0 = sStream.str();
                  sStream << str[i];
                  str1 = sStream.str();

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

                  if (constant.find_last_of('.') != string::npos) {
                     fOutError << "Error: incorrect constant" << endl;
                     cout << "Error: incorrect constant" << endl;
                     return false;
                  }
                  else {
                     Constant newConst = Constant(constant);
                     constants.addElement(constant);
                     int tableId;
                     constants.getIdByElement(newConst, tableId);
                     fOutToken << 6 << '\t'  << tableId << '\t' << 0 << '\t' << endl;
                  }

                  return analyzeString(str);
               }
               break;
               case 2: {

                  int tableId;

                  if (operators.isExist(str2)) {
                     operators.getIdByElement(str2, tableId);
                     fOutToken << 2 << '\t' << tableId << '\t' << -1 << endl;
                     str.erase(0, 2);
                     trim(str);
                     return analyzeString(str);
                  }

                  if (operators.isExist(str1)) {
                     operators.getIdByElement(str1, tableId);
                     fOutToken << 2 << '\t' << tableId << '\t' << -1 << endl;
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

      bool decommentString(string& str, bool isChanged) {
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

            if (isChanged) {
               return decommentString(str, isChanged);
            }

         }
         return true;
      }

      void buildTree(vector<Token> code) {

         TreeElement* little_tree_beg = new TreeElement;

         if (code.size() > 2) {
            //code.pop_back();

            buildSubTree(code, little_tree_beg);

            if (treeRoot == 0) {
               treeRoot = little_tree_beg;
               currentNode = treeRoot;
            }
            else {
               currentNode->right = little_tree_beg; 
            }

            while (currentNode->right != 0) { 
               currentNode = currentNode->right;
            };

         }
      }

      void buildSubTree(vector<Token> code, TreeElement*& beg) {
         vector<Token> L, R; 

         int bracket_num = 0;
         int L_num = 0;

         bool flag = false;

         if (code.size() == 1 && (getValue(code[0]) == ";" || getValue(code[0]) == ",")) {
            beg->id = ";";
            beg->type = 2;
         }
         else {

            vector<int> opers_n; 

            for (int i = 0; i < code.size(); i++) {
               if (getValue(code[i]) == "(") bracket_num++;
               if (getValue(code[i]) == ")") bracket_num--;
               if (code[i].getTableId() == 2 && bracket_num == 0) opers_n.push_back(i);
            }

            if (opers_n.size() == 0) { 
               flag = false;
            }
            else { 
               int low_num = -1; 
               for (int j = 0; j < opers_n.size() && low_num == -1; j++)
                  if (getValue(code[opers_n[j]]) == "=" || getValue(code[opers_n[j]]) == "+=" || getValue(code[opers_n[j]]) == "-=" || getValue(code[opers_n[j]]) == "*=")
                     low_num = opers_n[j];
               //Потом на + и -
               for (int j = opers_n.size() - 1; j >= 0 && low_num == -1; j--) {
                  if (getValue(code[opers_n[j]]) == "+" || getValue(code[opers_n[j]]) == "-") {
                     low_num = opers_n[j];
                  }
               }

               if (low_num == -1)
                  low_num = opers_n[opers_n.size() - 1];

               if (getValue(code[0]) == "(") L_num++;

               for (int j = 0; L_num < low_num; L_num++, j++)
                  L.push_back(code[L_num]);

               int R_num = 0;
               int l;
               if (getValue(code[low_num + 1]) == "(") R_num++;
               for (l = 0, R_num = low_num + 1 + R_num; R_num < code.size(); R_num++, l++)
                  R.push_back(code[R_num]);

               beg->left = new TreeElement;
               beg->right = new TreeElement;

               beg->id = getValue(code[low_num]);
               beg->type = 0;

               buildSubTree(L, beg->left);
               buildSubTree(R, beg->right);
               flag = true;
            }

            if (!flag) {
               int k = 0;
               while (getValue(code[k]) == "(") k++;
               beg->id = getValue(code[k]);
               beg->type = 1;

               if (code.size() > k + 1) {
                  beg->right = new TreeElement;
                  beg->right->id = ";";
                  beg->right->type = 2;
               }

            }
         }

      }

      int stringNumber, stringIncement;

      static inline void trim(string& out_)
      {
         int notwhite = out_.find_first_not_of(" \t\n");
         out_.erase(0, notwhite);
         notwhite = out_.find_last_not_of(" \t\n");
         out_.erase(notwhite + 1);
      }

      string getValue(Token& Token) {
         switch (Token.getTableId())
         {
         case 2: {
            Operator oper;
            operators.getElementById(Token.getRowNumber(), oper);
            return oper.getName();
         }
         case 3: {
            ReservedWord reservedWord;
            words.getElementById(Token.getRowNumber(), reservedWord);
            return reservedWord.getName();
         }
         case 4: {
            Separator separator;
            separators.getElementById(Token.getRowNumber(), separator);
            return string(1, separator.getName());
         }
         case 5: {
            Int integer;
            integers.getElementById(Token.getRowNumber(), integer);
            return integer.getName();
         }
         case 6: {
            Constant constant;
            constants.getElementById(Token.getRowNumber(), constant);
            return constant.getValue();
         }
         default:
            return "";
         }
      }

   public:
      vector<PostfixElem> PostfixVector;
      bool parseA = false, parseB = false, parseC = false, Aparsed = false, Bparsed = false;

      Translator() {
         alphabet = ImmutableTable<AlphabetUnit>("Alphabet.txt"); //1
         operators = ImmutableTable<Operator>("Operators.txt");//2
         words = ImmutableTable<ReservedWord>("ReservedWords.txt");//3
         separators = ImmutableTable<Separator>("Separators.txt");//4
         integers = MutableTable<Int>();//5
         constants = MutableTable<Constant>();//6

         ifstream fInStateTable("newTable.txt");

         while (!fInStateTable.eof()) {
            StateTableRow stateTableRow; 
            string inputString;

            fInStateTable >> inputString;

            while (inputString != "|") {
               stateTableRow.pushTerminal(inputString);
               fInStateTable >> inputString;
            };

            int jump, accept, returnState, stack, error; 

            fInStateTable >> jump >> accept >> stack >> returnState >> error;

            stateTableRow.setJump(jump - 1);
            stateTableRow.setAccept(accept);
            stateTableRow.setStack(stack);
            stateTableRow.setReturn(returnState);
            stateTableRow.setError(error);
               
            newTable.push_back(stateTableRow);
         };

      }

      bool lexicalAnalysis(string sourceFile, string tokenFile, string errorFile) {
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
         fOutToken << 4 << '\t' << 3 << '\t' << -1 << endl;

         fIn.close();
         fOutToken.close();
         fOutError.close();
         return !isErrorFound;
      }
   
      bool bracketAnalysis(string tokenFile, string errorFile, string newTokenFile) {
         ofstream fOutToken;
         fInToken.open(tokenFile.c_str(), ios::in);
         fOutError.open(errorFile.c_str(), ios::out);
         fOutToken.open(newTokenFile.c_str(), ios::out);
         Token currentToken;
         stack<string> bracketStack;
         deque<Token> tokenDeque;

         int tableId, rowId, chainId;

         streampos oldPointer = fInToken.tellg(), newPointer;

         bool errorFlag = false;    // Флаг конца файла (чтобы считать последний токен)

         string buf, bracket;         

         while (getline(fInToken, buf, '\t') && !errorFlag) {
            tableId = stoi(buf);
            getline(fInToken, buf, '\t');
            rowId = stoi(buf);
            getline(fInToken, buf, '\n');
            chainId = stoi(buf);

            currentToken = Token(tableId, rowId, chainId);

            string tokenValue = getValue(currentToken);
            trim(tokenValue);
         
            if (tokenValue == "{" || tokenValue == "(") {
               if (!bracketStack.empty()) {
                  bracket = bracketStack.top();
                  if (bracket == "(" && tokenValue == "{") {
                     fOutError << "Bracket Error: MISMATCH in " << tokenValue << endl;
                     cerr << "Bracket Error: MISMATCH in " << tokenValue << endl;
                     bracketStack.pop();
                     tokenDeque.push_back(Token(4, 1, -1));
                  }
               }
               bracketStack.push(tokenValue);
            }

            if (tokenValue == "}" || tokenValue == ")") {
               if (!bracketStack.empty()) {
                  bracket = bracketStack.top();
                  if (bracket == "{" && tokenValue == "}" || bracket == "(" && tokenValue == ")") {
                     bracketStack.pop();
                  }
                  else {
                     fOutError << "Bracket Error: MISMATCH in "  << tokenValue << endl;
                     cerr << "Bracket Error: MISMATCH in "  << tokenValue << endl;
                     if (bracket == "(" && tokenValue == "}") {
                        bracketStack.pop();
                        if (tokenDeque.back().getRowNumber() == 5) {
                           tokenDeque.pop_back();
                           tokenDeque.push_back(Token(4, 1, -1));
                           tokenDeque.push_back(Token(4, 5, -1));
                        }
                     }
                  }
               }
               else {
                  errorFlag = true;
                  fOutError << "Bracket Error: MISMATCH in " << tokenValue << " stack is empty" << endl;
                  cerr << "Bracket Error: MISMATCH in " << tokenValue << " stack is empty" << endl;
               }
            } 
            if (!(bracket == "{" && tokenValue == ")")) {
               tokenDeque.push_back(currentToken);
            }
         }

         if (!bracketStack.empty() && !errorFlag) {
            errorFlag = true;
            string value = bracketStack.top();
            fOutError << "Bracket Error: MISMATCH stack is not empty " << value << endl;
            cerr << "Bracket Error: MISMATCH stack is not empty " << value << endl;
            tokenDeque.push_back(Token(4, 3, -1));
         }

         Token tok;

         while (!tokenDeque.empty()) {
            tok = tokenDeque.front();
            tokenDeque.pop_front();
            fOutToken << tok.getTableId() << "\t" << tok.getRowNumber() << "\t" << tok.getChainNumber() << endl;
         }

         fOutError.close();
         fOutToken.close();
         fInToken.close();

         return errorFlag;
      }
   
      // Синтаксический анализатор
      bool syntaxAnalysis(string tokenFile, string errorFile) {
         string str;
         fInToken.open(tokenFile.c_str(), ios::in);
         fOutError.open(errorFile.c_str(), ios::out);
         Token currentToken, nextToken;
         stack<int> parseStack;
         bool errorFlag = false;
         int currentRow = 0;
         bool isInt = false; // Находимся ли мы в строке с объявлением типа
         int type_type = 0;      // Если находимся, то какой тип объявляем
         bool need_postfix = false;      // Нужно ли выполнять построение постфиксной записи для данной строки
         vector<Token> exprVector;  // Если да, то сюда помещаем токены в инфиксном (обычном) порядке
         bool eof_flag = fInToken.eof();    // Флаг конца файла (чтобы считать последний токен)

         int tableId, rowId, chainId;

         fInToken >> tableId;
         fInToken >> rowId;
         fInToken >> chainId;

         currentToken = Token(tableId, rowId, chainId);

         fInToken >> tableId;
         fInToken >> rowId;
         fInToken >> chainId;
         nextToken = Token(tableId, rowId, chainId);
         while (!eof_flag && !errorFlag)
         {
            string tokenValue = getValue(currentToken);
            trim(tokenValue);

            if (currentToken.getTableId() == 5 || currentToken.getTableId() == 6) tokenValue = "ID";

            // Ищем терминалы из списка
            bool find_terminal = false;

            for (int i = 0; i < (int)newTable[currentRow].getTerminal().size() && !find_terminal; i++)
            {
               if (newTable[currentRow].getTerminal()[i] == tokenValue)
                  find_terminal = true;
            }

            // Если нашли
            if (find_terminal) {

               if (newTable[currentRow].getStack())
                  parseStack.push(currentRow + 1);

               if (newTable[currentRow].getAccept())
               {
                  if (tokenValue == "ID" &&
                     (getValue(nextToken) == "=" ||
                        getValue(nextToken) == "+=" ||
                        getValue(nextToken) == "-=" ||
                        getValue(nextToken) == "*=" && !isInt))
                     need_postfix = true;


                  if (tokenValue == "if") {
                     parseA = true;
                     need_postfix = true;
                  }

                  if (parseA && Aparsed) {
                     parseB = true;
                     need_postfix = true;
                  }

                  if (parseB && parseA && Bparsed) {
                     parseB = true;
                     need_postfix = true;
                  }

                  if (tokenValue == "else") {
                     PostfixVector.pop_back();
                     PostfixVector.pop_back();
                     PostfixVector.push_back(PostfixElem("m" + to_string(m - 1)));
                     PostfixVector.push_back(PostfixElem("BP"));
                     PostfixVector.push_back(PostfixElem("m" + to_string(m - 2) + ":"));
                     parseC = true;
                     need_postfix = true;
                  }
                  
                  if (need_postfix) {
                     exprVector.push_back(currentToken);
                  }

                  // Если закончили разбор присваивания или части объявления
                  if (tokenValue == ";" || tokenValue == "," || (parseA && tokenValue == "{"))
                  {
                     // Добавим все, что разобрали, в постфиксную запись
                     if (!postfixExpr(exprVector))
                        errorFlag = true;
                     
                     // Сбрасываем все флаги
                     exprVector.clear();
                     need_postfix = false;
                  }

                  // Если закончили разбор объявления, сбросим флаг объявления
                  if (tokenValue == ";") {
                     isInt = false;
                  }

                  // Если попался тип, запоминаем его
                  if (tokenValue == "int") {
                     isInt = true;
                  }

                  if (tokenValue == "}" && Aparsed) {
                     PostfixVector.push_back(PostfixElem("m" + to_string(m - 1) + ":"));
                     m++;
                     PostfixVector.push_back(PostfixElem(";", 4));
                  }

                  if (tokenValue == "}" && Bparsed) {
                     PostfixVector.push_back(PostfixElem("m" + to_string(m - 1) + ":"));
                     m++;
                     PostfixVector.push_back(PostfixElem(";", 4));
                  }

                  // Заносим тип в таблицу идентификаторов
                  if (tokenValue == "ID" && isInt)
                  {
                     Int buffer;
                     integers.getElementById(currentToken.getRowNumber(), buffer);
                     buffer.setIsInit(true);

                     integers.setElementById(currentToken.getRowNumber(), buffer);
                  } else // Обработка необъявленного типа
                     if (tokenValue == "ID" && !isInt)
                     {
                        Int buffer;
                        integers.getElementById(currentToken.getRowNumber(), buffer);
                        if (buffer.getIsInit() == 0)
                        {
                           errorFlag = true;
                           fOutError << "Syntax Error: Undefined identifier \"" << buffer.getName() << "\"" << endl;
                           cerr << "Syntax Error: Undefined identifier \"" << buffer.getName() << "\"" << endl;
                        }
                     }

                  eof_flag = fInToken.eof();
                  currentToken = nextToken;
                  if (!eof_flag) {
                     fInToken >> tableId;
                     fInToken >> rowId;
                     fInToken >> chainId;
                     nextToken = Token(tableId, rowId, chainId);
                  }
               }

               if (newTable[currentRow].getReturnState())
               {
                  if (!parseStack.empty())
                  {
                     currentRow = parseStack.top();
                     parseStack.pop();
                  }
                  else // Если внезапно стек пуст
                  {
                     errorFlag = true;
                     cerr << "Syntax Error: Parse stack is empty!" << endl;
                     cerr << "Return requested by row " << currentRow 
                        << " (value = \"" << getValue(currentToken) << "\")" << endl;
                     fOutError << "Syntax Error: Parse stack is empty!" << endl;
                     fOutError << "Return requested by row " << currentRow 
                        << " (value = \"" << getValue(currentToken) << "\")" << endl;
                  }
               }
               else {
                  currentRow = newTable[currentRow].getJump();
               }
            }
            else
            {
               // Если ошибка безальтернативная
               if (newTable[currentRow].getError())
               {
                  errorFlag = true;
                  fOutError << "Syntax Error: Unexpected terminal \"" << getValue(currentToken) << "\"" << endl;
                  fOutError << "Must be: ";
                  for (int i = 0; i < (int)newTable[currentRow].getTerminal().size(); i++)
                     fOutError << " " << newTable[currentRow].getTerminal()[i] << " ";
                  fOutError << endl;
                  cerr << "Syntax Error: Unexpected terminal \"" << getValue(currentToken) << "\"" << endl;
                  cerr << "Must be: ";
                  for (int i = 0; i < (int)newTable[currentRow].getTerminal().size(); i++)
                     cerr << " " << newTable[currentRow].getTerminal()[i] << " ";
                  cerr << endl;
               }
               else
               {
                  currentRow++;
               }
            }
         };

         fInToken.close();
         fOutError.close();
         return !errorFlag;
      }

      // Построение постфиксной записи
      bool postfixExpr(vector<Token> t)
      {
         vector<PostfixElem> tempVector;
         bool errorFlag = postfixExpr(t, tempVector);
         for (int i = 0; errorFlag && i < (int)tempVector.size(); i++)
            PostfixVector.push_back(tempVector[i]);
         return errorFlag;
      }

      // Построение постфиксной записи (локально)
      bool postfixExpr(vector<Token> t, vector<PostfixElem>& tempVector)
      {
         stack<string> tempStack;
         bool errorFlag = false;
         int index = 0;

         while (index < (int)t.size() && !errorFlag)
         {
            int i;
            for (i = index; i < (int)t.size() && !errorFlag && getValue(t[i]) != ";" && getValue(t[i]) != ","; i++)
            {
               string token_text = getValue(t[i]);
               if (t[i].getTableId() == 5 || t[i].getTableId() == 6)
               {
                  tempVector.push_back(PostfixElem(token_text, 1, t[i].getTableId()));
               }
               else if (token_text == "(")
               {
                  tempStack.push(token_text);
               }
               else if (token_text == ")")
               {
                  while (!tempStack.empty() && tempStack.top() != "(")
                  {
                     string tmpstr = tempStack.top();
                     tempVector.push_back(PostfixElem(tmpstr));
                     tempStack.pop();
                  }
                  if (tempStack.empty())
                  {
                     cerr << "Syntax Error: Unexpected \")\" !" << endl;
                     fOutError << "Syntax Error: Unexpected \")\" !" << endl;
                     errorFlag = true;
                  }
                  else
                  {
                     tempStack.pop();
                  }
               }
               else if (t[i].getTableId() == 2)
               {
                  while (!tempStack.empty() && getPriority(token_text, tempStack.top()))
                  {
                     string tmpstr = tempStack.top();
                     tempVector.push_back(PostfixElem(tmpstr));
                     tempStack.pop();
                  }
                  tempStack.push(token_text);
               }
            }
            if (errorFlag)
            {
               tempVector.clear();
               return false;
            }
            index = i + 1;

            Int buffer;
            integers.getElementByName(tempVector[0].id, buffer);
            if (tempVector.size() == 2 && tempVector[0].table == 5 && buffer.getValue() == INT_MIN) {
               Int buffer; int id;
               if (tempVector[1].table == 5) {
                  integers.getElementByName(tempVector[1].id, buffer);
                  int value = buffer.getValue();
                  integers.getElementByName(tempVector[0].id, buffer);
                  integers.getIdByElement(buffer, id);
                  buffer.setIsInit(true);
                  buffer.setValue(value);
               }
               else {
                  integers.getElementByName(tempVector[0].id, buffer);
                  integers.getIdByElement(buffer, id);
                  buffer.setIsInit(true);
                  buffer.setValue(stoi(tempVector[1].id));
               }

               integers.setElementById(id, buffer);
            }

            while (!tempStack.empty()) {
               string tmpstr = tempStack.top();
               tempVector.push_back(PostfixElem(tmpstr));
               tempStack.pop();
            }
            tempVector.push_back(PostfixElem(";", 4));
         }
         if (parseA && !parseB) {
            tempVector.push_back(PostfixElem("m" + to_string(m++)));
            tempVector.push_back(PostfixElem("UPL"));
            Aparsed = true;
            parseA = false;
         } else if (Aparsed) {
               Bparsed = true;
               Aparsed = false;
            } 
               
         return true;
      }

      // Печать постфиксной записи в файл и на экран
      void postfixOutput(string file_tree)
      {
         ofstream out(file_tree.c_str());
         cout << "Postfix notation:" << endl;
         for (int i = 0; i < (int)PostfixVector.size(); i++)
         {
            cout << PostfixVector[i] << " ";
            out << PostfixVector[i] << " ";
         }
         cout << endl;
         out.close();
      }

      // Сравнение приоритетов операций
      bool getPriority(string oper1, string oper2)
      {
         int oper1Weight = 0, oper2Weight = 0;
         if (oper1 == "=" || oper1 == "+=" || oper1 == "-=" || oper1 == "*=") oper1Weight = 10;
         else if (oper1 == "!="  || oper1 == "<" || oper1 == "==") oper1Weight = 20;
         else if (oper1 == "+" || oper1 == "-") oper1Weight = 30;
         else oper1Weight = 40;
         if (oper2 == "=" || oper2 == "+=" || oper2 == "-=" || oper2 == "*=") oper2Weight = 10;
         else if (oper2 == "!=" || oper2 == "<" || oper2 == "==") oper2Weight = 20;
         else if (oper2 == "+" || oper2 == "-") oper2Weight = 30;
         else if (oper2 == "*") oper2Weight = 40;
         if (oper1Weight <= oper2Weight) return true;
         return false;
      };

      // Генерация кода
      bool castToAsm(string asmFile, string errorFile)
      {
         fOutToken.open(asmFile.c_str(), ios::in);
         fOutError.open(errorFile.c_str(), ios::out);

         int mCount = 0;

         bool need_adv_int = false;

         stack<PostfixElem> postfixStack;
         vector<PostfixElem> variableVector;
         vector<string> valueVector;
         stringstream outcode;

         int index = 0;
         bool local_error = false, elseFlag = false, isStarted = false, isBP = false;

         fOutToken << ".386\n.model FLAT, C\n\n";

         while (!local_error && index < (int)PostfixVector.size())
         {
            Int buf;
            integers.getElementByName(PostfixVector[index].id, buf);
            bool isUnar = false;
            string maybe_uninit_name = "";

            int i; 
            for (i = index; !local_error && i < (int)PostfixVector.size() && PostfixVector[i].id != ";"; i++)
            {
               if (PostfixVector[i].id.find("m") != string::npos) {
                  if (PostfixVector[i].id.find(":") != string::npos) {
                     if (!elseFlag) {
                        if (mCount % 2 == 1 && !isBP) {
                           outcode << "lbl_ex_" << PostfixVector[i].id.substr(0, PostfixVector[i].id.length() - 1) << ":\n";
                        }
                        elseFlag = true;
                     }
                     else {
                        isBP = false;
                        outcode << "afterelse_" << PostfixVector[i] << "\n";
                        elseFlag = false;
                     }
                  }
                  else {
                     index += 3;
                  }
                  continue;
               }
               if (PostfixVector[i].id == "UPL") {
                  isStarted = true;
                  mCount++;
                  outcode << "lbl_eq_" << PostfixVector[i - 1] << ":\n";
                  continue;
               }

               if (PostfixVector[i].id == "BP") {
                  mCount++;
                  isBP = true;
                  outcode << "\tjmp afterelse_" << PostfixVector[i - 1].id << "\n";
                  outcode << "lbl_ex_" << PostfixVector[i + 1].id.substr(0, PostfixVector[i + 1].id.length() - 1) << ":\n";
                  continue;
               }
               if (PostfixVector[i].table == 5 || PostfixVector[i].table == 6)
               {
                  postfixStack.push(PostfixVector[i]);
                  bool added = false;
                  for (int j = 0; !added && j < (int)variableVector.size(); j++)
                  {
                     if (variableVector[j] == PostfixVector[i])
                        added = true;
                  }
                  if (!added)
                  {
                     variableVector.push_back(PostfixVector[i]);
                     valueVector.push_back("");
                  }
                  Int lex_array_check;
                  integers.getElementByName(PostfixVector[index].id, lex_array_check);

                  if (PostfixVector[i].table == 5)
                  {
                     
                        isUnar = true;
                        maybe_uninit_name = PostfixVector[i].id;
                  }
               }
               else
               {
                  PostfixElem oper1p, oper2p;
                  int type1 = 0, type2 = 0;
                  Int lex;
                  Constant constant; 

                  oper2p = postfixStack.top();
                  postfixStack.pop();
                  oper1p = postfixStack.top();
                  postfixStack.pop();

                  if (oper1p.table == 5)
                  {
                     integers.getElementByName(oper1p.id, lex);
                     if (PostfixVector[i].id != "=") {
                        outcode << "\tfild\t" << oper1p.id << "\n";
                     }

                  }
                  else if (oper1p.table == 6)
                  {
                     constants.getElementByValue(oper1p.id, constant);
                     if (PostfixVector[i].id != "=")
                     {
                           outcode << "\tfild\tconst_" << constant.getValue()  << "\n";
                     }
                  }

                  if (oper2p.table == 5)
                  {
                     integers.getElementByName(oper2p.id, lex);
                        outcode << "\tfild\t" << oper2p.id << "\n";
                  }
                  else if (oper2p.table == 6)
                  {
                     constants.getElementByValue(oper2p.id, constant);
                     outcode << "\tfild\tconst_" << constant.getValue() << "\n";
                  }

                  if (PostfixVector[i].id == "+")
                  {
                     outcode << "\tfadd\n";
                  }
                  else if (PostfixVector[i].id == "-")
                  {
                     if (oper2p.id == "last" && oper1p.id != "last")
                        outcode << "\tfsubr\n";
                     else
                        outcode << "\tfsub\n";
                  }
                  else if (PostfixVector[i].id == "*")
                  {
                     outcode << "\tfmul\n";
                  }
                  else if (PostfixVector[i].id == "==")
                  {
                     outcode << "\tfcomp\n";
                     outcode << "\tfistp\ttmp_var_int_" << PostfixVector[i + 2] << "\n";
                     outcode << "\tfstsw\tax\n\tsahf\n";
                     outcode << "\tje lbl_eq_" << PostfixVector[i + 2] << "\n";
                     outcode << "\tfldz\n\tjmp lbl_ex_" << PostfixVector[i + 2] << "\n";
                     i += 2;
                     need_adv_int = true;
                  }
                  else if (PostfixVector[i].id == "!=")
                  {
                     outcode << "\tfcomp\n";
                     outcode << "\tfistp\ttmp_var_int_" << PostfixVector[i + 2] << "\n";
                     outcode << "\tfstsw\tax\n\tsahf\n";
                     outcode << "\tjne lbl_eq_" << PostfixVector[i + 2] << "\n";
                     outcode << "\tfldz\n\tjmp lbl_ex_" << PostfixVector[i + 2] << "\n";
                     i += 2;
                     need_adv_int = true;
                  }
                  else if (PostfixVector[i].id == "<")
                  {
                     outcode << "\tfcomp\n";
                     outcode << "\tfistp\ttmp_var_int_" << PostfixVector[i + 2] << "\n";
                     outcode << "\tfstsw\tax\n\tsahf\n";
                     if (oper2p.id == "last" && oper1p.id != "last")
                        outcode << "\tjb lbl_eq_" << PostfixVector[i + 2] << "\n";
                     else
                        outcode << "\tja lbl_eq_" << PostfixVector[i + 2] << "\n";
                     outcode << "\tfldz\n\tjmp lbl_ex_" << PostfixVector[i + 2] << "\n";
                     i += 2;
                     need_adv_int = true;
                  }
                  else if (PostfixVector[i].id == "=")
                  {
                        outcode << "\tfistp\t" << oper1p.id << "\n";
                        Int temp;
                        int id;
                        integers.getElementByName(PostfixVector[index].id, temp);
                        integers.getIdByElement(temp, id);
                        temp.setIsInit(true);
                        integers.setElementById(id, temp);
                  }
                  postfixStack.push(PostfixElem("last"));
               }

               if (i == index && PostfixVector[i + 2].id == "=" && PostfixVector[i + 1].table == 6)
               {
                  Int lex_init;
                  if (integers.getElementByName(PostfixVector[i].id, lex_init))
                  {
                     bool found = false;
                     int j;
                     for (j = 0; !found && j < (int)variableVector.size(); j++)
                     {
                        if (variableVector[j].id == PostfixVector[i].id)
                           found = true;
                     }
                     if (found)
                     {
                        Int temp; 
                        int id; 
                        integers.getElementByName(PostfixVector[index].id, temp);
                        integers.getIdByElement(temp, id);
                        temp.setIsInit(true);
                        integers.setElementById(id, temp);
                        valueVector[j - 1] = PostfixVector[i + 1].id;
                        if (!isStarted) {
                           i += 2;
                        }
                     }
                  }
               }
            }

            while (postfixStack.size() > 0)
               postfixStack.pop();
            index = i + 1;
         }

         stringstream printf_out;

         stringstream bss_out;
         bool need_bss = false;

         fOutToken << ".data\n";
         for (int i = 0; i < (int)variableVector.size(); i++)
         {
            Int lex;
            if (variableVector[i].table == 5)
            {
               integers.getElementByName(variableVector[i].id, lex);
               
                  if (lex.getIsInit())
                  {
                     need_bss = true;
                     Int buffer;
                     integers.getElementByName(variableVector[i].id, buffer);
                     bss_out << "\t" << variableVector[i].id << "\tdd\t" << buffer.getValue() << "\n";
                  }
                  else
                  {
                     need_bss = true;
                     
                     bss_out << "\t" << variableVector[i].id << "\tdd\t" << "?"<< "\n";
                  }
            } else {
               int hash, chain;
               Constant constant;
               constants.getElementByValue(variableVector[i].id, constant);
               fOutToken << "\tconst_" << constant.getValue() << "\tdd\t" << variableVector[i].id << "\n";
            }
         }

         if (need_adv_int)
         {
            fOutToken << "\ttmp_var_int_m" << mCount << "\tdd\t0\n";
         }
         if (need_bss)
         {
            
            fOutToken << bss_out.str();
         }

         fOutToken << "\n.code\nmain proc\n";
         //fOutToken << "\tfinit\n";
         outcode << "\tmov\t\teax, 0\n\tret\n";
         outcode << "main endp\n\nend main";

         fOutToken << outcode.str();
         fOutToken << printf_out.str();
         

         fOutToken.close();
         fOutError.close();
         return true;
      }

};

int main() {
   Translator t;
   t.lexicalAnalysis("Source.txt", "token.txt", "errorFile.txt");

   if (!t.bracketAnalysis("token.txt", "errorFile.txt", "token2.txt")) {
      if (t.syntaxAnalysis("token2.txt", "errorFile.txt")) {
         cout << "Success!!";
         t.postfixOutput("tree.txt");

         t.castToAsm("asmFile.txt", "errorFile.txt");
      }
   }

   
   

   return 0;
}
