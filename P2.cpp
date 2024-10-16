#include "Plan.h"
#include "Formula.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Function Prototypes
Plan createPlanWithMultipleCookies();
Plan createPlanWithMultipleCakes();
Plan createPlanWithMultiplePizzas();


int main() {
    
    Plan planCookie = createPlanWithMultipleCookies();
    Plan planCake = createPlanWithMultipleCakes();
    Plan planPizza = createPlanWithMultiplePizzas();

    cout << endl << endl;
    cout << "Current Plan objects and the Formulas they each hold: " << endl << endl;
    cout << "Plan with Cookie formulas- " << endl;
    cout << "Number of Cookie formulas: " << planCookie.getNumFormulas() << endl;
    cout << "Formula outputs in this Plan object: "  << endl << planCookie.getFormulaOutputs() << endl << endl;

    cout << "Plan with Cake formulas- " << endl;
    cout << "Number of Cake formulas: " << planCake.getNumFormulas() << endl;
    cout << "Formula outputs in this Plan object: " << endl << planCake.getFormulaOutputs() << endl << endl;

    cout << "Plan with Pizza formulas- " << endl;
    cout << "Number of Pizza formulas: " << planPizza.getNumFormulas() << endl;
    cout << "Formula outputs in this Plan object: " << endl << planPizza.getFormulaOutputs() << endl << endl;

    // Testing actual client methods:

    // Creating the Hawaiian Pizza formula
    int hawaiianInputQuantities[] = {4, 2, 4, 6, 3};
    string hawaiianInputNames[] = {"Dough", "Pizza Sauce", "Cheese", "Ham", "Pineapple"};
    string hawaiianOutputNames[] = {"Hawaiian Pizza"};
    Formula hawaiianPizza(5, 1, hawaiianInputQuantities, hawaiianInputNames, hawaiianOutputNames);
    hawaiianPizza.apply(hawaiianInputQuantities, hawaiianInputNames);

    // Adding the Hawaiian Pizza formula to the Pizza Plan
    planPizza.addFormula(hawaiianPizza);

    cout << "After adding the Hawaiian pizza formula-" << endl;
    cout << "Number of Pizza formulas: " << planPizza.getNumFormulas() << endl;
    cout << "Formula outputs in this Plan object: " << endl << planPizza.getFormulaOutputs() << endl << endl;

    // Testing removeformula with cookies
    planCookie.removeLastFormula();
    cout << "After removing the last cookie formula-" << endl;
    cout << "Number of Cookie formulas: " << planCookie.getNumFormulas() << endl;
    cout << "Formula outputs in this Plan object: " << endl << planCookie.getFormulaOutputs() << endl << endl;

    // Testing replaceFormula with cakes:
    // Creating the Fruit Cake formula
    int fruitInputQuantities[] = {3, 2, 4, 5, 2};
    string fruitInputNames[] = {"Flour", "Sugar", "Eggs", "Mixed Fruit", "Nuts"};
    string fruitOutputNames[] = {"Fruit Cake"};
    Formula fruitCake(5, 1, fruitInputQuantities, fruitInputNames, fruitOutputNames);
    fruitCake.apply(fruitInputQuantities, fruitInputNames);

    // Replacing the second formula in the Plan object with the Fruit Cake formula
    planCake.replaceFormula(1, fruitCake);

    cout << "After replacing one of the cake formulas with the Fruit Cake formula-" << endl;
    cout << "Number of Cake formulas: " << planCake.getNumFormulas() << endl;
    cout << "Formula outputs in this Plan object: " << endl << planCake.getFormulaOutputs() << endl << endl;

    
    // Use of copy constructor
    cout << "Creating another Pizza Plan- " << endl;
    Plan planPizza2 = planPizza;

    cout << "Plan with Pizza2 formulas- " << endl;
    cout << "Number of Pizza2 formulas: " << planPizza2.getNumFormulas() << endl;
    cout << "Formula outputs in this Plan object: " << planPizza2.getFormulaOutputs() << endl << endl;

    // Use of assignment operator
    cout << "Turning Cookie Plan to Cake Plan: " << endl;
    planCake = planCookie;

    cout << "After Cookie Plan turns into Cake Plan-" << endl;
    cout << "Number of Cake formulas: " << planCookie.getNumFormulas() << endl;
    cout << "Formula outputs in this Plan object: " << planCookie.getFormulaOutputs() << endl << endl;
    
    return 0;
}

