#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
using namespace std;

int ilosc = 0;
int* variation;
int* bestCycle;
float bestDistance = 1000;

float italy[15][2] = { 0 };
int population[15] = { 0 };
int maxPopulation = 0;
int counter = 0;
int id[15];
string cityName[15];

void ShortestCycle(int iterator) {
    float distance = 0;
    for (int i = 0; i < iterator - 1; i++) {
        int j = variation[i] - 1;
        int k = variation[i + 1] - 1;
        float x = italy[j][0] - italy[k][0];
        float y = italy[j][1] - italy[k][1];
        distance += sqrt(x * x + y * y);
    }

    float x = italy[variation[0] - 1][0] - italy[variation[iterator - 1] - 1][0];
    float y = italy[variation[0] - 1][1] - italy[variation[iterator - 1] - 1][1];
    distance += sqrt(x * x + y * y);

    if (distance < bestDistance) {
        bestDistance = distance;
        for (int i = 0; i < iterator; i++)
            bestCycle[i] = variation[i];
    }
}

bool IsPopulationInRange(int iterator) {
    int populationSum = 0;
    for (int i = 0; i < iterator; i++) {
        if (variation[i - 1] == variation[i] && i>0)
            continue;
        int j = variation[i] - 1;
        populationSum += population[j];
    }
    float precent = float(float(populationSum)/maxPopulation);
    printf("population sum:%f\n", precent);
    return (precent <=  0.6 && precent >=  0.4);
}

void Variations(int depth, int size, int iterator) {
    if (depth == 0) {
        printf("Warjacja %d: ", ilosc + 1);
        for (int j = 0; j < iterator; j++)
            printf("%d ", variation[j]);
        printf("\n");

        ShortestCycle(iterator);


        ilosc++;
        return;
    }
    for (int i = 1; i <= size; i++) {
        bool repeats = false;
        for (int c = 0; c < iterator; c++) {
            if (variation[c] == i) {
                repeats = true;
                break;
            }
        }
        if (repeats)
            continue;
        variation[iterator] = i;
        Variations(depth - 1, size, iterator + 1);
    }
}

int VariationsNumberFormula(int n, int m) {
    int result = 1;
    for (int i = 0; i < m; i++) {
        result *= n - i;
    }
    return result;
}

void Combinations(int depth, int size, int iterator, int start) {
    if (depth == 0) {
        printf("Kombinacje %d: ", ilosc + 1);
        for (int j = 0; j < iterator; j++)
            printf("%d ", variation[j]);
        printf("\n");


        if (IsPopulationInRange(iterator)) 
            counter++;

        ilosc++;
        return;
    }

    for (int i = start; i <= size; i++) {
        variation[iterator] = i;
        Combinations(depth - 1, size, iterator + 1, i);
    }
}

int CombinationsNumberFormula(int n, int m) {
    int result = 1;
    for (int i = 1; i < m + n; i++) {
        result *= i;
    }

    int silnia = 1;
    for (int i = 1; i < n; i++)
        silnia *= i;
    result = result / silnia;

    silnia = 1;
    for (int i = 1; i <= m; i++)
        silnia *= i;
    result = result / silnia;

    return result;
}

void MaxPopulation(int n) {
    maxPopulation = 0;
    for (int i = 0; i < n; i++) {
        maxPopulation += population[i];
    }
}

int main() {
    int m = 4;
    int n = 9;
    int size = 15;

    variation = new int[size];
    bestCycle = new int[size];

    ifstream file("italy.txt");
    if (!file) {
        cerr << "failed to open file\n";
        return 1;
    }

    for (int i = 0; i < size; i++) {
        file >> id[i] >> cityName[i] >> population[i] >> italy[i][0] >> italy[i][1];
    }
    file.close();

    for (int i = 0; i < size; i++) {
        cout << id[i] << " " << cityName[i] << " " << population[i]
            << " " << italy[i][0] << " " << italy[i][1] << endl;
    }

    MaxPopulation(n);
    printf("Number of variations %d\n", VariationsNumberFormula(n, m));

    Variations(m, n, 0);

    printf("best cycle: ");
    for (int i = 0; i < m; i++) {
        printf("%d ", bestCycle[i]);
    }
    for (int i = 0; i < m; i++) {
        cout << cityName[bestCycle[i] - 1] << " ";
    }
    printf("\nDistance: %f\n", bestDistance);

    ilosc = 0;
    printf("Number of combinations %d\n", CombinationsNumberFormula(n, m));

    Combinations(m, n, 0, 1);

    float szansa = ((float)counter / ilosc) * 100;
    printf("chance for population in range of 0.4*MaxPopulation and 0.6*MaxPopulation: %d/%d = %.2f%%\n", counter, ilosc, szansa);

    delete[] variation;
    delete[] bestCycle;

    return 0;
}
