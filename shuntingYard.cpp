#include "shuntingYard.h"

#include <iostream>
#include <map>
#include <stack>
#include <stdexcept>

using namespace std;

using type = Token::Type;
using assoc = Token::Associativity;

namespace
{
    const std::map<std::string, Token> Tokens = {
            {"+", Token {"+", type::Operator, 2,&add, 1, assoc::Left}},
            {"-", Token {"-", type::Operator, 2,&substract, 1, assoc::Left}},
            {"*", Token {"*", type::Operator, 2,&multiply, 2, assoc::Left}},
            {"/", Token {"/", type::Operator, 2,&divide, 2, assoc::Left}},
            {"^", Token {"^", type::Operator, 2,&raisePow, 3, assoc::Right}},
            {"(", Token {"(", type::Bracket}},
            {")", Token {")",type::Bracket}},
            {"sin", Token {"sin", type::Function, 1, &takeSin}},
            {"cos", Token {"cos", type::Function, 1, &takeCos}},
    };
}


bool isNumber(const string& token) {
    try {
        if (std::count(token.begin(), token.end(), '.') > 1 ||
                std::count(token.begin(), token.end(), ',') > 0 ||
                std::find(token.begin(), token.end(), '.') == token.begin()) {
            throw invalid_argument("Incorrect Number");
        }
        stof(token);
        return true;
    }
    catch (invalid_argument&){
        return false;
    }
}

bool isFunction(Token& token) {
    return token._type == type::Function;
}

bool isOperator(Token& token) {
    return token._type == type::Operator;
}

void addFromStackToOutput(queue<Token>& output, stack<Token>& operatorStack) {
    output.push(operatorStack.top());
    operatorStack.pop();
}

vector<string> tokenise(const string& input)
{
    vector<string> result;
    std::string token;
    type cur_type = type::None;
    type last_type = type::None;
    for (auto&& symbol: input) {
        if (symbol == ' ') {
            last_type = type::None;
            continue;
        }
        else if (isalpha(symbol)) {
            cur_type = type::Function;
        }
        else if (symbol == '(' || symbol == ')') {
            cur_type = type::Bracket;
        }
        else if (Tokens.find(string(1, symbol)) != Tokens.end()) {
            cur_type = type::Operator;
        }
        else if (isdigit(symbol) || symbol == '.') {
            cur_type = type::Number;
        }
        if (!token.empty() && (cur_type != last_type
            || cur_type == last_type && last_type == type::Bracket)) {
            if (last_type == type::Function && cur_type == type::Number ||
                    cur_type == type::Function && last_type == type::Number) {
                throw invalid_argument("Between numbers and functions must be an operator!");
            }
            result.push_back(token);
            token = symbol;
        }
        else {
            token += symbol;
        }
        last_type = cur_type;
    }
    result.push_back(token);
    return result;
}

std::queue<Token> shuntingYard(const vector<string>& input) {
    std::queue<Token> output;
    std::stack<Token> operatorStack;
    bool canAddUnarOperator = true;
    for (auto&& token: input) {
        if (token.empty()) {
            continue;
        }
        if (isNumber(token)) {
            output.push(Token{token, type::Number});
            canAddUnarOperator = false;
            continue;
        }
        if (Tokens.find(token) != Tokens.end()) {
            Token curToken = Tokens.at(token);
            if (isFunction(curToken)) {
                operatorStack.push(curToken);
            }
            else if (isOperator(curToken)) {
                if (token == "-" && canAddUnarOperator) {
                        output.push(Token{"0", type::Number});
                }
                while (!operatorStack.empty() && operatorStack.top()._value != "(" &&
                    (isFunction(operatorStack.top()) ||
                    operatorStack.top()._priority > curToken._priority ||
                    operatorStack.top()._priority == curToken._priority &&
                    curToken._associativity == assoc ::Left)) {
                    addFromStackToOutput(output, operatorStack);
                }
                operatorStack.push(curToken);
            }
            else if (token == "(") {
                operatorStack.push(curToken);
                canAddUnarOperator = true;
            }
            else if (token == ")") {
                while (!operatorStack.empty() &&
                operatorStack.top()._value != "(") {
                    addFromStackToOutput(output, operatorStack);
                }
                if (operatorStack.empty()) {
                    throw out_of_range("Extra ')'!");
                }
                operatorStack.pop();
                canAddUnarOperator = false;
            }
        }
        else {
            throw out_of_range("Invalid token!");
        }
    }
    while (!operatorStack.empty()) {
        addFromStackToOutput(output, operatorStack);
    }
    return output;
}

vector<double> takeArgs(int argsCount, std::stack<double>& result) {
    vector<double> args;
    for (int i = 0; i < argsCount; ++i) {
        if (result.empty()) {
            throw out_of_range("Incorrect number of arguments!");
        }
        args.push_back(result.top());
        result.pop();
    }
    return args;
}

double calculate(const std::string& input) {
    try {
        vector<string> tokens = tokenise(input);
        std::queue<Token> output = shuntingYard(tokens);
        std::stack<double> result;
        while (!output.empty()) {
            Token token = output.front();
            output.pop();
            if (token._type == type::Number) {
                result.push(stof(token._value));
            }
            if (isOperator(token) || isFunction(token)) {
                result.push(token._function(takeArgs(token._args, result)));
            }
        }
        if (result.size() > 1) {
            throw out_of_range("Incorrect number of arguments!");
        }
        return result.top();
    }
    catch (const string& error) {
        cout << error;
    }
    return 0;
}
