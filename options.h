#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "db_functions.h"
#include "menu.h"

struct steam{
    char name[50];
    char platform[50];
    char genre[50];
    float price;
    int keys;
    float public_rating;
    int year;
    int metacritic; 
    char studio[50];
};

typedef struct steam games;

int create(){
    display_creating_game();
    games game;
    FILE * arch;

    arch = load_db("steamDB.txt","a");

    setbuf(stdin, NULL);
    printf("Enter the name of the game: ");
    scanf("%49s",game.name);
    fix_formatting(game.name);
    
    setbuf(stdin, NULL);
    printf("Enter the name of the platform: ");
    scanf("%49s",game.platform);
    fix_formatting(game.platform);
    
    setbuf(stdin, NULL);
    printf("Enter the genre of the game: ");
    scanf("%49s",game.genre);
    fix_formatting(game.genre);
    
    setbuf(stdin, NULL);
    printf("Enter the price of the game: ");
    scanf("%f", &game.price);
    
    setbuf(stdin, NULL);
    printf("Enter the quantity of the game keys: ");
    scanf("%d", &game.keys);
    
    setbuf(stdin, NULL);
    printf("Enter public rating of the game: ");
    scanf("%f", &game.public_rating);
    
    setbuf(stdin, NULL);
    printf("Enter the year the game was released: ");
    scanf("%d", &game.year);
    
    setbuf(stdin, NULL);
    printf("Enter the game metascore: ");
    scanf("%d", &game.metacritic);
    setbuf(stdin, NULL);
    
    printf("Enter the game studio: ");
    scanf("%49s",game.studio);
    fix_formatting(game.studio);

    if(get_id() == 0)
        fprintf(arch,"%d | %s | %s | %s | %.2f | %d | %.2f | %d | %d | %s ",get_id(),game.name, game.platform, game.genre, game.price, game.keys, game.public_rating, game.year, game.metacritic, game.studio);
    else
        fprintf(arch,"\n%d | %s | %s | %s | %.2f | %d | %.2f | %d | %d | %s ",get_id(),game.name, game.platform, game.genre, game.price, game.keys, game.public_rating, game.year, game.metacritic, game.studio);

    fclose(arch);
    return 0;
}


int read(){
    clear_terminal();
    games game;
    FILE * arch;

    int option, id;

    arch = load_db("steamDB.txt","r");

    if(arch == NULL){
        printf("The file \"steamDB.txt does not exist\"");
        return 1;
    }

    printf("Enter -1 to list all OR an especific ID: ");
    scanf("%d", &option);

    if(option == -1){

        display_listing_all_games();

        while(1){

            if(feof(arch))
                break;

            fscanf(arch,"%d | %s | %s | %s | %f | %d | %f | %d | %d | %s ",&id, game.name, game.platform, game.genre, &game.price, &game.keys, &game.public_rating, &game.year, &game.metacritic, game.studio);
            printf("ID: %d | NAME: %s | PLATAFORM: %s | GENRE: %s | PRICE: $%.2f | KEYS: %d | PUBLIC RATING: %.2f | YEAR: %d | METASCORE: %d | STUDIO: %s \n\n", id, game.name, game.platform, game.genre, game.price, game.keys, game.public_rating, game.year, game.metacritic, game.studio);
        
        }
        
    }
    else{
        while(1){

            if(feof(arch)){
                printf("The system couldn't find the ID you provided.\n");
                break;
            }

            fscanf(arch,"%d | %s | %s | %s | %f | %d | %f | %d | %d | %s ",&id, game.name, game.platform, game.genre, &game.price, &game.keys, &game.public_rating, &game.year, &game.metacritic, game.studio);

            if(id == option){
                display_specific_game(option);
                printf("ID: %d | NAME: %s | PLATAFORM: %s | GENRE: %s | PRICE: $%.2f | KEYS: %d | PUBLIC RATING: %.2f | YEAR: %d | METASCORE: %d | STUDIO: %s \n\n", id, game.name, game.platform, game.genre, game.price, game.keys, game.public_rating, game.year, game.metacritic, game.studio);
                break;
            }
        }
        
    }
    fclose(arch);
    
    return 0;
}

