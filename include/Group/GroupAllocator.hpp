#ifndef GROUP_ALLOCATOR_H
#define GROUP_ALLOCATOR_H

#include <map>
#include <vector>
#include "Group/Group.hpp"

enum Method {
    EFFICIENCY = 0,
    CAPACITY,
};

class GroupAllocator {
    public:
        GroupAllocator() {}
        GroupAllocator(int numRacks, int numRacksPerGroup, int numGroups, int goalCapacity);
        void allocateGroups(const std::map<int, std::vector<int> >& unavailableSlots, Method method);
        void allocatePools(int numPools);
        void addServer(Server& toAdd, Method method);
        void displayGroup(int group);
        void displayGroups();
        void displayServers();
        void displayServers(int group);
        void calculateTotalPoolCapacity(int numPools);
        int calculateMinGuaranteedCapacity(int numPools);
    private:
        void sortGroups(Method method);
        int numRacks, numRacksPerGroup, numGroups, goalCapacity;
        std::vector<Group> groups;
        std::vector<int> totalPoolCapacity;
};

#endif
