#include "Server/Server.hpp"

Server::Server(int id, int size, int capacity) {
    this -> id = id;
    this -> size = size;
    this -> capacity = capacity;
}

void Server::setLocation(Location location) {
    this -> location = location;
}

void Server::setPool(int poolNumber) {
    this -> poolNumber = poolNumber;
}

int Server::getID() {
    return id;
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

const Location& Server::getLocation() const {
    return location;
}

void Server::display() {
    std::cout << "========Server ID: " << id << "========" << std::endl;
    std::cout << "Size: " << size << std::endl;
    std::cout << "Capacity: " << capacity << std::endl;
    std::cout << "Pool: " << poolNumber << std::endl;
    location.display();
}
