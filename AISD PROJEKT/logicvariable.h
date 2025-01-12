#ifndef LOGIC_VARIABLE_H
#define LOGIC_VARIABLE_H

#include <string>
#include <vector>
#include <map>

class LogicVariable
{
private:
    std::string name;
    int size;
    //std::vector<int> values;
    int * values;

    std::string addName(std::string otherName, std::string operator1);


public:
    LogicVariable(std::string name, int size, int step);

    LogicVariable( int size) : size(size), values(nullptr){}

    ~LogicVariable();

    LogicVariable(const LogicVariable& other);


    LogicVariable(LogicVariable&& other) noexcept;

    void setName(char name);
    std::string getName() const;

    void setValues(int step);
    void setValues(int * values);
    int * getValues() const;

    void displayValues();


    LogicVariable conjunction(LogicVariable & other);
    LogicVariable alternative(LogicVariable & other);
    LogicVariable exclusiveOr (LogicVariable & other);
    LogicVariable implication(LogicVariable & other);
    LogicVariable equivalence(LogicVariable & other);
    LogicVariable negation();


};

#endif // !LOGIC_VARIABLE
