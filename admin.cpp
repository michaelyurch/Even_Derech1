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

        if (input[i] == '}' && curItem.length() > 0) {
            for(int i2 = 0; i2 < curItem.length(); i2++) {
                if (curItem[i2] == ' ' || curItem[i2] == '\t' || curItem[i2] == '\n') {
                    std::string tempStr = curItem.substr(i2 + 1, curItem.length() - i2 - 1);
                    curItem = curItem.substr(0, i2) + tempStr;
                    i2--;
                }
            }

            scriptsList.push_back(curItem);
            scriptsList.push_back("|");
            scriptsList.push_back("}");
            scriptsList.push_back("|");
            curItem.clear();
            continue;
        }

        if (input[i] == '{' && curItem.length() > 0) {
            for(int i2 = 0; i2 < curItem.length(); i2++) {
                if (curItem[i2] == ' ' || curItem[i2] == '\t' || curItem[i2] == '\n') {
                    std::string tempStr = curItem.substr(i2 + 1, curItem.length() - i2 - 1);
                    curItem = curItem.substr(0, i2) + tempStr;
                    i2--;
                }
            }

            scriptsList.push_back(curItem);
            scriptsList.push_back("|");
            scriptsList.push_back("{");
            scriptsList.push_back("|");
            curItem.clear();
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
            scriptsList.push_back(",");
            curItem.clear();

            commandCurrentSequenceLength = 0;
            expressionCurrentSequenceLength = 0;
            continue;
        }

        int curChar = input[i];

        if((curChar >= 97 && curChar <= 122) || (curChar >= 65 && curChar <= 90)
            || input[i] == '"' || input[i] == '=' || input[i] == '<' || input[i] == '>'
            || input[i] == '_' || input[i] == '{' || input[i] == '}') {

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
            || input[i] == '-' || input[i] == '/' || isdigit(input[i]) || input[i] == '_'
            || input[i] == '{' || input[i] == '}') 
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

std::vector<std::string> admin::substituteVariablesValues(std::vector<std::string> items
    , int startLineIndex, int endLineIndex) {

    for (int i2 = startLineIndex; i2 < endLineIndex; i2++) {

            auto it_front = items.begin();
            advance(it_front, i2);
            std::string item = *it_front;

            std::cout<<item<<std::endl;

            it_front = items.begin();
            advance(it_front, i2+1);
            std::string nextItem = *it_front;

            if (item == "var") {

                varMap[nextItem] = "0";
                items.erase(items.begin() + i2);
                i2--;
                endLineIndex--;

                for (int i3 = 0; i3 < newLineIndexes.size(); i3++) {
                    auto it_front = newLineIndexes.begin();
                    advance(it_front, i3);

                    int curEndLineIndex = *it_front;
                    curEndLineIndex--;
                    newLineIndexes.at(i3) = curEndLineIndex;
                }
            }

            std::string curVar = varMap[item];
            if (curVar.length() > 0 && nextItem != "=") {
                items.at(i2) = curVar;
            }
        }
        return items;
}

std::vector<std::string> admin::fixSyntaxCorrection(std::vector<std::string> items
    , int startLineIndex, int endLineIndex) {
    
        for (int i2 = startLineIndex; i2 < endLineIndex; i2++) {
            auto it_front = items.begin();
            advance(it_front, i2);
            std::string item = *it_front;

            std::cout<<item<<std::endl;

            std::string prevItem;
            
            if (i2 > 0) {
                it_front = items.begin();
                advance(it_front, i2 - 1);
                prevItem = *it_front;
            }

            if (prevItem.length() > 0
                && (item[0] == ')' || item[0] == '+' || item[0] == '*' || item[0] == '/'
                || (item[0] == '-' && prevItem != "," && prevItem != "="
                    && commandsMap.find(item) != commandsMap.end()))) {
//std::cout<<"HERE!!!!!"<<std::endl;
                prevItem += item;
                items.erase(items.begin() + i2);
                i2--;
                items.at(i2) = prevItem;
                endLineIndex--;

                for (int i3 = 0; i3 < newLineIndexes.size(); i3++) {
                    auto it_front = newLineIndexes.begin();
                    advance(it_front, i3);

                    int curEndLineIndex = *it_front;
                    curEndLineIndex--;
                    newLineIndexes.at(i3) = curEndLineIndex;
                }
            }
        }

        for (int i2 = endLineIndex - 1; i2 >= startLineIndex; i2--) {
            auto it_front = items.begin();
            advance(it_front, i2);
            std::string item = *it_front;

   //         std::cout<<item<<std::endl;

            std::string nextItem;
            
            if (i2 + 1 < items.size()) {
                it_front = items.begin();
                advance(it_front, i2 + 1);
                nextItem = *it_front;
            }

            if (nextItem.length() > 0
                && (item[item.length() - 1] == '(' 
                || ((item[item.length() - 1] == '+' 
                || item[item.length() - 1] == '*' || item[item.length() - 1] == '/'
                || item[item.length() - 1] == '-') && (item.length() - 1 != 0)))) {
//std::cout<<"HERE!!!!!222222222222222222222222222"<<std::endl;
                item += nextItem;
                items.erase(items.begin() + i2 + 1);
                items.at(i2) = item;
                endLineIndex--;

                for (int i3 = 0; i3 < newLineIndexes.size(); i3++) {
                    auto it_front = newLineIndexes.begin();
                    advance(it_front, i3);

                    int curEndLineIndex = *it_front;
                    curEndLineIndex--;
                    newLineIndexes.at(i3) = curEndLineIndex;
                }
            }
        }
        return items;
}

