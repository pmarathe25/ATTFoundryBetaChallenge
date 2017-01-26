#ifndef GROUP_ALLOCATOR_H
#define GROUP_ALLOCATOR_H

#include <map>
#include <vector>
#include "Group/Group.hpp"

class GroupAllocator {
    public:
        GroupAllocator(int numRacks, int numRacksPerGroup);
        void allocate(std::map<int, std::vector<int> > unavailableSlots);
        void display();
    private:
        int numRacks, numRacksPerGroup, numGroups;
        std::vector<Group> groups;
};

#endif
