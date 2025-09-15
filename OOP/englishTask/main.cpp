#include "course.hpp"
#include "student.hpp"
#include <iostream>
#include <ctime>

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::cout << "=== Testing Student ===" << std::endl;
    Student s1;
    Student s2(30, 3);
    Student s3(s2);

    s1.addCredits(20);
    s1.takeCourse();
    s1.print();

    s1.reset();
    s1.print();

    std::cout << "Getter check: credits = " << s2.getCredits() << ", courses = "
        << s2.getCoursesTaken() << std::endl;

    s2.setCredits(100);
    s2.setCoursesTaken(10);
    s2.print();

    std::cout << "\n=== Testing Course ===" << std::endl;

    Course c1;
    Course c2(50, 5, StudyState::ENROLLED);
    printCourse(c1);
    printCourse(c2);

    c1.enrollStudent();
    printCourse(c1);

    if(c1.startCourse()) {
        c1.passExam(40);
    }
    printCourse(c1);

    c1.failExam();
    printCourse(c1);

    c1.passExam(60);
    c1.applyScholarship();
    printCourse(c1);

    c1.passExam(100);
    if(c1.graduate()) {
        std::cout << "Graduation successful!" << std::endl;
    } else {
        std::cout << "Not enough credits!" << std::endl;
    }
    printCourse(c1);

    c2.dropOutStudent();
    printCourse(c2);

    return 0;
}