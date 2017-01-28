#ifndef GROUP_ALLOCATOR_H
#define GROUP_ALLOCATOR_H

#include <map>
#include <vector>
#include "Group/Group.hpp"

class GroupAllocator {
    public:
        GroupAllocator() {}
        GroupAllocator(int numRacks, int numRacksPerGroup, int goalCapacity);
        void allocateGroups(std::map<int, std::vector<int> > unavailableSlots);
        void allocatePools(int numPools);
        void addServer(Server& toAdd);
        void displayGroups();
        void displayServers();
    private:
        void sortGroups();
        int numRacks, numRacksPerGroup, numGroups, goalCapacity;
        std::vector<Group> groups;
};

#endif
