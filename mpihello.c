#include <stdio.h>
#include "mpi.h"

int main(int argc, char* argv[])
{
	int rank, size;
	int tosend, torecv;
	unsigned char i;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if(size==1){
		fputs("Need more nodes.\n", stderr);
		return 1;
	}

	tosend=(rank+1)%size;
	torecv=rank-1;
	if(torecv==-1)
		torecv=size-1;

	printf("rank%d/%d, to=%d, from=%d\n", rank, size, tosend, torecv);

	i=0x55;

	if(!rank)
		MPI_Send(&i, 1, MPI_UNSIGNED_CHAR, tosend, tosend,	\
			MPI_COMM_WORLD);

	MPI_Recv(&i, 1, MPI_UNSIGNED_CHAR, torecv, rank,	\
		MPI_COMM_WORLD, MPI_STATUS_IGNORE);

	if(rank)
		MPI_Send(&i, 1, MPI_UNSIGNED_CHAR, tosend, tosend,	\
			MPI_COMM_WORLD);

	MPI_Barrier(MPI_COMM_WORLD);
	if(!rank)
		puts("Succeed.");

	MPI_Finalize();

	return 0;
}
