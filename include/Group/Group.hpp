#ifndef GROUP_H
#define GROUP_H
#include <vector>
#include <utility>
#include "Server/Server.hpp"

const int SLOTS_PER_RACK = 42;

class Group {
    public:
        Group(int id, int goalCapacity);
        Group(int id, int goalCapacity, const std::vector<int>& occupancy);
        bool addServer(Server& toAdd);
        void allocatePools(int numPools);
        float getEfficiency();
        int getGoalCapacity();
        void display();
        void displayServers();
        int getPoolCapacity(int pool);
        bool static groupEfficiencyComparator(Group& a, Group& b) {
            return a.getEfficiency() > b.getEfficiency();
        }
        bool static groupCapacityComparator(Group& a, Group& b) {
            return a.getGoalCapacity() > b.getGoalCapacity();
        }
    private:
        std::pair<int, int> findSmallestAvailableSlot(int size);
        void setAvailabilityList(const std::vector<int>& occupancy);
        void sortServers();
        int id, goalCapacity, availableSlots;
        float efficiency;
        std::vector<int> availability;
        std::vector<int> poolCapacities;
        std::vector<Server*> servers;
};

#endif
