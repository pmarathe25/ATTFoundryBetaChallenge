#include "Group/Group.hpp"
#include <iostream>

Group::Group(int id) {
    this -> id = id;
}

Group::Group(int id, std::vector<int> occupancy) : Group(id) {
    // TODO: save occupancy list in terms of contiguous available storage.
    availability = occupancy;
}

void Group::addServer(Server& toAdd) {

}

void Group::display() {
    for (int i = 0; i < availability.size(); ++i) {
        std::cout << availability.at(i) << std::endl;
    }
}
