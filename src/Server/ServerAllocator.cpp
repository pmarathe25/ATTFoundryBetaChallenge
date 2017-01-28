#include <fstream>
#include <algorithm>
#include "Server/ServerAllocator.hpp"

ServerAllocator::ServerAllocator(const std::string& filename) {
    read(filename);
    numGroups = numRacks / numRacksPerGroup;
    groupAllocator = GroupAllocator(numRacks, numRacksPerGroup, numGroups, int(totalCapacity / numGroups));
    groupAllocator.allocateGroups(occupancy);
    for (std::map<float, std::vector<Server*> >::reverse_iterator serverSet = serversByEfficiency.rbegin(); serverSet != serversByEfficiency.rend(); ++serverSet) {
        for (std::vector<Server*>::iterator server = (serverSet -> second).begin(); server != (serverSet -> second).end(); ++server) {
            groupAllocator.addServer(**server);
        }
    }
    groupAllocator.allocatePools(numPools);
    minGuaranteedCapacity = groupAllocator.calculateMinGuaranteedCapacity(numPools);
}

void ServerAllocator::displayServers() {
    for (int i = 0; i < servers.size(); ++i) {
        servers.at(i).display();
    }
}

void ServerAllocator::displayServersByGroup() {
    groupAllocator.displayServers();
}

void ServerAllocator::displayGroups() {
    groupAllocator.displayGroups();
}

void ServerAllocator::displayMinGuaranteedCapacity() {
    std::cout << "MINIMUM GUARANTEED CAPACITY: " << minGuaranteedCapacity << std::endl;
}

void ServerAllocator::read(const std::string& filename) {
    std::ifstream inputFile(filename);
    int numUnavailableLines, numServerLines;
    inputFile >> numRacks >> numRacksPerGroup >> numUnavailableLines >> numPools >> numServerLines;
    // Reserve space for servers.
    servers.reserve(numServerLines);
    // Read unavailable.
    for (int i = 0; i < numUnavailableLines; ++i) {
        int rackNumber, slotNumber;
        inputFile >> rackNumber >> slotNumber;
        occupancy[rackNumber].push_back(slotNumber);
    }
    for (int i = 0; i < numServerLines; ++i) {
        int size, capacity;
        inputFile >> size >> capacity;
        totalCapacity += capacity;
        servers.push_back(Server(i, size, capacity));
        serversByEfficiency[capacity / (float) size].push_back(&servers.back());
    }
    // Sort servers.
    for (std::map<float, std::vector<Server*> >::iterator serverSet = serversByEfficiency.begin(); serverSet != serversByEfficiency.end(); ++serverSet) {
        std::sort((serverSet -> second).begin(), (serverSet -> second).end(), Server::serverSizeComparator);
    }
    inputFile.close();
}
