/*
	Name: Roberto Sprengel Minozzo Tomchak
	GRR: 20232369
*/

/*
    Calculates inverse of a matrix using LU decomposition
    Also defines useful metrics
*/

#include "lu_decomposition.h"

/*
dabs: calculates the absolute value of a double
	x: number
return: abs(x)
*/
double dabs(double x) {
	return x>0? x: -x;
}

/*
max_in_column: finds the maximum value (in abs) in given column
	A: matrix (must be nxn)
	n: size of A
	i: index of column
return: position (line) of the maximum value in the column
*/
int max_in_column(double **A, int n, int i) {
    int pos = i;
    for (int j = i + 1; j < n; j++)
        if (dabs(A[j][i]) > dabs(A[pos][i]))
            pos = j;
    return pos;
}

/*
swap_lines: swaps two lines of given matrix
	A: matrix
	i: first line
	j: second line
*/
void swap_lines(double **A, int i, int j) {
    double *temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}


/*
create_lu: creates a LU matrix such that A = LU
    A: matrix
    n: size of A
return: LU
obs: helpful function for inverse_matrix
*/
double **create_lu(double **A, int n, int *column_pos) {
    double **LU = copy_matrix(A, n, n);

    // gauss elimination
    for (int i = 0; i < n; i++) {
        int pos = max_in_column(LU, n, i);
		int temp = column_pos[i];
        column_pos[i] = column_pos[pos];
		column_pos[pos] = temp;
        swap_lines(LU, i, pos);
        for (int j = i+1; j < n; j++) {
            double m = LU[j][i] / LU[i][i];
            LU[j][i] = m;
            for (int k = i + 1; k < n; k++)
                LU[j][k] -= LU[i][k] * m;
        }
    }

    return LU;
}

/*
retrosub_L: makes the retrosubstitution of L (L*y = b)
    LU: matrix A = LU
    y: array that stores the answer of retrosub_L
    i: position of b that contains a 1
    n: size of LU
return: void
*/
void retrosub_L(double **LU, double *y, int i, int n) {
    for (int j = 0; j < n; j++) {
        y[j] = (j == i);
        for (int k = 0; k < j; k++)
            y[j] -= LU[j][k] * y[k];
    }
}

/*
retrosub_U: makes the retrosubstitution of U (U*x = y)
    LU: matrix A = LU
    y: array such that U*x = y
    A_inv: matrix that will store the value of x
    i: column of A_inv such that A_inv[*][i] will receive x
    n: size of LU
return: void
*/
void retrosub_U(double **LU, double *y, double **A_inv, int i, int n) {
    for (int j = n - 1; j >= 0; j--) {
        A_inv[j][i] = y[j];
        for (int k = n - 1; k > j; k--)
            A_inv[j][i] -= LU[j][k] * A_inv[k][i];
        A_inv[j][i] /= LU[j][j];
    }
}

/*
inverse_matrix: calculates the inverse of A, using LU decomposition
    A: matrix (must be n x n)
    n: size of A
    time: total time of the algorithm (pass by reference)
return: the inverse of A
*/
double **inverse_matrix(double **A, int n, rtime_t *time) {
    rtime_t start = timestamp();
    // gauss elimination step
    int *column_pos = malloc(sizeof(double) * n);
	for (int i = 0; i < n; i++)
		column_pos[i] = i;
    double **LU = create_lu(A, n, column_pos);
    double **A_inv = create_matrix(n, n);

    // alternate between L*y = b and U*x = y
    double *y = malloc(sizeof(double) * n);
    for (int i = 0; i < n; i++) {
        retrosub_L(LU, y, i, n);
        retrosub_U(LU, y, A_inv, column_pos[i], n);
    }
    rtime_t end = timestamp();
    *time = end - start;
    free(y);
	free(column_pos);
    free_matrix(LU, n);
    return A_inv;
}

/*
l2_residual: calculates the l2 norm of the residual of A * A_inv - I
    A: matrix
    A_inv: inverse of A
    n: size of both A and A_inv
return: the l2 norm of the residual of A * A_inv - I
*/
double l2_residual(double **A, double **A_inv, int n) {
    double l2_avg = 0.0;
    // loop through columns
    for (int i = 0; i < n; i++) {
        double l2_norm = 0.0;  // norm of the i-th column
        // j = j-th line of A
        for (int j = 0; j < n; j++) {
            double temp = 0.0;
            // multiple A[j][*] with A_inv[*][i]
            for (int k = 0; k < n; k++) {
                temp += A[j][k] * A_inv[k][i];
            }
            double residual = temp - (j == i);  // (A * A_inv)[j][i] - I[j][i]
            l2_norm += (residual * residual);
        }
        l2_avg += sqrt(l2_norm);
    }
    return l2_avg / n;
}
