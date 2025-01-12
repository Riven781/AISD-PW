#ifndef __UTILS__H__
#define __UTILS__H__

#include <string>
#include <vector>
#include "onp.h"

void printSpaces(int i);
std::vector<wchar_t> splitWStringToChars(const std::wstring& input);
void displayExpression(std::wstring expressionList);
std::wstring convertFromLatex(std::string);

#endif  //!__UTILS__H__