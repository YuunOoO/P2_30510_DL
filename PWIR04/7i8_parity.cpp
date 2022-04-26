#include <thread>
#include <cstdio>
#include <windows.h>
#include <mutex>
#include <ctime>
std::mutex counter_mutex;
unsigned int counter = 0;
int stop = 10;
clock_t start;

void increment() {
    for (;;) {
        counter_mutex.lock();
        counter++;
        counter_mutex.unlock();
        Sleep(2000);
    }
}

void parity() {
    for (;;) {

        if (counter == stop)
        {
            printf("Czas wykonywania: %lu ms\n", clock() - start);
            break;
        }

        counter_mutex.lock();        
        if (counter % 2) {
            printf("%u jest nieparzyste\r\n", counter);
        }
        else {
            printf("%u jest parzyste\r\n", counter);
        }
        counter_mutex.unlock();
        Sleep(2000);
    }
}

int main() {
    start = clock();
    std::thread inc(increment);
    std::thread par(parity);

    inc.join();
    par.join();

    printf("Done\r\n");

    return 0;
}