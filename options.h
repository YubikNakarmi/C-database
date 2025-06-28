#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "db_functions.h"
#include "menu.h"

#define USERNAME "admin"
#define PASSWORD "1234"

struct steam{
    char medicine_name[50];
    char category[50];
    char unit[50];
    int quantity;
    char supplier[50]; 
    char expiry_date[50];
};

typedef struct steam records;

int login() {
    char username[50];
    char password[50];

    printf("=== LOGIN ===\n");
    printf("Username: ");
    scanf("%49s", username);
    printf("Password: ");
    scanf("%49s", password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Login successful!\n");
        return 1;
    } else {
        printf("Invalid credentials.\n");
        return 0;
    }
}

int create(){
    display_creating_game();
    records record; // defining structure variable
    FILE * arch;

    arch = load_db("recordDB.txt","a");

    setbuf(stdin, NULL);
    printf("Enter the medicine name: ");
    fgets(record.medicine_name,50,stdin);
    fix_formatting(record.medicine_name);
    
    setbuf(stdin, NULL);
    printf("Enter the category of medicine: ");
    fgets(record.category,50,stdin);
    fix_formatting(record.category);
    
    setbuf(stdin, NULL);
    printf("Enter the unit : ");
    fgets(record.unit,50,stdin);
    fix_formatting(record.unit);
    
    
    setbuf(stdin, NULL);
    printf("Enter the quantity in integer: ");
    scanf("%d", &record.quantity);

    setbuf(stdin, NULL);
    printf("Enter the supplier: ");
    fgets(record.supplier,50,stdin);
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
        printf("The file \"file does not exist\"");
        return 1;
    }

    rewind(arch);

    if(fgetc(arch) == EOF){
        printf("The file is empty.");
        return 1;
    }

    printf("Enter -1 to list all OR an especific ID: ");
    scanf("%d", &option);

    rewind(arch);

    if(option == -1){

        display_listing_all_games();

        while(1){

            if(feof(arch))
                break;

            fscanf(arch,"%d | %49[^|] | %49[^|] | %49[^|] | %d | %49[^|] | %49[^\n]", &id, record.medicine_name, record.category, record.unit, &record.quantity, record.supplier, record.expiry_date);
            printf("ID: %d | medicine_name: %s | category: %s | unit: %s | quantity: %d | supplier: %s | expiry_date: %s\n\n", id, record.medicine_name, record.category, record.unit, record.quantity, record.supplier, record.expiry_date);
        
        }
        
    }
    else{
        while(1){

            if(feof(arch)){
                printf("The system couldn't find the ID you provided.\n");
                break;
            }

            fscanf(arch,"%d | %49[^|] | %49[^|] | %49[^|] | %d | %49[^|] | %49[^\n]", &id, record.medicine_name, record.category, record.unit, &record.quantity, record.supplier, record.expiry_date);

            if(id == option){
                display_specific_game(option);
                printf("ID: %d | medicine_name: %s | category: %s | unit: %s | quantity: %d | supplier: %s | expiry_date: %s\n\n", id, record.medicine_name, record.category, record.unit, record.quantity, record.supplier, record.expiry_date);
                break;
            }
        }
        
    }
    fclose(arch);
    
    return 0;
}

int update(){
    clear_terminal();
    records record;
    FILE * arch;
    FILE * temp;
    
    int option, id, a, found_id = 0;

    arch = load_db("recordDb.txt","r");
    temp = load_db("temp____steamDB.txt","w");

    if(arch == NULL){
        printf("The file \"recordDb.txt\" does not exist!");
        return 1;
    }

    if(fgetc(arch) == EOF){
        printf("The file is empty.");
        remove("temp____steamDB.txt");
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
            printf("Enter the medicine_name of the record: ");
            fgets(record.medicine_name,50,stdin);
            fix_formatting(record.medicine_name);
            
            setbuf(stdin, NULL);
            printf("Enter the medicine_name of the category: ");
            fgets(record.category,50,stdin);
            fix_formatting(record.category);
            
            setbuf(stdin, NULL);
            printf("Enter the unit of the record: ");
            fgets(record.unit,50,stdin);
            fix_formatting(record.unit);
            
            setbuf(stdin, NULL);
            printf("Enter the quantity of the record quantity: ");
            scanf("%d", &record.quantity);
            
            setbuf(stdin, NULL);
            printf("Enter the supplier: ");
            fgets(record.supplier,50,stdin);
            fix_formatting(record.supplier);
            
            printf("Enter the record expiry_date: ");
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

    arch = load_db("recordDb.txt","w");
    temp = load_db("temp____steamDB.txt","r");

    while( (a = fgetc(temp)) != EOF )
        fputc(a, arch);
    
    fclose(arch);
    fclose(temp);

    if(found_id)
        printf("\nTask concluded.");
    
    else
        printf("\nThe system couldn't find the ID you provided.");

    remove("temp____steamDB.txt");

    return 0;
}

int del(){
    clear_terminal();
    records record;
    FILE * arch;
    FILE * temp;
    
    int option, id, a;

    arch = load_db("recordDb.txt","r");
    temp = load_db("temp____steamDB.txt","w");

    if(arch == NULL){
        printf("The file \"recordDb.txt\" does not exist!");
        return 1;
    }

    if(fgetc(arch) == EOF){
        printf("The file is empty.");
        remove("temp____steamDB.txt");
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

    arch = load_db("recordDb.txt","w");
    temp = load_db("temp____steamDB.txt","r");

    while( (a = fgetc(temp)) != EOF )
        fputc(a, arch);
    
    fclose(arch);
    fclose(temp);

    if(found_id)
        printf("\nTask concluded.");
    
    else
        printf("\nThe system couldn't find the ID you provided.");
    
    remove("temp____steamDB.txt");
    
    return 0;
}