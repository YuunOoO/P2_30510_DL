#include "mpi.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>



using namespace std;



int main(int argc, char* argv[])
{
	int id, count;
	int n = 6000000;
	srand(time(NULL));
	MPI_Init(&argc, &argv);



	//pobranie id oraz ilości procesów do zmiennych
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &count);




	srand(time(NULL));
	float x, y;
	int k = 0;
	//kod procesu komunikującego się z użytkownikiem
	if (id == 0) {

		int iteration = 100;
		MPI_Bcast(&iteration, 1, MPI_INT, 0, MPI_COMM_WORLD); //proces 0 jest nadawcą



		int* results = new int[count - 1];
		MPI_Request* requests = new MPI_Request[count - 1];
		MPI_Status* statuses = new MPI_Status[count - 1];



		//wywołujemy nasłuch od każdego procesu oprócz samego siebie
		//asynchroniczne wywołanie pozwoli uruchomić nasłuch dla każdego
		//procesu bez potrzeby czekania na dane od poprzednika
		for (int i = 1; i <= n; i++) {
			x = rand() / float(RAND_MAX);
			y = rand() / float(RAND_MAX);
			if (x * x + y * y <= 1) k++;
		};



		MPI_Waitall(count - 1, requests, statuses);//oczekuje



		//tu można by było coś zrobić z tymi danymi
		//ale to tylko przykład



		float p = 4. * k / n;
		cout << "pi = " << setprecision(10) << p << endl;



		delete[] results;
		delete[] requests;
		delete[] statuses;
	}
	//kod procesów wynokujących jakieś działania
	else {
		int iteration = 0;



		MPI_Bcast(&iteration, 1, MPI_INT, 0, MPI_COMM_WORLD); //pozostałe procesy czekają tu aż P0 nada wartość



		//jakieś operacje

		int dane = 1;
		MPI_Send(&dane, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}



	MPI_Finalize();
	return 0;
}