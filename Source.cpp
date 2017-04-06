#include <mpi.h>
#include <stdio.h>
#include <iostream>

using namespace std;


#define LIMIT     5     
#define FIRST     0   
#define ELEMENT   10
#define MAXSIZE   100



int main(int argc, char *argv[])
{

	int   ntasks, rank;
	int array[100];       //array
	int i;
	int pozition;         //position of the element
	int x;
	int low, high;
	int maxPosition;


	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &ntasks);


	if (0 == rank) {
		//read the array
		for (i = 0; i < LIMIT; i++)
			//scanf("%d", array[i]);	
			cin >> array[i];
	}

	//Broadcast data
	MPI_Bcast(array, MAXSIZE, MPI_INT, 0, MPI_COMM_WORLD);

	x = MAXSIZE / ntasks; 
	low = rank * x;
	high = low + x;
	for (i = LIMIT; i > 0; i--) {
		if (array[i] == ELEMENT) {
			pozition = i;
			break;
		}	
	}

	printf("I got %d position from %d\n", pozition, rank);

	//compute position

	MPI_Reduce(&pozition, &maxPosition, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

	if (0 == rank) {
		printf("The max position is%d\n", maxPosition);
	}
		
	system("PAUSE");
	MPI_Finalize();

}


