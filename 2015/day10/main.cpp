#include <iostream>
#include <vector>
#include <string>
#include <cassert>

/*!
 *  Generates the look and say sequence.
 * 
 *
 *      @param [in] sequence The seed sequence to generate the Look And Say Sequence
 *      @return The generated Look and Say Sequence
 *      @notes
 *      Look-and-say sequences are generated iteratively, using the previous value as input for the next step. For each step, take the previous value, and replace each run of digits (like 111) with the number of digits (3) followed by the digit itself (1).
 *		For example:
 *
 *			1 becomes 11 (1 copy of digit 1).
 *			11 becomes 21 (2 copies of digit 1).
 *			21 becomes 1211 (one 2 followed by one 1).
 *			1211 becomes 111221 (one 1, one 2, and two 1s).
 *			111221 becomes 312211 (three 1s, two 2s, and one 1).
 *
 */
static std::string generateLookAndSaySequence(const std::string& sequence)
{
	std::string nextSeq = "";
	int numCounter = 0;
	char currentChar;
	for (auto it = sequence.begin(); it != sequence.end(); ++it)
	{
		currentChar = *it;
		while (it != sequence.end() && currentChar == *it)
		{
			++numCounter;
			++it;
		}
		nextSeq += std::to_string(numCounter);
		nextSeq += std::to_string(currentChar - '0');
		numCounter = 0;
		--it;
	}
	return nextSeq;
}
/*!
 *  Generates the Look And Say Sequence iteratively using a seed sequence.
 *
 *      @param [in] sequence 
 *      @param [in] iterNum  
 *
 *      @return 
 */
static std::string generateLASS(const std::string& sequence, const int& iterNum)
{
	std::string nextSeq = sequence;
	for (int i = 0; i < iterNum; ++i)
	{
		nextSeq = generateLookAndSaySequence(nextSeq);
	}
	return nextSeq;
}
/*!
 *  Tests the functions.
 *
 *      @return 
 */
static bool testFunctions()
{
	std::string seqA("1");
	std::string seqB("11");
	std::string seqC("21");
	std::string seqD("1211");

	assert(generateLookAndSaySequence(seqA) == "11");
	assert(generateLookAndSaySequence(seqB) == "21");
	assert(generateLookAndSaySequence(seqC) == "1211");
	assert(generateLookAndSaySequence(seqD) == "111221");

	assert(generateLASS(seqA, 1) == seqB);
	assert(generateLASS(seqA, 3) == seqD);

	std::cout << __func__ << "(): Test Pass" << std::endl;

	return true;
}

int main()
{
	//testFunctions();
	
	std::cout << "Seed Sequence : " << std::endl;
	std::string seedSeq;
	std::cin >> seedSeq;
	std::cout << "Part 1 : " << generateLASS(seedSeq, 40).size() << std::endl;
	std::cout << "Part 2 : " << generateLASS(seedSeq, 50).size() << std::endl;

	return 0;
}