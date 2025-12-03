'''
See https://adventofcode.com/2025/day/1 for full details

Given:
    Numbered dials from 0 to 99,
    Dial starts by pointing at 50.

Required:
    PartA. Find the number of times the dial is left pointing at 0 after any rotation in the sequence.
    PartB. Find the sum between PartA and the number of times the dial points at 0 when rotating from A to B.
'''
DEBUG = False

def rotate_dial(current_dial, instruction):
    """
    Returns the next dial given instruction.
    Instruction format should be XYY, where
        X is a direction of rotation (Left or Right)
        Y is the number of rotations/ticks

    Ex. If dial is initially at 11, then R8 would cause the dial to point at 19.
        L19 would cause the dial to point at 0.
        If dial is initially at 5, then L10 would cause the dial to point at 95

    :param current_dial: The current number pointed by the dial
    :param instruction: The instruction containing the direction of rotation and number of rotations
    :return: (Integer: The next dial number, Integer: The number of rotations that crossed the number 0)
    """
    rotation_direction = instruction[0]
    rotation_number = int(instruction[1:])

    cross_counter = 0
    for move in range(rotation_number):
        if rotation_direction == 'R':
            current_dial = (current_dial + 1) % 100
        else:
            current_dial = (current_dial - 1) % 100
        if current_dial == 0:
            cross_counter += 1
    current_dial = current_dial % 100

    return current_dial, abs(cross_counter)


def get_number_dial_pointing_at_X(current_dial, instruction_set):
    total_pointer_counter = 0
    for instruction in instruction_set:
        current_dial, zero_cross_counter = rotate_dial(current_dial, instruction)

        if current_dial == 0:
            total_pointer_counter = total_pointer_counter + 1

    return total_pointer_counter


def get_number_dial_crossing_at_X(current_dial, instruction_set):
    total_pointer_counter = 0
    for instruction in instruction_set:
        current_dial, zero_cross_counter = rotate_dial(current_dial, instruction)

        total_pointer_counter = total_pointer_counter + zero_cross_counter

    return total_pointer_counter

def main():
    filename = input("Enter filename: ")
    with open(filename) as file:
        instruction_set = file.read().split()
        print(get_number_dial_pointing_at_X(50, instruction_set))
        print(get_number_dial_crossing_at_X(50, instruction_set))

def test_functions():

    # Right/CW Rotation
    current_dial, cross_counter = rotate_dial(11, 'R8')
    assert(current_dial == 19 and cross_counter == 0)
    current_dial, cross_counter = rotate_dial(19, 'L19')
    assert(current_dial == 0 and  cross_counter == 1)
    # Left/CCW Rotation
    current_dial, cross_counter = rotate_dial(5, 'L10')
    assert(current_dial == 95 and cross_counter == 1)
    current_dial, cross_counter = rotate_dial(0, 'R5')
    assert(current_dial == 5 and cross_counter == 0)

    instruction_set =  "L68\nL30\nR48\nL5\nR60\nL55\nL1\nL99\nR14\nL82".split()

    current_dial = 50
    assert(get_number_dial_pointing_at_X(current_dial, instruction_set) == 3)
    assert(get_number_dial_crossing_at_X(current_dial, instruction_set) == 6)

    print("All tests passed!")
    return True

if __name__ == "__main__":
    if DEBUG:
        test_functions()

    main()
