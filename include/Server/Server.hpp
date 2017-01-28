#ifndef SERVER_H
#define SERVER_H
#include <iostream>

class Location {
    public:
        Location() {}
        Location(int group, int rack, int slot) {
            this -> group = group;
            this -> rack = rack;
            this -> slot = slot;
        }
        void display() const {
            std::cout << "Group Number: " << group << std::endl;
            std::cout << "Rack Number: " << rack << std::endl;
            std::cout << "Slot Number: " << slot << std::endl;
        }
        int group, rack, slot;
};

class Server {
    public:
        Server(int id, int size, int capacity);
        void setLocation(Location location);
        void setPool(int poolNumber);
        int getID();
        int getPoolNumber();
        int getSize();
        int getCapacity();
        const Location& getLocation() const;
        void display();
        bool static serverCapacityComparator(Server* a, Server* b) {
            return a -> getCapacity() > b -> getCapacity();
        }
        bool static serverSizeComparator(Server* a, Server* b) {
            return a -> getSize() > b -> getSize();
        }
    private:
        int id, poolNumber, size, capacity;
        Location location;
};

#endif
