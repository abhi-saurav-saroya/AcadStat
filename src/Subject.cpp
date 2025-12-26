#include "Subject.h"
#include "utils.h"

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

Subject:: Subject(string name, string code, int mcode, float marks) : 
                subjectName(name), subjectCode(code), MCode(mcode), marksObtained(marks) {}

string Subject::getSubjectCode() const {
    return subjectCode;
}

int Subject::getMCode() const {
    return MCode;
}

string Subject::getSubjectName() const {
    return subjectName;
}

float Subject::getMarks() const {
    return marksObtained;
}

void Subject::setMarks(float marks) {
    marksObtained = marks;
}
