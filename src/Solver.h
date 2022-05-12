#pragma once
struct Cell
{
    int Row;
    int Coll;
    int Box; 
};

// Solver for sudoku BASE^2 X BASE^2 up to BASE^2 == 16
// The appropriate sudoku values mst follow 0, 1, 2, ..., BASE^2 - 1
template<int BASE>
class Solver
{
    private:
        static constexpr int WIDTH = BASE * BASE;
        static constexpr int CELL_COUNT = WIDTH * WIDTH;
        static constexpr short NO_CANDIDATES = 65535 >> (sizeof(short)*8 - WIDTH);
        short rows[WIDTH];
        short cols[WIDTH];
        short boxes[WIDTH];
        Cell emptyCells[CELL_COUNT];

        int emptyCellsCount;
        inline short NextCandidate(short availableCandidates);
        void Analyze(const int* puzzle, int* sollution);
        bool Backtrack(int* puzzle, int emptyCellIndex);
    public:
        void Solve(const int* puzzle, int* sollution);
};