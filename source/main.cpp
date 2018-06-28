// Part of Cadena by Tiger Sachse

#include <iostream>
#include <fstream>
#include "cadena.h"

// Entry point to example program.
int main(int argCount, char** argVector) {
    // If no file is provided, scream about it.
    if (argCount < 2) {
        std::cout << "ERROR: Missing file as first argument." << std::endl;

        return 0;
    }

    // If no search string is provided, scream about it.
    if (argCount < 3) {
        std::cout << "ERROR: Missing search string as second argument." << std::endl;

        return 0;
    }

    std::ifstream inputFile;
    inputFile.open(argVector[1]);

    // If the provided file cannot be opened, scream about it.
    if (!inputFile.is_open()) {
        std::cout << "ERROR: File not found." << std::endl;

        return 0;
    }

    // Initialize a new cadena from the input file, replacing newlines with spaces.
    Cadena cadena(inputFile, ' ');

    inputFile.close();

    std::cout << "Cadena is: " << cadena << std::endl;
    std::cout << "Length is: " << cadena.getLength() << std::endl;
    std::cout << "Occurences of string " << argVector[2] << " in cadena: ";
    std::cout << cadena.search(argVector[2]) << std::endl;
    
    return 0;
}
