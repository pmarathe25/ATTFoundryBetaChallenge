#include "Server/Server.hpp"
#include "Group/Group.hpp"
#include "Group/GroupAllocator.hpp"
#include <iostream>

int main() {
    Server test1 = Server(1, 3, 20);
    Server test2 = Server(2, 3, 19);
    Server test3 = Server(3, 2, 9);
    Server test4 = Server(4, 2, 8);
    Server test5 = Server(5, 2, 6);
    Server test6 = Server(6, 2, 5);
    Server test7 = Server(7, 1, 2);
    Server test8 = Server(8, 1, 2);
    Server test9 = Server(9, 1, 1);

    GroupAllocator allocater = GroupAllocator(3, 1, 26);
    // Creeate map of unavailable slots.
    std::map<int, std::vector<int> > occupancy;
    occupancy.insert({0, {4, 5, 6}});
    // occupancy.insert({1, {}});
    occupancy.insert({2, {5, 6}});
    // allocate groups.
    allocater.allocateGroups(occupancy);
    // Debug.
    allocater.displayGroups();
    allocater.addServer(test1);
    allocater.addServer(test2);
    allocater.addServer(test3);
    allocater.addServer(test4);
    allocater.addServer(test5);
    allocater.addServer(test6);
    allocater.addServer(test7);
    allocater.addServer(test8);
    allocater.addServer(test9);

    allocater.allocatePools(2);
    allocater.displayServers();
}
