#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

typedef struct MonsterNode MonsterNode;
typedef struct Levels Levels;
typedef struct Level Level;
typedef struct InventoryNode InventoryNode;
typedef struct Player Player;
typedef struct RessourceNode RessourceNode;

#include "monster.h"
#include "ressource.h"
#include "map.h"
#include "player.h"
#include "data.h"
#include "item.h"
#include "save.h"

#define TOOL_DURABILITY 10
#define SWORD_DURABILITY 10
#define SPEAR_DURABILITY 8
#define HAMMER_DURABILITY 5

#define MAX_RESSOURCE_STACK 20
#define MAX_INVENTORY_COUNT 10
#define NO_STORAGE_LIMIT 0

#define WEAR_LV1 1
#define WEAR_LV2 2
#define WEAR_LV3 4
#define WEAR_COMBAT 1

#define MAX_LEVEL 10

#define INIT_MAP_ROWS 10
#define INIT_MAP_COLUMNS 10

#define RESPAWN_RESSOURCE 10
#define RESPAWN_MONSTER 15

#define FLEE_RATE 30

#define TOTAL_ITEMS 34
extern char ITEMS[TOTAL_ITEMS][3][32];

#define TOTAL_CONVERTED 9
extern int CONVERTED_RESSOURCE[TOTAL_CONVERTED][2];

#define TOTAL_REQUIRED 9
extern int REQUIRED_TOOL[TOTAL_REQUIRED][4];

#define TOTAL_MONSTERS 16
extern char MONSTERS[TOTAL_MONSTERS][5][32];

extern char ITEM_TYPE[4][32];

#define TOTAL_LEVELS 9
extern int LEVELS[TOTAL_LEVELS][3];

#define TOTAL_CRAFTS 25
extern int CRAFT[TOTAL_CRAFTS][6];


#define BLACK "\033[0;30m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"

#define RESET "\033[0m"

//PLAYER
void initPlayer(Player *player);
void displayCharacter(Player *player);
void printInventory(InventoryNode *inventoryNode);
void addToStorage(InventoryNode **inventoryHead, int item, int quantity, int storageLimit, int durability);
int addIfStackable(int item, InventoryNode * inventoryNode, int quantity);
int playerInventoryIsFull(InventoryNode *inventoryHead);

//MOVEMENT
int handleMovement(Levels *levels, Player *player);
int checkCollision(Level *level, int targetRow, int targetColumn, Player *player, Levels *levels);
int move(Level *level, Player *player, char direction, Levels *levels);
Level *getCurrentMap(Player *player, Levels *levels);
void switchLevel(int target, Player *player, Levels *levels);

// MAP
int rand2 (int min, int max);
void printMap(int **map, int rows, int columns);
void createLevel(Level *level, int rows, int columns, int nbLevel);
void addPlayer(Level *level, Player *player);
void populate(Level *level, int entity, int quantity);
void populateLevel(Level *level);
void initMap(Levels *levels, int rows, int columns, Player *player);
void getColor(int entity);
void respawnMonsters(Level *level, MonsterNode *list, Player *player);
void respawnRessource(Level *level, RessourceNode *list, Player *player);

//RESSOURCE
int isMapRessource(int entity);
void addToRessourceList(RessourceNode **ressourceHead, int entity, int row, int column);
void printRessourceList(RessourceNode *ressourceNode);
int mapToItemRessource(int ressource);
int harvestRessource(RessourceNode *ressource, Player *player);
int canHarvest(int ressource, InventoryNode *inventoryNode);
int getRessourceLevel(int ressource);
RessourceNode *findRessourceNode(RessourceNode *ressourceNode, int row, int column);

//MONSTER
int isMonster(int entity);
void addToMonsterList(MonsterNode **monsterHead, int entity, int row, int column);
void printMonsterList(MonsterNode *monsterNode);
int findMonsterReference(int entity);
MonsterNode *findMonsterNode(MonsterNode *monsterNode, int row, int column);

//COMBAT
int handleCombat(MonsterNode *monsterNode, Player *player);
int flee();
void monsterAttack(Player *player, InventoryNode *armor, MonsterNode *monster);
void leveling(Player *player, MonsterNode *monster);
void attack(MonsterNode *monsterNode, InventoryNode *weapon);
int findLevelRequirement(int level);
void handlePotion(Player *player, InventoryNode *potion);

//MENU
void gameLoop(Levels *levels, Player *player);
int handleAction(Levels *levels, Player *player, char action);
void handleMainMenu(char action);

//ITEM
int isWeapon(int entity);
int isArmor(int entity);
int isTool(int entity);
int isHeal(int entity);
int isItemRessource(int entity);
int getDurability(int item);
void printItem(int item, int reference, int quantity, int durability);
int findItemReference(int entity);
int checkDurability(int ressource, int durability);
int isRequiredTool(int tool, int ressource, int durability);
void handleToolDurability(InventoryNode *inventoryNode, int ressource);
InventoryNode *itemSelect(InventoryNode *inventoryHead, int itemType);
int availableItems(InventoryNode *inventoryHead, int itemType);
InventoryNode *findItem(InventoryNode *inventoryHead, int itemType, int index);
void removeItem(InventoryNode **inventoryHead, InventoryNode *nodeToRemove);

//NPC
void handleNpc(Player *player, InventoryNode *chest);
void repair(InventoryNode *inventoryHead);
void transferItem(Player *player, InventoryNode *chest);
int transfer(InventoryNode **inventoryHead, InventoryNode *item, int storageLimit);
int hasRessource(InventoryNode *inventory, InventoryNode *chest, int ressource, int quantity);
int craftIndex(int item);
int canCraft(InventoryNode *inventory, InventoryNode *chest, int item, int currentMapLevel);
int craftableItemList(InventoryNode *inventory, InventoryNode *chest, int currentMapLevel);
int findItemToCraft(InventoryNode *inventory, InventoryNode *chest, int index, int currentMapLevel);
int removeRessource(InventoryNode *inventoryHead, int ressource, int quantity);
void craftItem(InventoryNode *inventory, InventoryNode *chest, int item);
void craft(InventoryNode *inventory, InventoryNode *chest, int currentMapLevel);

//SAVE
void save(Levels *levels, Player *player);
void savePlayer(Player *player, FILE *file, InventoryNode *chest);
void saveChest(InventoryNode *chest, FILE *file);
void saveInventory(InventoryNode *inventoryHead, FILE *file);
void saveMap(Level *level, FILE *file);
int loadSave(Levels *levels, Player *player);
void skipLine(FILE *file, int skip);
void checkMapSize(FILE *file, Level *level);
void fillLevel(Level *level, FILE *file, Player *player);
void loadLevels(FILE *file, Levels *levels, Player *player);
int processItemLine(char buffer[255], int infoPos);
void loadInventory(FILE *file, Player *player);
void loadChest(FILE *file, Levels *levels);
void loadPlayer(FILE *file, Player *player, Levels *levels);

//FREE
void freeMonsterList(MonsterNode *head);
void freeRessourceList(RessourceNode *head);
void freeMap(int **map, int rows);
void freeStorage(InventoryNode *head);
void freeLevel(Level *level);
void freeEverything(Levels *levels, Player *player);

#endif
