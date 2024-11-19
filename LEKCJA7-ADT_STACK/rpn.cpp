#include "rpn.h"
#include <iostream>
#include <stack>
#include <cctype>

using namespace std;

int rpn(const std::vector<std::string>& input){
    stack<string> stos;
    for (const auto& w : input) {
        if (isInt(w)){
            stos.push(w);
        }
        else if (isOperator(w))
        {
            int a = stoi(stos.top());
            stos.pop();
            int b = stoi(stos.top());
            stos.pop();
            if (w == "/"){
                stos.push(to_string(b/a));
            }
            else if (w == "*"){
                stos.push(to_string(b*a));
            }
            else if (w == "-")
            {
                stos.push(to_string(b-a));
            }
            else{
                stos.push(to_string(b+a));
            }

        }
        else{
            std::cout << "ERROR: Nie zidentyfikowany symbol" << std::endl;
            return 0;
        }
            
    }

    return stoi(stos.top());
}


bool isInt(const std::string& strWejsciowy){
    if (strWejsciowy.empty()) return false;
    std::size_t i = 0;
    if (strWejsciowy.at(0) == '-') i =1;
    if (i == 1 && strWejsciowy.length() == 1) return false;

    for(; i < strWejsciowy.length(); ++i){
        if (!std::isdigit(strWejsciowy.at(i))) return false;
    }

    return true;
}

bool isOperator(const std::string& strWejsciowy){
    if (strWejsciowy == "/" || strWejsciowy == "*" || strWejsciowy == "-"  || strWejsciowy == "+" ) return true;
    return false;

}
