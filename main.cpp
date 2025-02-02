#include "matlib.h"
#include "geometry.h"
#include "charts.h"

using namespace std;

int main()
{
    setDebugEnabled(true);
    testMatlib();
    testGeometry();
    testCharts();
    // testUsageExamples();
    std::vector<double> xValues{60, 70, 80, 90, 100, 110, 120, 130, 140};
    std::vector<double> yValues{};
    for (size_t i{0}; i < xValues.size(); i++)
    {
        yValues.push_back(blackScholesCallPrice(100,
                                                1,
                                                xValues[i],
                                                0.2,
                                                0.5));
    }
    plot("blackScholesCallPrices.html", xValues, yValues);
}