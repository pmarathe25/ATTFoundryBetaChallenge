#ifndef SERVER_ALLOCATOR_H
#define SERVER_ALLOCATOR_H
#include "Server/Server.hpp"
#include "Group/GroupAllocator.hpp"
#include <vector>
#include <string>

class ServerAllocator {
    public:
        ServerAllocator(Method method);
        void allocateServers();
        void displayServers();
        void displayServer(int server);
        void displayServersByGroup();
        void displayServersByGroup(int group);
        void displayGroup(int group);
        void displayGroups();
        void displayMinGuaranteedCapacity();
        void read(const std::string& filename);
        void write(const std::string& filename);
    private:
        void createMaps();
        std::vector<Server> servers;
        std::map<float, std::vector<Server*> > serversByEfficiency;
        std::map<int, std::vector<Server*> > serversByCapacity;
        std::map<int, std::vector<int> > occupancy;
        GroupAllocator groupAllocator;
        Method method;
        int numRacks, numRacksPerGroup, numGroups, numPools, totalCapacity = 0, minGuaranteedCapacity;
};

#endif
