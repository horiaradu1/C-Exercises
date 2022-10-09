#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

long int strToInt (char* input) {
    // Change the argv recieved from a char to int
    char *end;
    long int result = strtol(input, &end, 10);
    if (*end != '\0'){
        errno = 1;
    }
    return result;
}

void fillMat (int *matFill, int r, int c) {
    // Function to fill a Matrix, having r rows and c columns
    // With random numbers from 0-100
    for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++){
            matFill[(i * c) + j] = rand() % 101;
        }
    }
}

void printMat (int *matPrint, int r, int c) {
    // Function to print a Matrix
    for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++){
            printf("%d ", matPrint[(i * c) + j]);
        }
        printf(" \n");
    }
}

void printHelpAndExit (char *progName){
    // Function to exit the program
    printf("Usage: %s <N> <M> <seed>\n", progName);
    exit(0);
}

int *matMult (int *matrix1, int *matrix2, int r1, int c1, int r2, int c2) {
    // Initialize the result Matrix
    int *res = (int *) malloc(r1 * c2 * sizeof(int));

    for (int i = 0; i < r1; i++){
        for (int j = 0; j < c2; j++){
            res[(i * c2) + j] = 0;
        }
    }

    // Multiply the two Matrices
    for (int i = 0; i < r1; i++){
        for (int j = 0; j < c2; j++){
            for (int k = 0; k < r2; k++){
                res[(i * c2) + j] = res[(i * c2) + j] + matrix1[(i * c1) + k] * matrix2[(k * c2) + j];
            }
        }
    }
    return res;
}

int main (int argc, char *argv[]) {
    int m, n, seed;

    if (argc != 4){
        // Argument number check
        printf("ERROR: incorrect number of arguments\n");
        printHelpAndExit(argv[0]);
    }
    
    m = strToInt(argv[1]);
    n = strToInt(argv[2]);
    seed = strToInt(argv[3]);
    
    if (errno != 0 || m == 0 || n == 0){
        // Invalid argument check
        printf("ERROR: invalid argument\n");
        printHelpAndExit(argv[0]);
    }

    
    srand(seed);
    
    // Allocate the space for the Matrices
    int *mat1 = (int *) malloc(m * n * sizeof(int));
    int *mat2 = (int *) malloc(n * m * sizeof(int));
    int *mat;

    // Fill the Matrices
    fillMat(mat1, m, n);
    fillMat(mat2, n, m);
    
    // Print the Matrices
    printf("MATRIX 1:\n");
    printMat(mat1, m, n);

    printf("MATRIX 2:\n");
    printMat(mat2, n, m);
     
    // Time the duration of the multiplication
    clock_t start = clock();
    // Multiply the Matrices
    mat = matMult(mat1, mat2, m, n, n, m);
    clock_t end = clock();

    printf("RESULT:\n");
    printMat(mat, m, m);

    // Calculate time
    double execTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("EXECUTION TIME: %f\n", execTime);

    // Free memory allocated with malloc
    free(mat);
    free(mat1);
    free(mat2);

    return 0;
}