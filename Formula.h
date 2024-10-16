// Author: Brij Malhotra
// Filename: Formula.h
// Version: 1
// Description: This is the class declaration of the Formula object

#ifndef FORMULA_H
#define FORMULA_H

#include <string>

using namespace std;

class Formula
{
    protected: 

        int proficiencyLevel;
        int * outputQuantity;
        string * inputNameClass;
        string * outputNameClass;
        int inputSize;

    public:

        int * inputQuantityClass;
        int outputSize;
        // Constructor
        Formula(int inputSize = 1, int outputSize = 1, int inputQuantity[] = nullptr, string inputname[] = nullptr, string outputName[] = nullptr);

        // Copy constructor
        Formula(const Formula&);

        // Move constructor
        Formula(Formula&&);

        // Assignment operator
        void operator=(const Formula&);

        // Move assignment operator
        void operator=(Formula&&);
        
        // Destructor
        ~Formula();
        
        void copy(const Formula&);
        // Accessors
        int * getInputQuantity();
        int * getOutputQuantity();
        string * getInputName();
        string * getOutputName();

        // Client function 
        void apply(int inputQuantity[], string inputNames[]);

        // Operator overloading for addition
        Formula operator+(unsigned int);
        Formula operator+(const Formula&);
        Formula operator++();
        Formula operator++(int);
        Formula operator+=(unsigned int);
        Formula operator+=(const Formula&);

        // Operator overloading for comparison
        bool operator>(const Formula&);
        bool operator>=(const Formula&);
        bool operator<(const Formula&);
        bool operator<=(const Formula&);
        bool operator==(const Formula&);
        bool operator!=(const Formula&);
};

#endif