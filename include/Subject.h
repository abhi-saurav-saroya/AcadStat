#ifndef SUBJECT_H
#define SUBJECT_H

#include<vector>
#include<string>
#include <cctype>
using namespace std;

class Subject {
    private:
        string subjectName;
        string subjectCode;
        int MCode;
        float marksObtained;

    public:
        Subject(string name, string code, int mcode, float marks);
        string getSubjectCode() const;
        int getMCode() const;
        string getSubjectName() const;
        float getMarks() const;
        void setMarks(float marks);
};

#endif