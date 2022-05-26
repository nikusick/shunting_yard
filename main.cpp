#include "shuntingYard.h"

#include <iostream>

using namespace std;

int main() {
    //string str = "14 / ( 2 +5 ) * ( 10 / ( 7 - 2 ) ) ^ 2";
    //string str = "3+4*2/(1+(- 5))^2^3";
    //string str = "-4.5^( -2)";
    //string str = "(-1)-2*((-3)-(-4)-5+(-6))-7";
    //string str = "1/2+(2+3)/(sin(9-2)^2-6/7)^(13-9)";
    //string str = "17+1/2-(2+3)/(6/7^2)*17-9*(6*(6+sin(5))) + cos(6)^2";
    string str = "cos((5-2)^2*(58*8^2)^2)";
    cout << calculate(str) << endl;
    return 0;
}