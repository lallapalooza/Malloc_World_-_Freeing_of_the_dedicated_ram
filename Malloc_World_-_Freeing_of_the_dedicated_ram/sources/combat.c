#include "../headers/header.h"

int flee(){
    int rate = rand2(1,100);
    int loop = 1;

    if(rate <= FLEE_RATE){
        loop = 0;
    }

    if(loop == 1){
        printf("\nYou failed to flee\n");
    }else if(loop == 0){
        printf("\nYou fled\n\n");
    }

    return loop;
}

InventoryNode *findItem(InventoryNode *inventoryHead, int itemType, int index){
    int count = 0;

    while(inventoryHead != NULL){
        if(isWeapon(inventoryHead->value) && itemType == _weapon){
            count ++;
            if(count == index){
                printf("\n%s selected : ", ITEM_TYPE[itemType]);
                printItem(inventoryHead->value, inventoryHead->reference, inventoryHead->quantity, inventoryHead->durability);
                return inventoryHead;
            }
        }else if(isArmor(inventoryHead->value) && itemType == _armor){
            count ++;
            if(count == index){
                printf("\n%s selected : ", ITEM_TYPE[itemType]);
                printItem(inventoryHead->value, inventoryHead->reference, inventoryHead->quantity, inventoryHead->durability);
                return inventoryHead;
            }
        }else if (isHeal(inventoryHead->value) && itemType == _heal){
            count ++;
            if(count == index){
                printf("\n%s selected : ", ITEM_TYPE[itemType]);
                printItem(inventoryHead->value, inventoryHead->reference, inventoryHead->quantity, inventoryHead->durability);
                return inventoryHead;
            }
        }
        inventoryHead = inventoryHead->next;
    }

    return NULL;
}

int availableItems(InventoryNode *inventoryHead, int itemType){
    int count = 0;

    while(inventoryHead != NULL){
        if(isWeapon(inventoryHead->value) && itemType == _weapon){
            count ++;
            printf("%d - ", count);
            printItem(inventoryHead->value, inventoryHead->reference, inventoryHead->quantity, inventoryHead->durability);
        }else if(isArmor(inventoryHead->value) && itemType == _armor){
            count ++;
            printf("%d - ", count);
            printItem(inventoryHead->value, inventoryHead->reference, inventoryHead->quantity, inventoryHead->durability);
        }else if (isHeal(inventoryHead->value) && itemType == _heal){
            count ++;
            printf("%d - ", count);
            printItem(inventoryHead->value, inventoryHead->reference, inventoryHead->quantity, inventoryHead->durability);
        }
        inventoryHead = inventoryHead->next;
    }

    return count;
}

InventoryNode *itemSelect(InventoryNode *inventoryHead, int itemType){
    printf("\n%s Availables : \n\n", ITEM_TYPE[itemType]);
    int chosen;

    int index = availableItems(inventoryHead, itemType);

    if(index == 0){
        printf("No %s available !\n", ITEM_TYPE[itemType]);
        return NULL;
    }else if(index == 1){
        return findItem(inventoryHead, itemType, index);
    }else{
        do{
            printf("\nChoose a %s : ", ITEM_TYPE[itemType]);

            fflush(stdin);
            scanf("%d", &chosen);
        }while(chosen <= 0 && chosen > index);

        return findItem(inventoryHead, itemType, index);
    }
}

void attack(MonsterNode *monsterNode, InventoryNode *weapon){
    if(weapon != NULL && weapon->durability > 0){
        int damage = atoi(ITEMS[weapon->reference][_info]);
        monsterNode->hp -= damage;

        if(monsterNode->hp <= 0){
            monsterNode->hp = 0;
        }

        printf("You deal %d damage\n", damage);
        weapon->durability -= WEAR_COMBAT;

        if(weapon->durability == 0){
            printf("Your weapon is now broken\n");
        }
    }else{
        printf("Your deal 0 damage\n");
    }
}

void monsterAttack(Player *player, InventoryNode *armor, MonsterNode *monster){
    int damage = atoi(MONSTERS[monster->reference][_monsterDamage]);

    if(armor != NULL){
        damage -= round((damage*atoi(ITEMS[armor->reference][_info]))/100);
    }

    player->currentHp -= damage;

    printf("You take %d damage\n", damage);
}

int handleCombat(MonsterNode *monsterNode, Player *player){
    char action;
    int loop = 1;
    int defeated = 0;

    printf("\nYour are fighting a %s - Hp : %d | Dmg : %s\n", MONSTERS[monsterNode->reference][_name], monsterNode->hp, MONSTERS[monsterNode->reference][_monsterDamage]);

    InventoryNode *weapon = itemSelect(player->inventory, _weapon);

    InventoryNode *armor = itemSelect(player->inventory, _armor);

    do{
        printf("\nChoose an action ? (a : attack, p : use a potion, f : try to flee)  : ");
        fflush(stdin);
        scanf("%c", &action);

        system("cls"); //clear console

        if(action == 'a'){
            attack(monsterNode, weapon);
        }else if(action == 'p'){
            InventoryNode *potion = itemSelect(player->inventory, _heal);
        }else if(action == 'f'){
            loop = flee();
        }

        if(loop){
            if(monsterNode->hp > 0){
                monsterAttack(player, armor, monsterNode);

                printf("Your HP : %d | Ennemy HP : %d", player->currentHp, monsterNode->hp);
            }else if(player->currentHp > 0){

                loop = 0;
                defeated = 1;
            }else{
                printf("You are dead. GAME OVER.");
                loop = 0;
            }
        }


    }while(loop);

    return defeated;
}
