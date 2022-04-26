#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <thread>
#include <iostream>
#define SIZE 4

void add(int id, int* a, int* b, int* c) {
    c[id] = a[id] + b[id];
}


int main() {
    srand(time(NULL));
    int rozmiar;
    std::cout << "Podaj rozmiar: ";
    std::cin >> rozmiar;
    int *a = (int*)malloc(rozmiar);
    int *b= (int*)malloc(rozmiar);
    int *c = (int*)malloc(rozmiar);

    for (int i = 0; i < SIZE; i++) {
        a[i] = rand() % 100 + 1; //1 do 100
        b[i] = rand() % 100 + 1;
    }

    //wypisanie na ekranie A
    for (int i = 0; i < SIZE; i++) {
        printf("%i ", a[i]);
    }
    printf("\n");

    //wypisanie na ekranie B
    for (int i = 0; i < SIZE; i++) {
        printf("%u ", b[i]);
    }
    printf("\n");

    std::thread** threads = new std::thread * [SIZE];
    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < (SIZE); i++) {
       
        for (int j = i * 10; j < ((i * 10) + 10); j++)
        { 
            std::cout << i << " " << j<< std::endl;
            threads[i] = new std::thread(add, i, a, b, c); //wykorzystuje i jako id danego wÄ…tku
        }
    }
    auto end = std::chrono::steady_clock::now();
    printf("Czas trwania: %llu\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    for (int i = 0; i < SIZE; i++) {
        threads[i]->join();
    }

    for (int i = 0; i < SIZE; i++) {
        delete threads[i];
    }
    delete[] threads;

    //wypisanie na ekranie C
    for (int i = 0; i < SIZE; i++) {
        printf("%u ", c[i]);
    }

    return 0;
}
