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


void writeInMapRead(int** mapRead, int* saveInt, int row){
    for (size_t i=0; i<4; i+=1) {
        mapRead[row][i] = saveInt[i];
    }
    printf("\n");
}

int** readFile(){
    char string[255] ="";
    int* saveInt =NULL;

    FILE* f = fopen("save.txt", "r");
    int c=0;
    int row=0;

    int** mapRead=malloc(sizeof(int*)*4);

    for (size_t i=0; i<4; i+=1) {
        mapRead[i] = malloc(sizeof(int)*4);
    }

    for (size_t i =0; i<4; i+=1) {
        for (size_t j =0; j <4; j+=1) {
            mapRead[i][j] = 0;
        }
    }

    displayMap(mapRead);

    while(fgets(string, 255, f) != NULL){
        char* stringTok = strtok(string," ");
        saveInt = malloc(sizeof(int) * 10);
        c= 0;

        while (stringTok != NULL) {
            saveInt[c]= atoi(stringTok);
            stringTok= strtok(NULL, " ");
            c+=1;
        }

        writeInMapRead(mapRead, saveInt, row);
        row += 1;
    }

    displayMap(mapRead);

    fclose(f);
    freeMap(mapRead);
    return mapRead;
}

int main(int argc, char const *argv[]) {
    int** map = malloc(sizeof(int*)*4);
    for (size_t i =0; i < 4; i+=1) {
        map[i] = malloc(sizeof(int)*4);
    }
    for (size_t i = 0; i < 4; i+=1) {
        for (size_t j = 0; j < 4; j+=1) {
            map[i][j] = 1;
        }
    }
    writeInFile(map);
    readFile();
    freeMap(map);
    return 0;
}
