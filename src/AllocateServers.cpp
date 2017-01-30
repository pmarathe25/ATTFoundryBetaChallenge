#include "Server/Server.hpp"
#include "Group/Group.hpp"
#include "Group/GroupAllocator.hpp"
#include "Server/ServerAllocator.hpp"
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        throw std::invalid_argument("Must provide both an input and output file.");
    }
    ServerAllocator serverAllocator = (argc > 3 && toupper(argv[3][0]) == 'C') ? ServerAllocator(CAPACITY) : ServerAllocator(EFFICIENCY);
    serverAllocator.read(argv[1]);
    serverAllocator.allocateServers();
    serverAllocator.write(argv[2]);
    serverAllocator.displayMinGuaranteedCapacity();
}
