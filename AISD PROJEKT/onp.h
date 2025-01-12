#ifndef ONP_H
#define ONP_H

#include <vector>
#include "logicvariable.h"

extern const std::map<wchar_t, std::string> CONVERT_SYMBOL_MAP;
extern const std::vector<wchar_t>  operators;
extern const std::vector<char>  variables;

std::vector<wchar_t> convertToONP(std::wstring expression);
void displayONP(std::vector<wchar_t> expressionList);
std::vector<LogicVariable> getResult(std::vector<wchar_t> expressionList, std::vector<LogicVariable> logicVariables, bool onlyResult);
std::vector<LogicVariable> getListOfVariable(std::vector<wchar_t> expressionList);


#endif // !ONP_H
