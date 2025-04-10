#include <iostream>

class LCG {
private:
    long long a;    // współczynnik mnożący
    long long c;    // wyraz wolny (dodawany)
    long long M;    // moduł
    long long seed; // wartość początkowa

public:
    LCG(long long a_, long long c_, long long M_, long long seed_)
        : a(a_), c(c_), M(M_), seed(seed_) {}

    long long next() {
        seed = (a * seed + c) % M;
        return seed;
    }
};

int main() {
    // Przykładowe parametry (zwykle dobierane ostrożnie!)
    long long a = 1664525;
    long long c = 1013904223;
    long long M = 1LL << 32; // 2^32
    long long seed = 12345;  // wartość początkowa

    LCG generator(a, c, M, seed);

    // Wygeneruj 10 liczb pseudolosowych
    for (int i = 0; i < 10; ++i) {
        std::cout << generator.next() << std::endl;
    }

    return 0;
}
