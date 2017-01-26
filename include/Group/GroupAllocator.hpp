#include <map>

class GroupAllocator {
    public:
        GroupAllocator(int numRacks, int numRacksPerGroup);
        allocate(std::map<int, int> unavailableSlots);
    private:
        int numRacks, numRacksPerGroup, numGroups;

};
