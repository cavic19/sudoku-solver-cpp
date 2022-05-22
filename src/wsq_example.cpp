#include "WorkStealingStack.cpp"
#include "C:\Program Files (x86)\Microsoft SDKs\MPI\Include\mpi.h"
#include <iostream>



int main(int argc, char** argv)
{
    MPI_Init(&argc, &argv);
    int nproc, iproc;
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &iproc);

    WorkStealingStack<int, 10> wss;
    if (iproc == 0)
    {
        for (int i = 0; i < 10; i++)
        {
            wss.Push(i);
        }
    }




    MPI_Finalize();
    return 0;
}