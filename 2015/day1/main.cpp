/*
--- Day 1: Not Quite Lisp ---

An opening parenthesis, (, means he should go up one floor, and a closing parenthesis, ), means he should go down one floor.

For example:

    (()) and ()() both result in floor 0.
    ((( and (()(()( both result in floor 3.
    ))((((( also results in floor 3.
    ()) and ))( both result in floor -1 (the first basement level).
    ))) and )())()) both result in floor -3.

*/

#include <iostream>
#include <string>
#include <algorithm>

// Returns the string index where the floorCounter is first encountered as -1, otherwise Returns -1 if not found.
static int findBasementIndex(std::string puzzleInput)
{
    signed floorCounter = 0;
    unsigned int puzzleInputPosIndex = 1;
    for (std::string::iterator it = puzzleInput.begin(); it != puzzleInput.end(); ++it)
    {
        char currentChar = *it;
        if (currentChar == '(') ++floorCounter;
        else if (currentChar == ')') --floorCounter;

        if (floorCounter < 0) return puzzleInputPosIndex;

        ++puzzleInputPosIndex;
    }
    return 0;
}

// Returns the sum of all floor directions in the given string
static int sumFloorInstruction(std::string puzzleInput)
{
    unsigned int upCounter   = std::count(puzzleInput.begin(), puzzleInput.end(), '(');
    unsigned int downCounter = std::count(puzzleInput.begin(), puzzleInput.end(), ')');
    int floorCounter = upCounter - downCounter;

    return floorCounter;
}

int main(void)
{
    std::string puzzleInput;
    std::cin >> puzzleInput;

    std::cout << "Floor: " << sumFloorInstruction(puzzleInput) << std::endl;
    std::cout << "Basement Index " << findBasementIndex(puzzleInput) << std::endl;

    return 0;
}
