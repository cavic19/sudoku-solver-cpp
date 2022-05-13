#pragma once
#include <string>
namespace Sudoku{
    class Parser
    {
        private:
            int dim;
            char sollutionSeparator;
            char emptyCellSymbol;
            int emptyCellValue;
            void ParsePuzzle(const std::string line, int* puzzle) const;
        public:
            Parser(int dim, char sollutionSeparator = ';', char emptyCellSymbol = 'X', int emptyCellValue = -1);
            void Parse(const std::string line, int* puzzle, int* sollution) const;
    };
}