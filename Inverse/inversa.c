/*
    main
*/

#include "utils.h"
#include "array.h"
#include "lu_decomposition.h"

#include <fenv.h>

int main () {
    fesetround(FE_DOWNWARD);
    int n;
    scanf("%d", &n);
    double **A = create_matrix(n, n);
    read_matrix(A, n, n);
    rtime_t time;
    double **A_inv = inverse_matrix(A, n, &time);
    printf("%d\n", n);
    print_matrix(A_inv, n, n);
    double l2_norm = l2_residual(A, A_inv, n);
    printf("%.15e\n", l2_norm);
    printf("%.8e\n", time);
    return 0;
}
