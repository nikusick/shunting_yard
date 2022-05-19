#include <iostream>
#include <stack>
#include<string>
#include<vector>
#include <sstream>
#include <cstring>
#include<map>
#include <queue>
#include <variant>
#include <cmath>

#include "token.h"

using namespace std;



map<std::string, Operator> operators = {
        {"+", Operator{"+", 2, Operator::Associativity::Left, 1}},
        {"-", Operator{"-", 2, Operator::Associativity::Left, 1}},
        {"*", Operator{"*", 2, Operator::Associativity::Left, 2}},
        {"/", Operator{"/", 2, Operator::Associativity::Left, 2}},
        {"^", Operator{"^", 2, Operator::Associativity::Right, 3}},
        {"(", Operator{"(", 0, Operator::Associativity::Right, 0}},
};

bool isNumber(const string& token) {
    try {
        stof(token);
        return true;
    }
    catch (invalid_argument){
        return false;
    }
}

bool isOperator(const string& token) {
    for (auto&& item: operators) {
        if (item.first == token) {
            return true;
        }
    }
    return false;
}


Operator* findOperatorToken(const string& token) {
    for (auto&& item: operators) {
        if (item.first == token) {
            Operator* res = new Operator(item.second);
            return res;
        }
    }
}

vector<string> tokenise(const string& string1)
{
    const char* str = string1.data();
    vector<string> result;
    do
    {
        const char *begin = str;
        while(*str != ' ' && *str)
            str++;
        result.push_back(string(begin, str));
    } while (0 != *str++);
    return result;
}

std::queue<string> shuntingYard(const vector<string>& tokens) {
    std::queue<string> output;
    std::stack<Operator*> operatorStack;
    bool lastIsOperator = true;

    for (auto&& token: tokens) {
        if (isNumber(token)) {
            output.push(token);
            lastIsOperator = false;
        }
        if (isOperator(token) && token != "(" && token != ")") {
            Operator *token1 = findOperatorToken(token);
            while (!operatorStack.empty() && operatorStack.top()->_value != "(" &&
                    ((operatorStack.top()->_priority > token1->_priority) || operatorStack.top()->_priority == token1->_priority &&
                                                                                     token1->_associativity == Operator::Associativity::Left)) {
                output.push(operatorStack.top()->_value);
                operatorStack.pop();
            }
            operatorStack.push(token1);
            lastIsOperator = true;
        }
        if (token == "(") {
            operatorStack.push(findOperatorToken(token));
            lastIsOperator = true;
        }
        if (token == ")") {
            while (!operatorStack.empty() && operatorStack.top()->_value != "(") {
                output.push(operatorStack.top()->_value);
                operatorStack.pop();
            }
            if (operatorStack.empty()) {
                throw;
            }
            operatorStack.pop();
        }
        lastIsOperator = true;
    }
    while (!operatorStack.empty()) {
        output.push(operatorStack.top()->_value);
        operatorStack.pop();
    }
    return output;
}

float calculate(std::queue<string> output) {
    std::stack <float> result;
    while (!output.empty()) {
        string token = output.front();
        output.pop();
        float res;
        if (isNumber(token)) {
            result.push(stof(token));
        }
        if (isOperator(token)) {
            if (token == "+") {
                res = result.top();
                result.pop();
                res = result.top() + res;
                result.pop();
            }
            if (token == "-") {
                res = result.top();
                result.pop();
                res = result.top() - res;
                result.pop();
            }
            if (token == "*") {
                res = result.top();
                result.pop();
                res *= result.top();
                result.pop();
            }
            if (token == "/") {
                res = result.top();
                result.pop();
                res = result.top() / res;
                result.pop();
            }
            if (token == "^") {
                res = result.top();
                result.pop();
                res = pow(result.top(), res);
                result.pop();
            }
            result.push(res);
            cout << result.top() << endl;
        }
    }
    if (result.size() > 1) {
        throw out_of_range("Im stupid");
    }
    return result.top();
}

int main() {
    //string str = "14 / ( 2 + 5 ) * ( 10 / ( 7 - 2 ) ) ^ 2";
    string str = "3 + 4 * 2 / ( 1 + -5 ) ^ 2 ^ 3";
    vector<string> tokens = tokenise(str);
    std::queue<string> output = shuntingYard(tokens);
    std::queue<string> output1 = output;
    while(!output1.empty()) {
        cout << output1.front() << " ";
        output1.pop();
    }
    cout << endl;
    cout << calculate(output);
    return 0;
}
