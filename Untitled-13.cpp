#include <iostream>
#include <string>
using namespace std;
class Accommodation {
public:
    
    virtual void allocateRoom() = 0;
    virtual void vacateRoom() = 0;

    virtual ~Accommodation() {}
};

class HostelRoom : public Accommodation {
private:
    int roomNumber;
    string occupantName;
    bool isOccupied;

public:
    HostelRoom(int roomNumber)
        : roomNumber(roomNumber), occupantName(""), isOccupied(false) {}

    void allocateRoom() override {
        if (!isOccupied) {
            occupantName = "Student A";   
            isOccupied = true;
            cout << "Hostel Room " << roomNumber
                 << " allocated to " << occupantName << endl;
        } else {
            cout << "Room " << roomNumber << " is already occupied." << endl;
        }
    }
    void vacateRoom() override {
        if (isOccupied) {
            cout << "Room " << roomNumber
                 << " vacated by " << occupantName << endl;
            occupantName = "";
            isOccupied = false;
        } else {
            cout << "Room " << roomNumber << " is already empty." << endl;
        }
    }
};
class Apartment : public Accommodation {
private:
    string address;
    bool isOccupied;

public:
    Apartment(string address)
        : address(address), isOccupied(false) {}

    void allocateRoom() override {
        if (!isOccupied) {
            isOccupied = true;
            cout << "Apartment at [" << address << "] has been allocated." << endl;
        } else {
            cout << "Apartment at [" << address << "] is already occupied." << endl;
        }
    }

    void vacateRoom() override {
        if (isOccupied) {
            isOccupied = false;
            cout << "Apartment at [" << address << "] has been vacated." << endl;
        } else {
            cout << "Apartment at [" << address << "] is already empty." << endl;
        }
    }
};

int main() {
    
    Accommodation* acc1 = new HostelRoom(204);
    Accommodation* acc2 = new Apartment("Block C, Flat 7");

    acc1->allocateRoom();
    acc1->vacateRoom();
    acc1->vacateRoom();   

    cout << endl;

    acc2->allocateRoom();
    acc2->allocateRoom();   
    acc2->vacateRoom();

    delete acc1;
    delete acc2;

    return 0;
}