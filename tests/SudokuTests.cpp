#include "SudokuTests.h"
#include <chrono>

int Sudoku::TestResult::GetAvgTimeInNs()
{
    int sum = 0;
    for (int i = 0; i < TestCount; i++)
    {
        sum += times[i];
    }
    return sum / TestCount;
}

Sudoku::TestResult::TestResult(int testCount) : TestCount(testCount)
{
    isSuccess = new bool[testCount];
    times = new int[testCount];
    statusMessages = new std::string[testCount];
}

Sudoku::TestResult::~TestResult()
{
    delete[] isSuccess;
    delete[] times;
    delete[] statusMessages;
}

template<int BASE>
Sudoku::Tests<BASE>::Tests(int** puzzles, int** sollutions, int N, Solver<BASE>* solver) : puzzles(puzzles), sollutions(sollutions), PuzzleCount(N), solver(solver) 
{}

template<int BASE>
bool Sudoku::Tests<BASE>::AssertPuzzles(const int* puzzle1, const int* puzzle2, std::string* errorMessage)
{
    bool isSuccess = true;
    for (int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (puzzle1[i * WIDTH + j] == puzzle2[i * WIDTH + j])
            {
                *errorMessage  += std::to_string(puzzle1[i * WIDTH + j]) + ", ";
            }
            else
            {   
                *errorMessage  += std::to_string(puzzle1[i * WIDTH + j]) + "[" + std::to_string(puzzle2[i * WIDTH + j]) + "], ";
                isSuccess = false;
            }
        }
        *errorMessage += '\n';
    }
    return isSuccess;
}


template<int BASE>
Sudoku::TestResult Sudoku::Tests<BASE>::Run()
{
    TestResult* result = new TestResult(PuzzleCount);

    int actualSolution[CELL_COUNT] = {0};
    for (int i = 0; i < PuzzleCount; i++)
    {
        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        solver->Solve(puzzles[i], actualSolution);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        result->times[i] = std::chrono::duration_cast<std::chrono::nanoseconds> (end - start).count();
        std::string errorMessage = "";
        bool success = AssertPuzzles(actualSolution, sollutions[i], &errorMessage);
        result->statusMessages[i] = errorMessage;      
        result->isSuccess[i] = success;  
        result->Fails += !success;      
    }
    return *result;
}    

