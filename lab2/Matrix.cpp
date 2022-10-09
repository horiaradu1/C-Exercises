#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include "Matrix.h"

using namespace std;

/* Create and clear a/the Matrix */
Matrix :: Matrix(){
    _matrix.clear();
}

/* Get rows of Matrix */
int Matrix :: rows(){
    return _matrix.size();
}

/* Get columns of Matrix */
int Matrix :: columns(){
    return _matrix[0].size();
}

/* Fill a Matrix from a read file*/
int Matrix :: fill_from_file(char *path){
    ifstream myfile;
    myfile.open(path);
    if (myfile.fail()){
        //cout << "ERROR: File not found.\n";
        return -1;
    }

    string line;
    vector<int> row;

    /* Read the file line by line */
    while (getline(myfile, line)){
        row.clear();
        istringstream iss(line);
        string value_string;
        int value_int;
        while (iss >> value_string){
            char *end = NULL;
            const char *char_value_string = value_string.c_str();
            value_int = strtol(char_value_string, &end, 10);
            row.push_back(value_int);
            /* Check if there is any element that is not an int */
            if (*end != '\0'){
                cout << "ERROR: Matrix file contains a non-int.\n";
                return -1;
            }
        }
        _matrix.push_back(row);
    }
    myfile.close();
    
    /* Checks to see if the Matrix is of a correct size */
    for (int i = 0; i < _matrix.size(); i++){
        if (_matrix[0].size() != _matrix[i].size()){
            cout << "ERROR: Matrix size is wrong.\n";
            return -1;
        }
    }

    return 0;
}

/* Store current Matrix in a file */
int Matrix :: store_in_file(char *path){
    ofstream file;
    file.open(path);
    if (file.fail()){
        return -1;
    }

    for (int i = 0; i < rows(); i++){
        for (int j = 0; j < columns(); j++){
            file << index(i, j);
            if (j < columns() - 1){
                file << " ";
            }
        }
        if (i < rows() - 1){
            file << endl;
        }
        
    }
    return 0;
}

/* Print the Matrix */
void Matrix :: print(){
    for (int i = 0; i < rows(); i++){
        for (int j = 0; j < columns(); j++){
            cout << index(i, j);
            if (j < columns() - 1){
                cout << " ";
            }
        }
        if (i < rows() - 1){
            cout << endl;
        }
    }
}

/* Get value in the Matrix at a specific location */
int Matrix :: index(int row, int column){
    return _matrix[row][column];
}

/* Add the Matrix with another Matrix */
int Matrix :: add(Matrix *m){
    /* Check if you can add the matrixes */
    if ((rows() != m->rows()) || (columns() != m->columns())){
        return -1;
    }
    /* Add the matrixes */
    for (int i = 0; i < rows(); i++){
        for (int j = 0; j < columns(); j++){
            _matrix[i][j] = index(i, j) + m->index(i, j);
        }
    }
    return 0;
}

/* Add the Matrix with a number*/
int Matrix :: add(int val){
    for (int i = 0; i < rows(); i++){
        for (int j = 0; j < columns(); j++){
            _matrix[i][j] = index(i, j) + val;
        }
    }
    return 0;
}

/* Multiply the Matrix with another Matrix */
int Matrix :: mult(Matrix *m){
    /* Check if you can multiply the matrixes */
    if (columns() != m->rows()){
        return -1;
    }

    /* Create an empty Matrix */
    vector<vector<int>> res;
    for (int i = 0; i < rows(); i++){
        vector<int> row;
        for (int j = 0; j < m->columns(); j++){
            row.push_back(0);
        }
        res.push_back(row);
    }

    /* Does the multiplication */
    for (int i = 0; i < rows(); i++){
        for (int j = 0; j < m->columns(); j++){
            for (int k = 0; k < m->rows(); k++){
                res[i][j] = res[i][j] + index(i, k) * m->index(k, j);
            }
        }
    }

    _matrix = res;

    return 0;
}

/* Multiply the Matrix with a number */
int Matrix :: mult(int val){
    for (int i = 0; i < rows(); i++){
        for (int j = 0; j < columns(); j++){
            _matrix[i][j] = index(i, j) * val;
        }
    }
    return 0;
}