#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cctype>
#include <sstream>
#include <algorithm>

static std::map<std::string, int> outputMap;
static std::map<std::string, std::vector<std::string> > instructionMap;

// Returns TRUE if the string is a number, otherwise returns FALSE
static bool is_digits(const std::string& str)
{
    return std::all_of(str.begin(), str.end(), std::isdigit);
}

// Sorts the current instruction whether a constant or another instruction
static void parseInstruction(const std::string& instruction)
{
    std::vector<std::string> wordList;
    wordList.reserve(10);

    std::istringstream iss(instruction);
    std::string word;
    while (iss >> word)
        wordList.push_back(word);

    std::string wire = wordList.back();
    if (outputMap.count(wire) == 0) // Do not override value, if explicitly stored
    {
        if (wordList.size() == 3 && is_digits(wordList[0])) //Checks if integer or variable 
            outputMap[wire] = std::stoi(wordList[0]);
        else
            instructionMap[wire] = std::vector<std::string>(wordList.begin(), wordList.end() - 2);
    }

}

// Recursively solve the instruction until the operands are both constants
static int solveWire(std::string wire)
{

    if (outputMap.count(wire) == 0) // No results/ Not yet calculated
    {

        std::vector<std::string> instructionSet = instructionMap[wire];
        std::size_t instructionLength = instructionSet.size();

        if (instructionLength == 3) // x AND y
        {
            std::string bitA = instructionSet[0];
            std::string operation = instructionSet[1];
            std::string bitB = instructionSet[2];

            if (operation == "AND") outputMap[wire] = solveWire(bitA) & solveWire(bitB);
            else if (operation == "OR") outputMap[wire] = solveWire(bitA) | solveWire(bitB);
            else if (operation == "LSHIFT") outputMap[wire] = solveWire(bitA) << std::stoi(bitB);
            else if (operation == "RSHIFT") outputMap[wire] = solveWire(bitA) >> std::stoi(bitB);

        }
        else if (instructionLength == 2) // not x
        {
            std::string bitA = instructionSet[1];
            outputMap[wire] = ~solveWire(bitA) & 0xFFFF;
        }
        else if (instructionLength == 1)  // Variables
        {
            std::string bitA = instructionSet[0];
            outputMap[wire] = solveWire(bitA);
        }
        else if (instructionLength == 0) // Constants 
        {
            return std::stoi(wire);
        }

    }
    else
    {
        return outputMap[wire];
    }

    return outputMap[wire];
}

// Solve wire with the given list of wire instructions
// Part A : 
// Solve for wire A
static int connectWires(std::vector<std::string> &listOfInstructions, std::string wire)
{
    for (const auto& instruction : listOfInstructions)
        parseInstruction(instruction);

    return solveWire(wire);
}

// Solve wire with the given list of wire instructions
// Part B : 
// take the signal you got on wire a, 
// override wire b to that signal, 
// and reset the other wires (including wire a). 
// What new signal is ultimately provided to wire a?
static int connectWiresB(std::vector<std::string>& listOfInstructions, std::string wire)
{
    for (const auto& instruction : listOfInstructions)
        parseInstruction(instruction);

    int wireA = solveWire("a");

    instructionMap.clear();
    outputMap.clear();

    outputMap["b"] = wireA;
    
    for (const auto& instruction : listOfInstructions)
        parseInstruction(instruction);

    return solveWire(wire);
}

int main()
{

    std::vector<std::string> wireInstruction;
    std::string instruction;
    while (std::getline(std::cin, instruction))
        wireInstruction.push_back(instruction);


    std::cout << "Part A : a" << " : " << connectWires(wireInstruction, "a") << std::endl;
    std::cout << "Part B : a" << " : " << connectWiresB(wireInstruction, "a") << std::endl;

	return 0;
}