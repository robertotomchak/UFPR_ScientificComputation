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

// otimizacação simples: 3.7219999358e-03 1.5119998716e-03
// otimiação array of structs: 3.1289998442e-03 1.2749992311e-03


#define M 4  // loop unrolling

/*
TODO: algumas otimizações a se pensar:
	- como otimizar gauss?
	- stride? parece que não tem
	- tamanho das matrizes?
*/
void montaSL(double **A, double *b, long long int d, long long int p, double *xy) {
	double *temp = calloc(2*d+1, sizeof(double)); // temp[i] = soma(x[i]^i)
	double *xk = calloc(p, sizeof(double));
	temp[0] = p;
	long int i2, i3;
	for (long long int i = 0; i < p; i++) {
		// TODO: somas podem virar unrolling
		i2 = i << 1;
		i3 = i2 + 1;
		temp[1] += xy[i2];
		xk[i] = xy[i2];
		b[0] += xy[i3];
		b[1] += xy[i2] * xy[i3];
	}
	for (long long int i = 2; i <= d; i++) {
		for (long long int j = 0; j < p; j++) {
			// TODO: somas podem virar unrolling
			i2 = j << 1;
			i3 = i2 + 1;
			xk[j] = xy[i2] * xk[j];
			temp[i] += xk[j];
			b[i] += xy[i3] * xk[j];
		}
	}
	for (long long int i = d+1; i <= 2*d; i++) {
		for (long long int j = 0; j < p; j++) {
			// TODO: somas podem virar unrolling
			xk[j] = xy[j << 1] * xk[j];
			temp[i] += xk[j];
		}
	}
	// TODO: pra que acessar depois?
	for (long long int i = 0; i <= d; i++) {
		for (long long int j = 0; j <= d; j++)
			A[i][j] = temp[i+j];
	}
}

void eliminacaoGauss(double **A, double *b, int n) {
	for (long long int i = 0; i < n; ++i) {
		long long int iMax = i;
		for (long long int k = i+1; k < n; ++k)
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

			for (long long int k = i+1; k < n; ++k) {
				double m = A[k][i] / A[i][i];
				A[k][i]  = 0.0;
				// TODO: deveria dar pra fazer unrolling
				for (long long int j = i+1; j < n; ++j) 
					A[k][j] -= A[i][j]*m;
				b[k] -= b[i]*m;
			}
	}
}

void retrossubs(double **A, double *b, double *x, int n) {
	for (long long int i = n-1; i >= 0; --i) {
		x[i] = b[i];
		long long int j = i + 1;
		for (; j < n-n%M; j+=M) {
			// loop unrolling
			x[i] -= A[i][j]*x[j];
			x[i] -= A[i][j+1]*x[j+1];
			x[i] -= A[i][j+2]*x[j+2];
			x[i] -= A[i][j+3]*x[j+3];
		}
		for (; j < n; j++)
			x[i] -= A[i][j]*x[j];
			
		x[i] /= A[i][i];
	}
}

double P(double x, int N, double *alpha) {
	double Px = alpha[0];
	for (long long int i = 1; i <= N; ++i)
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
	double *xy = (double *) calloc(2*p, sizeof(double));

	// ler numeros
	for (long long int i = 0; i < p; i++) {
		scanf("%lf %lf", &x[i], &y[i]);
		xy[2*i] = x[i];
		xy[2*i+1] = y[i];
	}

	double **A = (double **) calloc(n, sizeof(double *));
	for (int i = 0; i < n; ++i)
		A[i] = (double *) calloc(n, sizeof(double));

	double *b = (double *) calloc(n, sizeof(double));
	double *alpha = (double *) calloc(n, sizeof(double)); // coeficientes ajuste

	// (A) Gera SL
	double tSL = timestamp();
	montaSL(A, b, N, p, xy);
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
