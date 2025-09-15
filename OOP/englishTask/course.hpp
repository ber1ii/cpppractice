#pragma once
#include "student.hpp"
#include <cstdlib>

enum class StudyState {
    NOT_ENROLLED, ENROLLED, STUDYING, GRADUATED
};

class Course {
private:
    Student s;
    StudyState currentState;

    static constexpr int MAX_CREDITS = 180;
public:
    // Default constr
    Course() : s(0, 0), currentState(StudyState::NOT_ENROLLED) {};

    // Param constr
    Course(int credits, int coursesTaken, StudyState cS) : s(credits, coursesTaken), currentState(cS) {};

    bool enrollStudent() {
        if(currentState == StudyState::NOT_ENROLLED) {
            currentState = StudyState::ENROLLED;
            
            return true;
        }
        return false;
    }

    bool dropOutStudent(){
        if(currentState != StudyState::NOT_ENROLLED && currentState != StudyState::GRADUATED) {
            currentState = StudyState::NOT_ENROLLED;
            s.reset();

            return true;
        }
        return false;
    }

    bool startCourse(){
        if(currentState == StudyState::ENROLLED || currentState == StudyState::STUDYING) {
            currentState = StudyState::STUDYING;
            s.takeCourse();

            return true;
        }
        return false;
    }

    bool passExam(int earnedCredits){
        if(currentState == StudyState::STUDYING && s.getCredits() < MAX_CREDITS){
            int newCredits = s.getCredits() + earnedCredits;

            if(newCredits >= MAX_CREDITS){
                newCredits = MAX_CREDITS;
            }
            s.setCredits(newCredits);
            return true;
        }
        return false;
    }

    bool failExam(){
        if(currentState == StudyState::STUDYING){
            std::cout << "Exam failed." << std::endl;
            return true;
        }

        return false;
    }

    bool graduate(){
        if((currentState == StudyState::STUDYING || currentState == StudyState::ENROLLED) && s.getCredits() >= 150){
            currentState = StudyState::GRADUATED;

            return true;
        }
        return false;
    }

    bool applyScholarship(){
        if((s.getCredits() >= 90 && s.getCredits() <= 180) && (currentState == StudyState::STUDYING || currentState == StudyState::ENROLLED)){
            int bonus = 5 + (std::rand() % 11);
            int newCredits = s.getCredits() + bonus;
            
            if(newCredits >= MAX_CREDITS){
                newCredits = MAX_CREDITS;
            }

            s.setCredits(newCredits);
            std::cout << "You have been awarded an additional: " << bonus
                << "credits by your scholarship" << std::endl;

            return true;
        }
        return false;
    }

    friend void printCourse(const Course&);
};

inline void printCourse(const Course &c){
    std::cout << "=== COURSE INFO ===" << std::endl;
    c.s.print();
    std::cout << "Current state: ";
    switch(c.currentState){
        case StudyState::NOT_ENROLLED:
            std::cout << "NOT ENROLLED";
            break;
        case StudyState::ENROLLED:
            std::cout << "ENROLLED";
            break;
        case StudyState::STUDYING:
            std::cout << "STUDYING";
            break;
        case StudyState::GRADUATED:
            std::cout << "GRADUATED";
            break;
    }

    std::cout << std::endl;
}