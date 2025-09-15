#pragma once
#include <iostream>

class Student {
private:
    int credits;
    int coursesTaken;
public:
    //Default constr
    Student(int c = 0, int cT = 0)
        : credits(c), coursesTaken(cT) {}

    // Copy constr
    Student(const Student& s)
        : credits(s.credits), coursesTaken(s.coursesTaken) {}

    // Getters
    int getCredits() const { return credits; }
    int getCoursesTaken() const { return coursesTaken; }
    
    // Setters
    void setCredits(int c) { credits = c; }
    void setCoursesTaken(int cT) { coursesTaken =  cT; }

    // Methods
    void addCredits(int x) { credits += x; }
    void takeCourse() { coursesTaken++; }
    void reset() { credits = 0; coursesTaken = 0; }
    void print() const {
        std::cout << "Credits: " << credits << ", in " << coursesTaken << " taken courses" << std::endl;
    }
};