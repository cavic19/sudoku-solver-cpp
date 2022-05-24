#include "IndexedQueue.h"
#include <stdexcept>
template<typename T, int BUFFER_SIZE>
void Sudoku::IndexedQueue<T, BUFFER_SIZE>::Enqueue(T item)
{
    if (len == BUFFER_SIZE)
    {
        throw std::overflow_error("Buffer overflow.");
    }
    buffer[(start + len++) % BUFFER_SIZE] = item;
}


template<typename T, int BUFFER_SIZE>
T Sudoku::IndexedQueue<T, BUFFER_SIZE>::Dequeue()
{
    if (len == 0)
    {
        throw std::underflow_error("Buffer underflow.");
    }
    auto result = buffer[start];
    start = (start + 1) % BUFFER_SIZE;
    --len;
    return result;
}

template<typename T, int BUFFER_SIZE>
int Sudoku::IndexedQueue<T, BUFFER_SIZE>::Size()
{
    return len;
}

template<typename T, int BUFFER_SIZE>
T& Sudoku::IndexedQueue<T, BUFFER_SIZE>::operator[](int i)
{
    if (i >= len)
    {
        throw std::overflow_error("Buffer overflow.");
    }
    return buffer[(start + i) % BUFFER_SIZE];
}