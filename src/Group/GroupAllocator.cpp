#include "Group/GroupAllocator.hpp"
#include <algorithm>
#include <iostream>

GroupAllocator::GroupAllocator(int numRacks, int numRacksPerGroup, int numGroups, int goalCapacity) {
    this -> numRacks = numRacks;
    this -> numRacksPerGroup = numRacksPerGroup;
    this -> numGroups = numGroups;
    this -> goalCapacity = goalCapacity;
}

void GroupAllocator::allocateGroups(const std::map<int, std::vector<int> >& unavailableSlots, Method method) {
    std::vector<int> groupOccupancy;
    int rackNumber;
    for (int i = 0; i < numGroups; ++i) {
        groupOccupancy.clear();
        rackNumber = i * numRacksPerGroup;
        // Iterate over each group and input a vector of all the unavailable slots in that group.
        for (int j = 0; j < numRacksPerGroup; ++j) {
            if (unavailableSlots.count(rackNumber) > 0) {
                // Grab the vector of all the unavailableSlots in this rack and iterate through it.
                for (std::vector<int>::const_iterator it = unavailableSlots.at(rackNumber).begin(); it != unavailableSlots.at(rackNumber).end(); ++it) {
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
    }
    for (int i = 0; i < numGroups; ++i) {
        sortedGroups.push_back(&groups.at(i));
    }
    sortGroups(method);
}

void GroupAllocator::allocatePools(int numPools) {
    for (int i = 0; i < numGroups; ++i) {
        groups.at(i).allocatePools(numPools);
    }
}

void GroupAllocator::addServer(Server& toAdd, Method method) {
    // Find a place to add the server.
    bool serverAdded = false;
    int groupModified = -1;
    for (int i = 0; i < sortedGroups.size() && !serverAdded; ++i) {
        serverAdded = sortedGroups.at(i) -> addServer(toAdd);
        if (serverAdded) {
            groupModified = i;
        }
    }
    // Moves the group that was just modified (if there was a group modified).
    if (groupModified != -1) {
        int index = 0;
        switch (method) {
            case EFFICIENCY:
            for (int i = 0; i < sortedGroups.size(); ++i) {
                if (sortedGroups.at(groupModified) -> getEfficiency() < sortedGroups.at(i) -> getEfficiency() && i != groupModified) {
                    index = i;
                }
            }
            break;
            case CAPACITY:
            for (int i = 0; i < groups.size(); ++i) {
                if (sortedGroups.at(groupModified) -> getGoalCapacity() < sortedGroups.at(i) -> getGoalCapacity() && i != groupModified) {
                    index = i;
                }
            }
            break;
        }
        Group* temp = sortedGroups.at(groupModified);
        sortedGroups.erase(groupModified + sortedGroups.begin());
        sortedGroups.insert(index + sortedGroups.begin(), temp);
    }
}

void GroupAllocator::displayGroup(int group) {
    groups.at(group).display();
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

void GroupAllocator::displayServers(int group) {
    groups.at(group).displayServers();
}

void GroupAllocator::calculateTotalPoolCapacity(int numPools) {
    totalPoolCapacity = std::vector<int> (numPools);
    for (int i = 0; i < numGroups; ++i) {
        for (int j = 0; j < numPools; ++j) {
            totalPoolCapacity.at(j) += groups.at(i).getPoolCapacity(j);
        }
    }
}

int GroupAllocator::calculateMinGuaranteedCapacity(int numPools) {
    calculateTotalPoolCapacity(numPools);
    int minGuaranteedCapacity = totalPoolCapacity.at(0);
    for (int i = 0; i < numGroups; ++i) {
        for (int j = 0; j < numPools; ++j) {
            int candidateCapacity = totalPoolCapacity.at(j) - groups.at(i).getPoolCapacity(j);
            if (candidateCapacity < minGuaranteedCapacity) {
                minGuaranteedCapacity = candidateCapacity;
            }
        }
    }
    return minGuaranteedCapacity;
}

void GroupAllocator::sortGroups(Method method) {
    switch (method) {
        case EFFICIENCY:
            std::sort(sortedGroups.begin(), sortedGroups.end(), Group::groupEfficiencyComparator);
            break;
        case CAPACITY:
            std::sort(sortedGroups.begin(), sortedGroups.end(), Group::groupCapacityComparator);
            break;
    }
}
