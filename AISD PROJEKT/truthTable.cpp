#include "onp.h"
#include "truthTable.h"
#include "utils.h"
#include <vector>
#include <math.h>



std::vector<LogicVariable> generateTruthTable(std::string strExpression,bool display, bool onlyResult){
    std::wstring expression = convertFromLatex(strExpression);
    std::vector<wchar_t> postfixNotation =convertToONP(expression);
    std::vector<LogicVariable> logicVariables = getListOfVariable(postfixNotation);
    std::vector<LogicVariable> result = getResult(postfixNotation, logicVariables, onlyResult);
    if (display){
        displayTruthTable(result, pow(2, logicVariables.size()));
    }    
    return result;
    

}


void displayTruthTable(std::vector<LogicVariable> logicVariables, int rowsNumber){
    std::vector<int> scopeSize;

    for (size_t i = 0; i < logicVariables.size(); i++)
    {
        std::cout << logicVariables.at(i).getName() << " | ";
        scopeSize.push_back(logicVariables.at(i).getName().size());
    }
    std::cout << std::endl;

    for (int i = 0; i < rowsNumber; i++)
    {
        for (size_t j = 0; j < logicVariables.size(); j++)
        {
            //std::cout << "spacje:" << scopeSize.at(j) << std::endl;
            int addSpaces = 0;
            if(scopeSize.at(j) != 0){
                addSpaces = scopeSize.at(j)/2;
            }

            if(scopeSize.at(j) != 0 && scopeSize.at(j) % 2 == 0){
                printSpaces(addSpaces - 1);
            }
            else{
                printSpaces(addSpaces);
            }
            
            
            
            std::cout << logicVariables.at(j).getValues()[i] << "";

            printSpaces(addSpaces);

            std::cout << " | ";
        }

        std::cout << std::endl;
           
    }
}