#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "options.h"
#include "menu.h"
#include "db_functions.h"

int main(){
    char username[50];
    char password[50];
    char userlevel[20] = "";

    printf("=== LOGIN ===\n");
    printf("Username: ");
    scanf("%49s", username);
    printf("Password: ");
    scanf("%49s", password);
    if (!login(username, password, userlevel)) { // Pass userlevel to login
        printf("Exiting program.\n");
        return 0;
    }

    char user_input;

    do{
        display_menu();

        scanf(" %c", &user_input); // Note the space before %c

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
            if(strcmp(userlevel, "admin") != 0) {
                printf("You do not have permission to access admin functions.\n");
                break;
            } else {  
                admin();
                log_message(username, "Admin operation performed");
            }
            break;
        
        default:
            break;
        }

        printf("\n\n\t\tPress Enter to Continue");
        while(getchar() != '\n');

    } while (user_input != 'l');
    
    return 0;
}