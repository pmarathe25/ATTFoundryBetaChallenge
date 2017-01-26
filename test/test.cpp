#include "Server/Server.hpp"
#include "Group/Group.hpp"
#include "Group/GroupAllocator.hpp"
#include <iostream>

int main() {
    Server test1 = Server(1, 3, 4);
    GroupAllocator allocater = GroupAllocator(3, 3);
    // Creeate map of unavailable slots.
    std::map<int, std::vector<int> > occupancy;
    occupancy.insert({0, {1, 5}});
    occupancy.insert({1, {0, 3}});
    occupancy.insert({2, {0, 3}});
    // allocate groups.
    allocater.allocate(occupancy);
    // Display
    allocater.display();
}
