#pragma once

#include "stdafx.h"

const double PI = 3.14159265358979;

/**
 *  Computes the cumulative
 *  distribution function of the
 *  normal distribution
 */
double normcdf(double x);

/**
 *  Computes the inverse of normcdf
 */
double norminv(double x);

/**
 * Computes the price of a European call option
 */
double blackScholesCallPrice(const double &strike,
                             const double &maturity,
                             const double &spot,
                             const double &volatility,
                             const double &rate);
/**
 * Computes the price of a European put option
 */
double blackScholesPutPrice(const double &strike,
                            const double &maturity,
                            const double &spot,
                            const double &volatility,
                            const double &rate);
/**
 * Computes the roots of a quadratic polynomial
 */
std::vector<double> solveQuadratic(const double &a,
                                   const double &b,
                                   const double &c);

/**
 * Computes the mean of a vector of doubles
 */
double mean(const std::vector<double> &numbers);

/**
 * Computes the standard deviation of a vector of doubles.  Default is sample standard deviation
 */
double standardDeviation(const std::vector<double> &numbers, bool sample = true);

/**
 * Take a vector of doubles and return the min
 */
double min(const std::vector<double> &numbers);

/**
 * Take a vector of doubles and return the max
 */
double max(const std::vector<double> &numbers);

/**
 * returns a vector of uniformly distributed random numbers in the range (0,1)
 */
std::vector<double> randuniform(int n);

/**
 * returns a vector of normally distributed random numbers with mean 0 and standard deviation 1
 */
std::vector<double> randn(int n);

/**
 * An alternative way to generate normally distributed random numbers using the Box–Muller algorithm
 */
std::vector<double> boxMullerNormal(int n);

/**
 * Takes as input a vector of doubles v and a percentile p and outputs the p-th percentile
 */
double prctile(const std::vector<double> &v, double p);

/**
 *  Test function
 */
void testMatlib();