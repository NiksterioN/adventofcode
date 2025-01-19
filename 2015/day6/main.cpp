#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <cassert>

using Point = std::pair<int, int>;
using PointStateMap = std::map<Point, bool>;
/*
To defeat your neighbors this year, all you have to do is set up your lights by doing the instructions Santa sent you in order.

For example :

turn on 0, 0 through 999, 999 would turn on(or leave on) every light.
toggle 0, 0 through 999, 0 would toggle the first line of 1000 lights, turning off the ones that were on, and turning on the ones that were off.
turn off 499, 499 through 500, 500 would turn off(or leave off) the middle four lights.
*/
static bool updatePointStateMap(const std::string &word)
{
	
	return true;
}

static bool initializePointStateMap(PointStateMap &pMap, 
									const int &numberOfRows, 
									const int &numberOfColumns,  
									const int &allInitialState = 0)
{

	for (int i = 0; i < 1000; ++i)
	{
		for (int j = 0; j < 1000; ++j)
			pMap.insert({ std::make_pair(i, j), false });
	}

	return true;
}


static bool executeInstruction(const std::string &word, const Point &p, PointStateMap &pMap)
{

	if (word.find("on") != std::string::npos)
	{
		pMap.find(p);
	}
	else if (word.find("off") != std::string::npos)
	{

	}
	else if (word.find("off") != std::string::npos)
	{

	}
	else
	{
		std::cerr << "No keyword matching [on, off, toggle] found.";
	}
	return true;
}

static PointStateMap executeInstructionList(const std::vector<std::string>& instructionList)
{
	//PointStateMap pMap = initializePointStateMap(1000, 1000);
	PointStateMap pMap;
	initializePointStateMap(pMap, 1000, 1000);
	//parseInstruction();

	Point currentPoint;

	for (const auto& instruction : instructionList)
	{
		executeInstruction(instruction, currentPoint, pMap);
	}

	return pMap;
}

static int countNumberOfOnStates(const PointStateMap& pMap)
{

	return 0;
}

static bool testFunctions()
{
	std::string instructionA("turn on 0,0 through 999,999");
	std::string instructionB("toggle 0,0 through 999,0");
	std::string instructionC("turn off 499,499 through 500,500");
	std::vector<std::string> instructionList{ { instructionA, instructionB, instructionC } };


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

	//executeInstructionList(instructionList);

	return 0;
}