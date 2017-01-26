#include "Group/Group.hpp"
#include <iostream>

Group::Group(int id) {
    this -> id = id;
}

Group::Group(int id, std::vector<int> occupancy) : Group(id) {
    // TODO: save occupancy list in terms of contiguous available storage.
    int index = 0;
    for (std::vector<int>::iterator it = occupancy.begin(); it != occupancy.end(); ++it) {
        availability.push_back(*it - index);
        availability.push_back(-1);
        index = *it + 1;
    }
}

void Group::addServer(Server& toAdd) {

}

void Group::display() {
    for (int i = 0; i < availability.size(); ++i) {
        std::cout << availability.at(i) << std::endl;
    }
}
