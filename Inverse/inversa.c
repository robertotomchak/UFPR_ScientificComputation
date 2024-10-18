/*
	Name: Roberto Sprengel Minozzo Tomchak
	GRR: 20232369
*/

/*
    main
*/

#include "utils.h"
#include "array.h"
#include "lu_decomposition.h"

#include <fenv.h>
#include <likwid.h>

int main () {
    fesetround(FE_DOWNWARD);
	LIKWID_MARKER_INIT;

    int n;
    scanf("%d", &n);
    double **A = create_matrix(n, n);
    read_matrix(A, n, n);

    rtime_t time;
	LIKWID_MARKER_START("inversa");
    double **A_inv = inverse_matrix(A, n, &time);
	LIKWID_MARKER_STOP("inversa");
    printf("%d\n", n);
    print_matrix(A_inv, n, n);
    double l2_norm = l2_residual(A, A_inv, n);
    printf("%.15e\n", l2_norm);
    printf("%.8e\n", time);

    free_matrix(A, n);
    free_matrix(A_inv, n);
	LIKWID_MARKER_CLOSE;
    return 0;
}
