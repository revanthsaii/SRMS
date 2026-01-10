#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/students.h"

struct Student students[100];
int studentCount = 0;

void loadStudents() {
    FILE *fp = fopen("data/students.txt", "r");
    studentCount = 0;

    if (fp == NULL) {
        printf("Note: No existing student data found. Starting fresh.\n");
        return;
    }

    while (fscanf(fp, "%d %s %f", 
        &students[studentCount].id,
        students[studentCount].name,
        &students[studentCount].marks) != EOF) 
    {
        studentCount++;
    }
    fclose(fp);
}

void saveStudents() {
    FILE *fp = fopen("data/students.txt", "w");
    for (int i = 0; i < studentCount; i++) {
        fprintf(fp, "%d %s %.2f\n",
            students[i].id,
            students[i].name,
            students[i].marks
        );
    }
    fclose(fp);
}

void displayStudents() {
    if (studentCount == 0) {
        printf("\nNo students in the database.\n");
        return;
    }
    
    printf("\n╔════════════════════════════════════════════╗\n");
    printf("║          STUDENT RECORDS (%d)             ║\n", studentCount);
    printf("╠════════════════════════════════════════════╣\n");
    printf("║  ID  │  Name                │  Marks      ║\n");
    printf("╠══════╪═══════════════════════╪═════════════╣\n");
    
    for (int i = 0; i < studentCount; i++) {
        printf("║ %-4d │ %-20s │  %6.2f     ║\n", 
            students[i].id, 
            students[i].name, 
            students[i].marks
        );
    }
    
    printf("╚══════╧═══════════════════════╧═════════════╝\n");
}

void searchStudent() {
    char key[50];
    printf("Enter ID or Name to search: ");
    scanf("%49s", key);

    int found = 0;

    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].name, key)==0 || students[i].id == atoi(key)) {
            printf("\nFound: %d %s %.2f\n",
                students[i].id,
                students[i].name,
                students[i].marks
            );
            found = 1;
        }
    }

    if (!found) printf("No student found!\n");
}

void sortStudents() {
    int choice;
    printf("\nSort By: 1-ID  2-Name  3-Marks: ");
    scanf("%d", &choice);

    for (int i = 0; i < studentCount-1; i++) {
        for (int j = i+1; j < studentCount; j++) {
            int swap = 0;

            if (choice == 1 && students[i].id > students[j].id) swap = 1;
            if (choice == 2 && strcmp(students[i].name, students[j].name) > 0) swap = 1;
            if (choice == 3 && students[i].marks < students[j].marks) swap = 1;

            if (swap) {
                struct Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }

    printf("\nStudents sorted successfully.\n");
}

void addStudent() {
    if (studentCount >= 100) {
        printf("\nError: Maximum student limit (100) reached!\n");
        return;
    }
    
    struct Student newStudent;
    char buffer[100];
    
    // Get and validate ID
    printf("\nEnter Student ID: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL || 
        sscanf(buffer, "%d", &newStudent.id) != 1) {
        printf("Invalid ID!\n");
        return;
    }
    
    // Check for duplicate ID
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == newStudent.id) {
            printf("Error: Student ID %d already exists!\n", newStudent.id);
            return;
        }
    }
    
    // Get name
    printf("Enter Name: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        printf("Invalid name!\n");
        return;
    }
    buffer[strcspn(buffer, "\n")] = 0;  // Remove newline
    strncpy(newStudent.name, buffer, 49);
    newStudent.name[49] = '\0';
    
    // Get marks
    printf("Enter Marks: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL || 
        sscanf(buffer, "%f", &newStudent.marks) != 1) {
        printf("Invalid marks!\n");
        return;
    }
    
    if (newStudent.marks < 0 || newStudent.marks > 100) {
        printf("Error: Marks must be between 0 and 100!\n");
        return;
    }
    
    students[studentCount++] = newStudent;
    printf("\nStudent added successfully!\n");
}

