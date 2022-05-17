#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <chrono>
#include <assert.h>
#include <windows.h>
#include <omp.h>
#include <vector>
#include <stdexcept>
#include <iostream>
using namespace std;
vector < int > vec;
int leng;
bool flag = false;
void wait(int x) {
    Sleep(x);
}

int k = 0;

void check_size(int &k)
{
    try {
        cout << vec.at(k) << endl;
        k++;
    }
    catch(out_of_range){
        flag = true;
        return;
    }
    leng = k;
    return;
}

int main() {
    int32_t i;
    uint32_t n = 10;
    int x = 10;

    for (int i = 0; i < x ; i++)
    {
        vec.push_back(i);
    }
    
    auto start = std::chrono::high_resolution_clock::now();

#pragma omp parallel num_threads(4) default(shared) private(i)
    {
#pragma omp sections
        {
            while (!flag)
            {
#pragma omp section
                {
                    check_size(k);
                }

#pragma omp section
                {
                    check_size(k);
                }
#pragma omp section
                {
                    check_size(k);
                }

#pragma omp section
                {
                    check_size(k);
                }
           }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
cout << "Parallel normal way";
cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()<<endl;

cout << "Dlugosc wektora to : " << leng;

    return 0;
}