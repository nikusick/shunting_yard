#include "Token.h"

#include <cmath>

float add(std::vector<float> args) {
    return args[0] + args[1];
}

float substract(std::vector<float> args) {
    return args[1] - args[0];
}

float multiply(std::vector<float> args) {
    return args[0] * args[1];
}

float divide(std::vector<float> args) {
    return args[1] / args[0];
}

float raisePow(std::vector<float> args) {
    return pow(args[1], args[0]);
}

float unarySubstract(std::vector<float> args) {
    return -args[0];
}

float takeSin(std::vector<float> args) {
    return sin(args[0]);
}

float takeCos(std::vector<float> args) {
    return cos(args[0]);
}
