#include <iostream>
#include <omp.h>

using namespace std;

int main(){
    long int a = 0, b = 0;

    int array_size = 10000;
    long int x[array_size], y[array_size];

#pragma omp parallel for
    for (int i = 0; i < array_size; ++i){
        x[i] = i;
        y[i] = i * 2;
    }

#pragma omp parallel shared(x, y, a, b)
    {
        long int a_parc = 0, b_parc = 0;

#pragma omp for
        for (int i = 0; i < array_size; ++i){
            a_parc = a_parc + x[i];
            b_parc = b_parc + y[i];
        }

#pragma omp critical
        {
            a = a + a_parc;
            b = b + b_parc;
        }
    }

    cout << "Soma de x = " << a << endl;
    cout << "Soma de y = " << b << endl;

    return 0;
}