std::vector<std::string> admin::calculateInternalExpressions(
    std::vector<std::string> items, int startLineIndex, int endLineIndex) {

            for (int i2 = startLineIndex; i2 < endLineIndex; i2++) {

            auto it_front = items.begin();
            advance(it_front, i2);
            std::string item = *it_front;

            std::cout<<item<<std::endl;
            
            std::string prevItem;
            std::string prevPrevItem;
            std::string nextItem;

            if (i2 - 2 >= 0) {
                it_front = items.begin();
                advance(it_front, i2 - 1);
                prevItem = *it_front;

                it_front = items.begin();
                advance(it_front, i2 - 2);
                prevPrevItem = *it_front;
            }

            if (i2 < items.size() - 1) {
                it_front = items.begin();
                advance(it_front, i2 + 1);
                nextItem = *it_front;
            }

            if (this->isExpressionToCalculation(item)) {
                item = this->determineCurrentOperation(item)->calculate();
                items.at(i2) = item;

                if (prevPrevItem.length() > 0) {
                    if (prevItem == "=") {
                        double doubleVal = std::stod(item);

//std::cout<<"bbb2222 "<<item<<std::endl;
                        varMap[prevPrevItem] = item;
                    }
                }
            }

            if (item == "bind") {
                if (prevPrevItem.length() > 0 && nextItem.length() > 0) {
                    bindMap[prevPrevItem] = nextItem;
                    bindedVariables.push_back(prevPrevItem);

                    Command* conectCommand = commandsMap["connect"];
                    ((ConnectCommand*)conectCommand)->setVarsAndBinds(varMap, bindMap
                        , bindedVariables);
                    
               //     std::cout<<"BIND ADDED\n";
                }
            }
        }
        return items;
}

