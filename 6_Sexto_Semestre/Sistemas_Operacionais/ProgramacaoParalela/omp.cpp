#include <iostream>
#include <omp.h>
using namespace std;
#define STEPCOUNTER 1000000000

int main()
{
    long i;
    double pi = 0;
    double partial_sum = 0.0;
#pragma omp parallel private(i) shared(partial_sum)
    {
        double partial_pi = 0;
#pragma omp for
        for (i = 0; i < STEPCOUNTER; ++i)
        {
            double p1 = 1.0 / (i * 4.0 + 1.0);
            double p2 = 1.0 / (i * 4.0 + 3.0);
            partial_pi += p1 - p2;
        }
#pragma omp atomic
        partial_sum += partial_pi;
    }
    
    cout << "Pi = " << partial_sum * 4.0 << endl;

    return 0;
}