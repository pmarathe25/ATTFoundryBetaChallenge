#ifndef GROUP_ALLOCATOR_H
#define GROUP_ALLOCATOR_H

#include <map>
#include <vector>
#include "Group/Group.hpp"

class GroupAllocator {
    public:
        GroupAllocator(int numRacks, int numRacksPerGroup, int goalCapacity);
        void allocate(std::map<int, std::vector<int> > unavailableSlots);
        void allocatePools(int numPools);
        void addServer(Server& toAdd);
        void display();
        void displayServers();
    private:
        int numRacks, numRacksPerGroup, numGroups, goalCapacity;
        std::vector<Group> groups;
};

#endif
