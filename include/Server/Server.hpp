#ifndef SERVER_H
#define SERVER_H

class Server {
    public:
        Server(int id, int size, int capacity);
        void setLocation(int rackNumber, int slotNumber);
        void setPool(int poolNumber);
        int getID();
        int getRackNumber();
        int getSlotNumber();
        int getPoolNumber();
        int getSize();
        int getCapacity();
    private:
        int id, rackNumber, slotNumber, poolNumber, size, capacity;
};

#endif
