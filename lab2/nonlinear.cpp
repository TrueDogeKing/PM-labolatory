#include <iostream>

using namespace std;

// Oblicza modularną odwrotność a mod M (a^(-1) mod M)
long long modInverse(long long a, long long M) {
    long long m0 = M, t, q;
    long long x0 = 0, x1 = 1;

    if (M == 1) return 0;

    while (a > 1) {
        q = a / M;
        t = M;

        M = a % M;
        a = t;
        t = x0;

        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}

// Generator (2.8)
long long nonlinear_gen_2_8(long long a, long long c, long long M, long long prev) {
    long long inv = (prev == 0) ? 0 : modInverse(prev, M);
    return (a * inv + c) % M;
}

// Generator (2.9) - równoległy
long long nonlinear_gen_2_9(long long a, long long b, long long n0, long long M, long long n) {
    long long val = a * (n + n0) + b;
    return modInverse(val, M);
}

int main() {
    // Parametry
    long long a = 17;
    long long c = 23;
    long long b = 19;
    long long M = 2147483647; // 2^31 - 1, liczba pierwsza
    long long n0 = 5;

    // Test generatora (2.8)
    long long x = 12345; // seed
    cout << "Generator (2.8):" << endl;
    for (int i = 0; i < 10; ++i) {
        x = nonlinear_gen_2_8(a, c, M, x);
        cout << x << " ";
    }
    cout << endl << endl;

    // Test generatora (2.9)
    cout << "Generator (2.9):" << endl;
    for (int i = 0; i < 10; ++i) {
        long long xi = nonlinear_gen_2_9(a, b, n0, M, i);
        cout << xi << " ";
    }
    cout << endl;

    return 0;
}
