#include "Group/Group.hpp"

Group::Group(int id) {
    this -> id = id;
}

Group(int id, std::vector<int> occupancy) : Group(id) {
    // TODO: save occupancy list in terms of contiguous available storage.

}

void Group::addServer(Server& toAdd) {

}
