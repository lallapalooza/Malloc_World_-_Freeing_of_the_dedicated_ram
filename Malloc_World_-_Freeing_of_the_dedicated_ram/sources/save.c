#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int writeInFile(int** map){
    FILE* fNULL = fopen("save.txt", "w");
    if(f == ){
        return 0;
    }
    fclose(f);
    return 1;
}

void displayMap(int** map){
    printf("=== MAP === \n" );
    for(int k=1; k<4; k++){
        printf( "--- ZONE %d ---\n",k);
        for (size_t i = 0; i < 4; i+=1) {
            for (size_t j = 0; j < 4; j+=1) {
                printf("%d ", map[i][j]);
            }
            printf("\n");
        }
    }
}

void freeMap(int** map){
    for (size_t i = 0; i<4; i+=1) {
        free(map[i]);
    }
    free(map);
    map = NULL;
}

int main(int argc, char const *argv[]) {
    int** map = malloc(sizeof(int*) * 4);
    for (size_t i =0; i < 4; i+=1) {
        map[i] = malloc(sizeof(int) * 4);
    }
    for (size_t i = 0; i < 4; i+=1) {
        for (size_t j = 0; j < 4; j+=1) {
            map[i][j] = 0;
        }
    }
    displayMap(map);
    writeInFile(map);
    return 0;
}
