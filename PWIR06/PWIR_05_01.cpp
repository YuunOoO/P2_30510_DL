#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <chrono>
#include <assert.h>
#include <windows.h>
#include <omp.h>
#include <iostream>

void DoSomethingFast() {
    Sleep(1000);
}

void DoSomethingLong() {
    Sleep(6000);
}


int main() {
    uint8_t id;

    auto start = std::chrono::high_resolution_clock::now();
    DoSomethingFast();
    auto end = std::chrono::high_resolution_clock::now();

    printf("Fast in time: %llu ms\r\n",
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    start = std::chrono::high_resolution_clock::now();
    DoSomethingLong();
    end = std::chrono::high_resolution_clock::now();

    printf("Long in time: %llu ms\r\n",
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    start = std::chrono::high_resolution_clock::now();

    int x;
    std::cout << "Podaj liczbe watkow: ";
    std::cin>>x;
    
#pragma omp parallel num_threads(x) private(id)
    {
        id = omp_get_thread_num();

        if (id % 2) {
            DoSomethingLong();
        }
        else {
            DoSomethingFast();
        }

        printf("Thread %d done work and wait on barrier\n", id);

#pragma omp barrier

        printf("Thread %d done work and already finnished\n", id);
    }

    end = std::chrono::high_resolution_clock::now();
    printf("Parallel normal way %llu ms\r\n",
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
    std::cout << "dla " << x << " watkow";

    return 0;
}