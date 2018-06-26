#include <iostream>
#include "LinkedList.h"

int main(void) {
    LinkedList list("Tiger was here.");

    list.append(" Here too!");

    std::cout << list << std::endl;

    std::cout << list[2] << std::endl;

    LinkedList list2;

    std::cout << list2 << std::endl;
    std::cout << list2[0] << std::endl;

    return 0;
}
