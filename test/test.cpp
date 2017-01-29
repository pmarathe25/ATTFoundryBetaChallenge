#include "Server/Server.hpp"
#include "Group/Group.hpp"
#include "Group/GroupAllocator.hpp"
#include "Server/ServerAllocator.hpp"
#include <iostream>

int main() {
    ServerAllocator serverAllocator = ServerAllocator(EFFICIENCY);
    serverAllocator.read("test/testInput.in");
    // serverAllocator.read("test/input");
    serverAllocator.displayGroup(6);
    serverAllocator.allocateServers();
    serverAllocator.displayServer(6771);
    serverAllocator.write("test/testOutput.out");
    serverAllocator.displayGroup(6);
    // serverAllocator.write("test/output");
    // serverAllocator.displayGroups();
    // serverAllocator.displayServersByGroup();
    // serverAllocator.displayServers();
    serverAllocator.displayMinGuaranteedCapacity();
}
