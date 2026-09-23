#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * Function: is_valid_square_factor
 * --------------------------------
 * Verifies whether an integer 'p' meets the conditions set in the article:
 * 1. p is a perfect square (p = k^2 for some integer k).
 * 2. x^2 > p (to guarantee positive legs and hypotenuse).
 * 3. Parity: If x^2 is even, p must be even. If x^2 is odd, p must be odd.
 */
int is_valid_square_factor(long long x2, long long p) {
    if (p >= x2 || p <= 0) {
        return 0;
    }

    // Check strict parity matching between x^2 and p
    if ((x2 % 2) != (p % 2)) {
        return 0;
    }

    // Check if p is a perfect square
    long long sqrt_p = (long long)llround(sqrt((double)p));
    if (sqrt_p * sqrt_p != p) {
        return 0;
    }

    return 1;
}

/*
 * Function: calculate_pythagorean_step
 * ------------------------------------
 * Given an initial leg 'x' and a square factor 'p', calculates:
 *   Y = (x^2 - p) / (2 * sqrt(p))
 *   Z = (x^2 + p) / (2 * sqrt(p))
 * Returns 1 if successful, or 0 if factor 'p' is invalid.
 */
int calculate_pythagorean_step(long long x, long long p, long long *Y, long long *Z) {
    long long x2 = x * x;

    if (!is_valid_square_factor(x2, p)) {
        return 0;
    }

    long long sqrt_p = (long long)llround(sqrt((double)p));

    *Y = (x2 - p) / (2 * sqrt_p);
    *Z = (x2 + p) / (2 * sqrt_p);

    return 1;
}

/*
 * Function: generate_pythagorean_quadruple
 * ----------------------------------------
 * Generates a Pythagorean quadruple (x1, x2, x3, z) by inductively applying
 * the square factor formulation in two steps:
 *   Step 1: x1 -> (x1, Y1, Z1)  such that x1^2 + Y1^2 = Z1^2
 *   Step 2: Assign x2 = Y1, and use Z1 as the base for the next step:
 *           Z1 -> (Z1, Y2, Z2)  such that Z1^2 + Y2^2 = Z2^2
 *   Substituting Z1^2 yields: x1^2 + Y1^2 + Y2^2 = Z2^2
 */
void generate_pythagorean_quadruple(int index, long long x1_in) {
    long long x1 = x1_in;
    long long x1_sq = x1 * x1;

    // Find the first valid square factor p1 for x1^2
    long long p1 = -1;
    for (long long p = 1; p < x1_sq; p++) {
        if (is_valid_square_factor(x1_sq, p)) {
            p1 = p;
            break; // Select the first valid square factor found
        }
    }

    if (p1 == -1) {
        printf("Quadruple %d: No valid square factor found for x1 = %lld (x1 must be > 2).\n", index, x1);
        return;
    }

    long long x2, z1;
    calculate_pythagorean_step(x1, p1, &x2, &z1);

    // Inductive step: the hypotenuse z1 becomes the base leg for the next step
    long long z1_sq = z1 * z1;
    long long p2 = -1;
    for (long long p = 1; p < z1_sq; p++) {
        if (is_valid_square_factor(z1_sq, p)) {
            p2 = p;
            break;
        }
    }

    long long x3, z2;
    calculate_pythagorean_step(z1, p2, &x3, &z2);

    // Output results and perform algebraic verification of the decomposition
    long long sum_of_squares = (x1 * x1) + (x2 * x2) + (x3 * x3);
    long long z_squared = z2 * z2;

    printf("--- Pythagorean Quadruple #%d ---\n", index);
    printf("  Step 1 (x1 = %lld, p1 = %lld): %lld^2 + %lld^2 = %lld^2\n", x1, p1, x1, x2, z1);
    printf("  Step 2 (x_inductive = %lld, p2 = %lld): %lld^2 + %lld^2 = %lld^2\n", z1, p2, z1, x3, z2);
    printf("  Final result (x1, x2, x3, z): (%lld, %lld, %lld, %lld)\n", x1, x2, x3, z2);
    printf("  Verification: %lld^2 + %lld^2 + %lld^2 = %lld + %lld + %lld = %lld\n", 
           x1, x2, x3, x1 * x1, x2 * x2, x3 * x3, sum_of_squares);
    printf("                z^2 = %lld^2 = %lld  [%s]\n\n", 
           z2, z_squared, (sum_of_squares == z_squared) ? "CORRECT" : "INCORRECT");
}

int main(void) {
    int n_quadruples;

    printf("===============================================================\n");
    printf("  Pythagorean Quadruple Generator (Inductive Method ESE-IPN)\n");
    printf("===============================================================\n\n");

    printf("Enter the number of Pythagorean quadruples to calculate: ");
    if (scanf("%d", &n_quadruples) != 1 || n_quadruples <= 0) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    printf("\nGenerating %d Pythagorean quadruples...\n\n", n_quadruples);

    // Start calculations from x1 = 3, skipping x = 1 and x = 2 per article restrictions
    long long current_x = 3;
    for (int i = 1; i <= n_quadruples; i++) {
        generate_pythagorean_quadruple(i, current_x);
        current_x++;
    }

    return 0;
}
