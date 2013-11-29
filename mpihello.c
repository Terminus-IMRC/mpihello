#include <stdio.h>
#include "mpi.h"

int main(int argc, char* argv[])
{
	int rank, size;
	int tosend, torecv;
	int len;
	unsigned char i;
	char filename[0xff];
	char pname[MPI_MAX_PROCESSOR_NAME];
	FILE* fp;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Get_processor_name(pname, &len);

	if(size==1){
		fputs("Need more nodes.\n", stderr);
		return 1;
	}

	sprintf(filename, "out%d.txt", rank);
	fp=fopen(filename, "w");

	tosend=(rank+1)%size;
	torecv=rank-1;
	if(torecv==-1)
		torecv=size-1;

	fprintf(fp, "rank%d/%d(%s), to=%d, from=%d\n", rank, size, pname, tosend, torecv);

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
