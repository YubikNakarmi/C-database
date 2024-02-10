#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "options.h"
#include "menu.h"

int main(){
    char user_input;

    do{
        display_menu();

        setbuf(stdin,NULL);
        scanf("%c", &user_input);

        user_input = tolower(user_input);

        switch (user_input)
        {
        case 'c': // CREATE
            create();
            break;            
            
        case 'r': // READ
            read();
            break;
        
        case 'u': // UPDATE
            update();
            break;
        
        case 'd': // DELETE
            break;
            
        case 'l': // LEAVE 
            return 0;
            break;
        
        default:
            printf("\n\t\t\tOption invalid!\n");
            break;
        }

        printf("\n\t\tPress Enter to Continue");
        setbuf(stdin,NULL);
        while( getchar() != '\n' );

    } while (user_input != 'l');
    
    return 0;
}