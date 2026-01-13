#ifndef STUDENTS_H
#define STUDENTS_H

struct Student {
    int id;
    char name[50];
    char department[30];
    int age;
    float marks;
};

void loadStudents();
void saveStudents();
void displayStudents();
void searchStudent();
void sortStudents();
void addStudent();
void updateStudent();
void deleteStudent();
void displayStatistics();
void displayTopPerformers();
void displayByDepartment();
int getStudentCount();
char getGrade(float marks);
const char* getPassStatus(float marks);
void exportCSV();

#endif
