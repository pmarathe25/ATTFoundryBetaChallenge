#include "Server/Server.hpp"
#include "Group/Group.hpp"
#include "Group/GroupAllocator.hpp"
#include "Server/ServerAllocator.hpp"

int main() {
    ServerAllocator serverAllocator = ServerAllocator(EFFICIENCY);
    serverAllocator.read("/home/pranav/Downloads/input-1.in");
    // serverAllocator.read("test/input");
    serverAllocator.allocateServers();
    // serverAllocator.displayServer(6771);
    serverAllocator.write("~/Downloads/output-1.out");
    // serverAllocator.displayGroup(6);
    serverAllocator.displayGroups();
    // serverAllocator.write("test/output");
    // serverAllocator.displayGroups();
    // serverAllocator.displayServersByGroup();
    // serverAllocator.displayServers();
    serverAllocator.displayMinGuaranteedCapacity();
}
