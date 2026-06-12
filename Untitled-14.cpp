#include <iostream>
#include <string>
using namespace std;
class Student;

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
        cout << "  Student | Name: " << name
             << " | Roll: " << rollNo
             << " | Sem: "  << semester
             << " | GPA: "  << GPA << endl;
    }

    string getRollNo() { return rollNo; }
    double getGPA()    { return GPA; }
};


enum class RoomType { SINGLE = 1, DOUBLE = 2, TRIPLE = 3 };

string roomTypeToString(RoomType type) {
    switch (type) {
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
    
    Room(int roomNumber, RoomType type, int floor)
        : roomNumber(roomNumber), type(type), floor(floor), currentCount(0) {
        capacity = static_cast<int>(type);          
        occupants = new Student*[capacity];
        for (int i = 0; i < capacity; i++)
            occupants[i] = nullptr;
    }

    bool addOccupant(Student* student) {
        if (currentCount >= capacity) {
            cout << "Room " << roomNumber << " is full. Cannot add "
                 << student->getName() << "." << endl;
            return false;
        }
        occupants[currentCount++] = student;
        cout << student->getName() << " added to Room "
             << roomNumber << "." << endl;
        return true;
    }

    bool removeOccupant(const string& rollNo) {
        for (int i = 0; i < currentCount; i++) {
            if (occupants[i]->getRollNo() == rollNo) {
                cout << occupants[i]->getName()
                     << " removed from Room " << roomNumber << "." << endl;
                
                for (int j = i; j < currentCount - 1; j++)
                    occupants[j] = occupants[j + 1];
                occupants[--currentCount] = nullptr;
                return true;
            }
        }
        cout << "Student with Roll No " << rollNo
             << " not found in Room " << roomNumber << "." << endl;
        return false;
    }
    
    void displayInfo() const {
        cout << "─────────────────────────────────────" << endl;
        cout << "Room No : " << roomNumber             << endl;
        cout << "Type    : " << roomTypeToString(type) << endl;
        cout << "Floor   : " << floor                  << endl;
        cout << "Occupancy: " << currentCount << "/" << capacity << endl;
        if (currentCount == 0) {
            cout << "  (vacant)" << endl;
        } else {
            cout << "Occupants:" << endl;
            for (int i = 0; i < currentCount; i++)
                occupants[i]->displayInfo();
        }
        cout << "─────────────────────────────────────" << endl;
    }

    int     getRoomNumber()  const { return roomNumber; }
    int     getFloor()       const { return floor; }
    int     getCapacity()    const { return capacity; }
    int     getCurrentCount()const { return currentCount; }
    bool    isFull()         const { return currentCount == capacity; }
    bool    isEmpty()        const { return currentCount == 0; }
    RoomType getType()       const { return type; }

    
    ~Room() {
        delete[] occupants;   
    }
};

int main() {
    
    Student s1("Ali",  20, "CS-101", 3, 3.8);
    Student s2("Babar",    21, "CS-102", 3, 3.2);
    Student s3("Hamza",  19, "CS-103", 2, 3.5);
    Student s4("Subhan",  22, "CS-104", 4, 2.9);

    
    Room r1(101, RoomType::SINGLE, 1);
    Room r2(202, RoomType::DOUBLE, 2);
    Room r3(305, RoomType::TRIPLE, 3);

    cout << "\n=== Allocating Students ===" << endl;
    r1.addOccupant(&s1);
    r1.addOccupant(&s2);  

    r2.addOccupant(&s2);
    r2.addOccupant(&s3);
    r2.addOccupant(&s4);    

    r3.addOccupant(&s1);
    r3.addOccupant(&s2);
    r3.addOccupant(&s3);
    r3.addOccupant(&s4);   

    cout << "\n=== Room Details ===" << endl;
    r1.displayInfo();
    r2.displayInfo();
    r3.displayInfo();

    cout << "\n=== Removing an Occupant ===" << endl;
    r2.removeOccupant("CS-102");
    r2.removeOccupant("CS-999");  

    cout << "\n=== Room 202 After Removal ===" << endl;
    r2.displayInfo();

    return 0;
}