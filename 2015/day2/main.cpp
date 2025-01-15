#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>

// Returns the volume of a box
int calculateBoxVolume(const int &l, const int &w, const int &h)
{
    return l*w*h;
}

// Returns a vector containing the three distinct face area of a box
std::vector<int> calculateSideArea(const int &l, const int &w, const int&h)
{
    std::vector<int> sideArea = {(l*w), (w*h), (h*l)};
    return sideArea;
}

// Returns the total surface area of a box
int calculateTotalSurfaceArea(const std::vector<int> &sideArea)
{
    int totalSurfaceArea = 0;

    for (auto it = sideArea.begin(); it != sideArea.end(); ++it)
        totalSurfaceArea += *it*2;
    return totalSurfaceArea;
}

int calculateRequiredWrappingPaper(const int &l, const int &w, const int &h)
{
    std::vector<int> sideArea = calculateSideArea(l, w, h);
    int totalSurfaceArea = calculateTotalSurfaceArea(sideArea);
    int smallestSurfaceArea = *std::min_element(sideArea.begin(), sideArea.end());

    return  totalSurfaceArea + smallestSurfaceArea;
}

// Returns the shortest distance around its side plus the volume of the present
int calculateRequiredRibbon(const int &l, const int &w, const int &h)
{
    std::vector<int> sideArea {l, w, h};
    std::sort(sideArea.begin(), sideArea.end());
    // calculate shortest distance around the box
    int totalPerimeter = 0;
    for (auto it = sideArea.begin(); it != sideArea.end()-1; ++it)
        totalPerimeter += *it*2;

    int boxVolume = calculateBoxVolume(l, w, h);

    return totalPerimeter + boxVolume;

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
