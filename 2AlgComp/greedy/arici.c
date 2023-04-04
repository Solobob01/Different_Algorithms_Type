#include <stdio.h>
#include <stdlib.h>

int** callocMatrix(int size){
    int** output = (int**)calloc(size, (sizeof(int*)));
    for(int i = 0;i < size;i++){
        output[i] = (int*)calloc(size, (sizeof(int)));
    }
    return output;
}

void freeMatrix(int** matrix,int size){
    for(int i = 0; i < size;i++){
        free(matrix[i]);
    }
    free(matrix);
}

int** readMatrix(int size, FILE* input) {
    int** matrix = callocMatrix(size);
    for(int i = 0;i < size;i++){
        for(int j = 0;j < size;j++){
            fscanf(input, "%d", &matrix[i][j]);
        }
    }
    return matrix;
}

void printMatrix(int** matrix, int size){
    for(int i = 0;i < size;i++){
        for(int j = 0;j < size;j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int** createSolution(int** matrix, int size,int starti, int startj){
    int** output = callocMatrix(size);
    output[starti][startj] = matrix[starti][startj];
    return output;
}

int detMax(int a, int b){
    if(a >= b){
        return a;
    }
    return b;
}

void solveLivada(int** livada, int size){
    int max = 0, starti = 0, startj = 0;
    while(starti != size - 1 || startj != size-1){
        max += livada[starti][startj];
        printf("%d %d\n",starti, startj);
        if(starti == size - 1){
            startj++;
        }else if(startj == size - 1){
            starti++;
        }else{
            if(livada[starti+1][startj] >= livada[starti][startj+1]){
                starti++;
            } else{
                startj++;
            }
        }
    }
    printf("Maxim:%d\n",max);
}

int main(){
    int size = -1,starti, startj;
    FILE* input = fopen("input.txt", "r");
    fscanf(input, "%d", &size);
    fscanf(input, "%d %d", &starti, &startj);
    int** livada = readMatrix(size, input);
    solveLivada(livada, size);
    printMatrix(livada, size);
    freeMatrix(livada, size);
    fclose(input);
    return 0;
}