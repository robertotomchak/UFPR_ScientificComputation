#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <fenv.h>
#include <math.h>
#include <stdint.h>

#include "utils.h"

/////////////////////////////////////////////////////////////////////////////////////
//   AJUSTE DE CURVAS
/////////////////////////////////////////////////////////////////////////////////////

void montaSL(double **A, double *b, int d, long long int p, double *x, double *y) {
	double *temp = calloc(2*d+1, sizeof(double));
	double *xk = calloc(p, sizeof(double));
	temp[0] = p;
	// TO-DO: array of structs
	for (int i = 0; i < p; i++) {
		temp[1] += x[i];
		xk[i] = x[i];
		b[0] += y[i];
		b[1] += x[i] * y[i];
	}
	for (int i = 2; i <= d; i++) {
		for (int j = 0; j < p; j++) {
			xk[j] = x[j] * xk[j];
			temp[i] += xk[j];
			b[i] += y[j] * xk[j];
		}
	}
	for (int i = d+1; i <= 2*d; i++) {
		for (int j = 0; j < p; j++) {
			xk[j] = x[j] * xk[j];
			temp[i] += xk[j];
		}
	}
	// pra que acessar depois?
	for (int i = 0; i <= d; i++) {
		for (int j = 0; j <= d; j++)
			A[i][j] = temp[i+j];
	}
}

void eliminacaoGauss(double **A, double *b, int n) {
	for (int i = 0; i < n; ++i) {
		int iMax = i;
		for (int k = i+1; k < n; ++k)
			if (A[k][i] > A[iMax][i])
				iMax = k;
			if (iMax != i) {
				double *tmp, aux;
				tmp = A[i];
				A[i] = A[iMax];
				A[iMax] = tmp;

				aux = b[i];
				b[i] = b[iMax];
				b[iMax] = aux;
			}

			for (int k = i+1; k < n; ++k) {
				double m = A[k][i] / A[i][i];
				A[k][i]  = 0.0;
				for (int j = i+1; j < n; ++j)
					A[k][j] -= A[i][j]*m;
				b[k] -= b[i]*m;
			}
	}
}

void retrossubs(double **A, double *b, double *x, int n) {
	for (int i = n-1; i >= 0; --i) {
		x[i] = b[i];
		for (int j = i+1; j < n; ++j)
			x[i] -= A[i][j]*x[j];
		x[i] /= A[i][i];
	}
}

double P(double x, int N, double *alpha) {
	double Px = alpha[0];
	for (int i = 1; i <= N; ++i)
		Px += alpha[i]*pow(x,i);

	return Px;
}

int main() {
	int N, n;
	long long int K, p;

	scanf("%d %lld", &N, &K);
	p = K;   // quantidade de pontos
	n = N+1; // tamanho do SL (grau N + 1)

	double *x = (double *) calloc(p, sizeof(double));
	double *y = (double *) calloc(p, sizeof(double));

	// ler numeros
	for (long long int i = 0; i < p; ++i)
		scanf("%lf %lf", x+i, y+i);

	double **A = (double **) calloc(n, sizeof(double *));
	for (int i = 0; i < n; ++i)
		A[i] = (double *) calloc(n, sizeof(double));

	double *b = (double *) calloc(n, sizeof(double));
	double *alpha = (double *) calloc(n, sizeof(double)); // coeficientes ajuste

	// (A) Gera SL
	double tSL = timestamp();
	montaSL(A, b, N, p, x, y);
	tSL = timestamp() - tSL;

	// (B) Resolve SL
	double tEG = timestamp();
	eliminacaoGauss(A, b, n); 
	retrossubs(A, b, alpha, n); 
	tEG = timestamp() - tEG;

	// Imprime coeficientes
	for (int i = 0; i < n; ++i)
		printf("%1.15e ", alpha[i]);
	puts("");

	// Imprime resíduos
	for (long long int i = 0; i < p; ++i)
		printf("%1.15e ", fabs(y[i] - P(x[i],N,alpha)) );
	puts("");

	// Imprime os tempos
	printf("%lld %1.10e %1.10e\n", K, tSL, tEG);

	return 0;
}
