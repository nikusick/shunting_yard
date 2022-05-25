#include "shuntingYard.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <stack>

using namespace std;

std::map<std::string, Operator> operators = {
        {"+", Operator{"+", Operator::Associativity::Left, 1, &add}},
        {"-", Operator{"-", Operator::Associativity::Left, 1, &substract}},
        {"*", Operator{"*", Operator::Associativity::Left, 2, &multiply}},
        {"/", Operator{"/", Operator::Associativity::Left, 2, &divide}},
        {"^", Operator{"^", Operator::Associativity::Right, 3, &raisePow}},
        {"~", Operator{"~", Operator::Associativity::Left, 4, &substract}},
        {"(", Operator{"(", Operator::Associativity::Right, 0}},
        {")", Operator{")", Operator::Associativity::Right, 0}},
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
    return operators.find(token) != operators.end();
}

vector<string> tokenise(const string& input)
{
    vector<string> result;
    result.push_back("");
    for (auto&& item: input) {
        if (isOperator(string(1, item))) {
            result.push_back(string(1, item));
            result.push_back("");
        }
        else {
            result.back() += item;
        }
    }
    return result;
}

std::queue<string> shuntingYard(const vector<string>& tokens) {
    std::queue<string> output;
    std::stack<Operator*> operatorStack;
    bool flag = true;
    for (auto&& token: tokens) {
        if (isNumber(token)) {
            output.push(token);
            flag = false;
        }
        if (isOperator(token) && token != "(" && token != ")") {
            Operator* curToken = &operators.at(token);
            if (token == "-" && flag) {
                if (!operatorStack.empty() && operatorStack.top()->_value == "(") {
                    output.push("0");
                    curToken = &operators.at("~");
                }
                if (output.empty()) {
                    output.push("0");
                }
            }
            while (!operatorStack.empty() && operatorStack.top()->_value != "(" &&
                   ((operatorStack.top()->_priority > curToken->_priority) || operatorStack.top()->_priority == curToken->_priority &&
                                                                                      curToken->_associativity == Operator::Associativity::Left)) {
                output.push(operatorStack.top()->_value);
                operatorStack.pop();
            }
            operatorStack.push(curToken);
        }
        if (token == "(") {
            operatorStack.push(&operators.at(token));
            flag = true;
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
            flag = false;
        }
    }
    while (!operatorStack.empty()) {
        output.push(operatorStack.top()->_value);
        operatorStack.pop();
    }
    return output;
}

float calculate(const std::string& input) {
    vector<string> tokens = tokenise(input);
    std::queue<string> output = shuntingYard(tokens);
    std::queue<string> output1 = output;
    while (!output1.empty()) {
        output1.pop();
    }
    std::stack <float> result;
    while (!output.empty()) {
        string token = output.front();
        output.pop();
        if (isNumber(token)) {
            result.push(stof(token));
        }
        if (isOperator(token)) {
            float b = result.top();
            result.pop();
            if (result.size() == 0) {
                throw;
            }
            float a = result.top();
            result.pop();
            result.push(operators.at(token)._function(a, b));
        }
    }
    if (result.size() > 1) {
        throw;
    }
    return result.top();
}
