#include "Group/Group.hpp"
#include <iostream>
#include <algorithm>
#include <climits>

Group::Group(int id, int goalCapacity) {
    this -> id = id;
    this -> goalCapacity = goalCapacity;
}

Group::Group(int id, int goalCapacity, const std::vector<int>& occupancy) : Group(id, goalCapacity) {
    setAvailabilityList(occupancy);
    efficiency = goalCapacity / (float) availableSlots;
}

bool Group::addServer(Server& toAdd) {
    std::pair<int, int> index = findSmallestAvailableSlot(toAdd.getSize());
    if (index.first != -1) {
        availability.at(index.first) -= toAdd.getSize();
        availability.at(index.first + 1) -= toAdd.getSize();
        availableSlots -= toAdd.getSize();
        goalCapacity -= toAdd.getCapacity();
        efficiency = goalCapacity / (float) availableSlots;
        toAdd.setLocation(Location(id, index.second / (SLOTS_PER_RACK + 1), index.second % (SLOTS_PER_RACK + 1)));
        servers.push_back(&toAdd);
        return true;
    } else {
        return false;
    }
}

void Group::allocatePools(int numPools) {
    sortServers();
    poolCapacities = std::vector<int>(numPools);
    for (std::vector<Server*>::iterator server = servers.begin(); server != servers.end(); ++server) {
        std::vector<int>::iterator minPoolCapacity = std::min_element(poolCapacities.begin(), poolCapacities.end());
        // Get index;
        int minPoolIndex = minPoolCapacity - poolCapacities.begin();
        // Update server.
        (*server) -> setPool(minPoolIndex);
        // Update pool capacity.
        (*minPoolCapacity) += (*server) -> getCapacity();
    }
}

float Group::getEfficiency() {
    return efficiency;
}

void Group::display() {
    std::cout << "====================Group " << id << "====================" << std::endl;
    std::cout << "Available Spots: " << availableSlots << std::endl;
    std::cout << "Efficiency: " << efficiency << std::endl;
    for (int i = 0; i < availability.size(); ++i) {
        std::cout << availability.at(i) << std::endl;
    }
}

void Group::displayServers() {
    std::cout << "====================Group " << id << "====================" << std::endl;
    for (int i = 0; i < servers.size(); ++i) {
        servers.at(i) -> display();
    }
}

std::pair<int, int> Group::findSmallestAvailableSlot(int size) {
    int minSize = INT_MAX, maxSlotIndex = -1, slotIndex = 0, index = -1;
    for (int i = 0; i < availability.size(); ++i) {
        if (availability.at(i) < minSize && availability.at(i) >= size) {
            minSize = availability.at(i);
            maxSlotIndex = slotIndex;
            index = i;
        }
        slotIndex += abs(availability.at(i));
    }
    if (index != -1) {
        maxSlotIndex += availability.at(index) - size;
    }
    return std::make_pair(index, maxSlotIndex);
}

void Group::setAvailabilityList(const std::vector<int>& occupancy) {
    int index = 0;
    availableSlots = 0;
    for (std::vector<int>::const_iterator it = occupancy.begin(); it != occupancy.end(); ++it) {
        availableSlots += *it - index;
        availability.push_back(*it - index);
        availability.push_back(-1);
        index = *it + 1;
    }
}

void Group::sortServers() {
    std::sort(servers.begin(), servers.end(), Server::serverComparator);
}
