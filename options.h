#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

FILE * load_db(char *option){
    FILE * arch;
    
    arch = fopen("steamDB.txt",option);

    return arch;
}

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

        fgets(line,255,arch);

        if (feof(arch)){
            break;
        }
        
        last_id = atoi(&line[0]);
    }

    return last_id + 1;
}

void create(){
    games game;
    FILE * arch;

    arch = load_db("a");

    printf("Enter the name of the game: ");
    scanf("%49s", game.name);
    setbuf(stdin, NULL);

    for(int i = 0; i < strlen(game.name); i++)
        game.name[i] = (game.name[i] == ' ') ? '_' : game.name[i];

    printf("Enter the name of the platform: ");
    scanf("%49s", game.platform);
    setbuf(stdin, NULL);

    printf("Enter the genre of the game: ");
    scanf("%49s", game.genre);
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
    fgets(game.studio, 50, stdin);
    setbuf(stdin, NULL);
    
    fprintf(arch,"%d | %s | %s | %s | %.2f | %d | %.2f | %d | %d | %s",get_id(),game.name, game.platform, game.genre, game.price, game.keys, game.public_rating, game.year, game.metacritic, game.studio);

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

            printf("ID: %d | NAME: %s | PLATAFORM: %s | GENRE: %s | PRICE: $%.2f | KEYS: %d | PUBLIC RATING: %f | YEAR: %d | METASCORE: %d | STUDIO: %s \n", id, game.name, game.platform, game.genre, game.price, game.keys, game.public_rating, game.year, game.metacritic, game.studio);
        }
    }else{
        while(1){

            fscanf(arch,"%d | %s | %s | %s | %f | %d | %f | %d | %d | %s",&id, game.name, game.platform, game.genre, &game.price, &game.keys, &game.public_rating, &game.year, &game.metacritic, game.studio);

            if(feof(arch)){
                printf("The system couldn't find the ID you provided.\n");
                break;
            }

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

    arch = load_db("a+"); // TODO ERROR HANDELING
    rewind(arch);

    while(1){

        if(feof(arch)){
            printf("The system couldn't find the ID you provided.\n");
            break;
        }

        fscanf(arch,"%d | %s | %s | %s | %.2f | %d | %.2f | %d | %d | %s",&id, game.name, game.platform, game.genre, &game.price, &game.keys, &game.public_rating, &game.year, &game.metacritic, game.studio);
 
        if(id == option){
            
            printf("Enter the name of the game: ");
            scanf("%49s", game.name);
            setbuf(stdin, NULL);

            for(int i = 0; i < strlen(game.name); i++)
                game.name[i] = (game.name[i] == ' ') ? '_' : game.name[i];

            printf("Enter the name of the platform: ");
            scanf("%49s", game.platform);
            setbuf(stdin, NULL);

            printf("Enter the genre of the game: ");
            scanf("%49s", game.genre);
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
            fgets(game.studio, 50, stdin);
            setbuf(stdin, NULL);
            
            fprintf(arch,"%d | %s | %s | %s | %.2f | %d | %.2f | %d | %d | %s",id ,game.name, game.platform, game.genre, game.price, game.keys, game.public_rating, game.year, game.metacritic, game.studio);
        }

    fclose(arch);
    }
}


// void remove(){
//     games game;
//     FILE * arch;

//     arch = load_db("");

//     fclose(arch);
// }