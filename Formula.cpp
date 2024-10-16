// Author: Brij Malhotra
// Filename: Formula.cpp
// Version: 1
// Description: This is the class implementation of the Formula object

#include "Formula.h"
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

Formula::Formula(int inSize, int outSize, int inputQuantity[], string inputName[], string outputName[]) : inputSize(inSize), outputSize(outSize)
{
    proficiencyLevel = 0;

    // Check for null arrays or empty strings
    bool areInputQuantitiesZero = (inputQuantity == nullptr) || all_of(inputQuantity, inputQuantity + inSize, [](int i) { return i == 0; });
    bool areInputNamesEmpty = (inputName == nullptr) || all_of(inputName, inputName + inSize, [](const string& s) { return s.empty(); });
    bool areOutputNamesEmpty = (outputName == nullptr) || all_of(outputName, outputName + outSize, [](const string& s) { return s.empty(); });

    if (areInputQuantitiesZero || areInputNamesEmpty || areOutputNamesEmpty)
    {
        inputSize = 1;
        outputSize = 1;
        inputQuantityClass = new int[1]{0};
        inputNameClass = new string[1]{"No input"};
        outputNameClass = new string[1]{"No output"};
    }
    else
    {
        inputQuantityClass = new int[inSize];
        inputNameClass = new string[inSize];
        outputNameClass = new string[outSize];

        for (int i = 0; i < inSize; i++)
        {
            inputQuantityClass[i] = abs(inputQuantity[i]);
            inputNameClass[i] = inputName[i];
        }
        for (int i = 0; i < outSize; i++)
        {
            outputNameClass[i] = outputName[i];
        }
    }

    outputQuantity = new int[outSize];
    int outputExpected = 0;
    for (int i = 0; i < inSize; i++)
    {
        outputExpected += inputQuantityClass[i];
    }

    outputExpected /= 2;

    for (int i = 0; i < outSize; i++)
    {
        outputQuantity[i] = outputExpected;
    }
}

Formula :: ~Formula(){
    delete[] inputQuantityClass;
    delete[] inputNameClass;
    delete[] outputNameClass;
    delete[] outputQuantity;
}

int * Formula :: getInputQuantity()
{
    return inputQuantityClass;
}

int * Formula :: getOutputQuantity()
{
    return outputQuantity;
}

string * Formula :: getInputName()
{
    return inputNameClass;
}

string * Formula :: getOutputName()
{
    return outputNameClass;
}

void Formula :: apply(int inputQuantity[], string inputNames[])
{
    proficiencyLevel++;

    int outputExpected = 0;
    for(int i = 0; i < inputSize; i++)
    {
        outputExpected += inputQuantity[i];
    }
    outputExpected /= 2;

    // Chances based on proficiency level
    int failureChance, reducedOutputChance, normalOutputChance;
    
    switch (proficiencyLevel)
    {
        case 1:
            failureChance = 25;
            reducedOutputChance = 20;
            normalOutputChance = 50;
            break;
        case 2:
            failureChance = 20;
            reducedOutputChance = 15;
            normalOutputChance = 55;
            break;
        default:
            failureChance = 10;
            reducedOutputChance = 20;
            normalOutputChance = 55;
            break;
    }

    int roll = rand() % 101;  // Generates a random number between 0 and 100

    if (roll < failureChance) // Failure
    {
        for (int i = 0; i < outputSize; i++)
        {
            outputQuantity[i] = 0;
        }
    }
    else if (roll < failureChance + reducedOutputChance) // 75% output
    {
        for (int i = 0; i < outputSize; i++)
        {
            outputQuantity[i] = (int)(round(outputExpected * 0.75));
        }
    }
    else if (roll < failureChance + reducedOutputChance + normalOutputChance) // 100% output
    {
        for (int i = 0; i < outputSize; i++)
        {
            outputQuantity[i] = outputExpected;
        }
    }
    else // 110% output
    {
        for (int i = 0; i < outputSize; i++)
        {
            outputQuantity[i] = (int)(round(outputExpected * 1.10));
        }
    }

    getOutputName();
    getOutputQuantity();
}

