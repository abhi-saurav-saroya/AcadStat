#include "Section.h"
#include "Student.h"
#include "utils.h"

#include <stdexcept>
#include <string>
#include <vector>
#include <iostream>
#include <cctype>
using namespace std;

Section::Section(string name) : sectionName(name) {}

string Section::getSectionName() const {
    return sectionName;
}

bool Section::studentExists(const string& stuID, const unsigned long long& uniRollNo) const {
    for (const Student& stu : students) {
        if (toLower(stuID) == toLower(stu.getStudentID()) || stu.getUniRollNo() == uniRollNo) {
            return true;
        }
    }
    return false;
}

Student& Section::getStudentByRollNo(unsigned long long uniRollNo) {
    for (Student& student : students) {
        if (student.getUniRollNo() == uniRollNo) {
            return student;
        }
    }
    throw runtime_error("Student not found.");
}

void Section::addStudent(const Student& stu){
    students.push_back(stu);
}