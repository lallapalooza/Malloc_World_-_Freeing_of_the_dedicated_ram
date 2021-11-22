#include "../headers/header.h"

//handling gameloop action (1 -> display character sheet / 2 -> move on the map / 3 -> Save progression
void handleAction(Levels *levels, Player *player, char action){

    if(action == '1'){
        displayCharacter(player);
    }else if(action == '2'){
        handleMovement(levels, player);
    }else if(action == '3'){
        printf("\nTODO : Save\n\n");
    }
}

// main game loop
void gameLoop(Levels *levels, Player *player){
    char action;

    do{

        printf("\n----------- MENU ----------\n\n");

        printf("1 - Character sheet \n"
               "2 - Move \n"
               "3 - Save \n"
               "4 - Exit \n"
               "\nChoose en option : ");


        fflush(stdin);
        scanf("%c", &action);

        system("cls"); //clear console

        handleAction(levels, player, action);

    }while(action != '4');
}

//handling main menu action (1 -> play game / 2 -> load save)
void handleMainMenu(char action){

    if(action == '1'){
        Levels *levels = malloc(sizeof(Levels));
        Player *player = malloc(sizeof(Player));

        initMap(levels, 10, 10, player);
        initPlayer(player);

        //printRessourceList(levels->lv1->ressourceList);
        //printMonsterList(levels->lv1->monsterList);

        gameLoop(levels, player);
    }else if(action == '2'){
        printf("\nTODO : Load Save\n\n");
    }

}
