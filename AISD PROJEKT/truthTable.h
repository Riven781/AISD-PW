#ifndef __GENERATETRUTHTABLE__H__
#define __GENERATETRUTHTABLE__H__

#include <iostream>
#include "onp.h"

std::vector<LogicVariable> generateTruthTable(std::string strExpression, bool display = true, bool onlyResult = false);
void displayTruthTable(std::vector<LogicVariable> logicVariables, int rowsNumber);

#endif  //!__GENERATETRUTHTABLE__H__