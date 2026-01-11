#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../include/auth.h"

int login() {
    char user[50], pass[50];
    int attempts = 3;
    
    while (attempts > 0) {
        printf("\n=== Login (%d attempts remaining) ===\n", attempts);
        printf("Username: ");
        scanf("%49s", user);
        printf("Password: ");
        scanf("%49s", pass);

        FILE *fp = fopen("data/credentials.txt", "r");
        if (!fp) {
            printf("Error: Could not open credentials file!\n");
            return 0;
        }

        char u[50], p[50], r[50];

        while (fscanf(fp, "%s %s %s", u, p, r) != EOF) {
            if (strcmp(user, u)==0 && strcmp(pass, p)==0) {
                logLoginHistory(user, 1);  // Success
                fclose(fp);
                printf("\nLogin successful! Welcome, %s.\n", user);
                return 1;
            }
        }

        fclose(fp);
        attempts--;
        logLoginHistory(user, 0);  // Failed
        printf("Invalid credentials!\n");
    }
    
    printf("\nToo many failed attempts. Access denied.\n");
    return 0;
}

void logLoginHistory(char *user, int success) {
    FILE *fp = fopen("data/login_history.txt", "a");
    if (!fp) return;

    time_t now = time(NULL);
    char *status = success ? "SUCCESS" : "FAILED";
    fprintf(fp, "[%s] %s - %s", status, user, ctime(&now));

    fclose(fp);
}
