#include  "Parser.h"
#include <cassert>

Sudoku::Parser::Parser(int dim, char sollutionSeparator, char emptyCellSymbol, int emptyCellValue) :
    dim(dim), 
    sollutionSeparator(sollutionSeparator), 
    emptyCellSymbol(emptyCellSymbol), 
    emptyCellValue(emptyCellValue)
{
}

void Sudoku::Parser::Parse(const std::string line, int* puzzle, int* sollution) const
{
    std::string puzzlePart = line.substr(0, line.find(sollutionSeparator)) + "\0";
    assert(puzzlePart.length() == dim * dim);
    ParsePuzzle(puzzlePart, puzzle);
    
    std::string sollutioPart = line.substr(line.find(sollutionSeparator) + 1, line.length());
    assert(sollutioPart.length() == dim * dim);
    ParsePuzzle(sollutioPart, sollution);
}

void Sudoku::Parser::ParsePuzzle(const std::string line, int* puzzle) const
{
    for (int i = 0; i < dim * dim; i++)
    {
        if (line[i] == emptyCellSymbol)
            puzzle[i] = emptyCellValue;
        else if (line[i] >= 'a')
            puzzle[i] = line[i] - 'a' + 10;
        else
            puzzle[i] = line[i] - '0';
    }
    
}