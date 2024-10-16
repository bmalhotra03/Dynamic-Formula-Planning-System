// Author: Brij Malhotra
// Filename: ExecutablePlan.cpp
// Version: 1
// Description: Child class of Plan, class implementation here

#include "ExecutablePlan.h"
#include <iostream>

using namespace std;

// Constructor
ExecutablePlan::ExecutablePlan(int size, Formula initialFormulas[]) : Plan(size, initialFormulas)
{
    currentStep = 0;
}

// Copy constructor
ExecutablePlan::ExecutablePlan(const ExecutablePlan& obj) : Plan(obj)
{
    currentStep = obj.currentStep;
}

// Move constructor
ExecutablePlan::ExecutablePlan(ExecutablePlan&& obj) : Plan(move(obj))
{
    currentStep = obj.currentStep;
    obj.currentStep = 0;
}

// Assignment operator
void ExecutablePlan::operator=(const ExecutablePlan& obj)
{
    if (this != &obj)
    {
        Plan::operator=(obj);
        currentStep = obj.currentStep;
    }
}

// Move assignment operator
void ExecutablePlan::operator=(ExecutablePlan&& obj)
{
    Plan::operator=(move(obj));
    currentStep = obj.currentStep;
    obj.currentStep = 0;
}

// Destructor
ExecutablePlan::~ExecutablePlan() { }

// Overridden client methods
shared_ptr<Stockpile> ExecutablePlan :: applyFormula(int index, std::shared_ptr<Stockpile> stockpile) {
    // Check if the index is within the valid range of formulas
    if (index < 0 || index >= getNumFormulas()) {
        throw std::out_of_range("Index is out of range of the formulas array.");
    }

    // Get the required quantity from the formula at the index
    int quantityNeeded = *formulas[index].getInputQuantity();

    // Check if stockpile has enough resources
    if (stockpile->hasResources(index, quantityNeeded)) {
        // Deduct resources from stockpile
        stockpile->deductResource(index, quantityNeeded);

        formulas[index].apply(formulas[index].getInputQuantity(), formulas[index].getInputName());
        currentStep++;
        return stockpile;
        
    } else {
        throw runtime_error("Insufficient resources in stockpile to apply formula.");
    }

}

void  ExecutablePlan::replaceFormula(int index, const Formula& formula)
{
    if (index >= currentStep)
    {
        Plan::replaceFormula(index, formula);
    }
    else
    {
        throw invalid_argument("Cannot replace a formula that has already been applied.");
    }
}

void ExecutablePlan::removeLastFormula() 
{

    if (getNumFormulas() == 0)
    {
        throw invalid_argument("Cannot remove the last formula if it has already been completed.");
    }
    else if (getNumFormulas() - 1 >= currentStep)
    {
        Plan::removeLastFormula();
    }
    else
    {
        // Do nothing
    }
}

int ExecutablePlan::getCurrentStep()
{
    return currentStep;
}

// Operator overloading for addition (ExecutablePlan with unsigned int)
ExecutablePlan ExecutablePlan::operator+(unsigned int x) const {
    ExecutablePlan result = *this;
    for (int i = 0; i < this->numFormulas; ++i) {
        result.formulas[i].inputQuantityClass += x;
    }
    return result;
}

// Operator overloading for addition (ExecutablePlan with another ExecutablePlan)
ExecutablePlan ExecutablePlan::operator+(const ExecutablePlan& obj) const {
    int newSize = this->numFormulas + obj.numFormulas;
    Formula* combinedFormulas = new Formula[newSize];
    for (int i = 0; i < this->numFormulas; ++i) {
        combinedFormulas[i] = this->formulas[i];
    }
    for (int i = 0; i < obj.numFormulas; ++i) {
        combinedFormulas[this->numFormulas + i] = obj.formulas[i];
    }
    ExecutablePlan result;
    result.formulas = combinedFormulas;
    result.numFormulas = newSize;
    return result;
}

// Operator overloading for increment (prefix)
ExecutablePlan ExecutablePlan::operator++() {
    for (int i = 0; i < numFormulas; ++i) {
        ++formulas[i].inputQuantityClass;
    }
    return *this;
}

// Operator overloading for increment (postfix)
ExecutablePlan ExecutablePlan::operator++(int x) {
    ExecutablePlan temp = *this;
    ++(*this); // Calls prefix increment
    return temp;
}

// Operator overloading for addition assignment (unsigned int)
ExecutablePlan ExecutablePlan::operator+=(unsigned int x) {
    *this = *this + x; // Utilizes the + operator
    return *this;
}

// Operator overloading for addition assignment (another ExecutablePlan)
ExecutablePlan ExecutablePlan::operator+=(const ExecutablePlan& obj) {
    *this = *this + obj; // Utilizes the + operator
    return *this;
}

// Operator overloading for comparison (greater than)
bool ExecutablePlan::operator>(const ExecutablePlan& obj) {
    return numFormulas > obj.numFormulas;
}

bool ExecutablePlan::operator>=(const ExecutablePlan& obj) {
    return numFormulas >= obj.numFormulas;
}

bool ExecutablePlan::operator<(const ExecutablePlan& obj) {
    return !(*this > obj);
}

bool ExecutablePlan::operator<=(const ExecutablePlan& obj) {
    return !(*this >= obj);
}

bool ExecutablePlan::operator==(const ExecutablePlan& obj) {
    if (numFormulas != obj.numFormulas) {
        return false;
    }

    for (int i = 0; i < numFormulas; ++i) {
        if (formulas[i].inputQuantityClass != obj.formulas[i].inputQuantityClass) {
            return false;
        }
    }
    return true;
}

bool ExecutablePlan::operator!=(const ExecutablePlan& obj) {
    return !(*this == obj);
}

