#include <stdio.h>
#include <stdlib.h>

int* callocVector(int size){
    int* output = (int*)calloc(size, sizeof(int));
    return output;
}

void freeVector(int* vector){
    free(vector);
}

int* readVector(FILE* input, int size){
    int* output = callocVector(size);
    for(int i = 0; i < size;i++){
        fscanf(input, "%d", &output[i]);
    }
    return output;
}

// se imparte in 1 si size - 1 probleme
int calculateSum(int* vector, int pos){
    if(pos == -1){
        return 0;
    }
    return vector[pos] + calculateSum(vector, pos - 1);
}

int main(){
    int size;
    FILE* input = fopen("input.txt", "r");
    fscanf(input, "%d", &size);
    int* vector = readVector(input, size);
    printf("Suma: %d\n", calculateSum(vector, size - 1));
    freeVector(vector);
    fclose(input);
    return 0;
}