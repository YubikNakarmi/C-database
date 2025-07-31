#ifndef ADMIN_H
#define ADMIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "db_functions.h"
#include "menu.h"

struct admin_user {
    char username[50];
    char password[50];
    char access_level[20]; // e.g., "admin", "user"
};

typedef struct admin_user AdminUser;
int add_user(){
    FILE *user_admin;
    FILE *user_admin_read;
    user_admin = fopen("admin_users.txt", "a");
    user_admin_read = fopen("admin_users.txt", "r");

    if (!user_admin || !user_admin_read) {
        printf("Could not open admin_users.txt for writing/reading.\n");
        if (user_admin) fclose(user_admin);
        if (user_admin_read) fclose(user_admin_read);
        return 1;
    }

    AdminUser admin;
    char line[256];
    int duplicate = 0;

    get_nonblank_input("Enter username: ", admin.username, 50);
    fix_formatting(admin.username);

    // Check for duplicate username
    while (fgets(line, sizeof(line), user_admin_read)) {
        char existing_username[50];
        sscanf(line, "%49[^,]", existing_username);
        if (strcmp(existing_username, admin.username) == 0) {
            duplicate = 1;
            break;
        }
    }
    fclose(user_admin_read);

    if (duplicate) {
        printf("Username already exists! User not added.\n");
        fclose(user_admin);
        return 1;
    }

    get_nonblank_input("Enter password: ", admin.password, 50);
    fix_formatting(admin.password);

    get_nonblank_input("Enter access level (admin/user): ", admin.access_level, 20);
    fix_formatting(admin.access_level);

    fprintf(user_admin, "%s,%s,%s\n", admin.username, admin.password, admin.access_level);
    fclose(user_admin);
    printf("User added successfully!\n");


    return 0;
}

int view_user() {
    char input[60];
    printf("Enter username to view or type 'all' to show all users: ");
    if (fgets(input, sizeof(input), stdin)) {
        input[strcspn(input, "\n")] = 0; // Remove newline
    }

    FILE *user_admin = fopen("admin_users.txt", "r");
    if (!user_admin) {
        printf("Could not open admin_users.txt for reading.\n");
        return 1;
    }

    char line[256];
    int found = 0;
    printf("+----------------------+----------------------+----------------------+\n");
    printf("|      Username        |      Password        |    Access Level      |\n");
    printf("+----------------------+----------------------+----------------------+\n");
    while (fgets(line, sizeof(line), user_admin)) {
        char username[50], password[50], access_level[20];
        if (sscanf(line, "%49[^,],%49[^,],%19[^\n]", username, password, access_level) == 3) {
            if (strcmp(input, "all") == 0 || strcmp(input, username) == 0) {
                printf("| %-20s | %-20s | %-20s |\n", username, password, access_level);
                found = 1;
            }
        }
    }
    printf("+----------------------+----------------------+----------------------+\n");
    fclose(user_admin);

    if (!found) {
        printf("No user(s) found for your selection.\n");
    }
    return 0;
}

int delete_user() {
    char username[50];
    int found = 0;
    get_nonblank_input("Enter username to delete: ", username, 50);
    fix_formatting(username);

    FILE *user_admin = fopen("admin_users.txt", "r");
    FILE *temp = fopen("admin_users_temp.txt", "w");
    if (!user_admin || !temp) {
        printf("Could not open files for deleting user.\n");
        if (user_admin) fclose(user_admin);
        if (temp) fclose(temp);
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), user_admin)) {
        char existing_username[50];
        sscanf(line, "%49[^,]", existing_username);
        if (strcmp(existing_username, username) != 0) {
            fputs(line, temp);
        } else {
            found = 1;
        }
    }
    fclose(user_admin);
    fclose(temp);

    remove("admin_users.txt");
    rename("admin_users_temp.txt", "admin_users.txt");

    if (found) {
        printf("User '%s' deleted successfully!\n", username);
    } else {
        printf("User '%s' not found.\n", username);
    }
    return 0;
}

int edit_user() {
    char username[50];
    int found = 0;
    get_nonblank_input("Enter username to edit: ", username, 50);
    fix_formatting(username);

    FILE *user_admin = fopen("admin_users.txt", "r");
    FILE *temp = fopen("admin_users_temp.txt", "w");
    if (!user_admin || !temp) {
        printf("Could not open files for editing user.\n");
        if (user_admin) fclose(user_admin);
        if (temp) fclose(temp);
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), user_admin)) {
        char existing_username[50];
        sscanf(line, "%49[^,]", existing_username);
        if (strcmp(existing_username, username) == 0) {
            found = 1;
            AdminUser admin;
            strcpy(admin.username, username); // Keep the same username
            get_nonblank_input("Enter new password: ", admin.password, 50);
            fix_formatting(admin.password);
            get_nonblank_input("Enter new access level (admin/user): ", admin.access_level, 20);
            fix_formatting(admin.access_level);
            fprintf(temp, "%s,%s,%s\n", admin.username, admin.password, admin.access_level);
        } else {
            fputs(line, temp);
        }
    }
    fclose(user_admin);
    fclose(temp);

    remove("admin_users.txt");
    rename("admin_users_temp.txt", "admin_users.txt");

    if (found) {
        printf("User '%s' edited successfully!\n", username);
    } else {
        printf("User '%s' not found.\n", username);
    }
    return 0;
}

int view_logs(){
    char date[16]; // Allow for "all" or YYYY-MM-DD
    char line[512];
    FILE *logfile;

    printf("Enter date to filter logs (YYYY-MM-DD) or type 'all' to show all logs: ");
    if (fgets(date, sizeof(date), stdin)) {
        date[strcspn(date, "\n")] = 0; // Remove newline
    }

    logfile = fopen("log.txt", "r");
    if (!logfile) {
        printf("Could not open log.txt\n");
        return 1;
    }

    int found = 0;
    if (strcmp(date, "all") == 0 || strlen(date) == 0) {
        printf("Showing all logs:\n");
        while (fgets(line, sizeof(line), logfile)) {
            printf("%s", line);
            found = 1;
        }
    } else {
        printf("Logs for %s:\n", date);
        while (fgets(line, sizeof(line), logfile)) {
            if (strncmp(line + 1, date, 10) == 0) { // +1 to skip the initial '['
                printf("%s", line);
                found = 1;
            }
        }
    }
    if (!found) {
        printf("No logs found for this selection.\n");
    }
    fclose(logfile);
    return 0;}
#endif
