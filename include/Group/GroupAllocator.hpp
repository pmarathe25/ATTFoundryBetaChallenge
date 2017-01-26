#include <map>
#include <vector>

class GroupAllocator {
    public:
        GroupAllocator(int numRacks, int numRacksPerGroup);
        allocate(std::map<int, std::vector<int> > unavailableSlots);
    private:
        int numRacks, numRacksPerGroup, numGroups;

};
