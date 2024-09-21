#include <stdio.h>
#include <math.h>
#include <float.h>
#include <fenv.h>

double dabs (double x) {
    return x > 0? x: -x;
}

double calculate_pi (double error, unsigned int *n_iterations, double *abs_rel_error) {
    double term_old, term_new, ans_old, ans_new;
    unsigned int k;

    k = 0;

    term_new = 1;
    ans_new = term_new;
    do {
        term_old = term_new;
        ans_old = ans_new;
        term_new = (term_old * k + term_old) / (2 * k + 3);
        k++;
        ans_new += term_new;
    } while (dabs(ans_new - ans_old) > error);

    *n_iterations = k;
    *abs_rel_error = dabs(ans_new - ans_old);
    return 2 * ans_new;
}

unsigned long int hex_value (double x) {
   return *(unsigned long int *) &x;
} 

unsigned long int ulp (double x, double y) {
    unsigned int a, b;
    if (x > y) {
        a = *(unsigned int *) &x;
        b = *(unsigned int *) &y;
    }
    else {
        b = *(unsigned int *) &x;
        a = *(unsigned int *) &y;
    }
    return a - b;
}

int main () {
    double tol, pi_down, pi_up, abs_rel_error, abs_true_error;
    unsigned int n_iterations;
    scanf("%lf", &tol);

    fesetround(FE_DOWNWARD);
    pi_down = calculate_pi(tol, &n_iterations, &abs_rel_error);
    abs_true_error = dabs(pi_down - M_PI);
    printf("%d\n", n_iterations);
    printf("%.15e %lx\n", abs_rel_error, hex_value(abs_rel_error));
    printf("%.15e %lx\n", abs_true_error, hex_value(abs_true_error));
    printf("%.15e %lx\n", pi_down, hex_value(pi_down));

    fesetround(FE_UPWARD);
    pi_up = calculate_pi(tol, &n_iterations, &abs_rel_error);
    printf("%.15e %lx\n", pi_up, hex_value(pi_up));
    printf("%ld\n", ulp(pi_down, pi_up));


    return 0;
}


