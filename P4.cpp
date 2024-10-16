// Author: Brij Malhotra
// Filename: P4.cpp
// Version: 1
// Description: Driver program for P4

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include "Formula.h"
#include "Plan.h"
#include "ExecutablePlan.h"
#include <string>

const int MAX_PLANS = 6;

// Function prototype declarations
Plan* GetPlan();
void SimulatePlans(Plan* planDB[], int size);
shared_ptr<Stockpile> getStockpile();
Plan operator+(unsigned int x, const Plan& obj); // Commutativity for addition

int main() {
    Plan* planDB[MAX_PLANS];

    for (int i = 0; i < MAX_PLANS; ++i) {
        planDB[i] = GetPlan();
    }

    // Test operator overloading
    cout << "Testing operator overloading" << endl << endl;
    planDB[3] = planDB[1] + 5;
    *planDB[4] = *planDB[5] + *planDB[6];
    
    // Test assignment operator and copy constructor
    cout << "Testing assignment operator and copy constructor" << endl << endl;
    Plan planX = *planDB[1];
    Plan planY(*planDB[2]);

    // Test comparison overloading
    cout << "Testing comparison operator overloading" << endl << endl;
    if (planDB[1] != planDB[4]){
        cout << "Plan 1 is not similar to Plan 2" << endl;
    } else {
        cout << "Plan 1 is similar to Plan 2" << endl;
    }

    if (planDB[3] > planDB[5]){
        cout << "Plan 3 is greater than Plan 5" << endl;
    } else {
        cout << "Plan 5 is greater than Plan 3" << endl;
    }

    if (planDB[2] <= planDB[3]){
        cout << "Plan 2 is either equal to or less than Plan 3" << endl;
    } else {
        cout << "Plan 2 is greater than Plan 3" << endl;
    }

    planX.removeLastFormula();

    if (*planDB[1] != planX){
        cout << "Plan 1 is not equal to Plan X" << endl;
    } else {
        cout << "Plan 1 is the same as Plan X" << endl;
    }

    // Performing increment and shortcut operations
    cout << "Performing increment and shortcut operations" << endl << endl;
    planDB[1]++;
    ++planDB[2];
    planDB[3] += 5;
    *planDB[3] += *planDB[4];
    planDB[3] = 5 + planDB[2];
    
    cout << "Simulating program functionality" << endl << endl;
    SimulatePlans(planDB, MAX_PLANS);

    // Zero out objects
    for (int i = 0; i < MAX_PLANS; ++i) {
        delete planDB[i];
        planDB[i] = nullptr;
    }

    return 0;
}

Plan operator+(unsigned int x, const Plan& obj){
    Formula * test = nullptr;
    Plan temp(0, test);
    temp = obj + x;
    return temp;
}

Plan* GetPlan() {
    srand(time(nullptr));
    int choice = rand() % 2 + 1;

    int numFormulas = rand() % 4 + 2; // Random number of formulas between 2 to 5.
    Formula* formulas = new Formula[numFormulas];
    for (int i = 0; i < numFormulas; ++i) {
        int inputQuantities[2] = {rand() % 10 + 1, rand() % 10 + 1};
        string inputNames[2] = {"InputA" + std::to_string(i), "InputB" + std::to_string(i)};
        string outputNames[2] = {"OutputA" + std::to_string(i), "OutputB" + std::to_string(i)};
        int insize = 2;
        int outsize = 2;
        formulas[i] = Formula(insize, outsize, inputQuantities, inputNames, outputNames);
    }

    if (choice == 1) {
        return new Plan(numFormulas, formulas);
    } else if (choice == 2) {
        return new ExecutablePlan(numFormulas, formulas);
    } else {
        throw runtime_error("No Plan object created");
    }
}

shared_ptr<Stockpile> getStockpile(){

    vector<int> initialResources = {50, 50 , 50, 50, 50, 50, 50, 50, 50};

    shared_ptr<Stockpile> stocks(new Stockpile(initialResources));

    return stocks;
}

void SimulatePlans(Plan* planDB[], int size) {
    srand(time(nullptr));

    int simulations = rand() % 16 + 5;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < simulations; ++j) {
            int action = rand() % 4 + 1;

            if (action == 1) {
                // Add formula
                int inputQuantities[] = { std::rand() % 10 + 1, std::rand() % 10 + 1 };
                string inputNames[] = { "ReplaceInputA", "ReplaceInputB" };
                string outputNames[] = { "ReplaceOutputA", "ReplaceOutputB" };
                Formula newFormula(2, 2, inputQuantities, inputNames, outputNames);
                planDB[i]->addFormula(newFormula);

            } else if (action == 2) {
                // Remove last formula
                planDB[i]->removeLastFormula();
            } else if (action == 3) {
                
                // Replace formula
                if (planDB[i]->getNumFormulas() > 0) {

                srand(static_cast<unsigned int>(time(nullptr)));

                int index = rand() % planDB[i]->getNumFormulas();
                int inputQuantities[] = { std::rand() % 10 + 1, std::rand() % 10 + 1 };
                string inputNames[] = { "ReplaceInputA", "ReplaceInputB" };
                string outputNames[] = { "ReplaceOutputA", "ReplaceOutputB" };
                Formula newFormula(2, 2, inputQuantities, inputNames, outputNames);
                planDB[i]->replaceFormula(index, newFormula);
                planDB[i]->getFormulaOutputs();
            }
            } else if (action == 4) {
                // Apply formula
                int index = rand() % planDB[i]->getNumFormulas();
                planDB[i]->applyFormula(index, getStockpile());
            } else {
                throw runtime_error("No action performed");
            }
        }
    }
}