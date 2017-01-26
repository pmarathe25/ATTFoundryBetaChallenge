#include "Group/GroupAllocator.hpp"

GroupAllocator::GroupAllocator(int numRacks, int numRacksPerGroup) {
    this -> numRacks = numRacks;
    this -> numRacksPerGroup = numRacksPerGroup;
    this -> numGroups = numRacks / numRacksPerGroup;
}

void GroupAllocator::allocate(std::map<int, std::vector<int> > unavailableSlots) {
    // Assumes the map contains every rack even if it has no unavailable slots.
    std::vector<int> groupOccupancy;
    int rackNumber;
    for (int i = 0; i < numGroups; ++i) {
        groupOccupancy.clear();
        rackNumber = i * numRacksPerGroup;
        // Iterate over each group and input a vector of all the unavailable slots in that group.
        for (int j = 0; j < numRacksPerGroup; ++j) {
            // Grab the vector of all the unavailableSlots in this rack and iterate through it.
            for (std::vector<int>::iterator it = unavailableSlots.at(rackNumber).begin(); it != unavailableSlots.at(rackNumber).end(); ++it) {
                // Compute a single number corresponding to the occupied slot number.
                groupOccupancy.push_back(j * SLOTS_PER_RACK + *it);
            }
            // Mark the end of each rack.
            groupOccupancy.push_back((j + 1) * SLOTS_PER_RACK);
        }
        groups.push_back(Group(i, groupOccupancy));
        ++rackNumber;
    }
}

void GroupAllocator::display() {
    for (int i = 0; i < numGroups; ++i) {
        groups.at(i).display();
    }
}
