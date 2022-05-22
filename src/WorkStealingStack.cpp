#include "Board.h"
#include <stack>
#include <stdexcept>
#include "C:\Program Files (x86)\Microsoft SDKs\MPI\Include\mpi.h"
using namespace Sudoku;

template<typename T, int SIZE>
class WorkStealingStack
{
    public:
        WorkStealingStack()
        {
            MPI_Comm_size(MPI_COMM_WORLD, &processNum);
            MPI_Comm_rank(MPI_COMM_WORLD, &processId);
            MPI_Win_create(buffer, SIZE * sizeof(T), sizeof(T), MPI_INFO_NULL, MPI_COMM_WORLD, &bufferWin);
            MPI_Win_create(index, sizeof(int), sizeof(int), MPI_INFO_NULL, MPI_COMM_WORLD, &indexWin);

            itemMPIType = MPI_Type_contiguous()
        }

        ~WorkStealingStack()
        {
            MPI_Win_free(&bufferWin);
            MPI_Win_free(&indexWin);
        }
        
        void Push(T item)
        {
            if (index > SIZE)
            {
                throw std::overflow_error();
            }
            buffer[index++] = item;
        }

        T Pop()
        {
            if (index == 0)
            {
                throw std::underflow_error();
            }
            return buffer[--index];
        }
        
        void PopRange(int n, const T* destination)
        {
            for (int i = 0; i < n; i++)
            {
                destination[i] = Pop();
            }
            
        }

        int Size() const
        {
            if (index == 0)
            {
                for (int i = 0; i < processNum; i++)
                {
                    if (i == processId)
                    {
                        continue;
                    }
                    if (RequestData(i))
                    {
                        break;
                    }
                }
                
            }
            return index;
        }

    private:
        MPI_Win bufferWin;
        MPI_Win indexWin;
        MPI_Datatype itemMPIType;

        int processId;
        int processNum;
        T buffer[SIZE];
        int index;
        bool RequestData(int processRank)
        {
            bool isSucces;
            int rankBufferIndex;
            MPI_Win_lock(MPI_LOCK_EXCLUSIVE, processRank, 0, indexWin);
            MPI_Win_lock(MPI_LOCK_EXCLUSIVE, processRank, 0, bufferWin);
            MPI_Get(&rankBufferIndex, 1, MPI_INT, targetRank, 0, 1, MPI_INT, indexWin);
            if(rankBufferIndex  <= 1)
            {
                isSucces = false;
            }
            else
            {
                MPI_Get(buffer[index], SIZE, )
            }   


            MPI_Win_unlock(processRank, bufferWin);
            MPI_Win_unlock(processRank, indexWin);
            return isSucces;
        }

};