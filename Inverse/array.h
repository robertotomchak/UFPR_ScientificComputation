/*
	Name: Roberto Sprengel Minozzo Tomchak
	GRR: 20232369
*/

/*
    Useful functions for array manipulation
    Uses double type in all array and matrices
*/
#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <stdlib.h>

/*
print_array: prints an array in the stdout (with %.15e format)
    a: array of doubles
    n: size of a
return: void
*/
void print_array(double *a, int n);

/*
print_matrix: prints a matrix in the stdout (with %.15e format)
    A: matrix of doubles
    n: number of rows of A
    m: number of columns of A
return: void
*/
void print_matrix(double **A, int n, int m);

/*
read_array: reads an array from stdin
    a: array of doubles
    n: size of a
return: void
*/
void read_array(double *a, int n);

/*
read_matrix: reads a matrix from stdin
    A: matrix of doubles
    n: number of rows of A
    m: number of columns of A
return: void
*/
void read_matrix(double **A, int n, int m);

/*
create_matrix: allocates memory for a matrix
    n: number of rows of A
    m: number of columns of A
return: matrix of size n x m
*/
double **create_matrix(int n, int m);

/*
copy_matrix: creates a copy of the given matrix
    A: matrix of doubles
    n: number of rows of A
    m: number of columns of A
return: a new matrix equal to A
*/
double **copy_matrix(double **A, int n, int m);

/*
free_matrix: frees the memory allocated for a matrix
    A: matrix of doubles
    n: number of rows of A
return: void
*/
void free_matrix(double **A, int n);

#endif
