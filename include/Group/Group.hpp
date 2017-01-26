#ifndef GROUP_H
#define GROUP_H

#include <vector>
#include "Server/Server.hpp"

const int SLOTS_PER_RACK = 42;

class Group {
    public:
        Group(int id);
        Group(int id, std::vector<int> occupancy);
        void addServer(Server& toAdd);
        void display();
    private:
        int id;
        std::vector<int> availability;
};

#endif
