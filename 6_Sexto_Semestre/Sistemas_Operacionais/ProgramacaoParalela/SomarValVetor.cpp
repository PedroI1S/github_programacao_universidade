#include <iostream>
#include <omp.h>
using namespace std;
#define STEPCOUNTER 1000000000

int main() {
    long i;
    int a = 0, b = 0;
    int x[5] = {1, 2, 3, 4, 5}, y[5] = {10, 20, 30, 40, 50};
    int n = 5;

#pragma omp parallel private(i) shared(a, b, n)
    {
#pragma omp for
        for (i = 0; i < n; ++i) {
#pragma omp critical
            {
                a += x[i];
                b += y[i];
            }
        }
    }
    cout << "a = " << a << ", b = " << b << endl;
    return 0;
}
