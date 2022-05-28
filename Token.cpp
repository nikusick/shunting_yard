#include "Token.h"

#include <cmath>

double add(std::vector<double> args) {
    return args[0] + args[1];
}

double substract(std::vector<double> args) {
    return args[1] - args[0];
}

double multiply(std::vector<double> args) {
    return args[0] * args[1];
}

double divide(std::vector<double> args) {
    return args[1] / args[0];
}

double raisePow(std::vector<double> args) {
    return pow(args[1], args[0]);
}

double takeSin(std::vector<double> args) {
    return sin(args[0]);
}

double takeCos(std::vector<double> args) {
    return cos(args[0]);
}
