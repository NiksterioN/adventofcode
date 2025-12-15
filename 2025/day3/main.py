"""
See https://adventofcode.com/2025/day/3 for full details
"""

import time

DEBUG = False


def get_max_joltage(battery_bank, num_of_digits):
    """
    Returns the maximum subsequence in a battery_bank given num_of_digits
    The length of battery_bank must be greater than the num_of_digits.

    :param battery_bank: The string containing the battery
    :param num_of_digits: The number of 'digits' to choose in the battery_bank
    :return: (Int : The maximum number that can be selected in the battery_bank given num_of_digits)
    """
    remaining_digits = len(battery_bank) - num_of_digits
    max_joltage = []

    for battery in battery_bank:
        while max_joltage and remaining_digits > 0 and max_joltage[-1] < battery:
            max_joltage.pop()
            remaining_digits = remaining_digits - 1
        max_joltage.append(battery)

    return int(''.join(max_joltage)[:num_of_digits])


def solve_part_a(list_of_battery_bank):
    total_joltage = 0
    for battery_bank in list_of_battery_bank:
        total_joltage = total_joltage + get_max_joltage(battery_bank, 2)
    return total_joltage


def solve_part_b(list_of_battery_bank):
    total_joltage = 0
    for battery_bank in list_of_battery_bank:
        total_joltage = total_joltage + get_max_joltage(battery_bank, 12)
    return total_joltage


def test_functions():
    # Part A
    assert (get_max_joltage("987654321111111", 2) == 98)
    assert (get_max_joltage("811111111111119", 2) == 89)
    assert (get_max_joltage("234234234234278", 2) == 78)
    assert (get_max_joltage("818181911112111", 2) == 92)

    list_of_battery_bank = """987654321111111
                                811111111111119
                                234234234234278
                                818181911112111
                                """
    list_of_battery_bank = list_of_battery_bank.split()
    assert (solve_part_a(list_of_battery_bank) == 357)

    # Part B
    assert (get_max_joltage("987654321111111", 12) == 987654321111)
    assert (get_max_joltage("811111111111119", 12) == 811111111119)
    assert (get_max_joltage("234234234234278", 12) == 434234234278)
    assert (get_max_joltage("818181911112111", 12) == 888911112111)
    assert (solve_part_a(list_of_battery_bank) == 3121910778619)

    print("All test passed!")

    return True


def main():
    if DEBUG:
        test_functions()

    filename = input("Enter input filename: ")
    start_time = time.time()
    with open(filename, mode="r") as file:
        list_of_battery_banks = file.read().split()
        print("Part A:", solve_part_a(list_of_battery_banks))
        print("Part B:", solve_part_b(list_of_battery_banks))
    print("Time to solve Part A and Part B: ", time.time() - start_time)
    return True


if __name__ == "__main__":
    main()
