#ifndef SECTION_H
#define SECTION_H

#include <vector>
#include <string>
#include <cctype>
using namespace std;

#include "Student.h"

class Section {
    private:
        string sectionName;
        vector<Student> students;

    public:
        Section(string name);
        string getSectionName() const;
        bool studentExists(const string& stuID, const unsigned long long& uniRollNo) const;
        Student& getStudentByRollNo(unsigned long long uniRollNo);
        void addStudent(const Student& stu);
};

#endif