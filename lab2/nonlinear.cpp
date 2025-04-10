#include <iostream>

using namespace std;
#define RANGE 10000 
#define BUCKET_NUM 10
#define A_LCG = 1664525
#define C_LCG = 1013904223
#define M_LCG 4294967296

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

void bucketSortAndPrint(long long* data, int size, int maxValue, const string& label) {
    int counts[BUCKET_NUM] = {0};
    int bucketSize = maxValue / BUCKET_NUM;

    for (int i = 0; i < size; ++i) {
        int bucket = data[i] / bucketSize;
        if (bucket >= BUCKET_NUM) bucket = BUCKET_NUM - 1;
        counts[bucket]++;
    }

    cout << "Rozkład (" << label << "):\n";
    for (int i = 0; i < BUCKET_NUM; ++i) {
        int low = i * bucketSize;
        int high = (i + 1) * bucketSize - 1;
        cout << "Bucket " << i + 1 << " [" << low << " - " << high << "]: " << counts[i] << " wartości\n";
    }
    cout << endl;
}

unsigned int LCG(long long a, long long c, long long m, long long& seed) {
    seed = (a * seed + c) % m;
    return seed;
}

int main() {
    // Parametry
    long long a = 17;
    long long c = 23;
    long long b = 19;
    long long M = 2147483647; // 2^31 - 1, liczba pierwsza
    long long n0 = 5;
    long long seed=12345;

    const int range=100;
    // Test generatora (2.8)
    long long x = 12345; // seed
    cout << "Generator (2.8):" << endl;
    for (int i = 0; i < 1000; ++i) {
        x = nonlinear_gen_2_8(a, c, M, x);
        x=x%1000;
        
    }

    
    cout << endl << endl;
    int count_bucket[BUCKET_NUM]={0};
    // Test generatora (2.9)
    long long xi;
    cout << "Generator (2.9):" << endl;
    for (int i = 0; i < 1000; ++i) {
        //long long xi = nonlinear_gen_2_9(a, b, n0, M, i);
        //xi=xi%1000;
        xi=LCG(a, c, M, seed);
        for (int j = 0; j < BUCKET_NUM; ++j) {
            if(xi>(M_LCG/BUCKET_NUM)*j && xi<=((M_LCG/BUCKET_NUM)*(j+1)))
                count_bucket[j]++;
        }
    }
    
    cout << "Rozklad  2.9 \n";
    for (int i = 0; i < BUCKET_NUM; ++i) {
        printf("bucket %d - %d\n",i,count_bucket[i]);
    }
    cout << endl;
    cout << endl;

    return 0;
}
