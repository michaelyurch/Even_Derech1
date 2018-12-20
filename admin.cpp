#include "admin.h"

int main(int argc, char* argv[]) {

    admin admin;

    std::ifstream readFile("input.txt");
    std::string lineFromFile;
    std::string script;

    if (!readFile.is_open()) {
        std::cout<<"Error ocured with openning of the file\n";
        return 0;
    }

    while (std::getline(readFile, lineFromFile)) {
        std::cout<<lineFromFile<<std::endl;
        script += '|';
        script += lineFromFile;
    }

    script += '|';

    readFile.close();

    std::vector<std::string> fff = admin.lexer(script);

    std::cout<<"LEXER'S RESULT:\n";

    for (int i = 0; i < fff.size(); i++) {

        auto it_front = fff.begin();
        advance(it_front, i);
        std::string str = *it_front;

        std::cout<<str<<std::endl;
    }

    admin.parcer(admin.lexer(script));

    return 0;
}

std::vector<std::string> admin::lexer (std::string input) {

    std::vector<std::string> scriptsList;
    int len = input.length();
    std::string curItem;

    bool isCommandReadNow = false;
    bool isExpressionReadNow = false;

    int commandCurrentSequenceLength = 0;
    int expressionCurrentSequenceLength = 0;
    int spaceCurrentSequenceLength = 0;

    char lastNonSpaceChar = ' ';

    for (int i = 0; i < len; i++) {

        if (curItem.length() == 0 && (input[i] == ' ' || input[i] == '\n'
                                        || input[i] == '\t')) {

            continue;
        }

        if (input[i] == '|') {
            for(int i2 = 0; i2 < curItem.length(); i2++) {
                if (curItem[i2] == ' ' || curItem[i2] == '\t' || curItem[i2] == '\n') {
                    std::string tempStr = curItem.substr(i2 + 1, curItem.length() - i2 - 1);
                    curItem = curItem.substr(0, i2) + tempStr;
                    i2--;
                }
            }

            scriptsList.push_back(curItem);
            scriptsList.push_back("|");
            curItem.clear();
        }

        if (input[i] == ',' && expressionCurrentSequenceLength > 0 
            && curItem.length() > 0 && !this->isContainsSpacesOnly(curItem)) {

            for(int i2 = 0; i2 < curItem.length(); i2++) {
                if (curItem[i2] == ' ' || curItem[i2] == '\t' || curItem[i2] == '\n') {
                    std::string tempStr = curItem.substr(i2 + 1, curItem.length() - i2 - 1);
                    curItem = curItem.substr(0, i2) + tempStr;
                    i2--;
                }
            }
            scriptsList.push_back(curItem);
            scriptsList.push_back(",");
            curItem.clear();

            commandCurrentSequenceLength = 0;
            expressionCurrentSequenceLength = 0;
            continue;
        }

        int curChar = input[i];

        if((curChar >= 97 && curChar <= 122) || (curChar >= 65 && curChar <= 90)
            || input[i] == '"' || input[i] == '=' || input[i] == '<' || input[i] == '>') {

            if (curItem.length() > 0 && commandCurrentSequenceLength == 0
                && !this->isContainsSpacesOnly(curItem)) {

                for(int i2 = 0; i2 < curItem.length(); i2++) {
                    if (curItem[i2] == ' ' || curItem[i2] == '\t' || curItem[i2] == '\n') {
                        std::string tempStr = curItem.substr(i2 + 1, curItem.length() - i2 - 1);
                        curItem = curItem.substr(0, i2) + tempStr;
                        i2--;
                    }
                }

                scriptsList.push_back(curItem);
                curItem.clear();
            }

            isCommandReadNow = true;
            isExpressionReadNow = false;

            commandCurrentSequenceLength++;
            expressionCurrentSequenceLength = 0;
        }

        else if(input[i] == '(' || input[i] == ')'
                || input[i] == '+' || input[i] == '*' || input[i] == ' ' 
                || input[i] == '\n' || input[i] == '\t'|| input[i] == '.'
                || (input[i] == '-'  && expressionCurrentSequenceLength == 0
                    && commandCurrentSequenceLength == 0)
                || (isdigit(input[i]) && expressionCurrentSequenceLength == 0
                    && commandCurrentSequenceLength == 0)) {

            if (curItem.length() > 0 && expressionCurrentSequenceLength == 0
                && !this->isContainsSpacesOnly(curItem)) {

                for(int i2 = 0; i2 < curItem.length(); i2++) {
                    if (curItem[i2] == ' ' || curItem[i2] == '\t' || curItem[i2] == '\n') {
                        std::string tempStr = curItem.substr(i2 + 1, curItem.length() - i2 - 1);
                        curItem = curItem.substr(0, i2) + tempStr;
                        i2--;
                    }
                }

                scriptsList.push_back(curItem);
                curItem.clear();
            }

            isCommandReadNow = false;
            isExpressionReadNow = true;

            commandCurrentSequenceLength = 0;
            expressionCurrentSequenceLength++;
        }

        if (((curChar >= 97 && curChar <= 122) || (curChar >= 65 && curChar <= 90)
            || input[i] == '"' || input[i] == '=' || input[i] == '<' || input[i] == '>'
            || input[i] == '-' || input[i] == '/' || isdigit(input[i])) 
            && commandCurrentSequenceLength > 0) {
            
            curItem += input[i];
        }

        else if ((isdigit(input[i]) || input[i] == '(' || input[i] == ')'
                || input[i] == '+' || input[i] == '-' || input[i] == '*'
                || input[i] == '/' || input[i] == ' ' || input[i] == '\n'
                || input[i] == '\t'|| input[i] == '.') && expressionCurrentSequenceLength > 0) {

            if (isdigit(lastNonSpaceChar) && spaceCurrentSequenceLength > 0 && isdigit(input[i])) {
                if (curItem.length() > 0 && !this->isContainsSpacesOnly(curItem)) {

                    for(int i2 = 0; i2 < curItem.length(); i2++) {
                        if (curItem[i2] == ' ' || curItem[i2] == '\t' || curItem[i2] == '\n') {
                            std::string tempStr = curItem.substr(i2 + 1, curItem.length() - i2 - 1);
                            curItem = curItem.substr(0, i2) + tempStr;
                            i2--;
                        }
                    }

                    scriptsList.push_back(curItem);
                    curItem.clear();

                    commandCurrentSequenceLength = 0;
                    expressionCurrentSequenceLength = 1;
                }
            }

            curItem += input[i];
        }

        if (!(input[i] == ' ' || input[i] == '\n' || input[i] == '\t')) {

            lastNonSpaceChar = input[i];
            spaceCurrentSequenceLength = 0;
        }

        else if(input[i] == ' ' || input[i] == '\n' || input[i] == '\t') {
            spaceCurrentSequenceLength++;
        }

        if ((i == len -1) && curItem.length() > 0) {
            if (!this->isContainsSpacesOnly(curItem)) {

                for(int i2 = 0; i2 < curItem.length(); i2++) {
                    if (curItem[i2] == ' ' || curItem[i2] == '\t' || curItem[i2] == '\n') {
                        std::string tempStr = curItem.substr(i2 + 1, curItem.length() - i2 - 1);
                        curItem = curItem.substr(0, i2) + tempStr;
                        i2--;
                    }
                }

                scriptsList.push_back(curItem);
                curItem.clear();
            }
        }
    }

    return scriptsList;
}

