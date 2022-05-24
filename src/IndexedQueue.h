#pragma once

namespace Sudoku
{
    template<typename T, int BUFFER_SIZE>
    class IndexedQueue
    {
        public:
            T Dequeue();
            void Enqueue(T);
            int Size();
            T& operator[](int);
        private:
            T buffer[BUFFER_SIZE];
            int start = 0;
            int len = 0;

    };
} // namespace Sudoku
