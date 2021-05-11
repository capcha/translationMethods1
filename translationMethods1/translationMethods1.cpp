#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <sstream>
#include <stack>

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

      vector<StateTableRow> newTable; 
      stack<int> ParseStack; 

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
         fIn.close();
         fOutToken.close();
         fOutError.close();
         return !isErrorFound;
      }
   
      bool syntaxAnalysis(string tokenFile, string errorFile) {
         string str;

         fInToken.open(tokenFile.c_str(), ios::in);
         fOutError.open(errorFile.c_str(), ios::out);

         Token currentToken, nextToken;
         
         int tableId, rowId, chainId;

         fInToken >> tableId;
         fInToken >> rowId;
         fInToken >> chainId;

         nextToken = Token(tableId, rowId, chainId);
         
         int currentRow = 0, prevRow;      
         bool isInt = false;
   
         bool localError = false, isTreeBuildStarted = false;

         vector<Token> treeVector;
         string prevTokenValue;

         int identNumber, type;

         while (!fInToken.eof() && !localError) {
            string tokenValue = getValue(nextToken);
   
            string token_str = getValue(nextToken); 
            if (nextToken.getTableId() == 5 || nextToken.getTableId() == 6) {
               token_str = "ID";
            }

            if (token_str == "ID") {
               isTreeBuildStarted = true;
            }

            bool isTerminalLegal = false; 

            for (int i = 0; i < newTable[currentRow].getTerminal().size() & !isTerminalLegal; i++) {
               if (newTable[currentRow].getTerminal()[i] == token_str) {
                  isTerminalLegal = true;
               }
            }

            if (isTerminalLegal) { 
               bool change_row = false; 

               if (newTable[currentRow].getStack()) {
                  ParseStack.push(currentRow + 1);
               }

               if (newTable[currentRow].getAccept()) { 

                  if (isTreeBuildStarted) {
                     treeVector.push_back(nextToken);
                  }

                  if (token_str == ";" || token_str == ",") { 
                     buildTree(treeVector);
                     treeVector.clear();
                     isTreeBuildStarted = false;
                  }

                  if (token_str == ";") {
                     isInt = false;
                  }

                  if (token_str == "int") {
                     isInt = true;
                  }

                  if (token_str == "=" && currentToken.getTableId() == 6) {
                     fOutError << "Ошибка в строке " << currentRow << ", константе не может быть присовенно значение" << endl;
                     cout << "Ошибка" << endl;
                     localError = true;
                  }

                  if (isInt && token_str == "=" && currentToken.getTableId() == 5) {
                     Int buffer;
                     integers.getElementById(currentToken.getRowNumber(), buffer);

                     if (buffer.getIsInit()) {
                        fOutError << "Ошибка в строке " << currentRow << ", Переменная " << getValue(currentToken) << " уже инициализирована инициализирована" << endl;
                        cout << "Ошибка" << endl;
                        localError = true;
                     }
                     else {
                        buffer.setIsInit(true);

                        integers.setElementById(currentToken.getRowNumber(), buffer);
                     }

                  }

                  if (token_str == "=" && currentToken.getTableId() == 5) {
                     Int buffer;
                     integers.getElementById(currentToken.getRowNumber(), buffer);

                     if (!buffer.getIsInit()) {
                        fOutError << "Ошибка в строке " << currentRow << ", Переменная " << getValue(currentToken) << " не инициализирована" << endl;
                        cout << "Ошибка" << endl;
                        localError = true;
                     }

                  }

                  currentToken = nextToken;
                  if (!fInToken.eof()) {
                     fInToken >> tableId;
                     fInToken >> rowId;
                     fInToken >> chainId;
                     nextToken = Token(tableId, rowId, chainId);
                  }
               }

               if (newTable[currentRow].getReturnState()) {
                  prevRow = currentRow; 
                  
                  currentRow = ParseStack.top();
                  bool changed = false;
                  ParseStack.pop();
                  while (!ParseStack.empty() && currentRow == ParseStack.top()) {
                     ParseStack.pop();
                     changed = true;
                  }
                  
                  if (changed) {
                     currentRow = ParseStack.top();
                  }

                  change_row = true;
               }


               if (!change_row && newTable[currentRow].getJump() != 0) {
                  currentRow = newTable[currentRow].getJump(); 
               }

            }
            else { 

               if (newTable[currentRow].getError()) { 
                  localError = true;
                  fOutError << "Ошибка в строке " << currentRow << ", символы: " << getValue(nextToken) << endl;
                  cout << "Ошибка" << endl;

                  fOutError << "Возможно на этом месте должно быть: ";
                  do {
                     for (int i = 0; i < newTable[currentRow].getTerminal().size(); i++) {
                        fOutError << newTable[currentRow].getTerminal()[i] << " ";
                     }
                     currentRow--;
                  } while (!newTable[currentRow].getError());
                  fOutError << endl;
               }
               else { 
                  currentRow++;
               }
            }
            prevTokenValue = token_str;
         }
         
         return localError;
      }

      void treeOutput(string f_name) {
         ofstream out_f(f_name.c_str());

         treeOutputRecurent(out_f, treeRoot);

         out_f.close();
      }

      void treeOutputRecurent(ofstream& out_f, TreeElement* beg) {
         if (beg != 0) {
            if (beg->left != 0) treeOutputRecurent(out_f, beg->left);
            if (beg->right != 0) treeOutputRecurent(out_f, beg->right);

            out_f << beg->id << " ";
         }
      }

};

int main() {
   Translator t;
   t.lexicalAnalysis("Source.txt", "Token.txt", "errorFile.txt");

   if (!t.syntaxAnalysis("Token.txt", "errorFile.txt")) {
      cout << "Success!!";
   }

   t.treeOutput("tree.txt");

   return 0;
}