void admin::parcer (std::vector<std::string> items) {

    std::map <std::string, Command*> commandsMap;

    commandsMap["openDataServer"] = new OpenDataServerCommand();
    commandsMap["connect"] = new ConnectCommand();
    commandsMap["="] = new AssignmentCommand();
    commandsMap["bind"] = new BindCommand();
    commandsMap["if"] = new ConditionCommand();
    commandsMap["while"] = new LoopCommand();
    commandsMap["<"] = new SmallerCommand();
    commandsMap[">"] = new BiggerCommand();
    commandsMap["<="] = new SmallerEqualsCommand();
    commandsMap[">="] = new BiggerEqualsCommand();
    commandsMap["=="] = new EqualsCommand();
    commandsMap["sleep"] = new SleepCommand();
    commandsMap["print"] = new PrintCommand();

    std::map <std::string, std::string> varMap;

    std::map <std::string, std::string> bindMap;

std::cout<<"PRINT_BEFORE****************8"<<std::endl;

    int startLineIndex = 0;
    int endLineIndex = -1;
    for (int i = 0; i < items.size(); i++) {

        auto it_front = items.begin();
        advance(it_front, i);
        std::string item = *it_front;

        if (item == "|" && i != 0) {
            startLineIndex = ++endLineIndex;
            endLineIndex =  i - 1;
        }
std::cout<<startLineIndex<<" and "<<endLineIndex<<std::endl;        
//std::cout<<"VAL****************8"<<std::endl;
        for (int i2 = startLineIndex; i2 <= endLineIndex; i2++) {

            it_front = items.begin();
            advance(it_front, i2);
            std::string item = *it_front;

            //std::cout<<item<<std::endl;
            if (item == "var") {

                it_front = items.begin();
                advance(it_front, i2+1);
                std::string nextItem = *it_front;

                varMap[nextItem] = "0";
            }
        }
//std::cout<<"Syntax****************8"<<std::endl;
        for (int i2 = startLineIndex; i2 <= endLineIndex; i2++, i++) {

            it_front = items.begin();
            advance(it_front, i2);
            std::string item = *it_front;
            std::string prevItem = " ";

            if (i2 > 0) {
                it_front = items.begin();
                advance(it_front, i2 - 1);
                prevItem = *it_front;
            }

            //std::cout<<item<<std::endl;
            if (item[0] == ')' || item[0] == '+' || item[0] == '*' || item[0] == '/'
                || (item[0] == '-' && prevItem == ",")) {
std::cout<<"HERE!!!!!"<<std::endl;
                prevItem += item;
                items.erase(items.begin() + i2);
                endLineIndex--;
                i2--;
                i--;
            }
        }
    }
    std::cout<<"PRINT_AFTER****************8"<<std::endl;
    for (int i = 0; i < items.size(); i++) {
        auto it_front = items.begin();
        advance(it_front, i);
        std::string item = *it_front;
        std::cout<<item<<std::endl;
    }
/*
    for (int i = 0; i < items.size(); i++) {
        auto it_front = items.begin();
        advance(it_front, i);
        std::string item = *it_front;

        Command* currentCommand = commandsMap[item];
        std::string curVar = varMap[item];

        std::cout<<item<<std::endl;
        if (curVar.length() > 0) {
            items.at(i) = curVar;
            std::cout<<"value of "<<item<<" is "<<curVar<<std::endl;
        }

//        if (currentCommand != NULL){
  //          std::cout<<"It's command\n";
    //    }

        if (item == "var") {

            it_front = items.begin();
            advance(it_front, i+1);
            std::string nextItem = *it_front;

            varMap[nextItem] = "0";
        }

      //  else if (this->isExpressionToCalculation(item)) {
        //    std::cout<<(this->determineCurrentOperation(item))->calculate()<<std::endl;
      //  }
    }*/
}

