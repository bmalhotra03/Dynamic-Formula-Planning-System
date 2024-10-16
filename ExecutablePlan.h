// Author: Brij Malhotra
// Filename: ExecutablePlan.h
// Version: 1
// Description: Child class of Plan, class declaration here

// Class invariant:
//      Same as parent, but formulas that have been applied cannot be replaced,
//      if a formula has been completed, it cannot be removed. Additionall, the
//      apply functionality for an ExecutablePlan object looks up a Stockpile class
//      to check for resources that are available so that the formula can be applied.

#include "Plan.h"
#include <stdexcept>
#include <iostream>
#include <memory>
#include "Stockpile.h"

using namespace std;

#ifndef EXECUTABLEPLAN_H
#define EXECUTABLEPLAN_H

// Class Invariant

class ExecutablePlan : public Plan
{
private:
    int currentStep;

public:
    // Constructor
    ExecutablePlan(int size = 0, Formula initialFormulas[] = nullptr);

    // Copy constructor
    ExecutablePlan(const ExecutablePlan&);

    // Move constructor
    ExecutablePlan(ExecutablePlan&&);

    // Assignment operator
    void operator=(const ExecutablePlan&);

    // Move assignment operator
    void operator=(ExecutablePlan&&);

    // Destructor
    ~ExecutablePlan();

    // Precondition: Index of formula to be applied and parameter for the resource stockpile
    // Postcondition: Formula is applied
    shared_ptr<Stockpile> applyFormula(int index, shared_ptr<Stockpile>) override;
    
    // Precondition: None.
    // Postcondition: Returns the current step of the Plan.
    int getCurrentStep();

    // Overridden client methods
    
    // Precondition: index is a valid index in the range [0, numFormulas-1] and formula is a valid Formula object. 
    //               Formula to be replaced should not be applied already.
    // Postcondition: The formula at the specified index in the formulas array is replaced by the new formula.
    void replaceFormula(int index, const Formula& formula) override;

    // Precondition: The formula should not be completed.
    // Postcondition: The last formula in the formulas array is removed and the array size is reduced by one. If numFormulas is zero, no changes are made.
    void removeLastFormula() override;

    // Operator overloading for addition

    // Pre and Post conditions are the same as parent class declarations
    ExecutablePlan operator+(unsigned int) const;
    ExecutablePlan operator+(const ExecutablePlan&) const;
    ExecutablePlan operator++();
    ExecutablePlan operator++(int);
    ExecutablePlan operator+=(unsigned int);
    ExecutablePlan operator+=(const ExecutablePlan&);

    // Operator overloading for comparison
    bool operator>(const ExecutablePlan&);
    bool operator>=(const ExecutablePlan&);
    bool operator<(const ExecutablePlan&);
    bool operator<=(const ExecutablePlan&);
    bool operator==(const ExecutablePlan&);
    bool operator!=(const ExecutablePlan&);  
};

#endif

// Implementation invariant:
//      Same as parent class. Additionally, it takes a smart pointer to a Stockpile class
//      and checks for resources based on the creation of the Stockpile resource object, it has
//      functionality that gives the client the knowledge of whether the formula can be applied or not