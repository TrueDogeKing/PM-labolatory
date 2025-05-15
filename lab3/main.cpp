#include <iostream>
#include <random>
#include <vector>
#include <tuple>

using namespace std;
int counter = 0;

double quantileA(double y)
{
    return 100 * y + 50;
}

double quantileB(double y)
{
    if (y <= 0.4) {
        return 1;
    }
    if (y <= 0.5) {
        return 2;
    }
    if (y <= 0.8) {
        return 3;
    }
    return 4;
}

bool exercie3(double u1,double u2) {
    //    h=1/50
    //    a=1*1/50
    // f(x)=1/5000x-1/100

    //printf("u2:%lf and f(u1)=%lf\n", u2, ((1.0 / 5000.0) * u1 -( 1.0 / 100.0)));


    if (u2 < 1 / 5000.0 * u1 - 1 / 100.0) {
        return true;
    }
    else {
        counter++;
        return false;
    }



}

int main()
{
    random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_real_distribution<double> dist(0, 1);
    double fmax = 1 / 50.0;
    double epsilon = fmax/100.0;

    const int N = 100000;

    vector<double> numbersA;
    vector<int> numbersB;

    for (int i = 0; i < N; i++) {
        numbersB.push_back(quantileB(dist(generator)));
    }
    bool running = true;
    for (int i = 0; i < N; i++) {
        running = true;
        //printf("iteration n:%d",N);
        while (running) {
            double u1 = quantileA(dist(generator));
            double u2 = (dist(generator));
            u2 *= (fmax+epsilon);
            //printf("u1:%lf, u2:%lf\n",u1,u2);
            if (exercie3(u1, u2)) {
                numbersA.push_back(u1);
                running=false;
            }
        }

    }

    vector<tuple<double, double, int>> distributionA;
    vector<int> distributionB(4, 0);

    for (int i = 0; i < 10; i++) {
        distributionA.push_back(make_tuple(50 + 10 * i, 50 + 10 * (i + 1), 0));
    }

    for (double num : numbersA) {
        int i = (num - 50) / 10;
        get<2>(distributionA[i])++;
    }

    for (int num : numbersB) {
        distributionB[num - 1]++;
    }

    for (auto dist : distributionA) {
        cout << get<0>(dist) << " - " << get<1>(dist) << ": " << get<2>(dist) << endl;
    }
    printf("iterations:%d\n", counter);

    for (int i = 0; i < 4; i++) {
        cout << i + 1 << ": " << distributionB[i] << endl;
    }
}