#ifndef RPN
#define RPN

#include <vector>
#include <string>

int rpn(const std::vector<std::string>& input);

bool isInt(const std::string& strWejsciowy);

bool isOperator(const std::string& strWejsciowy);

#endif // !RPN