int update(){
    clear_terminal();
    games game;
    FILE * arch;
    FILE * temp;
    
    int option, id, a, found_id = 0;

    arch = load_db("steamDB.txt","r");
    temp = load_db("temp____steamDB.txt","w");

    if(arch == NULL){
        printf("The file \"steamDB.txt\" does not exist!");
        return 1;
    }

    printf("Enter the especific ID that you want to modify: ");
    scanf("%d", &option);
    setbuf(stdin, NULL);
    fflush(stdin);

    display_update(option);

    while (1){
        fscanf(arch,"%d | %s | %s | %s | %f | %d | %f | %d | %d | %s ",&id, game.name, game.platform, game.genre, &game.price, &game.keys, &game.public_rating, &game.year, &game.metacritic, game.studio);
        if(option == id){
            found_id = 1;
            printf("Enter the name of the game: ");
            fgets(game.name,50,stdin);
            fix_formatting(game.name);
            
            setbuf(stdin, NULL);
            printf("Enter the name of the platform: ");
            fgets(game.platform,50,stdin);
            fix_formatting(game.platform);
            
            setbuf(stdin, NULL);
            printf("Enter the genre of the game: ");
            fgets(game.genre,50,stdin);
            fix_formatting(game.genre);
            
            setbuf(stdin, NULL);
            printf("Enter the price of the game: ");
            scanf("%f", &game.price);
            
            setbuf(stdin, NULL);
            printf("Enter the quantity of the game keys: ");
            scanf("%d", &game.keys);
            
            setbuf(stdin, NULL);
            printf("Enter public rating of the game: ");
            scanf("%f", &game.public_rating);
            
            setbuf(stdin, NULL);
            printf("Enter the year the game was released: ");
            scanf("%d", &game.year);
            
            setbuf(stdin, NULL);
            printf("Enter the game metascore: ");
            scanf("%d", &game.metacritic);
            setbuf(stdin, NULL);
            
            printf("Enter the game studio: ");
            fgets(game.studio,50,stdin);
            fix_formatting(game.studio);
        }
        if(id == 0)
            fprintf(temp,"%d | %s | %s | %s | %.2f | %d | %.2f | %d | %d | %s ",id,game.name, game.platform, game.genre, game.price, game.keys, game.public_rating, game.year, game.metacritic, game.studio);
        else
            fprintf(temp,"\n%d | %s | %s | %s | %.2f | %d | %.2f | %d | %d | %s ",id,game.name, game.platform, game.genre, game.price, game.keys, game.public_rating, game.year, game.metacritic, game.studio);
        if(feof(arch))
            break;
    }

    fclose(arch);
    fclose(temp);

    arch = load_db("steamDB.txt","w");
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
    games game;
    FILE * arch;
    FILE * temp;
    
    int option, id, a;

    arch = load_db("steamDB.txt","r");
    temp = load_db("temp____steamDB.txt","w");

    if(arch == NULL){
        printf("The file \"steamDB.txt\" does not exist!");
        return 1;
    }

    printf("Enter the especific ID that you want to modify: ");
    scanf("%d", &option);
    setbuf(stdin, NULL);
    fflush(stdin);

    display_delete(option);

    int found_id = 0;

    while (1){
        fscanf(arch,"%d | %s | %s | %s | %f | %d | %f | %d | %d | %s ",&id, game.name, game.platform, game.genre, &game.price, &game.keys, &game.public_rating, &game.year, &game.metacritic, game.studio);
        
        if(option == id){
            game.keys = 0;
            found_id = 1;
        }
            
        if(id == 0)
            fprintf(temp,"%d | %s | %s | %s | %.2f | %d | %.2f | %d | %d | %s ",id,game.name, game.platform, game.genre, game.price, game.keys, game.public_rating, game.year, game.metacritic, game.studio);
        else
            fprintf(temp,"\n%d | %s | %s | %s | %.2f | %d | %.2f | %d | %d | %s ",id,game.name, game.platform, game.genre, game.price, game.keys, game.public_rating, game.year, game.metacritic, game.studio);
        
        if(feof(arch)){
            break;
        }
    }

    fclose(arch);
    fclose(temp);

    arch = load_db("steamDB.txt","w");
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