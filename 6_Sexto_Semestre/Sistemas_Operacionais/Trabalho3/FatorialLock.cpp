#include <iostream>
#include <omp.h>

using namespace std;

int main() {
  long double product = 1;
  int n;

  omp_lock_t chave;

  cout << "Digite um valor para n (1-20): ";
  cin >> n;

  omp_init_lock(&chave);

#pragma omp parallel shared(product, chave)
  {
    long double parcial_product = 1;

#pragma omp for
    for (int i = n; i > 1; --i) {
      parcial_product *= i;
    }
    omp_set_lock(&chave);
  
    product *= parcial_product;

    omp_unset_lock(&chave);
  }

  omp_destroy_lock(&chave);

  cout << "Fatorial de " << n << " = " << product << endl;
  return 0;
}