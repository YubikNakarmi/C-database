#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "options.h"
#include "menu.h"
#include "db_functions.h"

int main(){
    char username[50];
    char password[50];

    printf("=== LOGIN ===\n");
    printf("Username: ");
    scanf("%49s", username);
    printf("Password: ");
    scanf("%49s", password);
    if (!login(username, password)) {
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
            log_message(username, "Create operation performed");
            break;        
            
        case 'r':
            read();
            log_message(username, "Read operation performed");
            break;
        
        case 'u':
            update();
            log_message(username, "Update operation performed");
            break;
        
        case 'd':
            del();
            log_message(username, "Delete operation performed");
            break;
            
        case 'l':
            log_message(username, "Logout");
            return 0;
            break;

        case 'a':
            admin();
            log_message(username, "Admin operation performed");
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