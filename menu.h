#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void clear_terminal(){
    #ifdef _WIN32
        system("cls");
    #elif __linux__
        system("clear");
    #endif
}

void display_menu(){
    clear_terminal();

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

void display_creating_game(){
    clear_terminal();
    printf("+---------------+\n");
    printf("| Creating game |\n");
    printf("+---------------+\n\n");
}

void display_listing_all_games(){
    clear_terminal();
    printf("+-------------------+\n");
    printf("| Listing all games |\n");
    printf("+-------------------+\n\n");
}

void display_specific_game(int id){
    clear_terminal();
    printf("+---------------------------------+\n");
    printf("| Now displaying game with ID [%d] |\n",id);
    printf("+---------------------------------+\n\n");
}

void display_update(int id){
    clear_terminal();
    printf("+-----------------------------------+\n");
    printf("| Now updating the game with ID [%d] |\n",id);
    printf("+-----------------------------------+\n\n");
}

void display_delete(int id){
    clear_terminal();
    printf("+----------------------------------------------------+\n");
    printf("|Now deleting all the keys from the game with ID [%d] |\n",id);
    printf("+----------------------------------------------------+\n");
}