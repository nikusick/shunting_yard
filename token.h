#ifndef SHUNTINGYARDALGORITHM_TOKEN_H
#define SHUNTINGYARDALGORITHM_TOKEN_H

#include<string>

struct Number {
    float _value;
};

struct Operator {
    std::string _value;
    int _args;
    enum class Associativity {
        Right,
        Left,
    };
    Associativity _associativity;
    int _priority;
};


#endif //SHUNTINGYARDALGORITHM_TOKEN_H
