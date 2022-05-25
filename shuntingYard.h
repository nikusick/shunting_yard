#ifndef SHUNTINGYARDALGORITHM_SHUNTINGYARD_H
#define SHUNTINGYARDALGORITHM_SHUNTINGYARD_H

#include <string>
#include <vector>
#include <sstream>
#include <cstring>
#include <map>
#include <queue>
#include <variant>
#include <cmath>

#include "operator.h"

bool isNumber(const std::string& token);
bool isOperator(const std::string& token);

std::vector<std::string> tokenise(const std::string& input);

std::queue<std::string> shuntingYard(const std::vector<std::string>& tokens);

float calculate(const std::string& input);

#endif //SHUNTINGYARDALGORITHM_SHUNTINGYARD_H
