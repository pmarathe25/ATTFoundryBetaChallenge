#include <vector>

const int SLOTS_PER_RACK = 43;

class Group {
    public:
        Group(int id);
        Group(int id, std::vector<int> occupancy);
        void addServer(Server& toAdd);
    private:
        int id;
        std::vector<int> availability;
};
