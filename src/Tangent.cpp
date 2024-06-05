#include "Tangent/Tangent.h"
#include "Version.h"
#include <iostream>

void printV()
{
    std::cout << "Tangent version: " << TANGENT_VERSION_MAJOR << "." << TANGENT_VERSION_MINOR << std::endl;
}

void Tangent::sayHello()
{
    printV();
}
