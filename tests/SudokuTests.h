#pragma once
struct TestResult
{
    int TestCount;
    int GetAvgTimeInNs();
    int Fails = 0;
    int* times;
};

class SudokuTests
{
    private:
        short** puzzles;
        short** sollutions;
        int PuzzleCount;
    public:
        SudokuTests(short** puzzles, short** sollutions, int N);
        TestResult* Run();
        bool AssertPuzzles(const short* puzzle1, const short* puzzle2);
         
};