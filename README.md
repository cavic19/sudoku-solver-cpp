# Zadání
Naimplementovat pomocí knihovny MPI paralelní algoritmus pro řešení sudoku (zobecnit na řešení 16x16). 
 1. Nejdřív naimplementovat jednoduchý sekvenční algoritmus
 2. Ten i za pomocí profileru optimalizovat
 3. Porovnat výslekdy sekvenční a paralelní implementace včetně naměření paralelního urychlení a efektivity

# Řešení
Jako sekvenční algoritmus byl zvolen backtracking. Jedná se o brute force agoritmus, kdy procházím všechny možnosti dokud nenaleznu tu správnou. Zároveň jednotlivé větvě stromu jsou nezávislé, tudíž dobře paralelizovatelné. Myšlenka paralelního algoritmu je jendoduchá. Nejdřív provedu hledání do šířky, čímž vyberu p různých počátečních podob sudoku, kde pe je take počet procesů. Posléze paralelně řeším takto nastavené sudoku. 

V ideálním případě, kdy bych nebyl omezen zadáním, tedy knihovnou MPI, tak se nabízí ještě implementovat tzv. work stealing. Ten by využíval sekvenční algoritmus hledání do hloubky, kde si postupně jendotlivé nody stromu ukládá algoritmus do zásobníku. V paralelním algoritmu pak ve chvílí kdy řešička skončí neúspěchem, tak se podívá k ostatním procesům do tohoto zásobníku a ukradne si třeba polovinu možností a dál pracuje. Tímto se zbavíme neaktivních procesů, které skončili dříve.
