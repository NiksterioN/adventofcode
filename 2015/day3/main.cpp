#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <utility>
#include <cassert>

using Point = std::pair<int, int>;

// Moves the point north (^), south (v), east (>), or west (<)
Point movePoint(const Point& point, const char& direction)
{
    Point currentPoint = point;
    switch (direction)
    {
    case '^':
        ++currentPoint.second;
        break;
    case 'v':
        --currentPoint.second;
        break;
    case '<':
        --currentPoint.first;
        break;
    case '>':
        ++currentPoint.first;
        break;
    default:
        break;
    }
    return currentPoint;
}

// Returns a vector containing the visited points in std::pair<x, y>
std::vector<Point> createVisitedPoints(const std::string& listOfDirection)
{
    Point currentPoint(0, 0);
    std::vector<Point> listOfPoints({ currentPoint });
    listOfPoints.reserve(listOfDirection.size());

    for (const char& direction : listOfDirection)
    {
        Point newPoint = movePoint(currentPoint, direction);
        listOfPoints.push_back(newPoint);
        currentPoint = newPoint;
    }

    return listOfPoints;
}

bool testFunctions()
{
    const std::string testDirectionA = "^";
    const std::string testDirectionB = "^v";
    const std::string testDirectionC = "";

    assert(movePoint(Point(0, 0), '^') == Point(0, 1));
    assert(movePoint(Point(0, 0), 'v') == Point(0, -1));
    assert(movePoint(Point(0, 0), '<') == Point(-1, 0));
    assert(movePoint(Point(0, 0), '>') == Point(1, 0));

    assert(createVisitedPoints(testDirectionA) == std::vector<Point>({ Point(0, 0), Point(0, 1) }));
    assert(createVisitedPoints(testDirectionB) == std::vector<Point>({ Point(0, 0), Point(0, 1), Point(0, 0) }));
    assert(createVisitedPoints(testDirectionC) == std::vector<Point>({ Point(0, 0) }));
    return true;
}

// Returns TRUE if the number is even, otherwise returns FALSE.
inline bool isEven(const int &n)
{
    return n % 2;
}

int main(void)
{
    //    testFunctions();
    std::string listOfDirection;
    std::cin >> listOfDirection;

    std::vector<Point> listOfVisitedPoints = createVisitedPoints(listOfDirection);

    std::set<Point> listOfUniqueVisitedPoints(listOfVisitedPoints.begin(), listOfVisitedPoints.end());
    std::cout << "Santa delivered at least " << listOfUniqueVisitedPoints.size() << " presents." << std::endl;

    //Santa and Robo-Santa start at the same location (delivering two presents to the same starting house), then take turns moving based on instructions

    std::string listOfSantaDirection;
    std::string listofRoboSantaDirection;
    for (int i = 0; i < listOfDirection.size(); ++i)
    {
        if (isEven(i)) listofRoboSantaDirection += listOfDirection[i];
        else listOfSantaDirection += listOfDirection[i];
    }

    std::vector<Point> listOfSantaVisitedPoints = createVisitedPoints(listOfSantaDirection);
    std::vector<Point> listOfRoboSantaVisitedPoints = createVisitedPoints(listofRoboSantaDirection);

    std::set<Point> listOfBothUniqueVisitedPoints(listOfSantaVisitedPoints.begin(), listOfSantaVisitedPoints.end());
    listOfBothUniqueVisitedPoints.insert(listOfRoboSantaVisitedPoints.begin(), listOfRoboSantaVisitedPoints.end());

    std::cout << "Santa and Robo-Santa delivered at least " << listOfBothUniqueVisitedPoints.size() << " presents." << std::endl;

    return 0;
}
