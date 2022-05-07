import requests
from bs4 import BeautifulSoup
from functools import reduce
import argparse

class Difficulty:
    GENTLE = "E"
    CHALLENGING = "C"
    MODERATE = "M"

OFFSET  = 6112

def build_endpoint(day_num, diff):
    return f"https://www.sudokudragon.com/dailysolve.php?DayNum={day_num}&Difficulty={diff}"

def fetch_data(amount: int, difficulty: str) -> list:
    for i in range(amount):
        print(f"Acquiring puzzle n: {OFFSET - i}, d: {difficulty}...")
        response = requests.get(build_endpoint(OFFSET-i, difficulty),headers={"User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/101.0.4951.54 Safari/537.36"})
        if response.ok:
            soup = BeautifulSoup(response.text, "html.parser")
            print("Extracting puzzle and solution...")
            yield extract_puzzle(soup, "Grid"), extract_puzzle(soup, "GridSol")


def extract_puzzle(content: BeautifulSoup, table_tag: str) -> list:
    table = content.find(lambda tag: tag.name=='table' and tag.has_attr('id') and tag['id']==table_tag)
    rows = table.findAll(lambda tag: tag.name=='tr')
    for row in rows[1:]:
        yield (int(cell.string) if cell.string != "\xa0" else 0 for cell in row.findAll(lambda tag: tag.name=='td')[1:])


def puzzle_to_string(puzzle: list) -> None:
    puzzle_rows = [reduce(lambda a,b: f"{a}{b}", p) for p in puzzle]
    return reduce(lambda a,b: f"{a}{b}", puzzle_rows)
    

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Nahraje zvolené množství sudoku zadané obtížnosti a jejich reseni ze sudokudragon.com.')
    parser.add_argument('-n', type=int, help="Mnozstvi stazenych sudoku.")
    parser.add_argument('-d', type=str, help="Obtiznost  sudoku (E,M,C).")
    parser.add_argument('-o', type=str, help="Cesta ulozeni  sudoku.")

    args = parser.parse_args()
    
    data = fetch_data(args.n, args.d)
    with open(args.o,"w") as f:
        for p,s in data:
            print("Reducing sudoku to compact format...")
            reduced_format = puzzle_to_string(p) + ";" + puzzle_to_string(s)
            print(f"Writing sudoku to {args.o}...")
            f.write(reduced_format + "\n")
            print("Success")




