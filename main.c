#include <stdio.h>
#include <stdlib.h>
#include "options.h"

int main(){
    char user_input;

    do{
        setbuf(stdin,NULL);
        
        printf("Enter one option: "); // TODO MAKE THIS NICE (TABELINHA DO GABRIEL)
        scanf("%c", &user_input);

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
            printf("Option invalid!\n");
            break;
        }

    } while (user_input != 'l');
    
    return 0;
}