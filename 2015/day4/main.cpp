#include <iostream>
#include <string>
#include <cassert>
#include "src/hashlibpp.h"

// Returns the MD5 hash of a given string
static std::string generateMD5Hash(const std::string &key)
{
	hashwrapper* h = new md5wrapper();
	std::string md5 = h->getHashFromString(key);

	delete h;
	return md5;
}

// Returns the lowest positive number with an MD5 Hash starting with "matchString"
static long findLowestPositiveHashNumber(const std::string &key, const std::string &matchString)
{
	long startNum = -1;
	std::string newMD5Hash, combinationKey;
	
	do
	{
		++startNum;
		combinationKey = key + std::to_string(startNum);
		newMD5Hash = generateMD5Hash(combinationKey);
	} while (newMD5Hash.substr(0, matchString.length()) != matchString);

	return startNum;

}

static bool testFunctions()
{
	std::string keyA = "abcdef";
	std::string keyB = "pqrstuv";

	assert(findLowestPositiveHashNumber(keyA, std::string("00000")) == 609043);
	assert(findLowestPositiveHashNumber(keyB, std::string("00000")) == 1048970);

	return true;
}

int main(void)
{
	//testFunctions();
	std::string secretKey;
	std::cout << "Input Key: " << std::endl;
	std::cin >> secretKey;

	std::cout << "Lowest Positive Hash Number with MD5 starting at 00000: " << findLowestPositiveHashNumber(secretKey, std::string("00000")) << std::endl;
	std::cout << "Lowest Positive Hash Number with MD5 starting at 000000: " << findLowestPositiveHashNumber(secretKey, std::string("000000")) << std::endl;
	
	return 0;
}