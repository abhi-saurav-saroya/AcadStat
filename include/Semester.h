#ifndef SEMESTER_H
#define SEMESTER_H

#include <vector>
#include <string>
#include <cctype>
using namespace std;

#include "Subject.h"

class Semester {
    private:
        int semesterNumber;
        vector<Subject> subjects;

    public:
        Semester(int semNo);
        int getSemesterNumber() const;
        bool subjectExists(const string& subcode) const;
        bool subjectExists(int mcode) const;
        int displaySubjects() const;
        void updateMarks(const string& subCode, float marks);
        void updateMarksByIndex(int index, float marks);
        void addSubject(const Subject& sub);
};


#endif