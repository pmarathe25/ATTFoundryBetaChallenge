#include "Group/GroupAllocator.hpp"
#include <algorithm>
#include <iostream>

GroupAllocator::GroupAllocator(int numRacks, int numRacksPerGroup, int goalCapacity) {
    this -> numRacks = numRacks;
    this -> numRacksPerGroup = numRacksPerGroup;
    this -> numGroups = numRacks / numRacksPerGroup;
    this -> goalCapacity = goalCapacity;
}

void GroupAllocator::allocateGroups(std::map<int, std::vector<int> > unavailableSlots) {
    // Assumes the map contains every rack even if it has no unavailable slots.
    std::vector<int> groupOccupancy;
    int rackNumber;
    for (int i = 0; i < numGroups; ++i) {
        groupOccupancy.clear();
        rackNumber = i * numRacksPerGroup;
        // Iterate over each group and input a vector of all the unavailable slots in that group.
        for (int j = 0; j < numRacksPerGroup; ++j) {
            // Grab the vector of all the unavailableSlots in this rack and iterate through it.
            if (unavailableSlots.count(rackNumber) > 0) {
                for (std::vector<int>::iterator it = unavailableSlots.at(rackNumber).begin(); it != unavailableSlots.at(rackNumber).end(); ++it) {
                    // Compute a single number corresponding to the occupied slot number.
                    groupOccupancy.push_back(j * (SLOTS_PER_RACK + 1) + *it);
                }
            }
            // Mark the end of each rack.
            groupOccupancy.push_back((j + 1) * SLOTS_PER_RACK + j);
            ++rackNumber;
        }
        // Group created.
        groups.push_back(Group(i, goalCapacity, groupOccupancy));
        sortGroups();
    }
}

void GroupAllocator::allocatePools(int numPools) {
    for (int i = 0; i < numGroups; ++i) {
        groups.at(i).allocatePools(numPools);
    }
}

void GroupAllocator::addServer(Server& toAdd) {
    // Find a place to add the server.
    bool serverAdded = false;
    int groupModified;
    for (int i = 0; i < groups.size() && !serverAdded; ++i) {
        serverAdded = groups.at(i).addServer(toAdd);
        groupModified = i;
    }
    // Moves the group that was just modified.
    int index = 0;
    for (int i = 0; i < groups.size(); ++i) {
        if (groups.at(groupModified).getEfficiency() < groups.at(i).getEfficiency() && i != groupModified) {
            index = i;
        }
    }
    Group temp = groups.at(groupModified);
    groups.erase(groupModified + groups.begin());
    groups.insert(index + groups.begin(), temp);
}

void GroupAllocator::displayGroups() {
    for (int i = 0; i < numGroups; ++i) {
        groups.at(i).display();
    }
}

void GroupAllocator::displayServers() {
    for (int i = 0; i < numGroups; ++i) {
        groups.at(i).displayServers();
    }
}

void GroupAllocator::sortGroups() {
    std::sort(groups.begin(), groups.end(), Group::groupComparator);
}
