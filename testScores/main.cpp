// Copyright 2019 David Boyd
#include <iostream>
#include <string>
#include <iomanip>

//===============
//=== Structs ===
//===============
struct Student {
    int         grade;
    std::string name;
};

//======================
//=== Fns Prototypes ===
//======================
double calcAverage(Student *, int);
void   displayResults(Student *, int, double);
void   getGrades(Student *, int);
void   getNames(Student *, int);
int    getNumStudents();
void   sortGrades(Student *, int);

//============
//=== Main ===
//============
int main () {

    Student *classroom = nullptr;
    int nStudents;
    double average;

    // Get number of students 
    nStudents = getNumStudents();
    std::cout << std::endl;
    
    // Dynamically allocate an array large enough
    // to hold number of students
    classroom = new Student[nStudents];  // Allocate memory 

    // Get student names and grades
    getNames(classroom, nStudents);
    std::cout << std::endl;
    getGrades(classroom, nStudents);
    std::cout << std::endl;

    // Bubble sort array based on stduent grades
    sortGrades(classroom, nStudents);

    // Calculate the total grades
    average = calcAverage(classroom, nStudents);

    // Display the results
    displayResults(classroom, nStudents, average);
    std::cout << std::endl;

    // Free dynamically allocated memory
    delete [] classroom;
    classroom = nullptr;

    return 0;
}

//=======================
//=== Fns Definitions ===
//=======================
//--- Average ------------------------------------------------------------------
double calcAverage(Student *s, int size) {
    double total = 0.0;
    for (int count = 0; count < size; ++count) {
        total += s[count].grade;
    }
    return (total / size);
}

//--- Display Results ----------------------------------------------------------
void displayResults(Student *s, int size, double avg) {
    int w1 = 20,  // char width for names
        w2 =  5;  // char width for averages

    std::cout << std::setprecision(1) << std::fixed << std::showpoint;
    std::cout << std::setw(w1) << std::left << "Name" 
              << std::setw(w2) << std::right << "Score" << std::endl;
    std::cout << "-------------------------" << std::endl;
    
    for (int count = 0; count < size; ++count) {
        std::cout << std::setw(w1) << std::left << s[count].name 
                  << std::setw(w2) << std::right << s[count].grade << std::endl;
        }
    std::cout << "-------------------------" << std::endl;
    std::cout << std::setw(w1) << std::left << "Average" 
                  << std::setw(w2) << std::right << avg << std::endl;
}

//--- Get Grades ---------------------------------------------------------------
void getGrades(Student *s, int size) {
    // find longest name
    int w1 = s[0].name.length();
    for (int i=0; i<size; ++i) {
       if (w1 < s[i].name.length()) {
            w1 = s[i].name.length();
       }
    }

    // get grades
    std::cout << "Enter the grades below." << std::endl;
    for (int count = 0; count < size; ++count) {
        std::cout << std::setw(w1) << std::left << s[count].name << ": ";
        std::cin  >> s[count].grade;
    }
}

//--- Get Student Names --------------------------------------------------------
void getNames(Student *s, int size) {
    std::cout << "Enter the names below." << std::endl;
    std::cin.ignore();
    for (int count = 0; count < size; ++count) {
        std::cout << "Student " << (count + 1) << ": ";
        std::getline(std::cin, s[count].name);
    }
}

//--- Get Number of Students ---------------------------------------------------
int getNumStudents() {
    int numOfStudents;
    std::cout << "How many students do you wish to process? ";
    std::cin  >> numOfStudents;
    return numOfStudents;
}

//--- Sort Grades --------------------------------------------------------------
void sortGrades(Student *s, int size) {
    Student temp;   // Holds a Student object
    bool swap;
    do {
        swap = false;
        for (int count = 0; count < (size-1); ++count) {
            if (s[count].grade > s[count+1].grade) {
                temp.grade = s[count].grade;
                temp.name = s[count].name;
                s[count].grade = s[count+1].grade;
                s[count].name = s[count+1].name;
                s[count+1].grade = temp.grade;
                s[count+1].name = temp.name;
                swap = true;
            }
        }
    } while (swap);
}