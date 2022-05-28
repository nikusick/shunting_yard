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
        None,
    };
    enum class Associativity {
        Right,
        Left,
    };
    Type _type;
    int _args;
    double(* _function)(std::vector<double>);
    int _priority;
    Associativity _associativity;
};


double add(std::vector<double>);
double substract(std::vector<double>);
double multiply(std::vector<double>);
double divide(std::vector<double>);
double raisePow(std::vector<double>);
double takeSin(std::vector<double>);
double takeCos(std::vector<double>);

#endif //SHUNTINGYARDALGORITHM_TOKEN_H
