#include <stdio.h>

int factorial_up(int n, int current, int result) {
    if (current > n)
        return result;
    return factorial_up(n, current + 1, result * current);
}

int main() {
    int n = 5;
    printf("Factorial of %d: %d\n", n, factorial_up(n, 1, 1));
    return 0;
}
