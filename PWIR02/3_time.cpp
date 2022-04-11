#include <cstdio>
#include <thread>
#include <windows.h>
#include <iostream>
#include <vector>

using namespace std;

void action(int id) {
    printf("Uruchamiam watek %d\n", id);
    Sleep(5 * 1000); //5 sekund
    printf("Koncze watek %d\n", id);
}

int main() {
    int thread_count;
    std::cout << "Podaj ilosc watkow!: ";
    std::cin >> thread_count;
    std::vector<std::thread> threads;
    //otwieranie wątków
    for (int i = 0; i < thread_count; i++) {
        threads.push_back(std::thread(action, i));

    }
    //watki pracują, ale trzeba je zsynchronizować
    for (int i = 0; i < thread_count; i++) {
        threads[i].join();
    }

    //alokowaliśmy pamięć więc pasuje ją zwolnić
    for (int i = 0; i < thread_count; i++) {
    }
    threads.clear();

    printf("Koniec programu \r\n");

    return 0;
}