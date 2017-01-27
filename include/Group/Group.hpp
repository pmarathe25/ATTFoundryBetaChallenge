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
        void addServer(Server& toAdd);
        void allocatePools(int numPools);
        float getEfficiency();
        void display();
        void displayServers();
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
