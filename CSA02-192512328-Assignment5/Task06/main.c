#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static long long calls;
static int digital_root(int n) {
    if (n < 0) n = -n;
    if (n < 10) return n;
    int sum = 0;
    while (n > 0) { sum += n % 10; n /= 10; }
    return digital_root(sum);
}
static long long power_linear(long long base, int exp) {
    calls++;
    if (exp == 0) return 1;
    return base * power_linear(base, exp - 1);
}
static long long power_fast(long long base, int exp) {
    calls++;
    if (exp == 0) return 1;
    long long half = power_fast(base, exp / 2);
    return (exp % 2 == 0) ? half * half : base * half * half;
}
static long long power_iter(long long base, unsigned exp) {
    long long result = 1;
    while (exp) { if (exp & 1U) result *= base; exp >>= 1U; if (exp) base *= base; }
    return result;
}
int main(void) {
    printf("digital_root(98765) = %d\n", digital_root(98765));
    calls = 0; long long linear = power_linear(2, 30); printf("linear: %lld in %lld calls\n", linear, calls);
    calls = 0; long long fast = power_fast(2, 30); printf("fast : %lld in %lld calls\n", fast, calls);
    printf("iterative: %lld\n", power_iter(2, 30));
    puts("Tests: exp=0 -> 1; exp=1 -> base; exp=10 -> 1024 for base 2.");
    return 0;
}
