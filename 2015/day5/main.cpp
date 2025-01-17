#include <iostream>
#include <cctype>
#include <cassert>
#include <string>
#include <vector>
#include <set>

// Returns TRUE if a character is a vowel, otherwise returns FALSE
static bool isVowel(const char &c)
{
    const char tempChar = tolower(c);
    return (tempChar == 'a' || tempChar == 'e' || tempChar == 'i' || tempChar == 'o' || tempChar == 'u');
}

// Returns TRUE if a string contains at least N vowels, otherwise returns FALSE
static bool containsNVowels(const std::string &word, const int n)
{
    int vowelCount = 0;
    for (const char& c : word)
    {
        if (isVowel(c))
            ++vowelCount;
        if (vowelCount == n)
            return true;
    }
    return false;
}

// Returns TRUE if a string contains a pair of any two same letters with N letters in between
static bool containsNLettersBetweenXLetters(const std::string &word, const int &n)
{
    const int indexDifference = n + 1;
    for (std::size_t currentIndex = 0; currentIndex < word.length() - 1; ++currentIndex)
    {
        char currentChar = word[currentIndex];
        std::size_t secondIndex = word.find(currentChar, currentIndex + 1);

        if ((secondIndex - currentIndex) == indexDifference)
            return true;
    }
   
    return false;
}

// Returns TRUE if a string contains XX Letters, otherwise returns FALSE
static bool containsXXLetters(const std::string& word)
{
    static std::vector<std::string> listOfExcludedWords{ {"ab"}, {"cd"}, {"pq"}, {"xy"} };
    bool wordFlag = false;
    for (const auto &excludedWords : listOfExcludedWords)
    {
        if (word.find(excludedWords) != std::string::npos)
            wordFlag = true;
    }

    return wordFlag;
}

// Returns TRUE if a string is nice, otherwise FALSE.
/*
A "nice" string is one with all of the following properties:

    It contains at least three vowels (aeiou only), like aei, xazegov, or aeiouaeiouaeiou.
    It contains at least one letter that appears twice in a row, like xx, abcdde (dd), or aabbccdd (aa, bb, cc, or dd).
    It does not contain the strings ab, cd, pq, or xy, even if they are part of one of the other requirements

Otherwise, the string is as a "naughty" string
*/
static bool isNiceString(const std::string &word)
{   
    return containsNVowels(word, 3) && containsNLettersBetweenXLetters(word, 0) && !containsXXLetters(word);
}

// Returns the number of nice strings in a listOfString
static int countNiceString(const std::vector<std::string> listOfString)
{
    int niceStringCounter = 0;
    
    for (const auto& word : listOfString)
    {
        if (isNiceString(word))
            ++niceStringCounter;
    }

    return niceStringCounter;
}

static bool testFunctionPartA()
{
    std::string wordA("ugknbfddgicrmopn");  // nice
    std::string wordB("aaa");               // nice    
    std::string wordC("jchzalrnumimnmhp");  // naughty
    std::string wordD("haegwjzuvuyypxyu");  // naughty
    std::string wordE("dvszwmarrgswjxmb");  // naughty

    std::vector<std::string> lowA{wordA, wordB, wordC, wordD, wordE};

    assert(containsNVowels(wordA, 2) == true);
    assert(containsNVowels(wordE, 2) == false);

    assert(containsNLettersBetweenXLetters(wordA, 0) == true);
    assert(containsNLettersBetweenXLetters(wordC, 0) == false);

    assert(containsXXLetters(wordA) == false);
    assert(containsXXLetters(wordD) == true);


    assert(isNiceString(wordA) == true);
    assert(isNiceString(wordB) == true);
    assert(isNiceString(wordC) == false); // no double letter
    assert(isNiceString(wordD) == false); // contains string xy
    assert(isNiceString(wordE) == false); // contains only one vowel

    assert(countNiceString(lowA) == 2);

    std::cout << __func__ << ": Test Pass" << std::endl;
    return true;
}

// Returns TRUE if a string contains a pair of any two letters
// that appears at least twice in the string without overlapping
// Otherwise, returns FALSE
static bool containsTwoXXLetters(const std::string &word)
{
    return true;
}

static bool testFunctionPartB()
{
    std::string wordA("qjhvhtzxzqqjkmpb");  // nice
    std::string wordB("xxyxx");             // nice
    std::string wordC("uurcxstgmygtbstg");  // naughty
    std::string wordD("ieodomkazucvgmuy");  // naughty

    assert(containsNLettersBetweenXLetters("xyxy", 1) == true);
    assert(containsNLettersBetweenXLetters("aaa", 1) == false);

    std::cout << __func__ << ": Test Pass" << std::endl;

    return true;
}



int main()
{
    //testFunctionPartA();
    testFunctionPartB();
    std::vector<std::string> listOfString;
    listOfString.reserve(1000);
    std::string direction;
    while (std::cin >> direction)
    {
        listOfString.push_back(direction);
    }
    
    std::cout << "Nice Strings:  " << countNiceString(listOfString) << std::endl;

    return 0;
}
