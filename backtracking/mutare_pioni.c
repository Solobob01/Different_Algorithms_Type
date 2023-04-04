#include <stdio.h>
#include <stdlib.h>

int** callocTable(int size){
    int** table = (int**)calloc(size, (sizeof(int*)));
    for(int i = 0;i < size;i++){
        table[i] = (int*)calloc(size, (sizeof(int)));
    }
    return table;
}

void freeTable(int** table, int size){
    for(int i = 0; i < size;i++){
        free(table[i]);
    }
    free(table);
}

int** readTable(FILE* input,int size, int posj){
    int** table = callocTable(size);
    for(int i = 0;i < size;i++){
        for(int j = 0;j < size;j++){
            fscanf(input, "%d", &table[i][j]);
        }
    }
    table[0][posj] = 3;
    return table;
}

void printTable(int** table, int size){
    for(int i = 0;i < size; i++){
        for(int j = 0;j < size;j++){
            if(table[i][j] == -1){
                printf("A ");
            } else {
            printf("%d ",table[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}
 //-1 - in fata -> nu se poate avansa
 //0 - nu exista
 //1 - stanga
 //2 - dreapta
void solveTable(int** table, int size, int posi, int posj, int contor){
    if(posi == size - 1){
        table[posi][posj] = contor;
        printTable(table, size);
        table[posi][posj] = 0;
        return;
    }
    table[posi][posj] = contor;
    if(posj > 0 && (table[posi + 1][posj - 1] == -1)){
        //inamic in stanga
        solveTable(table, size, posi + 1, posj - 1, contor + 1);
        table[posi + 1][posj - 1] = -1;
    }
    if((posj < size - 1) && (table[posi + 1][posj + 1] == -1)){
        //inaimc in dreapta
        solveTable(table, size, posi + 1, posj + 1, contor + 1);
        table[posi + 1][posj + 1] = -1;
    }
    if(table[posi + 1][posj] == -1){
        //inamic in fata
        table[posi][posj] = 0;
        return;
    }
    solveTable(table, size, posi + 1, posj, contor + 1);
    table[posi][posj] = 0;
    return;
}



int main(){
    int size, nrPion, pionJ;
    FILE* input = fopen("input.txt", "r");
    fscanf(input, "%d", &size);
    fscanf(input, "%d", &pionJ);
    int** table = readTable(input, size, pionJ);
    printf("Initial Table(A - enemy, 0 - blank space, number - path):\n");
    printTable(table, size);
    solveTable(table, size, 0, pionJ, 1);
    freeTable(table, size);
    fclose(input);
    return 0;
}