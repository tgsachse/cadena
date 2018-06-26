#include <iostream>
#include "cadena.h"

int main(void) {
    Cadena list("Tiger was here.");

    list.append(" Here too!");

    std::cout << list << std::endl;

    std::cout << list[2] << std::endl;

    Cadena list2;

    std::cout << list2 << std::endl;
    std::cout << list2[0] << std::endl;

    return 0;
}
