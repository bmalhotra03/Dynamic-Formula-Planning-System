// Author: Brij Malhotra
// Filename: Plan.h
// Version: Version 1
// Description: This is the class definition of the Plan object

// Class invariant:
//      The Plan object requires the size of the array of Formula objects being passed through
//      as well as the array of Formula objects. The construction of the Formula objects will be 
//      done using that class and it will give appropriate error handling and default values in case
//      an object is not created in a valid manner. The Plan class has certain public functionality for 
//      the Client to invoke such as applying a certain formula within the plan object, adding a formula 
//      to a Plan object, removing the last formula of the Plan object and replacing a present Formula within 
//      the Plan object. There are accessors of the number of formulas and the quantities of the outputs and names.
//      Additionally, the class supports operator overloading, subtraction is strictly not supported. The
//      operations that are available for the client to use are Addition: int + object, object + int, object + object,
//      post and pre increments for the objects, short cut addition += for objects with other objects or objects with 
//      integers. Additionally, all comparison operators are available for use too. The only operator that explicity
//      compares all values are the == operand to make sure both Plans are exactly the same. Comparisons can be done 
//      between one object and another

#include "Formula.h"
#include <string>
#include <iostream>
#include <memory>
#include "Stockpile.h"

using namespace std;

#ifndef PLAN_H
#define PLAN_H

class Plan
{
    private:
        
        // Private copy helper functionality 
        // Precondition: obj is a valid Plan object.
        // Postcondition: The current Plan object has the same numFormulas as obj and a deep copy of obj's formulas array.
        void planCopy(const Plan&);

    protected:
        Formula * formulas;
        int numFormulas;

    public:

        // Constructor
        // Precondition: size is a non-negative integer, initialFormulas is an array of Formulas of size 'size'.
        // Postcondition: A Plan object is initialized with numFormulas equal to 'size' and formulas array copied from initialFormulas.
        Plan(int size = 0, Formula initialFormulas[] = nullptr);

        // Copy constructor
        // Precondition: obj is a valid Plan object.
        // Postcondition: The current Plan object is a deep copy of obj.
        Plan(const Plan&);

        // Move constructor
        // Precondition: obj is a valid Plan object.
        // Postcondition: The current Plan object takes ownership of obj's resources, and obj is left in a safe empty state.
        Plan(Plan&&);

        // Assignment operator
        // Precondition: obj is a valid Plan object.
        // Postcondition: The current Plan object is a deep copy of obj, old memory is released.
        void operator=(const Plan&);

        // Move assignment operator
        // Precondition: obj is a valid Plan object.
        // Postcondition: The current Plan object swaps its resources with obj.
        void operator=(Plan&&);

        // Destructor
        // Precondition: None.
        // Postcondition: Memory allocated for formulas array is released and formulas pointer is set to nullptr.
        virtual ~Plan();

        // Client methods

        // Precondition: formula is a valid Formula object.
        // Postcondition: formulas array is expanded by one and the new formula is added to the end.
        void addFormula(const Formula&);

        // Precondition: None.
        // Postcondition: The last formula in the formulas array is removed and the array size is reduced by one. If numFormulas is zero, no changes are made.
        virtual void removeLastFormula();

        // Precondition: index is a valid index in the range [0, numFormulas-1] and formula is a valid Formula object.
        // Postcondition: The formula at the specified index in the formulas array is replaced by the new formula.
        virtual void replaceFormula(int, const Formula&);

        // Precondition: None.
        // Postcondition: Returns the number of formulas in the Plan.
        int getNumFormulas() const;

        // Precondition: None.
        // Postcondition: Returns a string representing the outputs of all formulas in the Plan.
        string getFormulaOutputs() const;

        // Precondition: Index of formula to be applied and parameter for the resource stockpile
        // Postcondition: Formula is applied
        virtual shared_ptr<Stockpile> applyFormula(int index, shared_ptr<Stockpile>);

        // Operator overloading for addition

        // Pre conditions: An integer is being added to a plan
        // Post conditions: Internal values of the formulas are changed accordingly
        Plan operator+(unsigned int) const;

        // Pre conditions: A plan is being added to a plan
        // Post conditions: A plan with formulas from both plans being added is retrieved
        Plan operator+(const Plan&) const;

        // Pre conditions: A plan is being incremented
        // Post conditions: Plan's formula objects have modified values (+1)
        Plan operator++();

        // Pre conditions: A plan is being incremented
        // Post conditions: Plan's formula objects have modified values (+1) AFTER usage
        Plan operator++(int);

        // Pre conditions: Shortcut addition with integer, same for addition with integer
        // Post conditions: Same for addition with integer
        Plan operator+=(unsigned int);

        // Pre conditions: Shortcut addition with plan object, same for addition with plan
        // Post conditions: Same for addition with plan
        Plan operator+=(const Plan&);

        // Operator overloading for comparison

        // Pre conditions: A plan object is being compared to another plan object
        // Post conditions: Boolean value is returned based on the conditions
        //                  all comparisons take in measure of internal object values
        //                  as well as Plan class variables
        bool operator>(const Plan&);
        bool operator>=(const Plan&);
        bool operator<(const Plan&);
        bool operator<=(const Plan&);
        bool operator==(const Plan&);
        bool operator!=(const Plan&);   
};

#endif

// Implementation invariant:
//      The client is not able to control the outputs and once they initialize a Formula object
//      to be applied and passed into the Plan object, they can only invoke the Plan object public
//      functionality of adding, removing, and replacing formulas. Additionally, all details of Plan
//      objects are given using the accessors. Ownership of objects is handled by Move Semantics with the
//      use of Copy Semantics and appropriate operator overloading. Operator overloading is completely internal,
//      the Formula class supports it as well, the addition is done to the internal Formulas within the plans, 
//      the comparison is based on internal values and the number of formulas per Plan.