#include <stdio.h>
#include <math.h>
#include <float.h>
#include <fenv.h>

double dabs (double x) {
    return x > 0? x: -x;
}

/*
 * calculates pi, based on given error
 * args:
 *  error: stopping condition, absolute differente between iterations;
 *  n_iterations: number of iterations (pass by reference);
 *  abs_aprox_error: absolute error between last two iterations (pass by reference)
 *  count_flops: number of flops done by the algorithm (pass by reference)
 * return: pi approximation
 *
 * obs: see README for details on calculations
 */
double calculate_pi (double error, unsigned int *n_iterations, double *abs_aprox_error, unsigned int *count_flops) {
    double term_old, term_new, ans_old, ans_new, numerator, denominator;
    unsigned int k;

    k = 0;
    *count_flops = 0;

    term_new = 1;
    ans_new = term_new;
    numerator = 1;
    denominator = 3;
    do {
        term_old = term_new;
        ans_old = ans_new;

        term_new = numerator / denominator * term_old;
        numerator += 1;
        denominator += 2;
        ans_new += term_new;
        *count_flops += 5;  // 1 div, 1 mul, 3 add
        k++;
    } while (dabs(ans_new - ans_old) > error);

    *n_iterations = k;
    *abs_aprox_error = dabs(ans_new - ans_old);
    // one more FLOP because of 2 * ans_new
    *count_flops += 1;
    return 2 * ans_new;
}

// returns the binary representation of the given double
unsigned long int hex_value (double x) {
   return *(unsigned long int *) &x;
} 

// calculates the ULP between given doubles
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
    return a - b - 1;
}

int main () {
    double tol, pi_down, pi_up, abs_aprox_error, abs_true_error;
    unsigned int n_iterations, count_flops;
    scanf("%lf", &tol);

    if (tol <= 0) {
        fprintf(stderr, "ERROR: tolerance must be positive\n");
        return 1;
    }

    fesetround(FE_DOWNWARD);
    pi_down = calculate_pi(tol, &n_iterations, &abs_aprox_error, &count_flops);
    abs_true_error = dabs(pi_down - M_PI);
    printf("%d\n", n_iterations);
    printf("%.15e %lX\n", abs_aprox_error, hex_value(abs_aprox_error));
    printf("%.15e %lX\n", abs_true_error, hex_value(abs_true_error));
    printf("%.15e %lX\n", pi_down, hex_value(pi_down));

    fesetround(FE_UPWARD);
    pi_up = calculate_pi(tol, &n_iterations, &abs_aprox_error, &count_flops);
    printf("%.15e %lX\n", pi_up, hex_value(pi_up));
    printf("%ld\n", ulp(pi_down, pi_up));
    printf("%d\n", count_flops);

    return 0;
}

