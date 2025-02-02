#include <iostream>
#include <cmath>
#include "geometry.h"
#include "matlib.h"
#include "testing.h"

double getArea(double radius)
{
    // Print the radius value if debugging is enabled
    DEBUG_PRINT("Radius = " + std::to_string(radius));
    // Check if the radius is negative and throw an exception if it is
    if (radius < 0)
    {
        throw std::invalid_argument("Radius cannot be negative");
    }
    // Compute the area and print the result if debugging is enabled
    double area = PI * pow(radius, 2.0);
    DEBUG_PRINT("Result = " + std::to_string(area)); // Print the computed area
    return area;
}

double getCircumference(double radius)
{
    // Print the radius value if debugging is enabled
    DEBUG_PRINT("Radius = " + std::to_string(radius));
    // Check if the radius is negative and throw an exception if it is
    if (radius < 0)
    {
        throw std::invalid_argument("Radius cannot be negative");
    }
    // Compute the area and print the result if debugging is enabled
    double circumference = 2 * PI * radius;
    DEBUG_PRINT("Result = " + std::to_string(circumference)); // Print the computed circumference
    return circumference;
}

///////////////////////////////////////////////
//
//   TESTS
//
///////////////////////////////////////////////

static void testArea()
{
    // general case, e.g. radius = 1, radius = 5, radius = 10
    ASSERT_APPROX_EQUAL(getArea(1), 3.14159265358979, 1e-7);
    ASSERT_APPROX_EQUAL(getArea(5), 78.5398163397447, 1e-7);
    ASSERT_APPROX_EQUAL(getArea(10), 314.159265358979, 1e-7);

    // small radius, e.g. r = 1e-4
    ASSERT_APPROX_EQUAL(getArea(1e-4), 0, 1e-7);

    // large radius, e.g. r = 1e6
    ASSERT_APPROX_EQUAL(getArea(1e6), 3141592653589.79, 1e-2);

    /* boundary cases */
    // zero radius, i.e. r = 0
    ASSERT_APPROX_EQUAL(getArea(0), 0, 1e-7);

    // floating point precision, e.g. r = 2.5
    ASSERT_APPROX_EQUAL(getArea(2.5), 19.6349540849362, 1e-7);
    ASSERT_APPROX_EQUAL(getCircumference(2.5), 15.7079632679489, 1e-7);
    // edge case, r = pi
    ASSERT_APPROX_EQUAL(getArea(PI), 31.0062766802997, 1e-7);
}

static void testCircumference()
{
    // general case, e.g. radius = 1, radius = 5, radius = 10
    ASSERT_APPROX_EQUAL(getCircumference(1), 6.28318530717958, 1e-7);
    ASSERT_APPROX_EQUAL(getCircumference(5), 31.4159265358979, 1e-7);
    ASSERT_APPROX_EQUAL(getCircumference(10), 62.8318530717958, 1e-7);

    // small radius, e.g. r = 1e-4
    ASSERT_APPROX_EQUAL(getCircumference(1e-7), 0, 1e-6);
    // large radius, e.g. r = 1e6
    ASSERT_APPROX_EQUAL(getCircumference(1e6), 6283185.30717958, 1e-7);

    /* boundary cases */
    // zero radius, i.e. r = 0
    ASSERT_APPROX_EQUAL(getCircumference(0), 0, 1e-7);

    // floating point precision, e.g. r = 2.5
    ASSERT_APPROX_EQUAL(getCircumference(2.5), 15.7079632679489, 1e-7);
    // edge case, r = pi
    ASSERT_APPROX_EQUAL(getCircumference(PI), 19.7392088021787, 1e-7);
}

void testGeometry()
{
    TEST(testArea);
    TEST(testCircumference);
}