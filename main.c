#include <stdio.h>
#include <stdlib.h>
#include "options.h"

int main(){
    char user_input;

    do{
        printf("Enter one option: "); // TODO MAKE THIS NICE (TABELINHA DO GABRIEL)
        scanf("%c", &user_input);

        switch (user_input)
        {
        case 'c': // CREATE
            create();
            break;
            
        case 'r': // READ
            /* code */
            break;
        
        case 'u': // UPDATE
            /* code */
            break;
        
        case 'd': // DELETE
            break;
            
        case 'l': // LEAVE 
            return 0;
        
        default:
            printf("Option invalid!");
            break;
        }

    } while (user_input != 'l');
    

        
    
    return 0;
}