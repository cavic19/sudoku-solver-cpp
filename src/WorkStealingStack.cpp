#include "Board.h"
#include <stack>
#include <stdexcept>
#include "C:\Program Files (x86)\Microsoft SDKs\MPI\Include\mpi.h"
#include <iostream>
using namespace Sudoku;

template<int SIZE>
class WorkStealingStack
{
    public:
        WorkStealingStack()
        {
            MPI_Comm_size(MPI_COMM_WORLD, &processNum);
            MPI_Comm_rank(MPI_COMM_WORLD, &processId);
            
            MPI_Win_create(buffer, SIZE * sizeof(int), sizeof(int), MPI_INFO_NULL, MPI_COMM_WORLD, &bufferWin);
            MPI_Win_create(&index, sizeof(int), sizeof(int), MPI_INFO_NULL, MPI_COMM_WORLD, &indexWin);
        }


        ~WorkStealingStack()
        {
            std::cout << "Deleting bufferWin";
            MPI_Win_free(&bufferWin);
            MPI_Win_free(&indexWin);
        }
        
        void Push(int item)
        {
            if (index > SIZE)
            {
                throw std::overflow_error("Buffer overflowed.");
            }
            buffer[index++] = item;
        }

        int Pop()
        {
            if (index == 0)
            {
                for (int i = 0; i < processNum; i++)
                {
                    if(RequestData(i))
                    {
                        break;
                    }
                }
                if (index == 0)  throw std::underflow_error("Buffer underflowed.");
            }
            return buffer[--index];
        }
        
        void PopRange(int n, const int* destination)
        {
            for (int i = 0; i < n; i++)
            {
                destination[i] = Pop();
            }
            
        }

        int Size() const
        {
            return index;
        }

    private:
        MPI_Win bufferWin;
        MPI_Win indexWin;
        MPI_Datatype itemMPIType;

        int processId;
        int processNum;
        int buffer[SIZE];
        int index;

        bool RequestData(int processRank) const
        {
            std::cout << "Requesting data from rank " << processRank << std::endl;
            bool isSucces;
            int rankBufferIndex;
            MPI_Win_lock(MPI_LOCK_EXCLUSIVE, processRank, 0, indexWin);
            MPI_Win_lock(MPI_LOCK_EXCLUSIVE, processRank, 0, bufferWin);


            MPI_Get(&rankBufferIndex, 1, MPI_INT, processRank, 0, 1, MPI_INT, indexWin);
            std::cout << "Rank buffer index is " << rankBufferIndex << std::endl;
            if(rankBufferIndex  <= 1)
            {
                isSucces = false;
            }
            else
            {
                int numOfItems = rankBufferIndex / 2;

                MPI_Get((void *)&buffer[index], SIZE, MPI_INT, processRank, rankBufferIndex, numOfItems, MPI_INT, bufferWin);
           
                // MPI_Fetch_and_op(&numOfItems,)
                
                MPI_Put(&numOfItems, 1, MPI_INT, processRank, 0, 1, MPI_INT, indexWin);
            }   

            MPI_Win_unlock(processRank, bufferWin);
            MPI_Win_unlock(processRank, indexWin);
            return isSucces;
        }

};