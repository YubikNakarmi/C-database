#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "options.h"
#include "menu.h"

int main(){
    if (!login()) {
        printf("Exiting program.\n");
        return 0;
    }

    char user_input;

    do{
        display_menu();

        setbuf(stdin,NULL);
        scanf("%c", &user_input);
        getchar(); //reads next

        user_input = tolower(user_input);

        switch (user_input)
        {
        case 'c':
            create();
            break;        
            
        case 'r':
            read();
            break;
        
        case 'u':
            update();
            break;
        
        case 'd':
            del();
            break;
            
        case 'l':
            return 0;
            break;

        case 'a':
            admin();
            break;
        
        default:
            break;
        }

        printf("\n\n\t\tPress Enter to Continue");
        setbuf(stdin,NULL);
        while( getchar() != '\n' );

    } while (user_input != 'l');
    
    return 0;
}