void admin::parcer (std::vector<std::string> script) {

    commandsMap["openDataServer"] = new OpenDataServerCommand();
    commandsMap["connect"] = new ConnectCommand();
    commandsMap["="] = NULL;
    commandsMap["bind"] = NULL;
    commandsMap["if"] = NULL;
    commandsMap["while"] = NULL;
    commandsMap["<"] = new SmallerCommand();
    commandsMap[">"] = new BiggerCommand();
    commandsMap["<="] = new SmallerEqualsCommand();
    commandsMap[">="] = new BiggerEqualsCommand();
    commandsMap["=="] = new EqualsCommand();
    commandsMap["sleep"] = new SleepCommand();
    commandsMap["print"] = new PrintCommand();

//std::cout<<"PRINT_BEFORE****************8"<<std::endl;

    std::vector<std::string> items;

    for (int i = 0; i < script.size(); i++) {

        auto it_front = script.begin();
        advance(it_front, i);
        std::string item = *it_front;

        items.push_back(item);

        if (item == "|") {
   //         std::cout<<i<<std::endl;
            newLineIndexes.push_back(i);
            newLineIndexesOriginal.push_back(i);
        }
    }

 //   std::vector<std::string> items = script;

    for (int i = 0; i < newLineIndexes.size(); i++) {
        auto it_front = newLineIndexes.begin();
        advance(it_front, i);

        int endLineIndex = *it_front;
        int startLineIndex = 0;
        
        if (i != 0) {
            it_front = newLineIndexes.begin();
            advance(it_front, i - 1);
            startLineIndex = *it_front + 1;
        }


        items = this->substituteVariablesValues(items, startLineIndex, endLineIndex);

        items = this->fixSyntaxCorrection(items, startLineIndex, endLineIndex);

        items = this->calculateInternalExpressions(items, startLineIndex, endLineIndex);

        for (int i2 = startLineIndex; i2 < endLineIndex; i2++) {

                        auto it_front = items.begin();
            advance(it_front, i2);
            std::string item = *it_front;
            
            std::string prevItem;
            std::string prevPrevItem;
            std::string nextItem;

            if (i2 - 2 >= 0) {
                it_front = items.begin();
                advance(it_front, i2 - 1);
                prevItem = *it_front;

                it_front = items.begin();
                advance(it_front, i2 - 2);
                prevPrevItem = *it_front;
            }

            if (i2 < items.size() - 1) {
                it_front = items.begin();
                advance(it_front, i2 + 1);
                nextItem = *it_front;
            }

            if (item == "connect") {
                Command* conectCommand = commandsMap[item];
                if (items[++i2] == ",") {
                    ++i2;
                }
                conectCommand->getFirstArgument(items[i2]);
                if (items[++i2] == ",") {
                    ++i2;
                }
                conectCommand->getSecondArgument(items[i2]);
                ((ConnectCommand*)conectCommand)->setVarsAndBinds(varMap, bindMap
                    , bindedVariables);

                conectCommand->execute();
                
             //   std::thread first (performCommand, conectCommand);
              //  first.join();
                continue;
            }

            if (item == "while" || item == "if") {
                if (i2 < items.size() - 3) {
                    it_front = items.begin();
                    advance(it_front, i2 + 2);
                    std::string nextNextItem = *it_front;

                    it_front = items.begin();
                    advance(it_front, i2 + 3);
                    std::string nextNextNextItem = *it_front;

                    Command *compareCommand = commandsMap[nextNextItem];
                std::cout<<nextItem<<" &^&^ 11111\n";    
                    compareCommand->getFirstArgument(nextItem);
                    std::cout<<nextNextNextItem<<" &^&^ 222222\n"; 
                    std::cout<<nextNextItem<<"\n";  
                    compareCommand->getSecondArgument(nextNextNextItem);
                    std::cout<<" &^&^ 333333\n";  
                    int result = compareCommand->execute();
                    std::cout<<"&^&^ 444444   "<<result<<std::endl;  
                    
                    int numOfOpenedBraces = 0;
                    int indexOfBlockEnd = -1;
                    int indexOfBlockBegin = i;

                    for (int i3 = i; i3 < newLineIndexes.size() - 1; i3++) {
                        
                        auto it_front = newLineIndexes.begin();
                        advance(it_front, i3);
                        int curItemNum = *it_front;
                        
                        auto it_front1 = items.begin();
                        advance(it_front1, curItemNum + 1);
                        std::string curItem = *it_front1;

                        if (curItem == "{") {
                            numOfOpenedBraces++;
                        }

                        if (curItem == "}") {
                            numOfOpenedBraces--;

                            if (numOfOpenedBraces == 0) {
                                indexOfBlockEnd = i3;
                                break;
                            }
                        }
                    }

                    std::cout<<"&^&^ 555555   "<<indexOfBlockEnd<<std::endl;
                    if (result == 1) {
                        beginBlockIndexesSteak.push_back(indexOfBlockBegin);
                        endBlockIndexesSteak.push_back(indexOfBlockEnd);
                        nameOfBlocksSteak.push_back(item);
                    }
                    else {

                        auto it_front = newLineIndexes.begin();
                        advance(it_front, indexOfBlockEnd);
                        int curItemNum = *it_front;

                        i = indexOfBlockEnd;
                        i2 = curItemNum + 1;
                        continue;
                    }  
                }
            }

            int indexOfEndClosestBlock = -1;
            int indexOfBeginClosestBlock = -1;
            std::string nameOfClosestBlock;

            if (endBlockIndexesSteak.size() > 0) {

                int lastIndex = endBlockIndexesSteak.size() - 1;

                indexOfEndClosestBlock = newLineIndexes[endBlockIndexesSteak
                    [lastIndex]];

                indexOfEndClosestBlock++;

                indexOfBeginClosestBlock = newLineIndexes[beginBlockIndexesSteak
                    [lastIndex]];

                indexOfBeginClosestBlock++;

                nameOfClosestBlock = nameOfBlocksSteak[lastIndex];
            }
            
            if (i2 == indexOfEndClosestBlock) {
                std::cout<<"////////////////////////////////////////// "
                <<nameOfClosestBlock<<std::endl;

                int lastIndex = endBlockIndexesSteak.size() - 1;

                if (nameOfClosestBlock == "while") {

                    int startOfLoopOriginal = newLineIndexesOriginal[beginBlockIndexesSteak
                            [lastIndex]];

                    startOfLoopOriginal++;

                    int endOfLoopOriginal = newLineIndexesOriginal[endBlockIndexesSteak
                            [lastIndex]];

                    endOfLoopOriginal++;

                    indexOfBeginClosestBlock += 2;

                    std::cout<<startOfLoopOriginal<<"\n";
                    std::cout<<endOfLoopOriginal<<"\n";
                    std::cout<<indexOfBeginClosestBlock<<"\n";
                    std::cout<<indexOfEndClosestBlock<<"\n";

                    int prevLoopShift = (endOfLoopOriginal - startOfLoopOriginal)
                        - (indexOfEndClosestBlock - indexOfBeginClosestBlock);

                    std::cout<<"RRRRRRRRRRRRRRRRRR prevLoopShift "
                    <<prevLoopShift<<"\n";

                    for (int i3 = i + 1; i3 < newLineIndexes.size(); i3++) {
                        newLineIndexes.at(i3) = newLineIndexes[i3] + prevLoopShift;
                    }
                    
                    for (int i3 = 0; i3 < prevLoopShift; i3++) {
                        items.insert(items.begin() + indexOfBeginClosestBlock + i3, "^");
                    }

                    int counter = indexOfBeginClosestBlock;

                    for (int i3 = startOfLoopOriginal; i3 <= endOfLoopOriginal; i3++) {
                        items.at(counter) = script[i3];
                        counter++;
                    }
                    print("AFTER_LOOP", items);

                    for (int i3 = beginBlockIndexesSteak[lastIndex]; 
                            i3 <= endBlockIndexesSteak[lastIndex]; i3++) {
                    std::cout<<"IIIIIIIIIIIIIIIII"<<i3<<"\n";
                        auto it_front = newLineIndexes.begin();
                        advance(it_front, i3);

                        int endLineIndex = *it_front;
                        int startLineIndex = 0;
        
                        if (i3 != 0) {
                            it_front = newLineIndexes.begin();
                            advance(it_front, i3 - 1);
                            startLineIndex = *it_front + 1;
                        }

                        this->substituteVariablesValues(items, startLineIndex
                            , endLineIndex);
                        this->fixSyntaxCorrection(items, startLineIndex
                            , endLineIndex);
                        this->calculateInternalExpressions(items, startLineIndex
                            , endLineIndex);
                    }

                    i = beginBlockIndexesSteak[lastIndex]-1;
                    i2 = newLineIndexes[i];

                    std::cout<<"UUUUUUUUUU" <<i<<" and "<<i2<<"\n";

                    endBlockIndexesSteak.pop_back();
                    beginBlockIndexesSteak.pop_back();
                    nameOfBlocksSteak.pop_back();

                    continue;
                }
            }
        }  
    }
    this->print("after", items);
}

void static performCommand(Command* command) {
    while (true) {
        command->execute();
    }
}

void admin::print(std::string str, std::vector<std::string> items) {
    std::cout<<"PRINT****************8"<<str<<std::endl;
    for (int i = 0; i < items.size(); i++) {
        auto it_front = items.begin();
        advance(it_front, i);
        std::string item = *it_front;
        std::cout<<item<<std::endl;
    }
        std::cout<<"ENDDDDDDDDDDDDDD****************8"<<str<<std::endl;
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

    if (expression[0] == '-') {
        for (int i = 1; i < expression.length(); i++) {
            if (expression[i] == '-') {
                expression[i] = '+';
            }
            else if (expression[i] == '+') {
                expression[i] = '-';
            }
        }
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