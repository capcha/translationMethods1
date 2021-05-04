#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include <sstream>
#include <stack>

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

      vector<StateTableRow> StateTable; //таблица разбора
      stack<int> ParseStack; //стек, используемый для разбора

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

      int stringNumber, stringIncement;

      static inline void trim(string& out_)
      {
         int notwhite = out_.find_first_not_of(" \t\n");
         out_.erase(0, notwhite);
         notwhite = out_.find_last_not_of(" \t\n");
         out_.erase(notwhite + 1);
      }

      string getValue(Token& token) {
         switch (token.getTableId())
         {
         case 2: {
            Operator oper;
            operators.getElementById(token.getRowNumber(), oper);
            return string(1, oper.getName());
         }
         case 3: {
            ReservedWord reservedWord;
            words.getElementById(token.getRowNumber(), reservedWord);
            return reservedWord.getName();
         }
         case 4: {
            Separator separator;
            separators.getElementById(token.getRowNumber(), separator);
            return string(1, separator.getName());
         }
         case 5: {
            Int integer;
            integers.getElementById(token.getRowNumber(), integer);
            return integer.getName();
         }
         case 6: {
            Constant constant;
            constants.getElementById(token.getRowNumber(), constant);
            return constant.getValue();
         }
         default:
            return NULL;
         }
      }

   public:
      Translator() {
         alphabet = ImmutableTable<AlphabetUnit>("Alphabet.txt");
         operators = ImmutableTable<Operator>("Operators.txt");
         words = ImmutableTable<ReservedWord>("ReservedWords.txt");
         separators = ImmutableTable<Separator>("Separators.txt");
         integers = MutableTable<Int>();
         constants = MutableTable<Constant>();

         ifstream fInStateTable("StateTable.txt");

         while (!fInStateTable.eof()) {
            StateTableRow stateTableRow; //добавляемый эллемент
            string inputString;

            fInStateTable >> inputString;

            while (inputString != "|") {
               stateTableRow.getTerminal().push_back(inputString);
               fInStateTable >> inputString;
            };

            int jump, accept, returnState, stack, error; 

            fInStateTable >> jump >> accept >> stack >> returnState >> error;

            stateTableRow.setJump(jump);
            stateTableRow.setAccept(accept);
            stateTableRow.setStack(stack);
            stateTableRow.setReturn(returnState);
            stateTableRow.setError(error);
               
            StateTable.push_back(stateTableRow);
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
         bool isErrorFound = false;
         string str;

         fInToken.open(tokenFile.c_str(), ios::in);
         fOutError.open(errorFile.c_str(), ios::out);

         Token currentToken, nextToken;
         
         int tableId, rowId, chainId;

         fInToken >> tableId;
         fInToken >> rowId;
         fInToken >> chainId;

         currentToken = Token(tableId, rowId, chainId);
         
         int currentRow = 0, prevRow;         
   
         bool localError = false, isTreeBuildStarted = false;

         vector<Token> treeVector;
         string prevTokenValue;

         int identNumber;

         while (!fInToken.eof() && !localError) {
            string tokenValue = getValue(currentToken);
   
            string token_str = getValue(currentToken); // какой текст содержится в токене
            if (currentToken.getTableId() == 5 || currentToken.getTableId() == 6) {
               token_str = "ID";
            }

            if (token_str == "ID") {
               isTreeBuildStarted = true;
            }

            bool isTerminalLegal = false; //допустим ли данный терминал

            for (int i = 0; i < StateTable[currentRow].getTerminal().size() & !isTerminalLegal; i++) {
               if (StateTable[currentRow].getTerminal()[i] == token_str)
                  isTerminalLegal = true;
            }

            if (isTerminalLegal) { //если получаем то, что ожидали то обрабатываем это

               bool change_row = false; //сменили ли мы строку

               if (StateTable[currentRow].getStack()) {
                  ParseStack.push(currentRow + 1); //если надо получить в стек - ложим
               }

               if (StateTable[currentRow].getAccept()) { //принимаем терминал и если надо - расширяем дерево

                  if (little_tree_bg) {
                     little_tree_code.push_back(currentToken);
                  }

                  if (token_str == ";" || token_str == ",") { //если закончили разбор цельного оператора
                     grow_tree(little_tree_code); //добавили всё что нужно в дерево

                     //и перешли в исходное состояние
                     little_tree_code.clear();
                     little_tree_bg = false;

                  }

                  //все, обнуляем типа больше нет
                  if (token_str == ";") {
                     have_type = false;
                  }

                  //Если мы нашли тип, то мы его запоминаем
                  if (token_str == "int" || token_str == "char") {
                     have_type = true;
                     if (token_str == "int")
                        type_type = 1;
                     if (token_str == "char")
                        type_type = 2;
                  }


                  //Заносим тип в таблицу идентицикаторов
                  if (token_str == "ID" && have_type && currentRow == 47) {
                     identifier.set_ind_type(getValue(currentToken), type_type);
                  }

                  //Если вдруг попытались присвоить что-то константе
                  if (currentRow == 30 && currentToken.table_n != 5) {
                     parse_error_f << "Ошибка в обработке " << getValue(currentToken) << " константе не может быть присовенно значение" << endl;
                     cout << "Lex error" << endl;
                     localError = true;
                  }


                  //и пошли дальше
                  currentToken = nextToken;
                  if (!parse_token_f.eof())
                     parse_token_f >> nextToken; //если принимает, то считываем новый
               }

               if (StateTable[currentRow].should_return) {
                  prev_row = currentRow; //запоминаем предыдущий
                  currentRow = ParseStack.top(); //если надо взять из стека - берём
                  ParseStack.pop();
                  change_row = true;
               }


               if (!change_row && StateTable[currentRow].jump != -1) {
                  currentRow = StateTable[currentRow].jump; //если надо прыгнуть - прыгаем
               }

            }
            else { //если произошщло несоответсвие
               if (StateTable[currentRow].error) { //если можем судить что уже ошибка, то возвращаем её
                  localError = true;
                  parse_error_f << "Ошибка в обработке " << getValue(currentToken) << endl;
                  cout << "Lex error" << endl;

                  //Для РГЗ 1, начало - вывод альтернатив
                  parse_error_f << "Возможно на этом месте должно быть: ";
                  do {
                     for (int i = 0; i < StateTable[currentRow].termenal.size(); i++) {
                        parse_error_f << StateTable[currentRow].termenal[i] << " ";
                     }
                     currentRow--;
                  } while (!StateTable[currentRow].error);
                  parse_error_f << endl;
                  //Для РГЗ 1 - конец
               }
               else { //Если нет - переходим на следующий
                  currentRow++;
               }
            }
            token_str_prev = token_str;
      
         }

      }
};

int main()
{
   Translator t;
   t.lexicalAnalysis("Source.txt", "Token.txt", "errorFile.txt");
   return 0;
}
