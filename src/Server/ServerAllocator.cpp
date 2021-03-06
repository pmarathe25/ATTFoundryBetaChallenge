#include <fstream>
#include <algorithm>
#include "Server/ServerAllocator.hpp"

ServerAllocator::ServerAllocator(Method method) {
    this -> method = method;
}

void ServerAllocator::allocateServers() {
    createMaps();
    switch (method) {
        case EFFICIENCY:
            for (std::map<float, std::vector<Server*> >::reverse_iterator serverSet = serversByEfficiency.rbegin(); serverSet != serversByEfficiency.rend(); ++serverSet) {
                for (std::vector<Server*>::iterator server = (serverSet -> second).begin(); server != (serverSet -> second).end(); ++server) {
                    groupAllocator.addServer(**server, method);
                }
            }
            break;
        case CAPACITY:
            for (std::map<int, std::vector<Server*> >::iterator serverSet = serversByCapacity.begin(); serverSet != serversByCapacity.end(); ++serverSet) {
                for (std::vector<Server*>::reverse_iterator server = (serverSet -> second).rbegin(); server != (serverSet -> second).rend(); ++server) {
                    groupAllocator.addServer(**server, method);
                }
            }
            break;
    }
    groupAllocator.allocatePools(numPools);
    minGuaranteedCapacity = groupAllocator.calculateMinGuaranteedCapacity(numPools);
}

void ServerAllocator::displayServers() {
    for (int i = 0; i < servers.size(); ++i) {
        servers.at(i).display();
    }
}

void ServerAllocator::displayServer(int server) {
    if (server < servers.size()) {
        servers.at(server).display();
    } else {
        std::cout << "Server " << server << " does not exist." << std::endl;
    }
}

void ServerAllocator::displayServersByGroup() {
    groupAllocator.displayServers();
}

void ServerAllocator::displayServersByGroup(int group) {
    groupAllocator.displayServers(group);
}

void ServerAllocator::displayGroup(int group) {
    groupAllocator.displayGroup(group);
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
    }
    numGroups = numRacks / numRacksPerGroup;
    groupAllocator = GroupAllocator(numRacks, numRacksPerGroup, numGroups, int(totalCapacity / numGroups));
    groupAllocator.allocateGroups(occupancy, method);
    inputFile.close();
}

void ServerAllocator::write(const std::string& filename) {
    std::ofstream outputFile(filename);
    for (int i = 0; i < servers.size(); ++i) {
        if (servers.at(i).isAllocated()) {
            outputFile << numRacksPerGroup * servers.at(i).getLocation().group + servers.at(i).getLocation().rack << " " << servers.at(i).getLocation().slot << " " << servers.at(i).getPoolNumber() << std::endl;
        } else {
            outputFile << "x" << std::endl;
        }
    }
    outputFile.close();
}

void ServerAllocator::createMaps() {
    for (int i = 0; i < servers.size(); ++i) {
        int capacity = servers.at(i).getCapacity();
        switch (method) {
            case EFFICIENCY:
                serversByEfficiency[capacity / (float) servers.at(i).getSize()].push_back(&servers.at(i));
                break;
            case CAPACITY:
                serversByCapacity[capacity].push_back(&servers.at(i));
                break;
        }
    }
    switch (method) {
        case EFFICIENCY:
            // Sort servers by efficiency by size.
            for (std::map<float, std::vector<Server*> >::iterator serverSet = serversByEfficiency.begin(); serverSet != serversByEfficiency.end(); ++serverSet) {
                std::sort((serverSet -> second).begin(), (serverSet -> second).end(), Server::serverSizeComparator);
            }
            break;
        case CAPACITY:
            // Sort servers by capacity by size
            for (std::map<int, std::vector<Server*> >::iterator serverSet = serversByCapacity.begin(); serverSet != serversByCapacity.end(); ++serverSet) {
                std::sort((serverSet -> second).begin(), (serverSet -> second).end(), Server::serverSizeComparator);
            }
            break;
    }
}
