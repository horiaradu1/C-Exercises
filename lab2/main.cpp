#include <iostream>
#include <fstream>
#include <vector>
#include "Matrix.h"

using namespace std;

void printHelpAndExit (char *progName){
    // Function to exit the program
    cout << "Usage: " << progName << " <operand1> <operation> <operand2> <output>\n";
    exit(0);
}

int main (int argc, char *argv[]) {

    /* Checks for the correct number of arguments */
    if (argc != 5){
        cout << "ERROR: Incorrect number of arguments.\n";
        printHelpAndExit(argv[0]);
    }

    /* Checks for the corect operation sign */
    string sign = argv[2];
    if (sign != "x" && sign != "X" && sign != "+"){
        cout << "ERROR: Incorrect operation arguments.\n";
        printHelpAndExit(argv[0]);
    }

    /* Define the matrixes we're gonne work with */
    Matrix op1 = Matrix();
    Matrix op2_matrix = Matrix();
    int op2_value;
    bool scalar= false;

    /* Fill both matrixes from file and check that they dont have any errors */
    if (op1.fill_from_file(argv[1]) != 0){
        cout << "ERROR: First operand has a problem.\n";
        printHelpAndExit(argv[0]);
    }
    /* Here it checks if operand 2 is a matrix or scalar */
    if (op2_matrix.fill_from_file(argv[3]) != 0){
        char *end = NULL;
        op2_value = strtol(argv[3], &end, 10);
        scalar = true;
        /* And if it is not any, counts it as an error */
        if (*end != '\0'){
            cout << "ERROR: Second operand must be a path to a Matrix or an int.\n";
            printHelpAndExit(argv[0]);
        }
    }

    /* Here takes places the calculation of each possible outcome */
    if (scalar == true){
        /* If operand 2 is a scalar, checks what operation to do */
        if ((sign == "x") || (sign == "X")){
            op1.mult(op2_value);
        }
        else
        if (sign == "+"){
            op1.add(op2_value);
        }
    }
    else
    { /* If the operand 2 is a matrix, checks what operation to do */
        if ((sign == "x") || (sign == "X")){
            if (op1.mult(&op2_matrix) != 0){
                /* Checks if you can multiply the matrixes */
                cout << "Error: Can't multiply those Matrixes.\n";
                printHelpAndExit(argv[0]);
            }
        }
        else
        if (sign == "+"){
            if (op1.add(&op2_matrix) != 0){
                /* Checks if you can add those matrixes */
                cout << "Error: Can't add those Matrixes.\n";
                printHelpAndExit(argv[0]);
            }
        }
    }
    /* Stores the result in the file location given by the argument */
    int e = op1.store_in_file(argv[4]);
    if (e != 0){
        cout << "Error: Can't store file.\n";
        printHelpAndExit(argv[0]);
    }

}