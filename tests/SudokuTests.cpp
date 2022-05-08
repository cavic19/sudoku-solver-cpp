#include "SudokuTests.h"
#include "../src/SudokuSolver.h"
#include <chrono>

int TestResult::GetAvgTimeInNs()
{
    int sum = 0;
    for (int i = 0; i < TestCount; i++)
    {
        sum += times[i];
    }
    return sum / TestCount;
}

SudokuTests::SudokuTests(short** puzzles, short** sollutions, int N) : puzzles(puzzles), sollutions(sollutions), PuzzleCount(N) {}

bool SudokuTests::AssertPuzzles(const short* puzzle1, const short* puzzle2)
{
    for (int i = 0; i < 9 * 9; i++)
        if (puzzle1[i] != puzzle2[i])
            return false;
    return true;   
}


TestResult* SudokuTests::Run()
{
    TestResult* result = new TestResult();
    result->times = new int[PuzzleCount];
    result->TestCount = PuzzleCount;

    short actualSolution[9 * 9] = {0};
    for (int i = 0; i < PuzzleCount; i++)
    {
        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        solve(puzzles[i], actualSolution);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        result->times[i] = std::chrono::duration_cast<std::chrono::nanoseconds> (end - start).count();
        
        bool isSuccess = AssertPuzzles(actualSolution, sollutions[i]);
        result->Fails += !isSuccess;
    }
    return result;
}    

