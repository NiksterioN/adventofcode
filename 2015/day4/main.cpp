#include <iostream>
#include <string>
#include <cassert>
#include "src/hashlibpp.h"

static std::string generateMD5Hash(const std::string &key)
{
	hashwrapper* h = new md5wrapper();
	std::string md5 = h->getHashFromString(key);

	delete h;
	return md5;
}

static long findLowestPositiveHashNumber(std::string key)
{
	long startNum = -1;
	std::string newMD5Hash, combinationKey;
	
	do
	{
		combinationKey = key + std::to_string(startNum);
		newMD5Hash = generateMD5Hash(combinationKey);
		++startNum;
	} while (newMD5Hash.substr(0, 5) != "00000");

	return startNum;

}

static bool testFunctions()
{
	std::string keyA = "abcdef";
	std::string keyB = "pqrstuv";


	assert(findLowestPositiveHashNumber(keyA) == 609043);
	assert(findLowestPositiveHashNumber(keyB) == 1048970);

	return true;
}

int main(void)
{
	//testFunctions();
	std::string secretKey;
	std::cout << "Input Key: " << std::endl;
	std::cin >> secretKey;

	//std::cout << generateMD5Hash(secretKey) << std::endl;
	std::cout << "Lowest Positive Hash Number with MD5 starting at 00000: " << findLowestPositiveHashNumber(secretKey) << std::endl;

	


	return 0;
}