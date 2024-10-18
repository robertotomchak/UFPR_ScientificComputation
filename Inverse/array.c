/*
	Name: Roberto Sprengel Minozzo Tomchak
	GRR: 20232369
*/

/*
    Useful functions for array manipulation
    Uses double type in all array and matrices
*/

#include "array.h"

/*
print_array: prints an array in the stdout (with %.15e format)
    a: array of doubles
    n: size of a
return: void
*/
void print_array(double *a, int n) {
    for (int i = 0; i < n - 1; i++)
        printf("%.15e ", a[i]);
    printf("%.15e\n", a[n-1]);
}

/*
print_matrix: prints a matrix in the stdout (with %.15e format)
    A: matrix of doubles
    n: number of rows of A
    m: number of columns of A
return: void
*/
void print_matrix(double **A, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m - 1; j++)
            printf("%.15e ", A[i][j]);
        printf("%.15e\n", A[i][m-1]);
    }
}

/*
read_array: reads an array from stdin
    a: array of doubles
    n: size of a
return: void
*/
void read_array(double *a, int n) {
    for (int i = 0; i < n; i++)
        scanf("%lf", &a[i]);
}

/*
read_matrix: reads a matrix from stdin
    A: matrix of doubles
    n: number of rows of A
    m: number of columns of A
return: void
*/
void read_matrix(double **A, int n, int m) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%lf", &A[i][j]);
}

/*
create_matrix: allocates memory for a matrix
    n: number of rows of A
    m: number of columns of A
return: matrix of size n x m
*/
double **create_matrix(int n, int m) {
    double **A = malloc(sizeof(double *) * n);
    for (int i = 0; i < m; i++)
        A[i] = malloc(sizeof(double) * m);
    return A;
}

/*
copy_matrix: creates a copy of the given matrix
    A: matrix of doubles
    n: number of rows of A
    m: number of columns of A
return: a new matrix equal to A
*/
double **copy_matrix(double **A, int n, int m) {
    double **B = create_matrix(n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            B[i][j] = A[i][j];
    return B;
}

/*
free_matrix: frees the memory allocated for a matrix
    A: matrix of doubles
    n: number of rows of A
return: void
*/
void free_matrix(double **A, int n) {
    for (int i = 0; i < n; i++)
        free(A[i]);
    free(A);
}
