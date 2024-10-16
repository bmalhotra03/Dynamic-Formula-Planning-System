// Author: Brij Malhotra
// Filenam: Stockpile.h
// Version: 1
// Description: Class declaration of the Stockpile class

#ifndef STOCKPILE_H
#define STOCKPILE_H

#include <vector>
#include <stdexcept>

class Stockpile {
private:
    std::vector<int> resources;

public:
    // Constructor
    explicit Stockpile(std::vector<int> initialResources);

    // Prevent copying of Stockpile instances
    Stockpile(const Stockpile&) = delete;
    Stockpile& operator=(const Stockpile&) = delete;

    // Check if enough resources are available
    bool hasResources(unsigned int index, int quantityNeeded) const;

    // Increase resource quantity
    void addResource(unsigned int index, int quantity);

    // Decrease resource quantity
    bool deductResource(unsigned int index, int quantity);

    // Get the current quantity of a resource
    int getResourceQuantity(unsigned int index) const;
};

#endif // STOCKPILE_H