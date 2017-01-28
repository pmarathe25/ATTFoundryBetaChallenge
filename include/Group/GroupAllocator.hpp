#ifndef GROUP_ALLOCATOR_H
#define GROUP_ALLOCATOR_H

#include <map>
#include <vector>
#include "Group/Group.hpp"

class GroupAllocator {
    public:
        GroupAllocator() {}
        GroupAllocator(int numRacks, int numRacksPerGroup, int numGroups, int goalCapacity);
        void allocateGroups(const std::map<int, std::vector<int> >& unavailableSlots);
        void allocatePools(int numPools);
        void addServer(Server& toAdd);
        void displayGroups();
        void displayServers();
        void calculateTotalPoolCapacity(int numPools);
        int calculateMinGuaranteedCapacity(int numPools);
    private:
        void sortGroups();
        int numRacks, numRacksPerGroup, numGroups, goalCapacity;
        std::vector<Group> groups;
        std::vector<int> totalPoolCapacity;
};

#endif
