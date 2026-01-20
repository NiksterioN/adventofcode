from collections import deque
import time


class Matrix:
    def __init__(self, matrix):
        self.original_matrix = matrix.copy()
        self.current_matrix = matrix.copy()
        self.next_matrix = []
        self.number_of_row = len(self.current_matrix)
        self.number_of_column = len(self.current_matrix[0])

    def reset(self):
        self.current_matrix = self.original_matrix.copy()

    def print(self):
        print(self.current_matrix)

    @property
    def traverse_matrix(self):
        """
        Iterates over the matrix to solve the number of accessible rolls.
        A roll is accessible if there are fewer than four (4) paper rolls in the eight adjacent positions.

        For example in the matrix below, '@' denotes a paper roll and '.' denotes an empty space.
        ['..@@.@',
         '@@@.@.',
         '@@@@@.']

        :return: The number of accessible paper rolls
        """
        total_accessible_rolls = 0

        for r in range(self.number_of_row):
            new_row = []
            for c in range(self.number_of_column):
                if self.current_matrix[r][c] == "@" and self.is_accessible_by_forklift((r, c)):
                    total_accessible_rolls = total_accessible_rolls + 1
                    new_row.append(".")
                else:
                    new_row.append(self.current_matrix[r][c])

            self.next_matrix.append(["".join(new_row)])

        self.current_matrix = self.next_matrix.copy()
        self.next_matrix = []
        return total_accessible_rolls

    @property
    def traverse_matrix_recursively(self):
        """
        Recursively iterates to solve the number of accessible rolls within the matrix (with each accessible paper rolls removed per call),
        until there is no more accessible rolls to remove.

        :return: The total number of rolls that can be removed
        """
        total_number_of_rolls = 0
        current_number_of_rolls = self.traverse_matrix
        total_number_of_rolls = current_number_of_rolls
        while current_number_of_rolls > 0:
            current_number_of_rolls = self.traverse_matrix
            total_number_of_rolls = total_number_of_rolls + current_number_of_rolls

        return total_number_of_rolls

    def is_accessible_by_forklift(self, coordinate):
        """
        Checks if there are fewer than four (4) paper rolls in the eight adjacent positions.
        :param matrix: The matrix or diagram
        :param coordinate: (r, c) : The position to check in the matrix

        :return:    True if the there are fewer than four (4) paper rolls in the eight adjacent positions.
                    Otherwise, returns False
        """
        if self.get_adjacent_sum(coordinate) < 4:
            return True
        else:
            return False

    def get_adjacent_sum(self, coordinates):
        """
        Get the number of paper rolls in the eight adjacent positions given in the coordinates (excluding the coordinate itself)
        For example in the given below
        ['..@',
         '@@@',
         '@@@']
        :param coordinates: (r, c) : The position to check in the matrix
        :return: The number of paper rolls in the eight adjacent positions given in the coordinates (excluding the coordinate itself)
        """
        number_of_adjacent_rolls = 0
        for r in range(coordinates[0] - 1, coordinates[0] + 2):
            for c in range(coordinates[1] - 1, coordinates[1] + 2):
                # Boundary conditions
                if r >= self.number_of_row or r < 0:
                    continue
                if c >= self.number_of_column or c < 0:
                    continue
                if (r, c) == coordinates:
                    continue
                if self.current_matrix[r][c] == "@":
                    number_of_adjacent_rolls = number_of_adjacent_rolls + 1
        return number_of_adjacent_rolls


def test_function():
    grid = """..@@.@@@@.\n
              @@@.@.@.@@\n
              @@@@@.@.@@\n
              @.@@@@..@.\n
              @@.@@@@.@@\n
              .@@@@@@@.@\n
              .@.@.@.@@@\n
              @.@@@.@@@@\n
              .@@@@@@@@.\n
              @.@.@@@.@."""

    grid = grid.split()
    test_matrix = Matrix(grid)

    assert (test_matrix.get_adjacent_sum((0, 0)) == 2)
    assert (test_matrix.get_adjacent_sum((1, 1)) == 6)
    assert (test_matrix.get_adjacent_sum((len(grid) - 1, len(grid[0]) - 1)) == 2)

    assert (test_matrix.traverse_matrix == 13)
    test_matrix.reset()
    assert (test_matrix.traverse_matrix_recursively == 43)

    print("test done")
    return True


def main():
    test_function()

    filename = "in.txt"
    with open(filename, "r") as file:
        matrix = file.read().split()
        puzzle_matrix = Matrix(matrix)
        start = time.time()
        print(puzzle_matrix.traverse_matrix)
        print(puzzle_matrix.traverse_matrix_recursively)
        end = time.time()

        print(end - start)


if __name__ == "__main__":
    main()
