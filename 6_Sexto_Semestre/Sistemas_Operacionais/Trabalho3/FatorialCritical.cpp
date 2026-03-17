#include <iostream>
#include <omp.h>

using namespace std;

int main() {
  long long int product = 1;

  int n; // Valor para o calculo do fatorial
  cout << "Digite um valor para n: ";
  cin >> n;

#pragma omp parallel shared(product)
  {
    long long int parcial_product = 1;
#pragma omp for
    for (int i = n; i > 1; --i) {
      parcial_product *= i;
    }
#pragma omp critical
    {
      product *= parcial_product;
    }
  }
  cout << "Fatorial de " << n << " = " << product << endl;
  return 0;
}