#!/usr/bin/python3

import sys
import random
import time

def print_help_and_exit():
    print("Usage: " + sys.argv[0] + " <N> <M> <seed>")
    sys.exit(0)

def print_matrix(mat):
    for column in mat:
        for item in column:
            print(str(item) + " ", end = '')
        print("")

def multiply_matrixes(mat1, mat2):
    rows_mat1 = len(mat1)
    cols_mat2 = len(mat2[0])

    # Initialize result matrix with the right size and fill it with zeroes
    res = [[0 for x in range(cols_mat2)] for y in range(rows_mat1)]

    # Iterate over rows of mat1
    for i in range(len(mat1)):
        # Iterate over columns of mat2:
        for j in range(len(mat2[0])):
            # Iterate over rows of mat2:
            for k in range(len(mat2)):
                res[i][j] = res[i][j] + mat1[i][k] * mat2[k][j]

    return res


if __name__ == "__main__":

    # Check that we have the right number of arguments
    if(len(sys.argv) != 4):
        print("ERROR: incorrect number of arguments")
        print_help_and_exit()

    # All argument should convert to integers
    try:
        N = int(sys.argv[1])
        M = int(sys.argv[2])
        seed = int(sys.argv[3])
    except:
        print("ERROR: invalid argument")
        print_help_and_exit()

    # initialize the random number generator with the seed
    random.seed(seed)

    # Generate 2 random matrixes
    mat1 = [[random.randrange(100) for i in range(M)] for j in range(N)]
    mat2 = [[random.randrange(100) for i in range(N)] for j in range(M)]

    # Print them:
    print("MATRIX 1:")
    print_matrix(mat1)
    print("MATRIX 2:")
    print_matrix(mat2)

    # Multiply
    start = time.time()
    result = multiply_matrixes(mat1, mat2)
    end = time.time()
    print("RESULT:")
    print_matrix(result)
    print("EXECUTION TIME: " + "%lf" % (end-start))