// Function declarations
Plan createPlanWithMultipleCookies() {
    // Chocolate Chip Cookie
    int chocoChipInputQuantities[] = {2, 1, 1, 1};
    string chocoChipInputNames[] = {"Flour", "Sugar", "Butter", "Chocolate Chips"};
    string chocoChipOutputNames[] = {"Chocolate Chip Cookie"};
    Formula chocoChipCookie(4, 1, chocoChipInputQuantities, chocoChipInputNames, chocoChipOutputNames);
    chocoChipCookie.apply(chocoChipInputQuantities, chocoChipInputNames);

    // Oatmeal Cookie
    int oatmealInputQuantities[] = {5, 10, 3, 2};
    string oatmealInputNames[] = {"Flour", "Sugar", "Butter", "Oats"};
    string oatmealOutputNames[] = {"Oatmeal Cookie"};
    Formula oatmealCookie(4, 1, oatmealInputQuantities, oatmealInputNames, oatmealOutputNames);
    oatmealCookie.apply(oatmealInputQuantities, oatmealInputNames);

    // Pumpkin Cookie
    int pumpkinInputQuantities[] = {4, 5, 2, 8};
    string pumpkinInputNames[] = {"Flour", "Sugar", "Butter", "Pumpkin Puree"};
    string pumpkinOutputNames[] = {"Pumpkin Cookie"};
    Formula pumpkinCookie(4, 1, pumpkinInputQuantities, pumpkinInputNames, pumpkinOutputNames);
    pumpkinCookie.apply(pumpkinInputQuantities, pumpkinInputNames);

    // Funfetti Cookie
    int funfettiInputQuantities[] = {1, 2, 3, 4};
    string funfettiInputNames[] = {"Flour", "Sugar", "Butter", "Sprinkles"};
    string funfettiOutputNames[] = {"Funfetti Cookie"};
    Formula funfettiCookie(4, 1, funfettiInputQuantities, funfettiInputNames, funfettiOutputNames);
    funfettiCookie.apply(funfettiInputQuantities, funfettiInputNames);

    // Combine all cookies into an array and create a Plan
    Formula allCookies[] = {chocoChipCookie, oatmealCookie, pumpkinCookie, funfettiCookie};
    Plan multipleCookiesPlan(4, allCookies);
    return multipleCookiesPlan;
}

Plan createPlanWithMultipleCakes() {
    // Chocolate Cake
    int chocolateInputQuantities[] = {2, 2, 3, 2};
    string chocolateInputNames[] = {"Flour", "Sugar", "Cocoa Powder", "Eggs"};
    string chocolateOutputNames[] = {"Chocolate Cake"};
    Formula chocolateCake(4, 1, chocolateInputQuantities, chocolateInputNames, chocolateOutputNames);
    chocolateCake.apply(chocolateInputQuantities, chocolateInputNames);

    // Strawberry Cake
    int strawberryInputQuantities[] = {2, 3, 5, 4};
    string strawberryInputNames[] = {"Flour", "Sugar", "Strawberries", "Eggs"};
    string strawberryOutputNames[] = {"Strawberry Cake"};
    Formula strawberryCake(4, 1, strawberryInputQuantities, strawberryInputNames, strawberryOutputNames);
    strawberryCake.apply(strawberryInputQuantities, strawberryInputNames);

    // Black Forest Cake
    int forestInputQuantities[] = {3, 6, 4, 2, 1};
    string forestInputNames[] = {"Flour", "Sugar", "Cocoa Powder", "Cherries", "Whipped Cream"};
    string forestOutputNames[] = {"Black Forest Cake"};
    Formula blackForestCake(5, 1, forestInputQuantities, forestInputNames, forestOutputNames);
    blackForestCake.apply(forestInputQuantities, forestInputNames);

    // Combine all cakes into an array and create a Plan
    Formula allCakes[] = {chocolateCake, strawberryCake, blackForestCake};
    Plan multipleCakesPlan(3, allCakes);
    return multipleCakesPlan;
}

Plan createPlanWithMultiplePizzas() {
    // Pepperoni Pizza
    int pepperoniInputQuantities[] = {6, 3, 6, 8};
    string pepperoniInputNames[] = {"Dough", "Pizza Sauce", "Cheese", "Pepperoni"};
    string pepperoniOutputNames[] = {"Pepperoni Pizza"};
    Formula pepperoniPizza(4, 1, pepperoniInputQuantities, pepperoniInputNames, pepperoniOutputNames);
    pepperoniPizza.apply(pepperoniInputQuantities, pepperoniInputNames);

    // Barbeque Pizza
    int bbqInputQuantities[] = {3, 3, 3, 6};
    string bbqInputNames[] = {"Dough", "Barbeque Sauce", "Cheese", "Chicken"};
    string bbqOutputNames[] = {"Barbeque Pizza"};
    Formula barbequePizza(4, 1, bbqInputQuantities, bbqInputNames, bbqOutputNames);
    barbequePizza.apply(bbqInputQuantities, bbqInputNames);

    // Cheese Pizza
    int cheeseInputQuantities[] = {4, 2, 6};
    string cheeseInputNames[] = {"Dough", "Pizza Sauce", "Cheese"};
    string cheeseOutputNames[] = {"Cheese Pizza"};
    Formula cheesePizza(3, 1, cheeseInputQuantities, cheeseInputNames, cheeseOutputNames);
    cheesePizza.apply(cheeseInputQuantities, cheeseInputNames);

    // Combine all pizzas into an array and create a Plan
    Formula allPizzas[] = {pepperoniPizza, barbequePizza, cheesePizza};
    Plan multiplePizzasPlan(3, allPizzas);
    return multiplePizzasPlan;
}