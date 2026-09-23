import math


def is_valid_square_factor(x2: int, p: int) -> bool:
    """Verifies whether an integer 'p' meets the conditions set in the article:
    1. p is a perfect square (p = k^2 for some integer k).
    2. x^2 > p (to guarantee positive legs and hypotenuse).
    3. Parity: If x^2 is even, p must be even. If x^2 is odd, p must be odd.
    """
    if p >= x2 or p <= 0:
        return False

    # Check strict parity matching between x^2 and p
    if (x2 % 2) != (p % 2):
        return False

    # Check if p is a perfect square
    sqrt_p = math.isqrt(p)
    if sqrt_p * sqrt_p != p:
        return False

    return True


def calculate_pythagorean_step(x: int, p: int) -> tuple[bool, int, int]:
    """Given an initial leg 'x' and a square factor 'p', calculates:
      Y = (x^2 - p) / (2 * sqrt(p))
      Z = (x^2 + p) / (2 * sqrt(p))
    Returns (True, Y, Z) if successful, or (False, 0, 0) if factor 'p' is invalid.
    """
    x2 = x * x

    if not is_valid_square_factor(x2, p):
        return False, 0, 0

    sqrt_p = math.isqrt(p)

    y = (x2 - p) // (2 * sqrt_p)
    z = (x2 + p) // (2 * sqrt_p)

    return True, y, z


def generate_pythagorean_quadruple(index: int, x1_in: int) -> None:
    """Generates a Pythagorean quadruple (x1, x2, x3, z) by inductively applying
    the square factor formulation in two steps:
      Step 1: x1 -> (x1, Y1, Z1)  such that x1^2 + Y1^2 = Z1^2
      Step 2: Assign x2 = Y1, and use Z1 as the base for the next step:
              Z1 -> (Z1, Y2, Z2)  such that Z1^2 + Y2^2 = Z2^2
      Substituting Z1^2 yields: x1^2 + Y1^2 + Y2^2 = Z2^2
    """
    x1 = x1_in
    x1_sq = x1 * x1

    # Find the first valid square factor p1 for x1^2
    p1 = -1
    for p in range(1, x1_sq):
        if is_valid_square_factor(x1_sq, p):
            p1 = p
            break  # Select the first valid square factor found

    if p1 == -1:
        print(f"Quadruple {index}: No valid square factor found for x1 = {x1} (x1 must be > 2).")
        return

    success, x2, z1 = calculate_pythagorean_step(x1, p1)

    # Inductive step: the hypotenuse z1 becomes the base leg for the next step
    z1_sq = z1 * z1
    p2 = -1
    for p in range(1, z1_sq):
        if is_valid_square_factor(z1_sq, p):
            p2 = p
            break

    success, x3, z2 = calculate_pythagorean_step(z1, p2)

    # Output results and perform algebraic verification of the decomposition
    sum_of_squares = (x1 * x1) + (x2 * x2) + (x3 * x3)
    z_squared = z2 * z2

    print(f"--- Pythagorean Quadruple #{index} ---")
    print(f"  Step 1 (x1 = {x1}, p1 = {p1}): {x1}^2 + {x2}^2 = {z1}^2")
    print(f"  Step 2 (x_inductive = {z1}, p2 = {p2}): {z1}^2 + {x3}^2 = {z2}^2")
    print(f"  Final result (x1, x2, x3, z): ({x1}, {x2}, {x3}, {z2})")
    print(f"  Verification: {x1}^2 + {x2}^2 + {x3}^2 = {x1 * x1} + {x2 * x2} + {x3 * x3} = {sum_of_squares}")
    print(f"                z^2 = {z2}^2 = {z_squared}  [{'CORRECT' if sum_of_squares == z_squared else 'INCORRECT'}]\n")


def main() -> None:
    print("===============================================================")
    print("  Pythagorean Quadruple Generator (Inductive Method ESE-IPN)")
    print("===============================================================\n")

    try:
        n_quadruples = int(input("Enter the number of Pythagorean quadruples to calculate: "))
        if n_quadruples <= 0:
            print("Invalid input. Please enter a positive integer.")
            return
    except ValueError:
        print("Invalid input. Please enter a positive integer.")
        return

    print(f"\nGenerating {n_quadruples} Pythagorean quadruples...\n")

    # Start calculations from x1 = 3, skipping x = 1 and x = 2 per article restrictions
    current_x = 3
    for i in range(1, n_quadruples + 1):
        generate_pythagorean_quadruple(i, current_x)
        current_x += 1


if __name__ == "__main__":
    main()
