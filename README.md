# Zadání
Naimplementovat pomocí knihovny MPI paralelní algoritmus pro řešení sudoku (zobecnit na řešení 16x16). 
 1. Nejdřív naimplementovat jednoduchý sekvenční algoritmus
 2. Ten i za pomocí profileru optimalizovat
 3. Porovnat výslekdy sekvenční a paralelní implementace včetně naměření paralelního urychlení a efektivity

# Řešení
Jako sekvenční algoritmus byl zvolen backtracking. Jedná se o brute force agoritmus, kdy procházím všechny možnosti dokud nenaleznu tu správnou. Zároveň jednotlivé větvě stromu jsou nezávislé, tudíž dobře paralelizovatelné. Myšlenka paralelního algoritmu je jendoduchá. Nejdřív provedu hledání do šířky, čímž vyberu p různých počátečních podob sudoku, kde pe je take počet procesů. Posléze paralelně řeším takto nastavené sudoku. 

V ideálním případě, kdy bych nebyl omezen zadáním, tedy knihovnou MPI, tak se nabízí ještě implementovat tzv. work stealing. Ten by využíval sekvenční algoritmus hledání do hloubky, kde si postupně jendotlivé nody stromu ukládá algoritmus do zásobníku. V paralelním algoritmu pak ve chvílí kdy řešička skončí neúspěchem, tak se podívá k ostatním procesům do tohoto zásobníku a ukradne si třeba polovinu možností a dál pracuje. Tímto se zbavíme neaktivních procesů, které skončili dříve.

# Testování
Pro testováním jsem vybral velmi složité sudoku, kteér sekvenčnímu backtracking algoritmu trvá cca 11s vyřešit.
```
+---+---+---+
|3.6|.7.|...|
|...|...|.51|
|8..|...|...|
+---+---+---+
|.1.|4.5|...|
|7..|...|6..|
|...|2..|...|
+---+---+---+
|.2.|...|.4.|
|...|.8.|3..|
|...|5..|...|
+---+---+---+
```
Zatámco paralenímu algoritmu, při 8 procesech, to trvalo vyřešit 1.879s. Tedy sekvenční čas běhu je $T_S = 10937ms$ a paralelní čas běhu je $T_P = 1879ms$. Z toho lze vypočíst urychlení $S = \frac{T_S}{T_P} = 5.8$ a efektivita je tedy $E = \frac{S}{p} = 0.725$.