bool admin::isExpressionToCalculation(std::string input) {

    if (input == "+" || input == "-" || input == "*" || input == "/") {
        return false;
    }

    int numOFBrackets = 0;

    for (int i = 0; i < input.length(); i++) {

        if (input[i] == '(' || input[i] == ')') {
            numOFBrackets++;
        }

        if (!(input[i] == '.' || input[i] == '(' || input[i] == ')'
            || input[i] == '+' || input[i] == '-' || input[i] == '*'
            || input[i] == '/' || isdigit(input[i]))) {
                
            return false;
        }
    }

    if (numOFBrackets % 2 == 1) {
        return false;
    }

    return true;
}

Expression* admin::determineCurrentOperation(std::string expression) {

    int len = expression.length();

    // if an expression in shape "(exp)", remove brackets to get shape "exp"
    if (expression[0] == '(' && expression[len - 1] == ')') {
        expression = expression.substr(1, len - 2);
        len -= 2;
    }

    if (expression.empty()) {
        return new Number("0");
    }

    bool isNumber = true;

    for (int i = 0; i < len; i++) {
        if (!isdigit(expression[i]) && expression[i] != '.') {
            isNumber = false;
            break;
        }
    }

    if (isNumber) {
        return new Number(expression);
    }

    int numOfOpenedBrackets = 0;

    for (int i = 0; i < len; i++) {

        if (expression[i] == '(') {
            numOfOpenedBrackets++;
        }

        if (expression[i] == ')') {
            numOfOpenedBrackets--;
        }

        if (numOfOpenedBrackets == 0 && (expression[i] == '+' || expression[i] == '-'
                                        || expression[i] == '*' || expression[i] == '/')) {
            
            if (expression[i] == '+') {
                return new PlusOperation(expression.substr(0, i),
                                    expression.substr(i + 1, len - i -1));
            }

            if (expression[i] == '-') {
                return new MinusOperation(expression.substr(0, i),
                                    expression.substr(i + 1, len - i -1));
            }
        }
    }

    numOfOpenedBrackets = 0;

    for (int i = 0; i < len; i++) {

        if (expression[i] == '(') {
            numOfOpenedBrackets++;
        }

        if (expression[i] == ')') {
            numOfOpenedBrackets--;
        }

        if (numOfOpenedBrackets == 0 && (expression[i] == '+' || expression[i] == '-'
                                        || expression[i] == '*' || expression[i] == '/')) {

            if (expression[i] == '*') {
                return new MulOperation(expression.substr(0, i),
                                    expression.substr(i + 1, len - i -1));
            }

            if (expression[i] == '/') {
                return new DivOperation(expression.substr(0, i),
                                    expression.substr(i + 1, len - i -1));
            }
        }
    }
}

bool admin::isContainsSpacesOnly(std::string input) {

    for (int i = 0; i < input.length(); i++) {
        if (!(input[i] == ' ' || input[i] == '\t' || input[i] == '\n')) {
            return false;
        }
    }

    return true;
}