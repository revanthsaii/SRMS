#include <stdio.h>
#include "../include/auth.h"
#include "../include/students.h"
#include "../include/utils.h"

int main() {

    if (!login()) {
        printf("Login failed!\n");
        return 0;
    }

    loadStudents();

    int choice;
    char buffer[100];

    while (1) {
        printf("\n--- MENU ---\n");
        printf("1. View Students\n");
        printf("2. Add Student\n");
        printf("3. Search Student\n");
        printf("4. Sort Students\n");
        printf("5. Export CSV\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            continue;
        }
        
        if (sscanf(buffer, "%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            continue;
        }

        switch (choice) {
            case 1: displayStudents(); break;
            case 2: addStudent(); saveStudents(); break;
            case 3: searchStudent(); break;
            case 4: sortStudents(); break;
            case 5: exportCSV(); break;
            case 6: saveStudents(); return 0;
            default: printf("Invalid choice! Please enter 1-6.\n");
        }
    }
}
