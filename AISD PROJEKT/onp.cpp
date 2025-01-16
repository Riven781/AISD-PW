#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <map>
#include <algorithm>
#include <math.h>
#include "logicvariable.h"
#include "utils.h"

using namespace std;

const std::map<wchar_t, std::string> CONVERT_SYMBOL_MAP = {{L'⇒', "->"}, {L'⇔', "<=>"}, {L'∧', "^"}, {L'∨', "v"}, {L'¬',"~"}, {L'⊕', "@"}};
const vector<wchar_t>  operators = {L'¬',L'∧',L'∨',L'⇒', L'⇔',L'⊕'};
const vector<char> variables  = {'p', 'q', 'r', 's', 't', 'u', 'w', 'z', 'x'};

vector<wchar_t> convertToONP(wstring expression){
    int priorities [] = {7,6,5,4,3,2};
    stack<wchar_t> operatorsStack;
    stack<int> priorityStack;
    vector<wchar_t> expressionList = splitWStringToChars(expression);
    vector<wchar_t> finalExpressionList;

    for(auto symbol : expressionList)
    {
        auto it = find(operators.begin(), operators.end(), symbol); //przyda sie dopiero w linijce 51 jest to zastapienie:  else if (auto it = find(operators.begin(), operators.end(), symbol); it != operators.end())

        if (find(variables.begin(), variables.end(), symbol) != variables.end()){
            finalExpressionList.push_back(symbol);
        }
        else if (symbol == '('){
            operatorsStack.push('(');
            priorityStack.push(1);
        }
        else if (symbol == ')'){
            while (operatorsStack.top() != '(')
            {
                finalExpressionList.push_back(operatorsStack.top());
                operatorsStack.pop();
                priorityStack.pop();
            }
            operatorsStack.pop();
            priorityStack.pop();
            
        }
        else if ( it != operators.end())
        {
            int priority = priorities[distance(operators.begin(), it)];
            if (operatorsStack.empty()){
                operatorsStack.push(*it);
                priorityStack.push(priority);

            }
            else{
                
                if (priority > priorityStack.top() || (symbol == L'¬' && operatorsStack.top() == L'¬')){
                    operatorsStack.push(*it);
                    priorityStack.push(priority);
                }
                else{
                    while (priority <= priorityStack.top())
                    {
                        finalExpressionList.push_back(operatorsStack.top());
                        priorityStack.pop();
                        operatorsStack.pop();
                        if (priorityStack.empty()){
                            break;
                        }
                    }
                    
                    operatorsStack.push(*it);
                    priorityStack.push(priority);
                    
                }
            }
        }
    }
    while(!operatorsStack.empty()){
        finalExpressionList.push_back(operatorsStack.top());
        operatorsStack.pop();
        priorityStack.pop();
    }

    return finalExpressionList;
}

void displayONP(vector<wchar_t> expressionList){
    for (wchar_t symbol : expressionList){
        auto it = CONVERT_SYMBOL_MAP.find(symbol); 
        if (it != CONVERT_SYMBOL_MAP.end()){
            std::cout << it->second;
        }
        else
        {
            std::cout << (char)symbol;
        }
    }
    std::cout << std::endl;
}



std::vector<LogicVariable> getListOfVariable(std::vector<wchar_t> expressionList){
    vector<string> listOfNameVariable;
    vector<LogicVariable> listOfVariable;
    for(auto symbol : expressionList)
    {
        if (find(operators.begin(), operators.end(), symbol) == operators.end()){
            auto it = std::find(listOfNameVariable.begin(), listOfNameVariable.end(), string(1,symbol));
            if (it == listOfNameVariable.end()){
                listOfNameVariable.push_back(string(1, symbol));
            }
        }
    }
    int size = listOfNameVariable.size();

    for (int i = 0; i < size; i++)
    {
        listOfVariable.push_back(LogicVariable(listOfNameVariable.at(i), pow(2, size), pow(2, i)));
    }    
    return listOfVariable;
}










vector<LogicVariable> getResult(std::vector<wchar_t> expressionList, vector<LogicVariable> logicVariables,bool onlyResult){
    std::map<char, vector<int>> convertSymbolsMap;
    stack<LogicVariable> variablesStack;
    vector<LogicVariable> resultWithSteps = logicVariables;

    for(auto symbol : expressionList)
    {
        if(find(variables.begin(), variables.end(), symbol) != variables.end()){  //wlozenie LogicVariable na stos operandow
            variablesStack.push( *find_if(logicVariables.begin(), logicVariables.end(), [&symbol](const LogicVariable& variable) {
                return variable.getName() == string(1, symbol);
            }));
        }
        else if(symbol == L'∧'){
            LogicVariable var1 = variablesStack.top();
            variablesStack.pop();
            LogicVariable var2 = variablesStack.top();
            variablesStack.pop();

            variablesStack.push( var2.conjunction(var1));
            if (!onlyResult)
            {
                resultWithSteps.push_back(variablesStack.top());
            }
            
        }
        else if(symbol == L'∨'){
            LogicVariable var1 = variablesStack.top();
            variablesStack.pop();
            LogicVariable var2 = variablesStack.top();
            variablesStack.pop();

            variablesStack.push( var2.alternative(var1));
            if (!onlyResult){
                resultWithSteps.push_back(variablesStack.top());
            }
            
        }
        else if(symbol == L'⇒'){
            LogicVariable var1 = variablesStack.top();
            variablesStack.pop();
            LogicVariable var2 = variablesStack.top();
            variablesStack.pop();

            variablesStack.push( var2.implication(var1));
            if (!onlyResult){
                resultWithSteps.push_back(variablesStack.top());
            }
            

        }
        else if(symbol == L'⇔'){
            LogicVariable var1 = variablesStack.top();
            variablesStack.pop();
            LogicVariable var2 = variablesStack.top();
            variablesStack.pop();

            variablesStack.push( var2.equivalence(var1));
            if(!onlyResult){
                resultWithSteps.push_back(variablesStack.top());
            }
            
        }
        else if(symbol == L'⊕'){
            LogicVariable var1 = variablesStack.top();
            variablesStack.pop();
            LogicVariable var2 = variablesStack.top();
            variablesStack.pop();

            variablesStack.push( var2.exclusiveOr(var1));
            if (!onlyResult){
                resultWithSteps.push_back(variablesStack.top());
            }


        }
        else if(symbol == L'¬'){
            LogicVariable var1 = variablesStack.top();
            variablesStack.pop();
            variablesStack.push( var1.negation());
            if (!onlyResult){
                resultWithSteps.push_back(variablesStack.top());
            }
        }
    }

    if (onlyResult)
    {
        resultWithSteps.push_back(variablesStack.top());
    }
    


    return resultWithSteps;

}



