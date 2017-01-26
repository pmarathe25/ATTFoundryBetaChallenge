#include "Server/Server.hpp"
#include <iostream>

int main() {
    Server test1 = Server(1, 3, 4);
    std::cout << test1.getCapacity() << std::endl;
    std::cout << test1.getSize() << std::endl;
}
