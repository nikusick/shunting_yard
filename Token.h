#ifndef SHUNTINGYARDALGORITHM_TOKEN_H
#define SHUNTINGYARDALGORITHM_TOKEN_H

#include <string>
#include <vector>

struct Token {
    std::string _value;
    enum class Type {
        Number,
        Operator,
        Function,
        Bracket,
    };
    enum class Associativity {
        Right,
        Left,
    };
    Type _type;
    int _args;
    float(* _function)(std::vector<float>);
    int _priority;
    Associativity _associativity;
};


float add(std::vector<float>);
float substract(std::vector<float>);
float multiply(std::vector<float>);
float divide(std::vector<float>);
float raisePow(std::vector<float>);
float unarySubstract(std::vector<float>);
float takeSin(std::vector<float>);
float takeCos(std::vector<float>);

#endif //SHUNTINGYARDALGORITHM_TOKEN_H
