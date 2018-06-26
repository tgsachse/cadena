// Part of Cadena by Tiger Sachse

#include <iostream>
#include <fstream>
#include "cadena.h"

int main(int argCount, char** argVector) {
    if (argCount < 2) {
        std::cout << "ERROR: Missing file as first argument." << std::endl;

        return 0;
    }

    if (argCount < 3) {
        std::cout << "ERROR: Missing search string as second argument." << std::endl;

        return 0;
    }

    std::ifstream inputFile;
    inputFile.open(argVector[1]);
    
    if (!inputFile.is_open()) {
        std::cout << "ERROR: File not found." << std::endl;

        return 0;
    }

    Cadena cadena(inputFile, '\0');
    inputFile.close();

    std::cout << "Cadena is: " << cadena << std::endl;
    std::cout << "Length is: " << cadena.getLength() << std::endl;
    //std::cout << cadena.search(argVector[2]) << std::endl;
    
    return 0;
}
