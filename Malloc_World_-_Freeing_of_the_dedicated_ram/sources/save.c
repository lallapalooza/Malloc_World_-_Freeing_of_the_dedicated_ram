#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int writeInFile(int** map){
    FILE* f = fopen("save.txt", "w");
    if(f == NULL){
        return 0;
    }
    fclose(f);
    return 1;
}

//taille de la map à modifier
void displayTab(int** map){
    for (size_t i = 0; i < 10; i++) {
        for (size_t j = 0; j < 10; j++) {
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char const *argv[]) {
    int** map = malloc(sizeof(int*) * 10);
    for (size_t i = 0; i < 10; i++) {
        map[i] = malloc(sizeof(int) * 10);
    }
    for (size_t i = 0; i < 10; i++) {
        for (size_t j = 0; j < 10; j++) {
            map[i][j] = 0;
        }
    }
    displayTab(map);
    writeInFile(map);
    return 0;
}
