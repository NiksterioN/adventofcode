#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>
#include <cctype>

std::vector<std::string> fetchWords(std::istream& is)
{
	std::vector<std::string> wordList;
	wordList.reserve(100);
	std::string word;
	while (getline(is, word))
		wordList.push_back(word);

	return wordList;
}

static int getEscapedStringLength(const std::string& word)
{
	std::size_t charCount = 0;
	for (auto it = word.begin() + 1; it != word.end() - 1; ++it)
	{
		const char currentChar = *it;
		if (std::isalpha(currentChar))
		{
			++charCount;
		}
		else if (currentChar == '\\')
		{
			// Peek at the next character
			const char nextChar = *(it + 1);
			if (nextChar == 'x')
			{
				++charCount;
				it = it + 3;
			}
			else
			{
				++charCount;
				++it;
			}
		}
	}
	return  charCount;
}

static int getEscapedStringLengthPartB(const std::string& word)
{
	std::size_t charCount = 6; // "" is always counted as 6
	for (auto it = word.begin() + 1; it != word.end() - 1; ++it)
	{
		const char currentChar = *it;
		if (std::isalpha(currentChar))
		{
			++charCount;
		}
		else if (currentChar == '\\')
		{
			// Peek at the next character
			const char nextChar = *(it + 1);
			if (nextChar == 'x')
			{
				charCount+= 5; // \\xAA is alaways 5 characters
				it = it + 3;
			}
			else
			{
				charCount += 4;// \\"\" is always 4 characters
				++it;
			}
		}
	}
	return  charCount;
}

static inline int getRawStringLength(const std::string& word)
{
	return word.size();
}


static int solvePuzzle(const std::vector<std::string>& wordList)
{
	int value = 0;
	for (const auto& word : wordList)
		value += (getRawStringLength(word) - getEscapedStringLength(word));
	return value;
}

static int solvePuzzlePartB(const std::vector<std::string>& wordList)
{
	int value = 0;
	for (const auto& word : wordList)
		value += (getEscapedStringLengthPartB(word) - getRawStringLength(word));
	return value;
}


static bool testFunctions()
{
	std::string wordA(R"("")");
	std::string wordB(R"("abc")");
	std::string wordC(R"("aaa\"aaa")");
	std::string wordD(R"("\x27")");

	assert(getRawStringLength(wordA) ==  2);
	assert(getRawStringLength(wordB) ==  5);
	assert(getRawStringLength(wordC) == 10);
	assert(getRawStringLength(wordD) ==  6);

	assert(getEscapedStringLength(wordA) == 0);
	assert(getEscapedStringLength(wordB) == 3);
	assert(getEscapedStringLength(wordC) == 7);
	assert(getEscapedStringLength(wordD) == 1);

	assert(getEscapedStringLengthPartB(wordA) == 6);
	assert(getEscapedStringLengthPartB(wordB) == 9);
	assert(getEscapedStringLengthPartB(wordC) == 16);
	assert(getEscapedStringLengthPartB(wordD) == 11);

	return 0;
}

int main()
{
	testFunctions();

	const auto wordList = fetchWords(std::cin);

	std::cout << "Part A : " << solvePuzzle(wordList);
	std::cout << "Part B : " << solvePuzzlePartB(wordList);
	return 0;
}