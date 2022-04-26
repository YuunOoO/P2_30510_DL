#include <thread>
#include <cstdio>
#include <windows.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>

thread_local unsigned int counter = 0;
int tab[100];
int zwykla_zmienna = 0;
thread_local int lokalna_zmienna = 0;
int sprawdz = 3;
////////////////////////


void increment(int id) {
    //for (int i = 0; i < 10; i++) {
    //    counter++;
    //    Sleep(300);
    //}

    //ten blok wykona się tylko raz mimo, że wątków jest więcej
   
    //for (int i = 0; i < 100; i++)
    //        std::cout << tab[i] << " ";   zad 1 wypisywanie
 
    for (int i = (id - 1); i < (id * 10); i++)
    {
        zwykla_zmienna += tab[i];
        lokalna_zmienna += tab[i];
    }

    if(id == sprawdz)
        std::cout << "Suma watku t"<<id<<": " << lokalna_zmienna << std::endl;
}

int main() {
    /* initialize random seed: */
    srand(time(NULL));

    for (int i = 0; i < 100; i++)
        tab[i] = rand() % 10 + 1;

    std::cout << "Wybierz tread do sprawdzenia: ";
    std::cin >> sprawdz;

    std::thread t1(increment, 1);
    std::thread t2(increment, 2);
    std::thread t3(increment, 3);
    std::thread t4(increment, 4);
    std::thread t5(increment, 5);
    std::thread t6(increment, 6);
    std::thread t7(increment, 7);
    std::thread t8(increment, 8);
    std::thread t9(increment, 9);
    std::thread t10(increment, 10);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    t9.join();
    t10.join();


    std::cout <<"Zwykla zmienna suma: "<< zwykla_zmienna << std::endl;
    std::cout << "Lokalna zmienna suma: " << lokalna_zmienna << std::endl;


    return 0;
}