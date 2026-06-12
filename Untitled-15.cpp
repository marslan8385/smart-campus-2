#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    string name;
    int age;
public:
    Person(string name, int age) : name(name), age(age) {}
    virtual void displayInfo() {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
    string getName() { return name; }
    virtual ~Person() {}
};

class Student : public Person {
private:
    string rollNo;
    int semester;
    double GPA;
public:
    Student(string name, int age, string rollNo, int semester, double GPA)
        : Person(name, age), rollNo(rollNo), semester(semester), GPA(GPA) {}

    void displayInfo() override {
        cout << "    >> " << name
             << " | Roll: " << rollNo
             << " | Sem: "  << semester
             << " | GPA: "  << GPA << endl;
    }
    string getRollNo() { return rollNo; }
    double getGPA()    { return GPA; }
};

enum class RoomType { SINGLE = 1, DOUBLE = 2, TRIPLE = 3 };

string roomTypeToString(RoomType t) {
    switch (t) {
        case RoomType::SINGLE: return "Single";
        case RoomType::DOUBLE: return "Double";
        case RoomType::TRIPLE: return "Triple";
        default:               return "Unknown";
    }
}

class Room {
private:
    int roomNumber;
    RoomType type;
    int floor;
    Student** occupants;
    int capacity;
    int currentCount;

public:
  
    Room() : roomNumber(0), type(RoomType::SINGLE),
             floor(0), currentCount(0), capacity(1) {
        occupants = new Student*[1];
        occupants[0] = nullptr;
    }

   
    Room(int roomNumber, RoomType type, int floor)
        : roomNumber(roomNumber), type(type),
          floor(floor), currentCount(0) {
        capacity  = static_cast<int>(type);
        occupants = new Student*[capacity];
        for (int i = 0; i < capacity; i++)
            occupants[i] = nullptr;
    }

    Room(const Room& other)
        : roomNumber(other.roomNumber), type(other.type),
          floor(other.floor), capacity(other.capacity),
          currentCount(other.currentCount) {
        occupants = new Student*[capacity];
        for (int i = 0; i < capacity; i++)
            occupants[i] = other.occupants[i];   
    }
    
    Room& operator=(const Room& other) {
        if (this == &other) return *this;
        delete[] occupants;
        roomNumber   = other.roomNumber;
        type         = other.type;
        floor        = other.floor;
        capacity     = other.capacity;
        currentCount = other.currentCount;
        occupants    = new Student*[capacity];
        for (int i = 0; i < capacity; i++)
            occupants[i] = other.occupants[i];
        return *this;
    }

    
    bool addOccupant(Student* student) {
        if (currentCount >= capacity) {
            cout << "  [!] Room " << roomNumber << " is full." << endl;
            return false;
        }
        occupants[currentCount++] = student;
        cout << "  [+] " << student->getName()
             << " assigned to Room " << roomNumber << "." << endl;
        return true;
    }


    bool removeOccupant(const string& rollNo) {
        for (int i = 0; i < currentCount; i++) {
            if (occupants[i]->getRollNo() == rollNo) {
                cout << "  [-] " << occupants[i]->getName()
                     << " removed from Room " << roomNumber << "." << endl;
                for (int j = i; j < currentCount - 1; j++)
                    occupants[j] = occupants[j + 1];
                occupants[--currentCount] = nullptr;
                return true;
            }
        }
        cout << "  [!] Roll No " << rollNo
             << " not found in Room " << roomNumber << "." << endl;
        return false;
    }

    
    void displayInfo() const {
        cout << "    Room " << roomNumber
             << " [" << roomTypeToString(type) << "]"
             << " | Floor " << floor
             << " | " << currentCount << "/" << capacity << " occupied" << endl;
        for (int i = 0; i < currentCount; i++)
            occupants[i]->displayInfo();
        if (currentCount == 0)
            cout << "    >> (vacant)" << endl;
    }

    int  getRoomNumber()   const { return roomNumber; }
    bool isFull()          const { return currentCount >= capacity; }
    bool isEmpty()         const { return currentCount == 0; }
    int  getCurrentCount() const { return currentCount; }
    int  getCapacity()     const { return capacity; }

    ~Room() { delete[] occupants; }
};

class HostelBlock {
private:
    string blockName;
    Room*  rooms;        
    int    totalRooms;
    int    roomCount;

public:
    
    HostelBlock(string blockName, int totalRooms)
        : blockName(blockName), totalRooms(totalRooms), roomCount(0) {
        rooms = new Room[totalRooms];   
    }

    bool addRoom(int roomNumber, RoomType type, int floor) {
        if (roomCount >= totalRooms) {
            cout << "  [!] Block " << blockName << " is at full room capacity." << endl;
            return false;
        }
        rooms[roomCount++] = Room(roomNumber, type, floor);
        cout << "  [+] Room " << roomNumber
             << " added to Block " << blockName << "." << endl;
        return true;
    }

    Room* findRoom(int roomNumber) {
        for (int i = 0; i < roomCount; i++)
            if (rooms[i].getRoomNumber() == roomNumber)
                return &rooms[i];
        return nullptr;
    }


    bool assignStudent(Student* student) {
        for (int i = 0; i < roomCount; i++) {
            if (!rooms[i].isFull())
                return rooms[i].addOccupant(student);
        }
        cout << "  [!] No available room in Block " << blockName << "." << endl;
        return false;
    }


    void displayInfo() const {
        cout << "┌─────────────────────────────────────────┐" << endl;
        cout << "  Block : " << blockName << endl;
        cout << "  Rooms : " << roomCount << " / " << totalRooms << endl;
        cout << "├─────────────────────────────────────────┤" << endl;
        for (int i = 0; i < roomCount; i++)
            rooms[i].displayInfo();
        cout << "└─────────────────────────────────────────┘" << endl;
    }

