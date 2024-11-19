#include "rpnTest.h"
#include "rpn.h"
#include "cassert"
#include <vector>
#include <iostream>

using namespace std;

void rpnTest(){

    //TEST: (2+3)*6  = 30
    assert(rpn(vector<string>{"2", "3", "+", "6", "*"}) == 30);

    //TEST: 6/2 = 3
    assert(rpn(vector<string>{"6", "2", "/"}) == 3);

    //TEST: 4-(-2) = 6
    assert(rpn(vector<string>{"4", "-" "2", "-"}) == 6); 

    //TEST: (3+4)*20-9 = 131
    assert(rpn(vector<string>{"3", "4", "+", "20", "*", "9", "-"}) == 131);

    //TEST: 3-4-5-6-7*2 = -26
    assert(rpn(vector<string>{"3", "4", "-", "5", "-", "6", "-", "7", "2", "*", "-"}) == -26);

    //TEST: (10+20)/10-(60-40)/10 = 1
    assert(rpn(vector<string>{"10", "20", "+", "10", "/", "60", "40", "-", "10", "/", "-"}) == 1);

    //TEST: 25+25/5+13/13-100/2+2*2 = -15
    assert(rpn(vector<string>{"25", "25", "5", "/", "+", "13", "13", "/", "+", "100", "2", "/", "-", "2", "2", "*", "+"}) == -15);

    
    std::cout << "Testy zostaly zakonczone pomyslnie" << std::endl;

    
}