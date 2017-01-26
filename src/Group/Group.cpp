#include "Group/Group.hpp"
#include <iostream>

Group::Group(int id) {
    this -> id = id;
}

Group::Group(int id, std::vector<int> occupancy) : Group(id) {
    int index = 0;
    for (std::vector<int>::iterator it = occupancy.begin(); it != occupancy.end(); ++it) {
        availability.push_back(*it - index);
        availability.push_back(-1);
        index = *it + 1;
    }
}

void Group::addServer(Server& toAdd) {
    // TODO: Implement add server - find smallest available spot for the server size and set the appropriate values in the server.

}

void Group::display() {
    for (int i = 0; i < availability.size(); ++i) {
        std::cout << availability.at(i) << std::endl;
    }
}

int Group::findSmallestAvailableSlot(int size) {
    int minSize, slotIndex, index;
    for (std::vector<int>::iterator it = availability.begin(); it != availability.end(); ++it) {
        if (*it < minSize && *it >= size) {
            minSize = *it;
            slotIndex = index;
        }
        index += abs(*it);
    }
    return slotIndex;
}
