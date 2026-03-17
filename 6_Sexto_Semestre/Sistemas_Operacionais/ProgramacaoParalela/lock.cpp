#include <iostream>
#include <omp.h>

omp_lock_t my_lock;
int counter = 0;

int main() {
    omp_init_lock(&my_lock);

#pragma omp parallel num_threads(2)
    {
        int pid = omp_get_thread_num();

        if(pid == 0) {
            for(int i = 0; i < 100; ++i) {
                omp_set_lock(&my_lock);
                counter++;
                omp_unset_lock(&my_lock);
            }
        }
        else {
            for(int i = 0; i < 100; ++i) {
                omp_set_lock(&my_lock);
                counter--;
                omp_unset_lock(&my_lock);
            }
        }
    }

    omp_destroy_lock(&my_lock);
    std::cout << "Valor final de counter: " << counter << std::endl;

    return 0;
}
