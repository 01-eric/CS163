#include <cstdio>

#ifndef STUDENT_H
#define STUDENT_H

class Student {

    public:
        Student(char* name, int id, double gpa);
        ~Student();
        char* getName();
        int getID();
        double getGPA();
        void setName(char* name);
        void setID(int id);
        void setGPA(double gpa);
        void print();       
    
    private:
        char* name;
        int id;
        double gpa;

};

#endif

Student::Student(char* name, int id, double gpa) {
    setName(name);
    setID(id);
    setGPA(gpa);
}

Student::~Student() {
    delete name;
}

char* Student::getName() {
    return name;
}

int Student::getID() {
    return id;
}

double Student::getGPA() {
    return gpa;
}

void Student::setName(char* name) {
    this->name = name;
}

void Student::setID(int id) {
    this->id = id;
}

void Student::setGPA(double gpa) {
    this->gpa = gpa;
}

void Student::print() {
    printf("%s - ID: %d - %.2f GPA", name, id, gpa);
}
