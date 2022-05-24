#include "WorkStealingStack.cpp"
#include "C:\Program Files (x86)\Microsoft SDKs\MPI\Include\mpi.h"
#include <iostream>

void printStack(WorkStealingStack<10>&, int id);

int main(int argc, char** argv)
{
    MPI_Init(&argc, &argv);
    int nproc, iproc;
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &iproc);
    WorkStealingStack<10>* wss = new WorkStealingStack<10>();
        for (int i = 0; i < 10; i++)
        {
            if (iproc == 0)
            {
                wss->Push(i);
            }
        }


    MPI_Barrier(MPI_COMM_WORLD);
    std::cout << "Hello from proc. " << iproc << ", size of my array is "<< wss->Size() << std::endl;
    if (iproc == 1)
    {
    printStack(*wss, iproc);

    }
    MPI_Barrier(MPI_COMM_WORLD);
    // std::cout << "Proc: "<< iproc << ", size: " << std::endl;
    delete wss;
    MPI_Finalize();
    return 0;
}

void printStack(WorkStealingStack<10> &s, int id)
{
    do 
    {
        std::cout << "Proc: "<< id << ", val: " << s.Pop() << std::endl;
    } while(s.Size() != 0);
    
}