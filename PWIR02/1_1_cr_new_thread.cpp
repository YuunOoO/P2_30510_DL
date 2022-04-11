#include <cstdio>
#include <iostream>
#include <thread>
#include <windows.h>
#include <chrono>
#include <mutex>
using namespace std::this_thread;
using namespace std;
int action(int id) {
    printf("Uruchamiam watek %d\n", id);
    Sleep(10 * 1000); //10 sekund
    printf("Koncze watek %d\n", id);
    return 0;
}

int main() {
    //tworzenie wątku

    int x = 1000;
    std::thread t1(action, 1); //konstruktor klasy t1 przyjmuje minimum wskaźnik na funckje do wykonania
    std::thread::id t1_id = t1.get_id(); cout << t1_id << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(x*2));
    std::thread t2(action, 2);  //funckja ta może coś zwracać, ale może zwaracać też void
    std::thread::id t2_id = t2.get_id(); cout << t2_id << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(x*3));
    std::thread t3(action, 3); //dalsze parametry zostaną przekazane do podanej funckji
    std::thread::id t3_id = t3.get_id(); cout << t3_id << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(x*4));

    t1.join();  //synchronizacja
    t2.join();  //wątek główny ma tu poczekać na te 3 wątki
    t3.join();  //inaczej program by się zakończył wcześniej bo wątki trwają minimum 10 sekund
    printf("Koniec programu \r\n");

    return 0;
}