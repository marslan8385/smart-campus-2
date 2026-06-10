#include <iostream>
#include <string>
using namespace std;

// Student Class
class Student {
private:
    string name;
    int rollNo;

public:
    Student(string n, int r) {
        name = n;
        rollNo = r;
    }

    string getName() {
        return name;
    }

    int getRollNo() {
        return rollNo;
    }
};

// Course Class
class Course {
private:
    string courseCode;
    string courseName;

public:
    Course(string code, string name) {
        courseCode = code;
        courseName = name;
    }

    string getCourseName() {
        return courseName;
    }

    string getCourseCode() {
        return courseCode;
    }
};

// Enrollment Class
class Enrollment {
private:
    Student* student;
    Course* course;
    string enrollmentDate;
    char grade;

public:
    Enrollment(Student* s, Course* c,
               string date, char g) {
        student = s;
        course = c;
        enrollmentDate = date;
        grade = g;
    }

    void displayEnrollment() {
        cout << "Student Name: "
             << student->getName() << endl;

        cout << "Roll No: "
             << student->getRollNo() << endl;

        cout << "Course Code: "
             << course->getCourseCode() << endl;

        cout << "Course Name: "
             << course->getCourseName() << endl;

        cout << "Enrollment Date: "
             << enrollmentDate << endl;

        cout << "Grade: "
             << grade << endl;
    }
};

int main() {
    Student s1("Ali", 101);
    Course c1("CS201", "OOP");

    Enrollment e1(&s1, &c1,
                  "09-06-2026", 'A');

    e1.displayEnrollment();

    return 0;
}