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
        printf("\n╔═══════════════════════════════════╗\n");
        printf("║   STUDENT MANAGEMENT SYSTEM       ║\n");
        printf("║   [%d students in database]        ║\n", getStudentCount());
        printf("╠═══════════════════════════════════╣\n");
        printf("║  1. View Students                 ║\n");
        printf("║  2. Add Student                   ║\n");
        printf("║  3. Update Student                ║\n");
        printf("║  4. Delete Student                ║\n");
        printf("║  5. Search Student                ║\n");
        printf("║  6. Sort Students                 ║\n");
        printf("║  7. Statistics                    ║\n");
        printf("║  8. Top Performers                ║\n");
        printf("║  9. Export CSV                    ║\n");
        printf("║ 10. Exit                          ║\n");
        printf("╚═══════════════════════════════════╝\n");
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
            case 3: updateStudent(); saveStudents(); break;
            case 4: deleteStudent(); saveStudents(); break;
            case 5: searchStudent(); break;
            case 6: sortStudents(); break;
            case 7: displayStatistics(); break;
            case 8: displayTopPerformers(); break;
            case 9: exportCSV(); break;
            case 10: saveStudents(); return 0;
            default: printf("Invalid choice! Please enter 1-10.\n");
        }
    }
}
