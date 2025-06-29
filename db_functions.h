#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#ifndef DB_FUNCTIONS_H
#define DB_FUNCTIONS_H

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
