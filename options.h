#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "db_functions.h"
#include "menu.h"
#include "admin.h"





 // Global variable to store the current user
struct steam{
    char medicine_name[50];
    char category[50];
    char unit[50];
    int quantity;
    char supplier[50]; 
    char expiry_date[50];
};

typedef struct steam records;

int login(char username[], char password[], char userlevel[]) {
    FILE *user_admin = fopen("admin_users.txt", "r");
    if (!user_admin) {
        printf("Could not open admin_users.txt for reading.\n");
        return 0;
    }

    char line[256];
    char file_username[50], file_password[50], file_access[20];
    int found = 0;

    while (fgets(line, sizeof(line), user_admin)) {
        // Parse line: username,password,access_level
        if (sscanf(line, "%49[^,],%49[^,],%19[^\n]", file_username, file_password, file_access) == 3) {
            if (strcmp(username, file_username) == 0 && strcmp(password, file_password) == 0) {
                found = 1;
                strcpy(userlevel, file_access); // Save access level
                printf("Login successful! Access level: %s\n", file_access);
                break;
            }
        }
    }
    fclose(user_admin);

    if (!found) {
        printf("Invalid credentials.\n");
        return 0;
    }
    return 1;
}

int admin(){
    
     char user_input;

    do{
        display_admin();

        setbuf(stdin,NULL);
        scanf("%c", &user_input);
        getchar(); //reads next

        user_input = tolower(user_input);

        switch (user_input)
        {
        case '1':
            add_user();
            break;        
            
        case '2':
            view_user();
            break;
        
        case '3':
            edit_user();
            break;
        
        case '4':
           delete_user();
            break;
            
        case '6':
            return 0;
            break;

        case '5':
            view_logs();
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

int create(){
    display_creating_game();
    records record; // defining structure variable
    FILE * arch;

    arch = load_db("recordDB.txt","a");

    setbuf(stdin, NULL);
    get_nonblank_input("Enter the medicine name: ", record.medicine_name, 50);
    fix_formatting(record.medicine_name);
    
    setbuf(stdin, NULL);
    get_nonblank_input("Enter the category of medicine: ", record.category, 50);
    fix_formatting(record.category);
    
    setbuf(stdin, NULL);
    get_nonblank_input("Enter the unit : ", record.unit, 50);
    fix_formatting(record.unit);
    
    
    setbuf(stdin, NULL);
    record.quantity = get_valid_int("Enter the quantity in integer: ");

    setbuf(stdin, NULL);
    get_nonblank_input("Enter the supplier: ", record.supplier, 50);
    fix_formatting(record.supplier);
    

    printf("Enter the record expiry_date: ");
    fgets(record.expiry_date,50,stdin);
    fix_formatting(record.expiry_date);

    if(get_id() == 0)
        fprintf(arch,"%d | %s | %s | %s | %d | %s | %s ",get_id(),record.medicine_name, record.category, record.unit, record.quantity, record.supplier, record.expiry_date);
    else
        fprintf(arch,"\n%d | %s | %s | %s | %d | %s | %s ",get_id(),record.medicine_name, record.category, record.unit, record.quantity, record.supplier, record.expiry_date);

    fclose(arch);
    return 0;
}


int read(){
    clear_terminal();
    records record;
    FILE * arch;

    int option, id;

    arch = load_db("recordDB.txt","r");

    if(arch == NULL){
        printf("The file \"recordDB.txt\" does not exist!\n");
        return 1;
    }

    int ch = fgetc(arch);
    if(ch == EOF){
        printf("The file is empty.\n");
        fclose(arch);
        return 1;
    }
    rewind(arch);

    printf("Enter -1 to list all OR a specific ID: ");
    scanf("%d", &option);

    rewind(arch);

    int any_output = 0;

    if(option == -1){
        // Print ASCII table header
        printf("+----+----------------------+-----------------+----------+----------+-----------------+--------------+\n");
        printf("| ID |   Medicine Name      |   Category      |  Unit    | Quantity |    Supplier     | Expiry Date  |\n");
        printf("+----+----------------------+-----------------+----------+----------+-----------------+--------------+\n");

        while (fscanf(arch,"%d | %49[^|] | %49[^|] | %49[^|] | %d | %49[^|] | %49[^\n]",
                      &id, record.medicine_name, record.category, record.unit, &record.quantity, record.supplier, record.expiry_date) == 7) {
            printf("| %-2d | %-20s | %-15s | %-8s | %-8d | %-15s | %-12s |\n",
                id, record.medicine_name, record.category, record.unit, record.quantity, record.supplier, record.expiry_date);
            any_output = 1;
        }

        printf("+----+----------------------+-----------------+----------+----------+-----------------+--------------+\n");
        if (!any_output) {
            printf("No records found.\n");
        }
    }
    else{
        int found = 0;
        while (fscanf(arch,"%d | %49[^|] | %49[^|] | %49[^|] | %d | %49[^|] | %49[^\n]",
                      &id, record.medicine_name, record.category, record.unit, &record.quantity, record.supplier, record.expiry_date) == 7) {
            if(id == option){
                // Print ASCII table header
                printf("+----+----------------------+-----------------+----------+----------+-----------------+--------------+\n");
                printf("| ID |   Medicine Name      |   Category      |  Unit    | Quantity |    Supplier     | Expiry Date  |\n");
                printf("+----+----------------------+-----------------+----------+----------+-----------------+--------------+\n");
                printf("| %-2d | %-20s | %-15s | %-8s | %-8d | %-15s | %-12s |\n",
                    id, record.medicine_name, record.category, record.unit, record.quantity, record.supplier, record.expiry_date);
                printf("+----+----------------------+-----------------+----------+----------+-----------------+--------------+\n");
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("The system couldn't find the ID you provided.\n");
        }
    }
    fclose(arch);

    printf("\nPress Enter to continue...");
    setbuf(stdin, NULL);
    while(getchar() != '\n');

    return 0;
}

int update(){
    clear_terminal();
    records record;
    FILE * arch;
    FILE * temp;
    
    int option, id, a, found_id = 0;

    arch = load_db("recordDb.txt","r");
    temp = load_db("temp____recordDB.txt","w");

    if(arch == NULL){
        printf("The file \"recordDb.txt\" does not exist!");
        return 1;
    }

    if(fgetc(arch) == EOF){
        printf("The file is empty.");
        remove("temp____recordDB.txt");
        return 1;
    }

    rewind(arch);

    printf("Enter the especific ID that you want to modify: ");
    scanf("%d", &option);
    setbuf(stdin, NULL);
    fflush(stdin);

    display_update(option);

    while (1){
        fscanf(arch,"%d | %49[^|] | %49[^|] | %49[^|] | %d | %49[^|] | %49[^\n]", &id, record.medicine_name, record.category, record.unit, &record.quantity, record.supplier, record.expiry_date);
        if(option == id){
            found_id = 1;
            printf("Enter the medicine name: ");
            get_nonblank_input("Enter the medicine name: ", record.medicine_name, 50);
            fix_formatting(record.medicine_name);
            
            setbuf(stdin, NULL);
            printf("Enter the category of medicine: ");
            get_nonblank_input("Enter the category of medicine: ", record.category, 50);
            fix_formatting(record.category);
            
            setbuf(stdin, NULL);
            printf("Enter the unit of medicine: ");
            get_nonblank_input("Enter the unit of medicine: ", record.unit, 50);
            fix_formatting(record.unit);
            
             setbuf(stdin, NULL);
             record.quantity = get_valid_int("Enter the quantity in integer: ");
            
            setbuf(stdin, NULL);
            printf("Enter the supplier: ");
            get_nonblank_input("Enter the supplier: ", record.supplier, 50);
            fix_formatting(record.supplier);
            
            printf("Enter the  expiry_date: ");
            fgets(record.expiry_date,50,stdin);
            fix_formatting(record.expiry_date);
        }
        if(id == 0)
            fprintf(temp,"%d | %s | %s | %s | %d | %s | %s ",id,record.medicine_name, record.category, record.unit, record.quantity, record.supplier, record.expiry_date);
        else
            fprintf(temp,"\n%d | %s | %s | %s | %d | %s | %s ",id,record.medicine_name, record.category, record.unit, record.quantity, record.supplier, record.expiry_date);
        if(feof(arch))
            break;
    }

    fclose(arch);
    fclose(temp);

    arch = load_db("recordDB.txt","w");
    temp = load_db("temp____recordDB.txt","r");

    while( (a = fgetc(temp)) != EOF )
        fputc(a, arch);
    
    fclose(arch);
    fclose(temp);

    if(found_id)
        printf("\nTask concluded.");
    
    else
        printf("\nThe system couldn't find the ID you provided.");

    remove("temp____record.txt");

    return 0;
}

int del(){
    clear_terminal();
    records record;
    FILE * arch;
    FILE * temp;
    
    int option, id, a;

    arch = load_db("recordDB.txt","r");
    temp = load_db("temp____recordDB.txt","w");

    if(arch == NULL){
        printf("The file \"recordDB.txt\" does not exist!");
        return 1;
    }

    if(fgetc(arch) == EOF){
        printf("The file is empty.");
        remove("temp____recordDB.txt");
        return 1;
    }

    rewind(arch);

    printf("Enter the item ID: ");
    scanf("%d", &option);
    setbuf(stdin, NULL);
    fflush(stdin);

    display_delete(option);

    int found_id = 0;

    while (1){

        if(feof(arch)){
            break;
        }

        fscanf(arch,"%d | %49[^|] | %49[^|] | %49[^|] | %d | %49[^|] | %49[^\n]", &id, record.medicine_name, record.category, record.unit, &record.quantity, record.supplier, record.expiry_date);

        if(option == id){
            found_id = 1;
            continue;
        }

        if(id-found_id == 0)
            fprintf(temp,"%d | %s | %s | %s | %d | %s | %s ",id-found_id,record.medicine_name, record.category, record.unit, record.quantity, record.supplier, record.expiry_date);
        else
            fprintf(temp,"\n%d | %s | %s | %s | %d | %s | %s ",id-found_id,record.medicine_name, record.category, record.unit, record.quantity, record.supplier, record.expiry_date);
        
    }


    fclose(arch);
    fclose(temp);

    arch = load_db("recordDB.txt","w");
    temp = load_db("temp____recordDB.txt","r");

    while( (a = fgetc(temp)) != EOF )
        fputc(a, arch);
    
    fclose(arch);
    fclose(temp);

    if(found_id)
        printf("\nTask concluded.");
    
    else
        printf("\nThe system couldn't find the ID you provided.");
    
    remove("temp____recordDB.txt");
    
    return 0;
}