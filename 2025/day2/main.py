"""
See https://adventofcode.com/2025/day/2 for more details

"""
import time

DEBUG = False

def get_product_id_ranges(product_id):
    """
    Returns the starting range and the stopping range of the given product.
    :param product_id: The product id containing the start and stop ranges delimited with a dash (-)
    :return: (Start Range, Stop Range)
    """
    start_range, stop_range = product_id.split('-')
    return int(start_range), int(stop_range)

def is_invalid_product_id(product_id, part):
    """
    Returns True if the given product is invalid. Otherwise, returns False.
    A product_id is invalid if
        Part = A
        - is made only of some sequence of digits repeated ONLY twice.
            So, 55 (5 twice), 6464 (64 twice), and 123123 (123 twice) would all be invalid IDs.
        Part = B
        - is made only of some sequence of digits repeated AT LEAST twice.
            So, 12341234 (1234 two times), 123123123 (123 three times),
                1212121212 (12 five times), and 1111111 (1 seven times) are all invalid IDs.
    :param product_id: The product_id to be checked.
    :param part: The criteria part of the problem required
    :return: True if the given product is invalid. Otherwise, False.
    """
    product_id_str = str(product_id)
    digit_count = len(product_id_str)
    part = part.lower()

    if part == "a":
        middle_digit = digit_count // 2
        product_id_first_half = product_id_str[:middle_digit]
        product_id_second_half_str = product_id_str[middle_digit:]
        if product_id_first_half == product_id_second_half_str:
            return True

    if part == "b":
        for index in range(1, digit_count):
            repeating_digit_index = product_id_str.find(product_id_str[:index], index)
            repeating_number = product_id_str[:repeating_digit_index]
            test = product_id_str.split(repeating_number)
            if all(item == '' for item in test):
                return True
    return False

def solve_part(product_id_range_list, part):
    count = 0
    part = part.lower()
    for product_id_range in product_id_range_list.split(','):
        start_range, stop_range = get_product_id_ranges(product_id_range)
        for product_id in range(start_range, stop_range + 1):
            if is_invalid_product_id(product_id, part):
                count += product_id
    return count

def test_functions():

    assert(get_product_id_ranges("11-22") == (11, 22))

    assert(is_invalid_product_id(11, "a") == True)
    assert(is_invalid_product_id(1188511885, "a") == True)
    assert(is_invalid_product_id(12, "a") == False)
    assert(is_invalid_product_id(11885911885, "a") == False)


    product_id_range_list =     """11-22,95-115,998-1012,1188511880-1188511890,222220-222224,
                                    1698522-1698528,446443-446449,38593856-38593862,565653-565659,
                                    824824821-824824827,2121212118-2121212124"""

    assert(solve_part(product_id_range_list, "a") == 1227775554)

    assert (is_invalid_product_id(123123123, "b") == True)
    assert(is_invalid_product_id(1188511885, "b") == True)
    assert (is_invalid_product_id(11885911885, "b") == False)
    assert (is_invalid_product_id(1231123123, "b") == False)
    assert(solve_part(product_id_range_list, "b") == 4174379265)

    print("All Test Passed!")
    return True

def main():
    filename = input("Enter the filename: ")
    with open(filename, 'r') as file:
        start_time = time.time()
        product_range_list = file.read()
        print("partA:", solve_part(product_range_list, "a"))
        print("partB:", solve_part(product_range_list, "b"))
        print("--- %s seconds ---" % (time.time() - start_time))
    return True

if __name__ == "__main__":
    if DEBUG:
        test_functions()
    main()

