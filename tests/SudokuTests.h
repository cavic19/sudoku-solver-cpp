#pragma once
#include "../src/Solver.h"
#include <string>
namespace Sudoku{
    struct TestResult
    {
        int TestCount;
        int GetAvgTimeInNs();
        int Fails = 0;
        int* times;
        bool* isSuccess;
        int* numberOfSolutions;
        std::string* statusMessages;
        TestResult(int testCount);
        ~TestResult();
    };

    template<int BASE>
    class Tests
    {
        private:
            static constexpr int WIDTH = BASE * BASE;
            static constexpr int CELL_COUNT = WIDTH * WIDTH;
            int** puzzles;
            int** sollutions;
            int PuzzleCount;
            Solver<BASE>* solver;
        public:
            Tests(int** puzzles, int** sollutions, int N, Solver<BASE>* solver);
            TestResult Run();
            bool AssertPuzzles(const int* puzzle1, const int* puzzle2, std::string* errorMessage);
            
    };

    template class Tests<3>;
    template class Tests<4>;
}