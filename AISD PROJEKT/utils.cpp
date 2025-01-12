#include <iostream>
#include "utils.h"
#include <vector>
#include <map>
#include "onp.h"

using namespace std;

void printSpaces(int i){
    for (int k = 0; k < i; k++)
    {
        std::cout << " ";
    }
}

vector<wchar_t> splitWStringToChars(const wstring& input) {
    vector<wchar_t> result;
    for (wchar_t ch : input) {
        result.push_back(ch);
    }
    return result;
}


void displayExpression(wstring expressionList){
    for (wchar_t symbol : expressionList){
        auto it = CONVERT_SYMBOL_MAP.find(symbol);
        if (it != CONVERT_SYMBOL_MAP.end()){
            std::cout << it->second;
        }
        else
        {
            if (iswspace(symbol)){
                continue;
            }
            std::cout << (char)symbol;
        }
    }
    std::cout << std::endl;
}


std::wstring convertFromLatex(std::string expression){
    std::wstring wExpression(expression.begin(), expression.end());
    std::map<std::wstring, wchar_t> latexSymbols = {
        {L"\\\\neg", L'¬'},
        {L"\\\\and", L'∧'},
        {L"\\\\or", L'∨'},
        {L"\\\\impl", L'⇒'},
        {L"\\\\equi", L'⇔'},
        {L"\\\\xor", L'⊕'}
    };
    for (const auto& latexSymbol : latexSymbols)
    {
        size_t pos = 0;
        while ((pos = wExpression.find(latexSymbol.first, pos)) != std::wstring::npos) {
            wExpression.replace(pos, latexSymbol.first.length(), 1, latexSymbol.second);
            pos += 1;
        }
    }

    return wExpression;
    
}