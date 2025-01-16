#include "logicvariable.h"
#include <iostream>
#include <string>
#include "onp.h"

using namespace std;


LogicVariable::LogicVariable(string name, int size, int step) : name(name), size(size),  values(nullptr){
    values = new int[size]{0};
    setValues(step);

};

LogicVariable::~LogicVariable(){
    if(values != nullptr){
        delete [] values;
    }
    
}

LogicVariable::LogicVariable(LogicVariable&& other) noexcept
    : name(std::move(other.name)), size(other.size), values(other.values) {
    other.size = 0;
    other.values = nullptr;
}

LogicVariable::LogicVariable(const LogicVariable& other)
    : name(other.name), size(other.size), values(nullptr) {
    if (size > 0) {
        values = new int[size];
        std::copy(other.values, other.values + size, values);
    }
}

void LogicVariable::setValues(int step){
    bool set1 = true;
    for (int i = 0; i < size; ++i){
        if (i % step == 0){
            set1 = !set1;
        }
        if (set1)
        {
            values[i] = 1;
        }
    }
}

string LogicVariable::addName(string otherName, string operator1){
    string newName;
    if (name.size() == 1 && otherName.size() == 1){
        newName = name  + " " + operator1 + " " + otherName;
    }
    else if (name.size() == 1){
        newName = name  + " " + operator1 + " " + "(" + otherName + ")";
    }
    else if(otherName.size() == 1){
        newName = "(" +  name + ")"  + " " + operator1 + " " + otherName;
    }
    else{
        newName = "(" +  name + ")"  + " " + operator1 + "(" + otherName + ")";
    }
    return newName;
}


void LogicVariable::setValues(int * values){
    this->values = values;
}

string LogicVariable::getName() const{
    return name;
}

int* LogicVariable::getValues() const{
    return values;
}


void LogicVariable::displayValues(){
    for (int i = 0; i < size; i++)
    {
        std::cout << values[i] << std::endl;
    }
    
}


LogicVariable LogicVariable::conjunction(LogicVariable& other ){
    LogicVariable resultVariable(size);
    int * newValues = new int[size];
    for (int i = 0; i < size; i++)
    {
        newValues[i] = values[i] && other.values[i];
    }
    resultVariable.values = newValues;


    resultVariable.name = addName(other.name, CONVERT_SYMBOL_MAP.at(L'∧'));

    return resultVariable;
    
}

LogicVariable LogicVariable::alternative(LogicVariable& other ){
    LogicVariable resultVariable(size);
    int * newValues = new int[size];
    for (int i = 0; i < size; i++)
    {
        newValues[i] = values[i] || other.values[i];
    }
    resultVariable.values = newValues;

   

    resultVariable.name = addName(other.name, CONVERT_SYMBOL_MAP.at(L'∨'));

    return resultVariable;
}

LogicVariable LogicVariable::implication(LogicVariable& other ){
    LogicVariable resultVariable(size);
    int * newValues = new int[size];
    for (int i = 0; i < size; i++)
    {
        if ( (values[i] == 1) && (other.values[i] == 0)){
            
            newValues[i] = 0;
        }
        else{
            newValues[i] = 1;
        }

    }
    resultVariable.values = newValues;

    resultVariable.name = addName(other.name, CONVERT_SYMBOL_MAP.at(L'⇒'));
    return resultVariable;
}



LogicVariable LogicVariable::equivalence(LogicVariable& other ){
    LogicVariable resultVariable(size);
    int * newValues = new int[size];
    for (int i = 0; i < size; i++)
    {
        newValues[i] = values[i] == other.values[i];
    }
    resultVariable.values = newValues;


    resultVariable.name = addName(other.name, CONVERT_SYMBOL_MAP.at(L'⇔'));

    return resultVariable;
}


LogicVariable LogicVariable::negation(){
    LogicVariable resultVariable(size);
    int * newValues = new int[size];
    for (int i = 0; i < size; i++)
    {
        newValues[i] =  !values[i];
    }
    resultVariable.values = newValues;

    if (name.size() == 1)
    {
        resultVariable.name = CONVERT_SYMBOL_MAP.at(L'¬') + " " + name;
    }
    else{
        resultVariable.name = CONVERT_SYMBOL_MAP.at(L'¬') + " (" + name + ")";
    }
    

    

    return resultVariable;
}


LogicVariable LogicVariable::exclusiveOr (LogicVariable & other){
LogicVariable resultVariable(size);
    int * newValues = new int[size];
    for (int i = 0; i < size; i++)
    {
        newValues[i] = !(values[i] == other.values[i]);
    }
    resultVariable.values = newValues;

    resultVariable.name = addName(other.name, CONVERT_SYMBOL_MAP.at(L'⊕'));

    return resultVariable;

}

