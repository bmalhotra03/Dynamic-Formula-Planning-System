// Author: Brij Malhotra
// Filename: Plan.cpp
// Version: 1
// Description: This is the class implementation of the Plan object

#include "Plan.h"

Plan :: Plan(int size, Formula initialFormulas[]){
    
    numFormulas = abs(size);
    formulas = new Formula[numFormulas];
    for (int i = 0; i < numFormulas; i++){
        formulas[i].copy(initialFormulas[i]);
        formulas[i].apply(formulas[i].getInputQuantity(), formulas[i].getInputName());
    }
}

void Plan :: planCopy(const Plan& obj){
    numFormulas = obj.numFormulas;
    formulas = new Formula[numFormulas];

    for (int i = 0; i < numFormulas; i++){
        formulas[i].copy(obj.formulas[i]);
    }
}

Plan :: Plan(const Plan& obj){
    planCopy(obj);
}

void Plan :: operator=(const Plan& obj)
{
    if (this != &obj)
    {
        delete[] formulas;  // Delete the old memory
        planCopy(obj);      // Then copy the new content
    }
}

Plan :: Plan(Plan&& obj){
    numFormulas = obj.numFormulas;
    formulas = obj.formulas;

    obj.numFormulas = 0;
    obj.formulas = nullptr;
}

void Plan :: operator=(Plan&& obj){
    swap(numFormulas, obj.numFormulas);
    swap(formulas, obj.formulas);
}

Plan :: ~Plan(){
    delete [] formulas;
    formulas = nullptr;
}

// Client methods
void Plan :: addFormula(const Formula& formula)
{
    Formula* newFormulas = new Formula[numFormulas + 1];
    for (int i = 0; i < numFormulas; i++) {
        newFormulas[i].copy(formulas[i]);
    }
    newFormulas[numFormulas].copy(formula);

    delete[] formulas;
    formulas = newFormulas;
    numFormulas++;
}

void Plan :: removeLastFormula()
{
    if (numFormulas == 0) return;

    Formula* newFormulas = new Formula[numFormulas - 1];
    for (int i = 0; i < numFormulas - 1; i++) {
        newFormulas[i].copy(formulas[i]);
    }

    delete[] formulas;
    formulas = newFormulas;
    numFormulas--;
}

void Plan :: replaceFormula(int index, const Formula& formula)
{
    if (index >= 0 && index < numFormulas) {
        formulas[index].copy(formula);
    }
}

int Plan :: getNumFormulas() const{
    return numFormulas;
}

string Plan :: getFormulaOutputs() const{
    string result = "";
    for(int i = 0; i < numFormulas; i++) {
        string* outputNames = formulas[i].getOutputName();
        int* outputQuantities = formulas[i].getOutputQuantity();
        for(int j = 0; j < formulas[i].outputSize; j++) {
            result += outputNames[j] + ": " + to_string(outputQuantities[j]) + "\n";
        }
    }
    return result;
}

shared_ptr<Stockpile> Plan :: applyFormula(int index, shared_ptr<Stockpile> s){
    formulas[index].apply(formulas[index].getInputQuantity(), formulas[index].getInputName());
    return s;
}

// Operator overloading for addition
Plan Plan::operator+(unsigned int x) const {
    Plan result = *this;
    for (int i = 0; i < this->numFormulas; ++i) {
        result.formulas[i].inputQuantityClass += x;
    }
    return result;
}

// Operator overloading for addition of two Plan objects
Plan Plan::operator+(const Plan& obj) const {
    int newSize = this->numFormulas + obj.numFormulas;
    
    // Dynamically allocate the memory for the new array.
    Formula* combinedFormulas = new Formula[newSize];

    // Copy the elements from the current object.
    for (int i = 0; i < this->numFormulas; ++i) {
        combinedFormulas[i] = this->formulas[i];
    }

    // Copy the elements from the other object, offset by the size of the current object's array.
    for (int i = 0; i < obj.numFormulas; ++i) {
        combinedFormulas[this->numFormulas + i] = obj.formulas[i];
    }

    // Create a new Plan object to return.
    Plan result;
    result.formulas = combinedFormulas;
    result.numFormulas = newSize;

    return result;
}

// Operator overloading for increment
Plan Plan::operator++() {
    for (int i = 0; i < numFormulas; ++i) {
        ++formulas[i].inputQuantityClass;
    }
    return *this;
}

Plan Plan::operator++(int) {
    Plan temp = *this;
    operator++(); // Calls pre-increment
    return temp;
}

// Operator overloading for addition shortcut
Plan Plan::operator+=(unsigned int x) {
    *this = *this + x; // Utilizes the + operator
    return *this;
}

Plan Plan::operator+=(const Plan& obj) {
    *this = *this + obj; // Utilizes the + operator
    return *this;
}

// Operator overloading for comparison
bool Plan::operator>(const Plan& obj) {
    return numFormulas > obj.numFormulas;
}

bool Plan::operator>=(const Plan& obj) {
    return numFormulas >= obj.numFormulas;
}

bool Plan::operator<(const Plan& obj) {
    return !(*this > obj);
}

bool Plan::operator<=(const Plan& obj) {
    return !(*this >= obj);
}

bool Plan::operator==(const Plan& obj) {
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

bool Plan::operator!=(const Plan& obj) {
    return !(*this == obj);
}