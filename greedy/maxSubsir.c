#include <stdio.h>
#include <stdlib.h>

int* readInput(FILE* input,int *n){
    fscanf(input, "%d", n);
    int* v = (int*)calloc(*n, sizeof(int));
    for(int i = 0; i < *n;i++){
        fscanf(input, "%d", &v[i]);
    }
    return v;
}

void printVector(int* v, int n){
    for(int i = 0; i < n;i++){
        printf("%d ", v[i]);
    }
    printf("\n");
}

int findMax(int* v, int n){
    int max = 1, finalMax = 1;
    for(int i = 0;i < n-1;i++){
        if(v[i + 1] >= v[i]){
            max++;
        }else{
            if(finalMax <= max){
                finalMax = max;
            }
            max = 1;
        }
    }
    if(finalMax <= max){
        return max;
    }
    return finalMax;
}

int main(){
    int n = -1;
    FILE* input = fopen("./input.txt", "r");
    int* v = readInput(input, &n);
    printf("Max:%d\n", findMax(v,n));
    free(v);
    fclose(input);
    return 0;


}