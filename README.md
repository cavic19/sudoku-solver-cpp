# Zadání

Dobry den,

ano Sudoku je dobra uloha. Aby to nebylo uplne trivialni, tak se asi
nejlepe hodi implementace pres MPI. Take je dobre si ulohu zobecnit ne
jen na hry 3x3x3, ale treba 5x5x5. To zakladni Sudoku se vetsinou
vyresi velice rychle a tezko se na tom pomeruje urychleni.

S pozdravem, Tomas O.

# Nápady
 - Nejdřív sepiš single CPU verzi
     - V ní nejdřív jen přepiš rekurzivní funkci (no-tail) a tu se pokus optimalizovat. Asi prevedenim na tail jestli půjde
     - Optimalizuj skrze metody na PAA (for rolling, horizontal memory lines ... atd)
 - Integruj paralelni algoritmus
     - Simultánní checkování řádku a sloupce 


Každý optimalizacni krok otaguj na gitu popřípadě udělej branch aspon pro single a multi?
https://codegolf.stackexchange.com/questions/190727/the-fastest-sudoku-solver
TDoku: https://github.com/t-dillon/tdoku/blob/master/src/solver_basic.cc

Resit pomoci bitovych operaci?

## Backtracking
Lze paralelizovar checkovani sloupcu a radku

## Simulated Annealing
Lze paralelizvoat subboxy

# TODO
 - Pridat namespace Sudoku a prejmenovat SudokuParser -> Parser, atd.