void Formula :: copy(const Formula& obj)
{
    proficiencyLevel = obj.proficiencyLevel;
    inputSize = obj.inputSize;
    outputSize = obj.outputSize;
    
    // Allocate memory
    inputQuantityClass = new int[inputSize];
    inputNameClass = new string[inputSize];
    outputQuantity = new int[outputSize];
    outputNameClass = new string[outputSize];

    for (int i = 0; i < inputSize; i++){
        inputQuantityClass[i] = obj.inputQuantityClass[i];
        inputNameClass[i] = obj.inputNameClass[i];
    }
    
    for (int i = 0; i < outputSize; i++){
        outputQuantity[i] = obj.outputQuantity[i];
        outputNameClass[i] = obj.outputNameClass[i];
    }
}

Formula :: Formula(const Formula& obj){
    copy(obj);
}

void Formula :: operator=(const Formula& obj){
    if (this != &obj){
        delete[] inputQuantityClass;
        delete[] inputNameClass;
        delete[] outputNameClass;
        delete[] outputQuantity;
        copy(obj);
    }
}

Formula :: Formula(Formula&& obj){
    proficiencyLevel = obj.proficiencyLevel;
    outputQuantity = obj.outputQuantity;
    inputQuantityClass = obj.inputQuantityClass;
    inputNameClass = obj.inputNameClass;
    outputNameClass = obj.outputNameClass;
    inputSize = obj.inputSize;
    outputSize = obj.outputSize;
}

void Formula :: operator=(Formula&& obj){
    swap(proficiencyLevel, obj.proficiencyLevel);
    swap(outputQuantity, obj.outputQuantity);
    swap(inputQuantityClass, obj.inputQuantityClass);
    swap(inputNameClass, obj.inputNameClass);
    swap(outputNameClass, obj.outputNameClass);
    swap(inputSize, obj.inputSize);
    swap(outputSize, obj.outputSize);
}

// Operator overloading for addition
// Add unsigned int to each value of the inputQuantityClass array
Formula Formula::operator+(unsigned int x) {
    Formula result(*this); // Create a copy of the current object
    for (int i = 0; i < inputSize; ++i) {
        result.inputQuantityClass[i] += x;
    }
    return result;
}

// Add values of the obj.inputQuantityClass to the inputQuantityClass
Formula Formula::operator+(const Formula& obj) {
    Formula result(*this); // Create a copy of the current object
    int minSize = min(inputSize, obj.inputSize); // Operate up to the smallest inputSize
    for (int i = 0; i < minSize; ++i) {
        result.inputQuantityClass[i] += obj.inputQuantityClass[i];
    }
    return result;
}

// Post-increment: add 1 to all inputQuantityClass values
Formula Formula::operator++(int) {
    Formula temp(*this); // Make a copy for the result
    operator++(); // Use the pre-increment to add one
    return temp; // Return the unmodified copy
}

// Pre-increment: add 1 to all inputQuantityClass values
Formula Formula::operator++() {
    for (int i = 0; i < inputSize; ++i) {
        ++inputQuantityClass[i];
    }
    return *this; // Return the current object after modification
}

// Shortcut for addition with an unsigned int, similar to above
Formula Formula::operator+=(unsigned int x) {
    *this = *this + x; // Use the + operator to perform the addition
    return *this; // Return the current object
}

// Shortcut for addition with another Formula object, similar to above
Formula Formula::operator+=(const Formula& obj) {
    *this = *this + obj; // Use the + operator to perform the addition
    return *this; // Return the current object
}

// Comparison operators
bool Formula::operator>(const Formula& obj) {
    return (inputSize > obj.inputSize);
}

bool Formula::operator>=(const Formula& obj) {
    if (inputSize > obj.inputSize) return true;
    if (inputSize == obj.inputSize) {
        // Check if all data members are the same
        for (int i = 0; i < inputSize; ++i) {
            if (inputQuantityClass[i] != obj.inputQuantityClass[i] || inputNameClass[i] != obj.inputNameClass[i])
                return false;
        }
        return true;
    }
    return false;
}

bool Formula::operator<(const Formula& obj) {
    return !(*this > obj);
}

bool Formula::operator<=(const Formula& obj) {
    return !(*this >= obj);
}

// Equality and inequality operators
bool Formula::operator==(const Formula& obj) {
    if (inputSize != obj.inputSize) return false;
    for (int i = 0; i < inputSize; ++i) {
        if (inputQuantityClass[i] != obj.inputQuantityClass[i] || inputNameClass[i] != obj.inputNameClass[i])
            return false;
    }
    return true;
}

bool Formula::operator!=(const Formula& obj) {
    return !(*this == obj);
}

