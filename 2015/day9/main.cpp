#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <sstream>
#include <cassert>
#include <numeric>
#include <algorithm>

#define NODES 30


std::vector<std::pair<int, int> > nodeGraph[NODES]; 
std::map<std::string, int> nameToNodeGraph;             // {{"NodeA" : 0}, {"NodeB", 1}}

std::vector<int> allDistance[NODES];
/*!
 *  Parses the nodes for operation.
 *
 *      @param [in] node - String Node
 *      @note Node must be in the format : XXXX to YYYYY = AAAA,
 *      where   XXXX and YYY are location,
 *              AAAA is the distance between both location,
 */
static void parseNodes(const std::string& node)
{
    std::istringstream iss(node);
    std::string word;

    std::vector<std::string> wordList;
    while (iss >> word)
        wordList.push_back(word);
    

    std::string originCity = wordList[0];
    std::string destinationCity = wordList[2];
    int distance = std::stoi(wordList[4]);
   
   static int nodeCounter = 0;
    if (nameToNodeGraph.count(wordList[0]) == 0)
    {   
        nameToNodeGraph[wordList[0]] =  nodeCounter;
        ++nodeCounter;
    }

    if (nameToNodeGraph.count(wordList[2]) == 0)
    {
        nameToNodeGraph[wordList[2]] = nodeCounter;
        ++nodeCounter;
    }

    // Undirected Graph 
    nodeGraph[nameToNodeGraph[originCity]].push_back(std::make_pair(nameToNodeGraph[destinationCity], distance));
    nodeGraph[nameToNodeGraph[destinationCity]].push_back(std::make_pair(nameToNodeGraph[originCity], distance));

}

static int nodeDepth = 0;

/**
    @brief  Sums all the distance between node to node
    @param  nodePath - 
    @retval          - 
**/
static int crawlNodePath(const std::vector<int> &nodePath)
{
    int sumDistance = 0;
    for (auto it = nodePath.begin(); it != nodePath.end(); ++it)
    {
        for (auto& node : nodeGraph[*it])
        {
            // check if the next node in nodePath is connected to the current node
            if ((it + 1 != nodePath.end()) && node.first == *(it + 1))
            {
                sumDistance += node.second;
            }
        }
    }
    return sumDistance;
}
}

/**
    @brief  Generates all possible permutations for the given nodes
    @param  node -
    @retval      -
**/
static int generateNodePath(const int node)
{
    std::vector<int> nodes;
    for (int i = 0; i <nameToNodeGraph.size(); ++i)
        nodes.push_back(i);

    int minDistance = 999;
    do
    {
        minDistance = std::min(minDistance, crawlNodePath(nodes));
        /*
        for (auto i : nodes)
            std::cout << i;
        std::cout << "\n";*/
    }while(std::next_permutation(nodes.begin(), nodes.end()));

    return minDistance;
}
/**
    @brief  Generates all possible permutations for the given nodes
    @param  node - 
    @retval      - 
**/
static int generateNodePathB(const int node)
{
    std::vector<int> nodes;
    for (int i = 0; i < nameToNodeGraph.size(); ++i)
        nodes.push_back(i);

    int maxDistance = 0;
    do
    {
        maxDistance = std::max(maxDistance, crawlNodePath(nodes));
        /*
        for (auto i : nodes)
            std::cout << i;
        std::cout << "\n";*/
    } while (std::next_permutation(nodes.begin(), nodes.end()));

    return maxDistance;
}

static bool testFunctions()
{
    std::string nodeA("London to Dublin = 464");
    std::string nodeB("London to Belfast = 518");
    std::string nodeC("Dublin to Belfast = 141");
    std::vector<std::string> nodeList{nodeA, nodeB, nodeC};
    
    for (auto i : nodeList)
        parseNodes(i);

    generateNodePath(0);


    return true;
}
int main()
{
    //testFunctions();

    std::vector <std::string > wordList;
    std::string word;
    wordList.reserve(100);
    while (getline(std::cin, word))
        wordList.push_back(word);

    for (const auto& w : wordList)
        parseNodes(w);

    std::cout << "Min Distance: " << generateNodePath(0) << "\n";
    std::cout << "Max Distance: " << generateNodePathB(0) << "\n";

    return 0;

}
