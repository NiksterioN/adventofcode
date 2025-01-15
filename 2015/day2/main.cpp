#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <cstdio>

// Returns the volume of a closed box
// Volume of Box = length * width * height
int calculateBoxVolume(const int &l, const int &w, const int &h)
{
    return l*w*h;
}

// Returns a vector containing the three distinct face area of a box
// Area = side1 * side2
std::vector<int> calculateSideArea(const int &l, const int &w, const int&h)
{
    std::vector<int> sideArea = {(l*w), (w*h), (h*l)};
    return sideArea;
}

// Returns the total surface area of a closed box
// Total Box Surface Area = 2 * (SA1 + SA2 + SA3)
int calculateTotalSurfaceArea(const std::vector<int> &sideArea)
{
    return 2 * std::accumulate(sideArea.begin(), sideArea.end(), 0);
}

// Returns the sum of the total box surface area and the smallest surface area (extra)
int calculateRequiredWrappingPaper(const int &l, const int &w, const int &h)
{
    std::vector<int> sideArea = calculateSideArea(l, w, h);
    int totalSurfaceArea = calculateTotalSurfaceArea(sideArea);

    int smallestSurfaceArea = *std::min_element(sideArea.begin(), sideArea.end());

    return  totalSurfaceArea + smallestSurfaceArea;
}

// Returns the smallest perimeter of one face
// Perimeter = 2*(side1+side2)
int calculateShortestPerimeter(const int &l, const int &w, const int &h)
{
    std::vector<int> sideLength {l, w, h};
    std::sort(sideLength.begin(), sideLength.end());

    return 2 * (sideLength[0] + sideLength[1]);
}

// Returns sum of the shortest distance around its side and the volume of the box
int calculateRequiredRibbon(const int &l, const int &w, const int &h)
{
    int shortestPerimeter = calculateShortestPerimeter(l, w, h);
    int boxVolume = calculateBoxVolume(l, w, h);

    return shortestPerimeter + boxVolume;
}

int main(void)
{
    int l, w, h;
    int totalWrappingPaper = 0;
    int totalRibbonLength = 0;
    while (std::scanf("%dx%dx%d", &l, &w, &h) == 3)
    {
        totalWrappingPaper += calculateRequiredWrappingPaper(l, w, h);
        totalRibbonLength += calculateRequiredRibbon(l, w, h);
    }

    std::cout << "Total Wrapping Paper (ft^3) needed: " << totalWrappingPaper << std::endl;
    std::cout << "Total Ribbon Paper (ft) needed: " << totalRibbonLength << std::endl;
    return 0;
}
