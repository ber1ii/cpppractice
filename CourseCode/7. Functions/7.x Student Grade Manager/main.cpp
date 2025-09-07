#include <iostream>
#include <string>
#include <vector>

struct Student {
    std::string name;
    int mathsScore{};
    int scienceScore{};
    int englishScore{};
    double averageScore{};
    char letterGrade{};
};

void inputStudents(int numStudents, std::vector<Student>& students);
void calculateAverage(std::vector<Student>& students);
void calculateLetterGrade(std::vector<Student>& students);
void displayResults(const std::vector<Student>& students);

int main(){
    std::vector<Student> students;
    int numStudents;
    std::cout << "Enter the number of students: ";
    std::cin >> numStudents;
    students.resize(numStudents);

    inputStudents(numStudents, students);
    calculateAverage(students);
    calculateLetterGrade(students);
    displayResults(students);
}

void inputStudents(int numStudents, std::vector<Student>& students){
    for(int i = 0; i < numStudents; i++){
        std::cout << "Enter the name of student " << i + 1 << ": ";
        std::cin >> students[i].name;
        std::cout << "Enter the maths score for this student: ";
        std::cin >> students[i].mathsScore;
        
        while(students[i].mathsScore < 0 || students[i].mathsScore > 100){
            std::cout << "Invalid maths score. Please enter a score between 0 and 100: ";
            std::cin >> students[i].mathsScore;
        }
        
        std::cout << "Enter the science score for this student: ";
        std::cin >> students[i].scienceScore;
        
        while(students[i].scienceScore < 0 || students[i].scienceScore > 100){
            std::cout << "Invalid science score. Please enter a score between 0 and 100: ";
            std::cin >> students[i].scienceScore;
        }

        std::cout << "Enter the english score for this student: ";
        std::cin >> students[i].englishScore;
        
        while(students[i].englishScore < 0 || students[i].englishScore > 100){
            std::cout << "Invalid english score. Please enter a score between 0 and 100: ";
            std::cin >> students[i].englishScore;
        }
    }
}


void calculateAverage(std::vector<Student>& students){
    for(int i = 0; i < students.size(); i++){
        int totalScore = students[i].mathsScore + students[i].scienceScore + students[i].englishScore;
        double averageScore = totalScore / 3.0;
        students[i].averageScore = averageScore;
    }
}

void calculateLetterGrade(std::vector<Student>& students){
    for(int i = 0; i < students.size(); i++){
        int score = static_cast<int>(students[i].averageScore);
        
        switch(score / 10){
            case 10:
            case 9: students[i].letterGrade = 'A'; break;
            case 8: students[i].letterGrade = 'B'; break;
            case 7: students[i].letterGrade = 'C'; break;
            case 6: students[i].letterGrade = 'D'; break;
            default: students[i].letterGrade = 'F'; break;
        }
    }
}

void displayResults(const std::vector<Student>& students){
    std::cout << "Student Name\tMaths\tScience\tEnglish\tAverage\tLetter Grade" << std::endl;
    for(int i = 0; i < students.size(); i++){
        std::cout << "\t" << students[i].name << "\t" << students[i].mathsScore << "\t" << students[i].scienceScore << "\t" << students[i].englishScore << "\t" << students[i].averageScore << "\t" << students[i].letterGrade << std::endl;
    }
}