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

void solveLivada(int** livada, int** solution, int size, int starti, int startj){
    for(int i = starti; i >= 0;i--){
        for(int j = startj; j >=0;j--){
            if((i == starti) && (j == startj)){
                continue;
            }
            if(i == starti){
                solution[i][j] = livada[i][j] + solution[i][j + 1];
                continue;
            }
            if(j == startj){
                solution[i][j] = livada[i][j] + solution[i + 1][j];
                continue;
            } else {
            solution[i][j] = livada[i][j] + detMax(solution[i+1][j], solution[i][j+1]);
            }
        }
    }
}

int main(){
    int size = -1,starti, startj;
    FILE* input = fopen("input.txt", "r");
    fscanf(input, "%d", &size);
    fscanf(input, "%d %d", &starti, &startj);
    int** livada = readMatrix(size, input);
    int** solution = createSolution(livada, size,starti, startj);
    solveLivada(livada, solution, size, starti, startj);
    printMatrix(livada, size);
    printMatrix(solution, size);
    printf("Numarul maxim: %d\n", solution[0][0]);
    freeMatrix(livada, size);
    fclose(input);
    return 0;
}