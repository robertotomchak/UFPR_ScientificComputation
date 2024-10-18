/*
	Name: Roberto Sprengel Minozzo Tomchak
	GRR: 20232369
*/

/*
    Calculates inverse of a matrix using LU decomposition
    Also defines useful metrics
*/

#ifndef LU_DECOMPOSITION_H
#define LU_DECOMPOSITION_H

#include <stdlib.h>
#include <math.h>
#include "array.h"
#include "utils.h"

/*
inverse_matrix: calculates the inverse of A, using LU decomposition
    A: matrix (must be n x n)
    n: size of A
    time: total time of the algorithm (pass by reference)
return: the inverse of A
*/
double **inverse_matrix(double **A, int n, rtime_t *time);

/*
l2_residual: calculates the l2 norm of the residual of A * A_inv - I
    A: matrix
    A_inv: inverse of A
    n: size of both A and A_inv
return: the l2 norm of the residual of A * A_inv - I
*/
double l2_residual(double **A, double **A_inv, int n);

#endif
