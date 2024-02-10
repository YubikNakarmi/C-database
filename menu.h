#include <stdio.h>
#include<time.h>
#include <stdlib.h>

void display_menu(){
    system("cls");

    FILE * arch;
    arch = fopen("logo.txt","r");

    char menu_line[255];

    while(1){

        if (feof(arch)){
            break;
        }

        fgets(menu_line,255,arch);

        printf("%s",menu_line);
    }
    fclose(arch);
}