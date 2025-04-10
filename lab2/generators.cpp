#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

class LinearGenerator {
    unsigned int a, c, m, seed;

public:
    LinearGenerator(unsigned int a, unsigned int c, unsigned int m, unsigned int seed = 1)
        : a(a), c(c), m(m), seed(seed) {}

    unsigned int generate_number() {
        seed = (a * seed + c) % m;
        return seed;
    }

    double generate_probability() {
        return static_cast<double>(generate_number()) / m;
    }

    vector<int> generate_numbers(int n, int custom_m = -1) {
        if (custom_m == -1) custom_m = m;
            vector<int> result;
        for (int i = 0; i < n; ++i) {
            result.push_back(static_cast<int>((custom_m * generate_probability())));
        }
        return result;
    }
};

class RegisterGenerator {
    int p, q, size, accuracy;
    unsigned long long seed;

public:
    RegisterGenerator(int p, int q, unsigned long long seed = 1ULL << 31, int accuracy = 31)
        : p(p), q(q), size(p + q), seed(seed), accuracy(accuracy) {}

    int generate_bit() {
        int p_bit = (seed >> (p - 1)) & 1;
        int q_bit = (seed >> (q - 1)) & 1;
        int bit = p_bit ^ q_bit;
        seed >>= 1;
        seed |= static_cast<unsigned long long>(bit) << size;
        return bit;
    }

    double generate_probability() {
        double result = 0.0;
        double weight = 0.5;
        for (int i = 0; i < accuracy; ++i) {
            if (generate_bit()) result += weight;
            weight /= 2;
        }
        return result;
    }

    vector<int> generate_numbers(int n, int custom_m = -1) {
        if (custom_m == -1) custom_m = 1 << accuracy;
        vector<int> result;
        for (int i = 0; i < n; ++i) {
            result.push_back(static_cast<int>(custom_m * generate_probability()));
        }
        return result;
    }
};

class NonlinearGenerator {
    unsigned int a, c, m, seed;

    static long long modInverse(long long a, long long M) {
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

public:
    NonlinearGenerator(unsigned int a, unsigned int c, unsigned int m, unsigned int seed)
        : a(a), c(c), m(m), seed(seed) {}

    unsigned int generate_number() {
        long long inv = (seed == 0) ? 0 : modInverse(seed, m);
        seed = (a * inv + c) % m;
        return seed;
    }

    double generate_probability() {
        return static_cast<double>(generate_number()) / m;
    }

    vector<int> generate_numbers(int n, int custom_m = -1) {
        if (custom_m == -1) custom_m = m;
            vector<int> result;
        for (int i = 0; i < n; ++i) {
            result.push_back(static_cast<int>(custom_m * generate_probability()));
        }
        return result;
    }
};


struct Bucket {
    int min, max, count;
    Bucket(int min, int max) : min(min), max(max), count(0) {}
};

vector<Bucket> split_into_buckets(const vector<int>& data, int bucket_count, int max_value) {
    int per_bucket = max_value / bucket_count;
    vector<Bucket> buckets;

    for (int i = 0; i < bucket_count; ++i)
        buckets.emplace_back(i * per_bucket, (i + 1) * per_bucket);

    for (int number : data) {
        int bucket_id = number / per_bucket;
        if (bucket_id >= 0 && bucket_id < bucket_count)
            buckets[bucket_id].count++;
    }
    return buckets;
}

int main() {
    unsigned int a = 67986, c = 1, m = 1 << 31;
    int p = 7, q = 3;
    unsigned int seed = 15;
    int N = 100000;
    int bucket_count = 10;

    m=10000;

    cout << "a = " << a << ", c = " << c << ", m = " << m << endl;
    cout << "p = " << p << ", q = " << q << endl;
    cout << "seed = " << seed << ", N = " << N << ", buckets = " << bucket_count << endl;

    LinearGenerator linearGen(a, c, m, seed);
    RegisterGenerator regGen(p, q, seed);
    NonlinearGenerator nonlinearGen(a, c, m, seed);

    auto linear_numbers = linearGen.generate_numbers(N, m);
    auto register_numbers = regGen.generate_numbers(N, m);

    //auto nonlinear_numbers = nonlinearGen.generate_numbers(N, m);

    long long linear_avg = 0, reg_avg = 0, nonlinear_avg = 0;
    for (int num : linear_numbers) linear_avg += num;
    for (int num : register_numbers) reg_avg += num;
    linear_avg /= N;
    reg_avg /= N;

    cout << fixed << setprecision(2);
    cout << "\nLinear average = " << linear_avg << endl;
    cout << "Register average = " << reg_avg << endl;

    auto linear_buckets = split_into_buckets(linear_numbers, bucket_count, m);
    auto reg_buckets = split_into_buckets(register_numbers, bucket_count, m);

    cout << "\nLinear buckets:" << endl;
    for (const auto& b : linear_buckets)
        cout << "[" << b.min << " - " << b.max << "] " << b.count << endl;

    cout << "\nRegister buckets:" << endl;
    for (const auto& b : reg_buckets)
        cout << "[" << b.min << " - " << b.max << "] " << b.count << endl;

    return 0;
}
