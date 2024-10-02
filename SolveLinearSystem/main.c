#include <stdio.h>
#include <stdlib.h>
#include <likwid.h>
#include "utils.h"

#define MAX 100

double dabs(double x) {
	return x > 0? x : -x;
}

unsigned int findMax(double **A, unsigned int i, unsigned int n) {
	unsigned int res = i;
	for (unsigned int j = i+1; j < n; j++)
		if (A[j][i] > A[res][i])
			res = j;
	return res;
}

void swapLine(double **A, double *b, unsigned int i, unsigned int j) {
	// swap A
	double *pj = A[j];
	A[j] = A[i];
	A[j] = pj;

	// swap b
	double temp = b[j];
	b[j] = b[i];
	b[i] = temp;
}

int gaussElimination (double **A, double *b, unsigned int n, double *ans) {
	for (unsigned int i = 0; i < n; i++) {
		unsigned int iPivot = findMax(A, i, n);
		if (i != iPivot)
			swapLine(A, b, i, iPivot);
		for (unsigned int k = i + 1; k < n; k++) {
			double m = A[k][i] / A[i][i];
			A[k][i] = 0.0;
			for (unsigned int j = i + 1; j < n; j++)
				A[k][j] -= A[i][j] * m;
			b[k] -= b[i] * m;
		}
	}

	for (int i = n - 1; i >= 0; i--) {
		ans[i] = b[i];
		for (unsigned int j = i + 1; j < n; j++)
			ans[i] -= A[i][j] * ans[j];
		ans[i] /= A[i][i];
	}
	return 1;
}

double norm(double *ans_old, double *ans_new, unsigned int n) {
	double res = dabs(ans_old[0] - ans_new[0]);
	for (unsigned int i = 1; i < n; i++) {
		double temp = dabs(ans_old[i] - ans_new[i]);
		if (temp > res) res = temp;
	}
	return res;
}

unsigned int gaussSeidel(double **A, double *b, unsigned int n, double *ans, unsigned int max_iterations, double error) {
	unsigned int iterations = 0;
	// initialize with zeros
	double *ans_old = malloc(n * sizeof(double));
	for (unsigned int i = 0; i < n; i++)
		ans[i] = 0;

	do {
		for (unsigned int i = 0; i < n; i++)
			ans_old[i] = ans[i];
		for (unsigned int i = 0; i < n; i++) {
			ans[i] = b[i];
			for (unsigned int j = 0; j < n; j++) {
				if (j < i)
					ans[i] -= A[i][j] * ans[j];
				else if (j > i)
					ans[i] -= A[i][j] * ans_old[j];
			}
			ans[i] /= A[i][i];
		}
		iterations += 1;
	} while (iterations < max_iterations && norm(ans_old, ans, n) > error);

	return iterations;
}
	

int main () {
	LIKWID_MARKER_INIT;
	unsigned int n;
	scanf("%d", &n);

	double **A = malloc(n * sizeof(double *));
	double *b = malloc(n * sizeof(double));
	double *x = malloc(n * sizeof(double));

	for (unsigned int i = 0; i < n; i++) {
		A[i] = malloc(n * sizeof(double));
		for (unsigned int j = 0; j < n; j++)
			scanf("%lf", &A[i][j]);
		scanf("%lf", &b[i]);
	}

	double start, end;

	LIKWID_MARKER_START("EG");
	start = timestamp();
	gaussElimination(A, b, n, x);
	end = timestamp();
	LIKWID_MARKER_STOP("EG");
	for (unsigned int i = 0; i < n; i++)
		printf("%lf ", x[i]);
	printf("\n");
	printf("time: %lf\n", end-start);

	start = timestamp();
	gaussSeidel(A, b, n, x, 50, 1e-04);
	end = timestamp();
	for (unsigned int i = 0; i < n; i++)
		printf("%lf ", x[i]);
	printf("\n");
	printf("time: %lf\n", end-start);
	
	LIKWID_MARKER_CLOSE;
	return 0;
}
