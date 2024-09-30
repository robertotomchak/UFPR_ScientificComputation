#include <stdio.h>
#include <stdlib.h>
#include "likwid.h"
//#include "utils.h"

#define MAX 100

int gaussElimination (double A[][MAX], double *b, unsigned int n, double *ans) {
	for (unsigned int i = 0; i < n; i++) {
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

int main () {
	LIKWID_MARKER_INIT;
	unsigned int n;
	scanf("%d", &n);

	double A[MAX][MAX];
	double b[MAX];
	double x[MAX];

	for (unsigned int i = 0; i < n; i++) {
		for (unsigned int j = 0; j < n; j++)
			scanf("%lf", &A[i][j]);
		scanf("%lf", &b[i]);
	}

	double start, end;

	LIKWID_MARKER_START("EG");
	//start = timestamp();
	gaussElimination(A, b, n, x);
	//end = timestamp();
	LIKWID_MARKER_STOP("EG");
	for (unsigned int i = 0; i < n; i++)
		printf("%lf ", x[i]);
	printf("\n");
	//printf("time: %lf\n", end-start);
	
	LIKWID_MARKER_CLOSE;
	return 0;
}
