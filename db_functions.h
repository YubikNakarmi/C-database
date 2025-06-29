#ifndef DB_FUNCTIONS_H
#define DB_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

void get_nonblank_input(char *prompt, char *buffer, int size) {
    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, size, stdin)) {
            // Remove trailing newline
            buffer[strcspn(buffer, "\n")] = 0;
            // Check if input is not blank
            if (strlen(buffer) > 0) {
                break;
            } else {
                printf("Input cannot be blank. Please try again.\n");
            }
        }
    }
}

// Add this to a utils.h or at the top of options.h
int get_valid_int(const char *prompt) {
    char buffer[64];
    int value;
    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin)) {
            // Remove newline
            buffer[strcspn(buffer, "\n")] = 0;
            // Check if input is not blank and is a valid integer
            if (strlen(buffer) > 0 && sscanf(buffer, "%d", &value) == 1) {
                return value;
            } else {
                printf("Invalid input. Please enter a valid integer.\n");
            }
        }
    }
}


void log_message(const char *username, const char *message) {
    FILE *logfile = fopen("log.txt", "a");
    if (logfile == NULL) return;

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char timestamp[32];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", t);

    fprintf(logfile, "[%s] | (%s)| %s\n", timestamp, username, message);
    fclose(logfile);
}

FILE * load_db(char *file_name, char *option){
    FILE * arch;
    
    arch = fopen(file_name,option);

    return arch;
}

void fix_formatting(char *string){
    string[strcspn(string, "\n")] = 0;

    for(int i = 0; i < strlen(string); i++){
        string[i] = tolower(string[i]);
        string[i] = (string[i] == ' ') ? '_' : string[i];
    }
}

int get_id (){
    FILE * arch;

    arch = load_db("recordDB.txt","r");
    
    if (arch == NULL)
        arch = load_db("recordDB.txt","a");

    int c = fgetc(arch);
    
    if (c == EOF) {
        return 0; // If the file is empty, it means that there are no games registered. 
    } else {
        ungetc(c, arch);
    }

    char line[255];
    int last_id;
    
    while(1){

        if (feof(arch)){
            break;
        }

        fgets(line,255,arch);
        
        last_id = atoi(&line[0]);
    }

    return last_id + 1;
}
#endif
