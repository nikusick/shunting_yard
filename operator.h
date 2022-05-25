#ifndef SHUNTINGYARDALGORITHM_OPERATOR_H
#define SHUNTINGYARDALGORITHM_OPERATOR_H

#include <string>
#include <cmath>

struct Operator {
    std::string _value;
    enum class Associativity {
        Right,
        Left,
    };
    Associativity _associativity;
    int _priority;
    float(*_function)(float, float);
};


float add(float a, float b);
float substract(float a, float b);

float multiply(float a, float b);

float divide(float a, float b);

float raisePow(float a, float b);

#endif //SHUNTINGYARDALGORITHM_OPERATOR_H
