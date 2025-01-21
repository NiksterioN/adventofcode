#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <cassert>
#include <cctype>

using Point = std::pair<int, int>;
using PointStateMap = std::map<Point, int>;

// Returns true if PointStateMap initialization is done
static bool initializePointStateMap(PointStateMap &pMap, 
									const int &numberOfRows, 
									const int &numberOfColumns,  
									const int &allInitialState = 0)
{

	for (int x = 0; x < numberOfColumns; ++x)
	{
		for (int y = 0; y < numberOfRows; ++y)
			pMap.insert({ std::make_pair(x, y), allInitialState });
	}

	return true;
}


// Returns TRUE if an instruction is successfully executed, otherwise returns FALSE.
static bool executeInstructionSetA(const std::string &instruction, const Point &currentPoint, PointStateMap &pMap)
{
	if (instruction.find("on") != std::string::npos)
		pMap[currentPoint] = true;
	else if (instruction.find("off") != std::string::npos)
		pMap[currentPoint] = false;
	else if (instruction.find("toggle") != std::string::npos)
		pMap[currentPoint] = !(pMap[currentPoint]);
	else
	{
		std::cerr << "No keyword matching [on, off, toggle] found.";
		return false;
	}

	return true;
}

// Returns TRUE if an instruction is successfully executed, otherwise returns FALSE.
/*
The phrase turn on actually means that you should increase the brightness of those lights by 1.
The phrase turn off actually means that you should decrease the brightness of those lights by 1, to a minimum of zero.
The phrase toggle actually means that you should increase the brightness of those lights by 2.
*/
static bool executeInstructionSetB(const std::string& instruction, const Point& currentPoint, PointStateMap& pMap)
{
	if (instruction.find("on") != std::string::npos)
		pMap[currentPoint] += 1;
	else if (instruction.find("off") != std::string::npos)
	{
		if (pMap[currentPoint] > 0) pMap[currentPoint] -= 1;
	}
	else if (instruction.find("toggle") != std::string::npos)
		pMap[currentPoint] += 2;
	else
	{
		std::cerr << "No keyword matching [on, off, toggle] found.";
		return false;
	}

	return true;
}
// Returns by reference the startPoint and stopPoint in a given instruction
static bool parsePointInstruction(const std::string& instruction, Point& startPoint, Point& stopPoint)
{
	std::regex word_regex("(\\d+,\\d+)");
	auto words_begin = std::sregex_iterator(instruction.begin(), instruction.end(), word_regex);
	auto words_end = std::sregex_iterator();

	std::vector<std::pair<int, int>> pairVector;
	pairVector.reserve(2);
	for (std::sregex_iterator i = words_begin; i != words_end; ++i)
	{
		std::smatch match = *i;
		std::string strmatch = match.str();

		std::size_t commaIndex = strmatch.find(',');
		int x = std::stoi(strmatch.substr(0, commaIndex));
		int y = std::stoi(strmatch.substr(commaIndex + 1, strmatch.length() - commaIndex));

		pairVector.emplace_back(x, y);
	}

	startPoint = pairVector[0];
	stopPoint = pairVector[1];

	return true;
}


/*
 * Returns the final state of all points after executing instruction list
 * For example :
 * 
 * turn on 0, 0 through 999, 999 would turn on(or leave on) every light.
 * toggle 0, 0 through 999, 0 would toggle the first line of 1000 lights, turning off the ones that were on, and turning on the ones that were off.
 * turn off 499, 499 through 500, 500 would turn off(or leave off) the middle four lights.
*/
static PointStateMap executeInstructionList(const std::vector<std::string>& instructionList, bool (*executeInstructionSetB)(const std::string& instruction, const Point& currentPoint, PointStateMap& pMap))
{
	PointStateMap pMap;
	initializePointStateMap(pMap, 1000, 1000);

	for (const auto& instruction : instructionList)
	{
		Point currentPoint, startPoint, endPoint;
		parsePointInstruction(instruction, startPoint, endPoint);
		for (int i = startPoint.first; i <= endPoint.first; ++i)
		{
			for (int j = startPoint.second; j <= endPoint.second; ++j)
				executeInstructionSetB(instruction, std::make_pair(i, j), pMap);
		}
	}

	return pMap;
}

// Counts the number of ON states in a given PointStateMap
static int countNumberOfOnStates(const PointStateMap& pMap)
{
	int numberOfOnStates = 0;
	for (auto it = pMap.begin(); it != pMap.end(); ++it)
	{
		numberOfOnStates += it->second;
	}
	return numberOfOnStates;
}



static bool testFunctions()
{
	std::string instructionA("turn on 0,0 through 999,999");
	std::string instructionB("toggle 0,0 through 999,0");
	std::string instructionC("turn off 499,499 through 500,500");

	std::vector<std::string> instructionList{ { instructionA, instructionB, instructionC } };

	Point a(0, 0);
	Point b(0, 1);
	Point c(1, 0);

	PointStateMap pMap{ {a, true}, {b, false}, {c, true} };
	
	assert(countNumberOfOnStates(pMap) == 2);

	std::cout << __func__ << ": Test Pass" << std::endl;

	return true;
}


int main(void)
{
	testFunctions();

	std::vector<std::string> instructionList;
	std::string instruction;
	instructionList.reserve(100);
	while (std::getline(std::cin, instruction))
	{
		instructionList.push_back(instruction);
	}

	std::cout << "PartA: " << countNumberOfOnStates(executeInstructionList(instructionList, executeInstructionSetA)) << std::endl;
	std::cout << "PartB: " << countNumberOfOnStates(executeInstructionList(instructionList, executeInstructionSetB)) << std::endl;

	return 0;
}