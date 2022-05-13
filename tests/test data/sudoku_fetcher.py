
from typing import Iterable
from urllib import response
import requests
from bs4 import BeautifulSoup
from functools import reduce
import argparse
from abc import ABC, abstractmethod
from datetime import datetime

class SudokuFetcher(ABC):
    def __init__(self) -> None:
        self._session = requests.Session()

    def _log(self, log_message: str) -> None:
        time = datetime.now().strftime("%H:%M:%S")
        print(f"[{time}]\t{log_message}")

    @abstractmethod
    def get_puzzle_and_sollution(self) -> Iterable:
        """Returns sudoku in standard matrix format"""
        pass

    def format_puzzle_to_reduced_form(self, puzzle: list) -> str:
        puzzle_rows = [reduce(lambda a,b: f"{a}{b}", p) for p in puzzle]
        return reduce(lambda a,b: f"{a}{b}", puzzle_rows)

    def fetch(self, amount: int) -> Iterable:
        generator = self.get_puzzle_and_sollution()
        for i in range(amount):
            self._log(f"Getting puzzle and sollution n. {i} from website.")
            puzzle, sollution = next(generator)
            self._log(f"Reducing puzzle n. {i} to compact format.")
            reduced_puzzle = self.format_puzzle_to_reduced_form(puzzle)
            self._log(f"Reducing sollution n. {i} to compact format.")
            reduced_sollution = self.format_puzzle_to_reduced_form(sollution)
            yield reduced_puzzle + ";" + reduced_sollution

class SudokuDragonFetcher(SudokuFetcher):  
    OFFSET  = 6112
    THRESHOLD = 1000
    def __init__(self, difficulty: str) -> None:
        """Difficulty E for gentle, M for moderate, C for challenging"""
        self.difficulty = difficulty
        super().__init__()

    def get_puzzle_and_sollution(self) -> Iterable:
        """Returns sudoku in standard matrix format"""
        self._session.headers = {
            "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/101.0.4951.54 Safari/537.36"
            }
        i = 0
        while i <= self.THRESHOLD:  
            response = self._session.get(f"https://www.sudokudragon.com/dailysolve.php?DayNum={self.OFFSET - i}&Difficulty={self.difficulty}")
            if response.ok:
                i += 1
                soup = BeautifulSoup(response.text, "html.parser")
                yield self.__extract_puzzle(soup, "Grid"), self.__extract_puzzle(soup, "GridSol")

    def __extract_puzzle(self, content: BeautifulSoup, table_tag: str) -> list:
        table = content.find(lambda tag: tag.name=='table' and tag.has_attr('id') and tag['id']==table_tag)
        rows = table.findAll(lambda tag: tag.name=='tr')
        for row in rows[1:]:
            # -1 to comply with SudokuSolver input format 0,.., n-1 
            yield (int(cell.string) - 1 if cell.string != "\xa0" else "X" for cell in row.findAll(lambda tag: tag.name=='td')[1:])

class SudokuPuzzleOnline(SudokuFetcher):
    def __init__(self, difficulty: int) -> None:
        """Difficulty 1 for beginner, 2 for confident, 3 for expert"""
        self.difficulty = str(difficulty)
        super().__init__()

    def get_puzzle_and_sollution(self) -> Iterable:
        for i in range(1, 1000):
            payload = f"grid=2&SelectNiveau={self.difficulty}&TextNum={i}"
            response = self._session.post("https://www.sudoku-puzzles-online.com/cgi-bin/hexadoku/print-a-solution-hexadoku.cgi",data=payload)
            if response.ok:
                soup = BeautifulSoup(response.text, "html.parser")
                yield self.__extract_puzzle(soup)
        raise OverflowError()

    def __extract_puzzle(self, content):
        table = content.find(lambda tag: tag.name=='table' and tag.has_attr('id') and tag['id']=="grid")
        puzzle = []
        sollution = []
        for row in table.findAll(lambda tag: tag.name== 'tr'):
            puzzle_row = []
            sollution_row = []
            for cell in row.findAll(lambda tag: tag.name == 'td'):
                if "E" in cell.attrs["class"]:
                    puzzle_row.append("X")
                else:
                    puzzle_row.append(cell.string)
                sollution_row.append(cell.string.lower())
            puzzle.append(puzzle_row)
            sollution.append(sollution_row)
        return puzzle, sollution



if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Nahraje zvolené množství sudoku zadané obtížnosti a jejich reseni ze sudokudragon.com.')
    parser.add_argument('-n', type=int, help="Mnozstvi stazenych sudoku.")
    parser.add_argument('-d', type=str, help="Obtiznost  sudoku (E,M,C).")
    parser.add_argument('-o', type=str, help="Cesta ulozeni  sudoku.")

    args = parser.parse_args()
    fetcher = SudokuPuzzleOnline(args.d)

    with open(args.o,"w") as f:
        for formatted_puzzle in fetcher.fetch(args.n):
            f.write(formatted_puzzle + "\n")




