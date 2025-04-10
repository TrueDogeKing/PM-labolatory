#include <iostream>
#include <vector>
#include <bitset>
#include <cmath>

using namespace std;

class LFSR {
private:
    vector<bool> state; // rejestr bitów
    int p, q;           // pozycje XOR
    int index;          // aktualna pozycja
public:
    LFSR(int p_, int q_, const vector<bool>& seed)
        : p(p_), q(q_), state(seed), index(seed.size()) {}

    // Wygeneruj kolejny bit
    bool next_bit() {
        bool new_bit = state[state.size() - p] ^ state[state.size() - q];
        state.push_back(new_bit);
        return new_bit;
    }

    // Wygeneruj liczbę w [0, 1) na podstawie L bitów
    double next_uniform(int L = 32) {
        double U = 0.0;
        for (int i = 1; i <= L; ++i) {
            bool bit = next_bit();
            U += bit * pow(2, -i);
        }
        return U;
    }

    void print_state(int n = 32) {
        for (int i = state.size() - n; i < state.size(); ++i) {
            cout << state[i];
        }
        cout << endl;
    }
};

int main() {
    // Przykład: p=10, q=3, ziarno (seed) 1 0 1 1 1 0 0 1 0 1
    int p = 10, q = 3;
    vector<bool> seed = {1,0,1,1,1,0,0,1,0,1}; // k = p

    LFSR generator(p, q, seed);

    // Generuj i wypisz 5 liczb w [0, 1)
    for (int i = 0; i < 5; ++i) {
        double u = generator.next_uniform();
        cout << "U[" << i << "] = " << u << endl;
    }

    return 0;
}
