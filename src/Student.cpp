#include "Student.h"
#include "Semester.h"
#include "utils.h"

#include <stdexcept>
#include <string>
#include <vector>
#include <iostream>
#include <cctype>
using namespace std;

Student::Student(string name, string id, unsigned long long roll)
    : studentName(name), studentID(id), uniRollNo(roll) {}

string Student::getStudentID() const {
    return studentID;
}

unsigned long long Student::getUniRollNo() const {
    return uniRollNo;
}

bool Student::semesterExists(int semNo) const {
    for (const Semester& sem : semesters) {
        if (sem.getSemesterNumber() == semNo)
            return true;
    }
    return false;
}

Semester& Student::getSemesterByNumber(int semNo) {
    for (Semester& sem : semesters) {
        if (sem.getSemesterNumber() == semNo)
            return sem;
    }
    throw runtime_error("Semester not found");
}

void Student::addSemester(const Semester& sem) {
    semesters.push_back(sem);
}
