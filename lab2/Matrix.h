#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

using namespace std;

class Matrix {

public:
    Matrix();               // create an empty matrix

    int rows();             // return number of rows of the matrix
    int columns();          // return number of columns of the matrix

    /* The function fill_from_file initializes the matrix content from a file,
     * the format of the file is: one row per line, values separated with
     * spaces, for example here is the content of a file describing a 3 by 4
     * matrix:
     * 45 15 87 12
     * 12 48 878 7
     * 11 25 85 44
     * The function returns 0 on success, -1 on error.
     */
    int fill_from_file(char *path);

    /* The function store_in_file writes the matrix content in a file, using
     * the same format as described above. Returns 0 on success, -1 on error */
    int store_in_file(char *path);

    /* Prints the matrix on the console */
    void print();

    int index(int row, int column); // returns the value at the coordinates

    /* Matrix - matrix addition: add m to the current matrix and overwrite the
     * current matrix with the result: */
    int add(Matrix *m);

    /* Matrix - scalar addition: add val to the current matrix and overwrite
     * the current matrix with the resul: */
    int add(int val);

    /* Matrix - matrix multiplication: multiply the current matrix by m and
     * overwrite the current matrix with the result */
    int mult(Matrix *m);

    /* Matrix - scalar multiplication: multiply the current matrix by m and
     * overwrites the current matrix with the result */
    int mult(int val);

private:
    /* A bi-dimensional vector containing the matrix content: */
    vector<vector<int>> _matrix;
};

#endif /* ifndef MATRIX_H */
