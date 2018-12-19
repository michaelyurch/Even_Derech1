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
        script += ' ';
        script += lineFromFile;
    }
    readFile.close();

    std::list<std::string> fff = admin.lexer(script);

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

std::list<std::string> admin::lexer (std::string input) {

    std::list<std::string> scriptsList;
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

void admin::parcer (std::list<std::string> items) {

    std::map <std::string, Command*> commandsMap;

    commandsMap["openDataServer"] = new OpenDataServerCommand();
    for (int i = 0; i < items.size(); i++) {
        auto it_front = items.begin();
        advance(it_front, i);
        std::string item = *it_front;

        Command* currentCommand = commandsMap[item];
     //   std::cout<<item<<std::endl;

        if (currentCommand != NULL) {
            
        }

        else if (this->isExpression(item)) {
        //    std::cout<<(this->determineCurrentOperation(item))->calculate()<<std::endl;
        }
    }
}

bool admin::isExpression(std::string input) {
    for (int i = 0; i < input.length(); i++) {
        if (!(input[i] == '.' || input[i] == '(' || input[i] == ')'
            || input[i] == '+' || input[i] == '-' || input[i] == '*'
            || input[i] == '/' || isdigit(input[i]))) {
                
            return false;
        }
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