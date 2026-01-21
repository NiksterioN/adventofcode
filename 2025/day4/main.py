import time
import cProfile
import pstats

class Matrix:
    def __init__(self, matrix):
        self.original_matrix = matrix.copy()
        self.accessible_rolls = set()
        self.all_rolls = set()

        for r, r_elem in enumerate(matrix):
            for c, c_elem in enumerate(matrix[r]):
                if c_elem == "@":
                    self.all_rolls.add((r, c))

    def reset(self):
        self.all_rolls.clear()
        self.accessible_rolls.clear()
        for r, r_elem in enumerate(self.original_matrix):
            for c, c_elem in enumerate(self.original_matrix[r]):
                if c_elem == "@":
                    self.all_rolls.add((r, c))

    def __str__(self):
        return "\n".join(self.current_matrix) + "\n"

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
        for roll in self.all_rolls:
            if self.is_accessible_by_forklift(roll):
                total_accessible_rolls = total_accessible_rolls + 1
                self.accessible_rolls.add(roll)
        self.all_rolls = self.all_rolls - self.accessible_rolls
        self.accessible_rolls.clear()
        return total_accessible_rolls

    @property
    def traverse_matrix_recursively(self):
        """
        Recursively iterates to solve the number of accessible rolls within the matrix (with each accessible paper rolls removed per call),
        until there is no more accessible rolls to remove.
        :return: The total number of rolls that can be removed
        """

        current_number_of_rolls = self.traverse_matrix
        total_number_of_rolls = current_number_of_rolls

        while current_number_of_rolls > 0:
            current_number_of_rolls = self.traverse_matrix
            total_number_of_rolls = total_number_of_rolls + current_number_of_rolls
        return total_number_of_rolls

    def is_accessible_by_forklift(self, coordinate):
        """
        Checks if there are fewer than four (4) paper rolls in the eight adjacent positions.
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
                if (r, c) != coordinates and (r, c) in self.all_rolls:
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
    test_matrix = Matrix(grid)
    assert (test_matrix.traverse_matrix_recursively == 43)

    print("-- All Unit Tests Passed! --")
    return True


def main():
    test_function()

    filename = "in.txt"
    with open(filename, "r") as file:
        matrix = file.read().split()
        puzzle_matrix = Matrix(matrix)
        start = time.time()
        print(puzzle_matrix.traverse_matrix)

        with cProfile.Profile() as pr:
            print(puzzle_matrix.traverse_matrix_recursively)

        stats = pstats.Stats(pr)
        stats.sort_stats(pstats.SortKey.TIME)
        stats.print_stats()

        end = time.time()

        print(end - start)


if __name__ == "__main__":
    main()
