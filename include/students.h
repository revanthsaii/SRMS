#ifndef STUDENTS_H
#define STUDENTS_H

struct Student {
    int id;
    char name[50];
    char department[30];
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
int getStudentCount();
void exportCSV();

#endif
