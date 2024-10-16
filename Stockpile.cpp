// Author: Brij Malhotra
// Filenam: Stockpile.cpp
// Version: 1
// Description: Class implementation of the Stockpile class

#include "Stockpile.h"

// Constructor
Stockpile::Stockpile(std::vector<int> initialResources) : resources(move(initialResources)) {}

// Check if enough resources are available
bool Stockpile::hasResources(unsigned int index, int quantityNeeded) const {
    if (index >= resources.size()) {
        throw std::out_of_range("Index out of range for stockpile resources");
    }
    return resources[index] >= quantityNeeded;
}

// Increase resource quantity
void Stockpile::addResource(unsigned int index, int quantity) {
    if (index >= resources.size()) {
        throw std::out_of_range("Index out of range for stockpile resources");
    }
    resources[index] += quantity;
}

// Decrease resource quantity
bool Stockpile::deductResource(unsigned int index, int quantity) {
    if (index >= resources.size()) {
        throw std::out_of_range("Index out of range for stockpile resources");
    }
    if (resources[index] < quantity) {
        return false; // Not enough resources to deduct
    }
    resources[index] -= quantity;
    return true;
}

// Get the current quantity of a resource
int Stockpile::getResourceQuantity(unsigned int index) const {
    if (index >= resources.size()) {
        throw std::out_of_range("Index out of range for stockpile resources");
    }
    return resources[index];
}