#pragma once
#include <string>
namespace Sudoku{
    class Parser
    {
        public:
            Parser(int dim, char sollutionSeparator = ';', char emptyCellSymbol = '.', int emptyCellValue = -1);
            void Parse(const std::string line, int* puzzle) const;
            void Parse(const std::string line, int* puzzle, int* sollution) const;


        private:
            int dim;
            char sollutionSeparator;
            char emptyCellSymbol;
            int emptyCellValue;

    };
}