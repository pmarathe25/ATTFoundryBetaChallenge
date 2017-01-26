#include "Server/Server.hpp"

Server::Server(int id, int size, int capacity) {
    this -> id = id;
    this -> size = size;
    this -> capacity = capacity;
}

void Server::setLocation(int rackNumber, int slotNumber) {
    this -> rackNumber = rackNumber;
    this -> slotNumber = slotNumber;
}

void Server::setPool(int poolNumber) {
    this -> poolNumber = poolNumber;
}

int Server::getID() {
    return id;
}

int Server::getRackNumber() {
    return rackNumber;
}

int Server::getSlotNumber() {
    return slotNumber;
}

int Server::getPoolNumber() {
    return poolNumber;
}

int Server::getSize() {
    return size;
}

int Server::getCapacity() {
    return capacity;
}
