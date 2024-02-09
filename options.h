#include <stdio.h>
#include <stdlib.h>

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
        arch = load_db("a+");

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
    
    fprintf(arch,"%d | %s | %s | %f | %d | %f | %d | %d | %s",get_id(),game.name, game.platform, game.genre, game.price, game.keys, game.public_rating, game.year, game.metacritic, game.studio);

    fclose(arch);
    
}


// void read(int option){
//     games game;
//     FILE * arch;

//     arch = load_db("r");

//     if(option == -1){

//         while(1){

//             fscanf(arch,"%s",line);

//             if(feof(arch))
//                 break;

//             printf("%s\n",line);
//     }
//     }

//     fclose(arch);
// }

// void update(){
//     games game;
//     FILE * arch;

//     arch = load_db("");

//     fclose(arch);
// }


// void remove(){
//     games game;
//     FILE * arch;

//     arch = load_db("");

//     fclose(arch);
// }

