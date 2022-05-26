#include "shuntingYard.h"

#include <map>
#include <stack>
#include <stdexcept>

using namespace std;

using type = Token::Type;
using assoc = Token::Associativity;

std::map<std::string, Token> _tokens = {
        {"+", Token{"+", type::Operator, 2,
                    &add, 1, assoc::Left}},
        {"-", Token{"-", type::Operator, 2,
                    &substract, 1, assoc::Left}},
        {"*", Token{"*", type::Operator, 2,
                    &multiply, 2, assoc::Left}},
        {"/", Token{"/", type::Operator, 2,
                    &divide, 2, assoc::Left}},
        {"^", Token{"^", type::Operator, 2,
                    &raisePow, 3, assoc::Right}},
        {"~", Token{"~", type::Operator, 1,
                    &unarySubstract, 4, assoc::Left}},
        {"(", Token{"(", type::Bracket}},
        {")", Token{")",type::Bracket}},
        {"sin", Token{"sin", type::Function, 1, &takeSin}},
        {"cos", Token{"cos", type::Function, 1, &takeCos}},
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
    result.emplace_back("");
    for (auto&& item: input) {
        if (_tokens.find(string(1, item)) != _tokens.end()) {
            result.emplace_back(1, item);
            result.emplace_back("");
        }
        else {
            if (item != ' ') {
                result.back() += item;
            }
        }
    }
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
        Token curToken = _tokens.at(token);
        if (isFunction(curToken)) {
            operatorStack.push(curToken);
        }
        if (isOperator(curToken) &&
        token != "(" && token != ")") {
            if (token == "-" && canAddUnarOperator) {
                if (!operatorStack.empty() &&
                operatorStack.top()._value == "(") {
                    curToken = _tokens.at("~");
                }
                else if (output.empty()) {
                    output.push(Token{"0", type::Number});
                }
            }
            while (!operatorStack.empty() &&
            operatorStack.top()._value != "(" &&
            (isFunction(operatorStack.top()) ||
            operatorStack.top()._priority > curToken._priority ||
            operatorStack.top()._priority == curToken._priority &&
            curToken._associativity == assoc ::Left)) {
                addFromStackToOutput(output, operatorStack);
            }
            operatorStack.push(curToken);
        }
        if (token == "(") {
            operatorStack.push(curToken);
            canAddUnarOperator = true;
        }
        if (token == ")") {
            while (!operatorStack.empty() &&
            operatorStack.top()._value != "(") {
                addFromStackToOutput(output, operatorStack);
            }
            if (operatorStack.empty()) {
                throw;
            }
            operatorStack.pop();
            canAddUnarOperator = false;
        }
    }
    while (!operatorStack.empty()) {
        addFromStackToOutput(output, operatorStack);
    }
    return output;
}

float calculate(const std::string& input) {
    vector<string> tokens = tokenise(input);
    std::queue<Token> output = shuntingYard(tokens);
    std::stack <float> result;
    while (!output.empty()) {
        Token token = output.front();
        output.pop();
        if (token._type == type::Number) {
            result.push(stof(token._value));
        }
        if (isOperator(token) || isFunction(token)) {
            vector <float> args;
            for (int i = 0; i < token._args; ++i) {
                if (result.empty()) {
                    throw;
                }
                args.push_back(result.top());
                result.pop();
            }
            result.push(token._function(args));
        }
    }
    if (result.size() > 1) {
        throw;
    }
    return result.top();
}
