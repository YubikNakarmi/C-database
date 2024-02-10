#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "db_functions.h"

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

int get_id (){
    FILE * arch;

    arch = load_db("r"); // TODO ERROR HANDELING

    if (arch == NULL)
        arch = load_db("a");

    int c = fgetc(arch);
    
    if (c == EOF) {
        return 0; // If the file is empty, it means that there are no games registered. 
    } else {
        ungetc(c, arch);
    }

    char line[255];
    int last_id;
    
    while(1){

        if (feof(arch)){
            break;
        }

        fgets(line,255,arch);
        
        last_id = atoi(&line[0]);
    }

    return last_id + 1;
}

void create(){
    games game;
    FILE * arch;

    arch = load_db("a");

    setbuf(stdin, NULL);
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
    
    fprintf(arch,"%d | %s | %s | %s | %.2f | %d | %.2f | %d | %d | %s \n",get_id(),game.name, game.platform, game.genre, game.price, game.keys, game.public_rating, game.year, game.metacritic, game.studio);

    fclose(arch);
}


void read(){
    games game;
    FILE * arch;

    int option, id;

    arch = load_db("r");

    printf("Enter -1 to list all OR an especific ID: ");
    scanf("%d", &option);

    if(option == -1){
        
        while(1){
            
            if(feof(arch)){
                printf("final do arquivo.\n");
                break;
            }

            fscanf(arch,"%d | %s | %s | %s | %f | %d | %f | %d | %d | %s",&id, game.name, game.platform, game.genre, &game.price, &game.keys, &game.public_rating, &game.year, &game.metacritic, game.studio);

            printf("ID: %d | NAME: %s | PLATAFORM: %s | GENRE: %s | PRICE: $%.2f | KEYS: %d | PUBLIC RATING: %.2f | YEAR: %d | METASCORE: %d | STUDIO: %s \n", id, game.name, game.platform, game.genre, game.price, game.keys, game.public_rating, game.year, game.metacritic, game.studio);
        }

    }else{
        while(1){

            if(feof(arch)){
                printf("The system couldn't find the ID you provided.\n");
                break;
            }

            fscanf(arch,"%d | %s | %s | %s | %f | %d | %f | %d | %d | %s",&id, game.name, game.platform, game.genre, &game.price, &game.keys, &game.public_rating, &game.year, &game.metacritic, game.studio);

            if(id == option){
                printf("ID: %d | NAME: %s | PLATAFORM: %s | GENRE: %s | PRICE: $%.2f | KEYS: %d | PUBLIC RATING: %.2f | YEAR: %d | METASCORE: %d | STUDIO: %s \n", id, game.name, game.platform, game.genre, game.price, game.keys, game.public_rating, game.year, game.metacritic, game.studio);
                break;
            }
        }

    fclose(arch);
    }
}

void update(){
    games game;
    FILE * arch;

    int option, id;

    printf("Enter -1 to list all OR an especific ID: ");
    scanf("%d", &option);

    arch = load_db("r+"); // TODO ERROR HANDELING

    while(1){

        if(feof(arch)){
            printf("The system couldn't find the ID you provided.\n");
            break;
        }

        fscanf(arch,"%d | %s | %s | %s | %f | %d | %f | %d | %d | %s",&id, game.name, game.platform, game.genre, &game.price, &game.keys, &game.public_rating, &game.year, &game.metacritic, game.studio);
 
        if(id == option){

            printf("DEBUG!!!!\n");
            
            setbuf(stdin, NULL);
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

            // fprintf(arch,"%d | %s | %s | %s | %.2f | %d | %.2f | %d | %d | %s ",id,game.name, game.platform, game.genre, game.price, game.keys, game.public_rating, game.year, game.metacritic, game.studio);
            fputs("teste",arch);
            break;
        }

    }
    fclose(arch);
}


// void remove(){
//     games game;
//     FILE * arch;

//     arch = load_db("");

//     fclose(arch);
// }