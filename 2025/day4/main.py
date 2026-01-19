from collections import deque
import time


def traverse_matrix(matrix):
    """
    Iterates over the matrix to solve the number of accessible rolls.
    A roll is accessible if there are fewer than four (4) paper rolls in the eight adjacent positions.
    :param matrix: The matrix or diagram.
    For example in the matrix below, '@' denotes a paper roll and '.' denotes an empty space.
    ['..@@.@',
     '@@@.@.',
     '@@@@@.']

    :return: (The matrix with paper rolls removed, The number of accessible paper rolls)
    """

    number_of_row = len(matrix)
    number_of_column = len(matrix[0])
    total_accessible_rolls = 0
    new_matrix = []

    for r in range(number_of_row):
        new_column = []
        for c in range(number_of_column):
            if matrix[r][c] == "@" and is_accessible_by_forklift(matrix, (r, c)):
                total_accessible_rolls = total_accessible_rolls + 1
                new_column.append(".")
            else:
                new_column.append(matrix[r][c])
        new_matrix.append(new_column)
    return (new_matrix, total_accessible_rolls)


def traverse_matrix_recursively(matrix):
    """
    Recursively iterates to solve the number of accessible rolls within the matrix (with each accessible paper rolls removed per call),
    until there is no more accessible rolls.

    :param matrix: The matrix or diagram.
    :return: The total number of rolls that can be removed
    """
    total_number_of_rolls = 0
    new_matrix, current_number_of_rolls = traverse_matrix(matrix)
    total_number_of_rolls = current_number_of_rolls
    while current_number_of_rolls > 0:
        new_matrix, current_number_of_rolls = traverse_matrix(new_matrix)
        total_number_of_rolls = total_number_of_rolls + current_number_of_rolls

    return total_number_of_rolls


def is_accessible_by_forklift(matrix, coordinate):
    """
    Checks if there are fewer than four (4) paper rolls in the eight adjacent positions.
    :param matrix: The matrix or diagram
    :param coordinate: (r, c) : The position to check in the matrix

    :return:    True if the there are fewer than four (4) paper rolls in the eight adjacent positions.
                Otherwise, returns False
    """
    if get_adjacent_sum(matrix, coordinate) < 4:
        return True
    else:
        return False


def get_adjacent_sum(matrix, coordinates):
    """
    Get the number of paper rolls in the eight adjacent positions given in the coordinates (excluding the coordinate itself)
    For example in the given below 
    ['..@',
     '@@@',
     '@@@']
    :param matrix: The matrix or diagram
    :param coordinates: (r, c) : The position to check in the matrix
    :return: The number of paper rolls in the eight adjacent positions given in the coordinates (excluding the coordinate itself)
    """
    number_of_adjacent_rolls = 0
    number_of_row = len(matrix)
    number_of_column = len(matrix[0])
    for r in range(coordinates[0] - 1, coordinates[0] + 2):
        for c in range(coordinates[1] - 1, coordinates[1] + 2):
            # Boundary conditions
            if r >= number_of_row or r < 0:
                continue
            if c >= number_of_column or c < 0:
                continue
            if (r, c) == coordinates:
                continue
            if matrix[r][c] == "@":
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

    grid = grid.split();
    assert (get_adjacent_sum(grid, (0, 0)) == 2)
    assert (get_adjacent_sum(grid, (1, 1)) == 6)
    assert (get_adjacent_sum(grid, (len(grid) - 1, len(grid[0]) - 1)) == 2)

    assert (traverse_matrix(grid)[1] == 13)
    assert (traverse_matrix_recursively(grid) == 43)
    return True


def main():
    test_function()

    filename = "in.txt"
    with open(filename, "r") as file:
        matrix = file.read().split()

        start = time.time()
        print(traverse_matrix(matrix)[1])
        print(traverse_matrix_recursively(matrix))
        end = time.time()

        print(end - start)


if __name__ == "__main__":
    main()
