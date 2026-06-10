#include <iostream>
#include <string>
using namespace std;

// Faculty Class
class Faculty {
private:
    string name;
    string employeeID;

public:
    Faculty(string n, string id) {
        name = n;
        employeeID = id;
    }

    string getName() {
        return name;
    }
};

// Course Class
class Course {
private:
    string courseCode;
    string courseName;
    int creditHours;
    Faculty* instructor;
    int maxCapacity;
    int enrolledCount;

public:
    // Constructor
    Course(string code, string name, int credits,
           Faculty* inst, int capacity) {
        courseCode = code;
        courseName = name;
        creditHours = credits;
        instructor = inst;
        maxCapacity = capacity;
        enrolledCount = 0;
    }

    // Enroll Student
    void enrollStudent() {
        if (enrolledCount < maxCapacity) {
            enrolledCount++;
            cout << "Student Enrolled Successfully!" << endl;
        } else {
            cout << "Course is Full!" << endl;
        }
    }

    // Display Course Information
    void displayCourse() {
        cout << "\nCourse Code: " << courseCode << endl;
        cout << "Course Name: " << courseName << endl;
        cout << "Credit Hours: " << creditHours << endl;
        cout << "Instructor: " << instructor->getName() << endl;
        cout << "Maximum Capacity: " << maxCapacity << endl;
        cout << "Enrolled Students: " << enrolledCount << endl;
    }
};

int main() {
    Faculty f1("Ahmed Khan", "F101");

    Course c1("CS201", "Object Oriented Programming",
              3, &f1, 30);

    c1.enrollStudent();
    c1.enrollStudent();

    c1.displayCourse();

    return 0;
}