    int getTotalBeds() const {
        int beds = 0;
        for (int i = 0; i < roomCount; i++)
            beds += rooms[i].getCapacity();
        return beds;
    }

    int getOccupiedBeds() const {
        int occupied = 0;
        for (int i = 0; i < roomCount; i++)
            occupied += rooms[i].getCurrentCount();
        return occupied;
    }

    string getBlockName() const { return blockName; }
    int    getRoomCount() const { return roomCount; }

    ~HostelBlock() { delete[] rooms; }
};


class HostelManager {
private:
    string       hostelName;
    HostelBlock** blocks;       
    int          maxBlocks;
    int          blockCount;

public:
    HostelManager(string hostelName, int maxBlocks)
        : hostelName(hostelName), maxBlocks(maxBlocks), blockCount(0) {
        blocks = new HostelBlock*[maxBlocks];
        for (int i = 0; i < maxBlocks; i++)
            blocks[i] = nullptr;
    }


    bool addBlock(const string& blockName, int totalRooms) {
        if (blockCount >= maxBlocks) {
            cout << "[!] Cannot add more blocks." << endl;
            return false;
        }
        blocks[blockCount++] = new HostelBlock(blockName, totalRooms);
        cout << "[+] Block '" << blockName << "' added to " << hostelName << "." << endl;
        return true;
    }

    HostelBlock* findBlock(const string& blockName) {
        for (int i = 0; i < blockCount; i++)
            if (blocks[i]->getBlockName() == blockName)
                return blocks[i];
        return nullptr;
    }

    
    bool addRoomToBlock(const string& blockName, int roomNo,
                        RoomType type, int floor) {
        HostelBlock* block = findBlock(blockName);
        if (!block) {
            cout << "[!] Block '" << blockName << "' not found." << endl;
            return false;
        }
        return block->addRoom(roomNo, type, floor);
    }

    bool assignStudentToBlock(const string& blockName, Student* student) {
        HostelBlock* block = findBlock(blockName);
        if (!block) {
            cout << "[!] Block '" << blockName << "' not found." << endl;
            return false;
        }
        return block->assignStudent(student);
    }

    
    bool removeStudentFromRoom(const string& blockName,
                               int roomNo, const string& rollNo) {
        HostelBlock* block = findBlock(blockName);
        if (!block) {
            cout << "[!] Block '" << blockName << "' not found." << endl;
            return false;
        }
        Room* room = block->findRoom(roomNo);
        if (!room) {
            cout << "[!] Room " << roomNo << " not found in Block "
                 << blockName << "." << endl;
            return false;
        }
        return room->removeOccupant(rollNo);
    }

    void displayInfo() const {
        cout << "\n╔═════════════════════════════════════════╗" << endl;
        cout << "  Hostel : " << hostelName                     << endl;
        cout << "  Blocks : " << blockCount                     << endl;
        cout << "╚═════════════════════════════════════════╝" << endl;
        for (int i = 0; i < blockCount; i++)
            blocks[i]->displayInfo();
    }

    void displayStats() const {
        int totalBeds = 0, occupiedBeds = 0;
        for (int i = 0; i < blockCount; i++) {
            totalBeds    += blocks[i]->getTotalBeds();
            occupiedBeds += blocks[i]->getOccupiedBeds();
        }
        cout << "\n── Hostel Statistics ──────────────────────" << endl;
        cout << "  Total beds    : " << totalBeds              << endl;
        cout << "  Occupied beds : " << occupiedBeds           << endl;
        cout << "  Vacant beds   : " << (totalBeds-occupiedBeds) << endl;
        cout << "───────────────────────────────────────────" << endl;
    }

    ~HostelManager() {
        for (int i = 0; i < blockCount; i++)
            delete blocks[i];
        delete[] blocks;
    }
};


int main() {
    
    Student s1("Ali",   20, "CS-101", 3, 3.8);
    Student s2("Babar",     21, "CS-102", 3, 3.2);
Student s3("Hamza", 19, "CS-103", 2, 3.5);
    Student s4("Subhan",   22, "CS-104", 4, 2.9);
    Student s5("Ahmed",     20, "CS-105", 2, 3.6);

    
    HostelManager hostel("Green Valley Hostel", 3);
    hostel.addBlock("Block A", 3);
    hostel.addBlock("Block B", 3);

    cout << "\n── Adding Rooms ───────────────────────────" << endl;
    hostel.addRoomToBlock("Block A", 101, RoomType::SINGLE, 1);
    hostel.addRoomToBlock("Block A", 102, RoomType::DOUBLE, 1);
    hostel.addRoomToBlock("Block A", 103, RoomType::TRIPLE, 2);

    hostel.addRoomToBlock("Block B", 201, RoomType::DOUBLE, 1);
    hostel.addRoomToBlock("Block B", 202, RoomType::TRIPLE, 2);

    
    cout << "\n── Assigning Students ─────────────────────" << endl;
    hostel.assignStudentToBlock("Block A", &s1);
    hostel.assignStudentToBlock("Block A", &s2);
    hostel.assignStudentToBlock("Block A", &s3);
    hostel.assignStudentToBlock("Block B", &s4);
    hostel.assignStudentToBlock("Block B", &s5);

    hostel.displayInfo();
    hostel.displayStats();
    cout << "\n── Removing Student ───────────────────────" << endl;
    hostel.removeStudentFromRoom("Block A", 102, "CS-102");

    hostel.displayStats();

    return 0;
}