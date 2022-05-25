#include <iostream>
#include<string>
#include "shuntingYard.h"

using namespace std;

int main() {
    //string str = "14 / ( 2 +5 ) * ( 10 / ( 7 - 2 ) ) ^ 2";
    //string str = "3+4*2/(1+(-5))^2^3";
    string str = "-4.5 ^( -2)";
    //string str = "(-1)-2*((-3)-( -4)-5+(-6))-7";
    cout << calculate(str);
    return 0;
}
