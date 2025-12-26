#include "C:\Users\hp\OneDrive\Documents\PROJECTS\Fun Activities\AcadStat\include\Semester.h"
#include "C:\Users\hp\OneDrive\Documents\PROJECTS\Fun Activities\AcadStat\include\Subject.h"
#include "C:\Users\hp\OneDrive\Documents\PROJECTS\Fun Activities\AcadStat\include\utils.h"

#include <iostream>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

Semester:: Semester(int semNo) : semesterNumber(semNo) {}

int Semester::getSemesterNumber() const {
    return semesterNumber;
}

bool Semester::subjectExists(const string& subcode) const {
    for (const Subject& sub : subjects) {
        if (toLower(subcode) == toLower(sub.getSubjectCode()))
            return true;
    }
    return false;
}

bool Semester::subjectExists(int mcode) const {
    for (const Subject& sub : subjects) {
        if (mcode == sub.getMCode())
            return true;
    }
    return false;
}

int Semester::displaySubjects() const {
    if(subjects.empty()) {
        cout << "No subjects available in this semester." << endl;
        return 0;
    }

    cout << "Subject List:" << endl;
    for (size_t i = 0; i < subjects.size(); ++i) {
        cout << "\t" 
             << (i + 1) 
             << ". " 
             << subjects[i].getSubjectCode() 
             << " (" 
             << subjects[i].getMCode() 
             << "): "
             << subjects[i].getSubjectName() 
             << endl;
    }
    return static_cast<int>(subjects.size());
}

void Semester::updateMarks(const string& subCode, float marks) {
    for (Subject& sub : subjects) {
        if (toLower(sub.getSubjectCode()) == toLower(subCode)) {
            sub.setMarks(marks);
            return;
        }
    }
    throw runtime_error("Subject not found.");
}       

void Semester::updateMarksByIndex(int index, float marks) {
    subjects.at(index).setMarks(marks);
}

void Semester::addSubject(const Subject& sub) {
    subjects.push_back(sub);
}