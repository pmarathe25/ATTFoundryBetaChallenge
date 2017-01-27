#include "Server/Server.hpp"
#include "Group/Group.hpp"
#include "Group/GroupAllocator.hpp"
#include <iostream>

int main() {
    Server test1 = Server(1, 3, 20);
    Server test2 = Server(2, 3, 6);
    Server test3 = Server(3, 3, 10);
    Server test4 = Server(4, 3, 4);
    Server test5 = Server(5, 3, 6);
    Server test6 = Server(6, 3, 9);

    Server test7 = Server(7, 3, 2);
    Server test8 = Server(8, 3, 3);

    GroupAllocator allocater = GroupAllocator(3, 1, 18);
    // Creeate map of unavailable slots.
    std::map<int, std::vector<int> > occupancy;
    occupancy.insert({0, {1, 5}});
    occupancy.insert({1, {0, 3, 7, 24}});
    occupancy.insert({2, {0, 3}});
    // allocate groups.
    allocater.allocate(occupancy);
    // Debug.
    allocater.display();
    allocater.addServer(test1);
    allocater.addServer(test2);
    allocater.addServer(test3);
    allocater.addServer(test4);
    allocater.addServer(test5);
    allocater.addServer(test6);
    allocater.addServer(test7);
    allocater.addServer(test8);

    allocater.allocatePools(2);

    allocater.displayServers();
}
