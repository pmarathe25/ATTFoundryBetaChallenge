#include "Server/Server.hpp"
#include "Group/Group.hpp"
#include "Group/GroupAllocator.hpp"
#include "Server/ServerAllocator.hpp"
#include <iostream>

int main() {
    ServerAllocator serverAllocator = ServerAllocator(CAPACITY);
    // serverAllocator.read("test/testInput.in");
    serverAllocator.read("test/input");
    // serverAllocator.displayGroups();
    serverAllocator.allocateServers();
    // serverAllocator.write("test/testOutput.out");
    serverAllocator.write("test/output");
    serverAllocator.displayServersByGroup();
    // serverAllocator.displayServers();
    serverAllocator.displayMinGuaranteedCapacity();
}