void updateStudent() {
    int id;
    char buffer[100];
    
    printf("\nEnter Student ID to update: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL || 
        sscanf(buffer, "%d", &id) != 1) {
        printf("Invalid ID!\n");
        return;
    }
    
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            printf("Current: ID=%d, Name=%s, Marks=%.2f\n", 
                   students[i].id, students[i].name, students[i].marks);
            
            // Update name
            printf("Enter new name (or '-' to keep current): ");
            if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
                buffer[strcspn(buffer, "\n")] = 0;
                if (strcmp(buffer, "-") != 0) {
                    strncpy(students[i].name, buffer, 49);
                    students[i].name[49] = '\0';
                }
            }
            
            // Update marks
            printf("Enter new marks (or -1 to keep current): ");
            if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
                float marks;
                if (sscanf(buffer, "%f", &marks) == 1 && marks >= 0) {
                    if (marks <= 100) {
                        students[i].marks = marks;
                    } else {
                        printf("Warning: Marks must be <= 100. Keeping old value.\n");
                    }
                }
            }
            
            printf("\nStudent updated successfully!\n");
            return;
        }
    }
    printf("Student with ID %d not found!\n", id);
}

void deleteStudent() {
    int id;
    char buffer[100];
    
    printf("\nEnter Student ID to delete: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL || 
        sscanf(buffer, "%d", &id) != 1) {
        printf("Invalid ID!\n");
        return;
    }
    
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            printf("Student found: %s (ID: %d, Marks: %.2f)\n", 
                   students[i].name, students[i].id, students[i].marks);
            
            // Confirm deletion
            printf("Are you sure you want to delete this student? (y/n): ");
            if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
                return;
            }
            
            if (buffer[0] == 'y' || buffer[0] == 'Y') {
                // Shift remaining students left to fill the gap
                for (int j = i; j < studentCount - 1; j++) {
                    students[j] = students[j + 1];
                }
                studentCount--;
                printf("\nStudent deleted successfully!\n");
            } else {
                printf("\nDeletion cancelled.\n");
            }
            return;
        }
    }
    printf("Student with ID %d not found!\n", id);
}

void displayStatistics() {
    if (studentCount == 0) {
        printf("\nNo students in database. Cannot display statistics.\n");
        return;
    }
    
    float total = 0, max = students[0].marks, min = students[0].marks;
    
    for (int i = 0; i < studentCount; i++) {
        total += students[i].marks;
        if (students[i].marks > max) max = students[i].marks;
        if (students[i].marks < min) min = students[i].marks;
    }
    
    float average = total / studentCount;
    
    printf("\n╔═══════════════════════════════════╗\n");
    printf("║     STATISTICS DASHBOARD          ║\n");
    printf("╠═══════════════════════════════════╣\n");
    printf("║ Total Students:  %-16d ║\n", studentCount);
    printf("║ Average Marks:   %-16.2f ║\n", average);
    printf("║ Highest Marks:   %-16.2f ║\n", max);
    printf("║ Lowest Marks:    %-16.2f ║\n", min);
    printf("╚═══════════════════════════════════╝\n");
}

void displayTopPerformers() {
    if (studentCount == 0) {
        printf("\nNo students in database.\n");
        return;
    }
    
    char buffer[100];
    int n = 5;  // Default to top 5
    
    printf("\nEnter number of top performers to display (default 5): ");
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        int input;
        if (sscanf(buffer, "%d", &input) == 1 && input > 0) {
            n = input;
        }
    }
    
    if (n > studentCount) n = studentCount;
    
    // Sort by marks (descending) using a temporary array
    struct Student sorted[100];
    for (int i = 0; i < studentCount; i++) {
        sorted[i] = students[i];
    }
    
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = i + 1; j < studentCount; j++) {
            if (sorted[i].marks < sorted[j].marks) {
                struct Student temp = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = temp;
            }
        }
    }
    
    printf("\n╔════════════════════════════════════════════╗\n");
    printf("║       TOP %d PERFORMERS                    ║\n", n);
    printf("╠════════════════════════════════════════════╣\n");
    printf("║ Rank │  ID  │  Name         │  Marks      ║\n");
    printf("╠══════╪══════╪═══════════════╪═════════════╣\n");
    
    for (int i = 0; i < n; i++) {
        printf("║  %-2d  │ %-4d │ %-13s │  %6.2f     ║\n", 
               i + 1, sorted[i].id, sorted[i].name, sorted[i].marks);
    }
    
    printf("╚══════╧══════╧═══════════════╧═════════════╝\n");
}

void exportCSV() {
    FILE *fp = fopen("output/exported_students.csv", "w");
    
    if (!fp) {
        printf("\nError: Could not create CSV file! Check if output/ directory exists.\n");
        return;
    }
    
    fprintf(fp, "ID,Name,Marks\n");

    for (int i = 0; i < studentCount; i++) {
        fprintf(fp, "%d,%s,%.2f\n",
            students[i].id, students[i].name, students[i].marks
        );
    }

    fclose(fp);
    printf("\nStudents exported to CSV!\n");
}
