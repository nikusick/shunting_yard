#ifndef SHUNTINGYARDALGORITHM_SHUNTINGYARD_H
#define SHUNTINGYARDALGORITHM_SHUNTINGYARD_H

#include "Token.h"

#include <queue>

std::vector<std::string> tokenise(const std::string& input);

std::queue<Token> shuntingYard(const std::vector<std::string>& tokens);

double calculate(const std::string& input);

#endif //SHUNTINGYARDALGORITHM_SHUNTINGYARD_H
