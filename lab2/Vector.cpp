#include <iostream>
#include <vector>

using namespace std;

class VectorLCG {
private:
    vector<vector<long long>> A; // Macierz współczynników A
    vector<long long> X;         // Wektor stanu Xn
    long long M;                 // Modulo

public:
    VectorLCG(const vector<vector<long long>>& A_, const vector<long long>& X0, long long M_)
        : A(A_), X(X0), M(M_) {}

    vector<long long> next() {
        vector<long long> Xnext(X.size(), 0);
        for (size_t i = 0; i < A.size(); ++i) {
            for (size_t j = 0; j < A[i].size(); ++j) {
                Xnext[i] = (Xnext[i] + A[i][j] * X[j]) % M;
            }
        }
        X = Xnext;
        return X;
    }

    void print_state() {
        for (auto val : X)
            cout << val << " ";
        cout << endl;
    }
};

int main() {
    // Przykład z wektorem 3-elementowym
    vector<vector<long long>> A = {
        {69069,     0,        0},
        {397204094, 742938285, 0},
        {0,         1099087573, 68909602460261}
    };

    vector<long long> X0 = {1, 2, 3}; // Wektor początkowy
    long long M = (1LL << 31) - 1;    // Przykład: 2^31 - 1 (liczba pierwsza)

    VectorLCG generator(A, X0, M);

    // Generujemy 5 wektorów
    for (int i = 0; i < 5; ++i) {
        generator.next();
        generator.print_state();
    }

    return 0;
}
