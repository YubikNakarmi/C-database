#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE * load_db(char *option){
    FILE * arch;
    
    arch = fopen("steamDB.txt",option);

    return arch;
}

void fix_formatting(char *string){
    string[strcspn(string, "\n")] = 0;

    for(int i = 0; i < strlen(string); i++)
        string[i] = (string[i] == ' ') ? '_' : string[i];
}