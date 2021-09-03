#include <stdlib.h>
#include <stdio.h>
#include <time.h>

double *createEmptyArray(int n);
double *randomArray(int n);
double **randSqrMatriz(int n);
double tempoMultIJ(int n, double **matrix, double *array, double *result);
double tempoMultJI(int n, double **matrix, double *array, double *result);
void emptyArray(int n, double *array);

int main(void){
    srand(time(NULL));
    int nMaximo = 16000;
    
    double **A = randSqrMatriz(nMaximo);
    double *x  = randomArray(nMaximo);
    double *b  = createEmptyArray(nMaximo);

    FILE *csv_file = fopen("temposC.csv", "w");
    fprintf(csv_file,"n,TempoIJ,TempoJI\n");

    int n;
    int range = 16;
    for (int i = 0; i <= range; i++) {
        n = i * 1000;
        double tempoIJ = tempoMultIJ(n,A,x,b);
        emptyArray(n,b);
        double tempoJI = tempoMultJI(n,A,x,b);
        printf("n = %5d -> ij: %.6f / ji: %.6f \n",n,tempoIJ,tempoJI);
        fprintf(csv_file,"%d,%.6f,%.6f\n",n,tempoIJ,tempoJI);
    }
    
    fclose(csv_file);
    return 0;
}

double *createEmptyArray(int n) {
    double *array = (double *)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++){
        array[i] = 0;
    }
    return array;
}

double *randomArray(int n) {
    double *array = (double *)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++){
        array[i] = (double)rand();
    }
    return array;
}

double **randSqrMatriz(int n) {
    double **matriz = (double **)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++){
        matriz[i] = randomArray(n);
    }
    return matriz;
}

double tempoMultIJ(int n, double **matriz, double *array, double *result) {
    double s;
    clock_t start = clock();
    for (int i = 0; i < n; i++){
        s = 0;
        for (int j = 0; j < n; j++){
            s += matriz[i][j] * array[j];
        }
        result[i] = s;
    }
    clock_t end = clock();
    return (double)(end - start)/CLOCKS_PER_SEC;
}

double tempoMultJI(int n, double **matriz, double *array, double *result){
    double t;
    clock_t start = clock();
    for (int j = 0; j < n; j++){
        t = array[j];
        for (int i = 0; i < n; i++){
            result[i] += matriz[i][j] * t;
        }
    }
    clock_t end = clock();
    return (double)(end - start)/CLOCKS_PER_SEC;
}

void emptyArray(int n, double *array) {
    for (int i = 0; i < n; i++) {
        array[i] = 0;
    }
}
