#include "matlib.h"

const double ROOT_2_PI = sqrt(2.0 * PI);

static inline double hornerFunction(double x, double a0, double a1)
{
  return a0 + x * a1;
}

static inline double hornerFunction(double x, double a0, double a1, double a2)
{
  return a0 + x * hornerFunction(x, a1, a2);
}

static inline double hornerFunction(double x, double a0, double a1, double a2, double a3)
{
  return a0 + x * hornerFunction(x, a1, a2, a3);
}

static inline double hornerFunction(double x, double a0, double a1, double a2, double a3, double a4)
{
  return a0 + x * hornerFunction(x, a1, a2, a3, a4);
}

static inline double hornerFunction(double x, double a0, double a1, double a2, double a3, double a4,
                                    double a5)
{
  return a0 + x * hornerFunction(x, a1, a2, a3, a4, a5);
}

static inline double hornerFunction(double x, double a0, double a1, double a2, double a3, double a4,
                                    double a5, double a6)
{
  return a0 + x * hornerFunction(x, a1, a2, a3, a4, a5, a6);
}

static inline double hornerFunction(double x, double a0, double a1, double a2, double a3, double a4,
                                    double a5, double a6, double a7)
{
  return a0 + x * hornerFunction(x, a1, a2, a3, a4, a5, a6, a7);
}

static inline double hornerFunction(double x, double a0, double a1, double a2, double a3, double a4,
                                    double a5, double a6, double a7, double a8)
{
  return a0 + x * hornerFunction(x, a1, a2, a3, a4, a5, a6, a7, a8);
}

/**
 *  Arguably this is a little easier to read than the original normcdf
 *  function as it makes the use of horner's method obvious.
 */
double normcdf(double x)
{
  DEBUG_PRINT("normcdf(" << x << ")");
  if (x < 0)
  {
    return 1 - normcdf(-x);
  }
  double k = 1 / (1 + 0.2316419 * x);
  double poly = hornerFunction(k,
                               0.0, 0.319381530, -0.356563782,
                               1.781477937, -1.821255978, 1.330274429);
  double approx = 1.0 - 1.0 / ROOT_2_PI * exp(-0.5 * x * x) * poly;
  return approx;
}

/*  Constants required for Moro's algorithm */
static const double a0 = 2.50662823884;
static const double a1 = -18.61500062529;
static const double a2 = 41.39119773534;
static const double a3 = -25.44106049637;
static const double b1 = -8.47351093090;
static const double b2 = 23.08336743743;
static const double b3 = -21.06224101826;
static const double b4 = 3.13082909833;
static const double c0 = 0.3374754822726147;
static const double c1 = 0.9761690190917186;
static const double c2 = 0.1607979714918209;
static const double c3 = 0.0276438810333863;
static const double c4 = 0.0038405729373609;
static const double c5 = 0.0003951896511919;
static const double c6 = 0.0000321767881768;
static const double c7 = 0.0000002888167364;
static const double c8 = 0.0000003960315187;

double norminv(double x)
{
  // We use Moro's algorithm
  DEBUG_PRINT("norminv(" << x << ")");
  double y = x - 0.5;
  if (y < 0.42 && y > -0.42)
  {
    double r = y * y;
    DEBUG_PRINT("Case 1, r=" << r);
    return y * hornerFunction(r, a0, a1, a2, a3) / hornerFunction(r, 1.0, b1, b2, b3, b4);
  }
  else
  {
    double r;
    if (y < 0.0)
    {
      r = x;
    }
    else
    {
      r = 1.0 - x;
    }
    DEBUG_PRINT("Case 2, r=" << r);
    double s = log(-log(r));
    double t = hornerFunction(s, c0, c1, c2, c3, c4, c5, c6, c7, c8);
    if (x > 0.5)
    {
      return t;
    }
    else
    {
      return -t;
    }
  }
}

double blackScholesCallPrice(const double &strike,
                             const double &maturity,
                             const double &spot,
                             const double &volatility,
                             const double &rate)
{
  double d1 = (1 / (volatility * std::sqrt(maturity))) * (std::log(spot / strike) + (rate + pow(volatility, 2.0) / 2) * std::sqrt(maturity));
  double d2 = (1 / (volatility * std::sqrt(maturity))) * (std::log(spot / strike) + (rate - pow(volatility, 2.0) / 2) * std::sqrt(maturity));
  double parity = normcdf(d1) * spot - normcdf(d2) * strike * std::exp(-rate * maturity);
  DEBUG_PRINT("Put-Call Parity = " << parity << "\n");
  return parity;
}

double blackScholesPutPrice(const double &strike,
                            const double &maturity,
                            const double &spot,
                            const double &volatility,
                            const double &rate)
{
  double d1 = (1 / (volatility * std::sqrt(maturity))) * (std::log(spot / strike) + (rate + pow(volatility, 2.0) / 2) * std::sqrt(maturity));
  double d2 = (1 / (volatility * std::sqrt(maturity))) * (std::log(spot / strike) + (rate - pow(volatility, 2.0) / 2) * std::sqrt(maturity));
  double parity = normcdf(-d2) * strike * std::exp(-rate * maturity) - normcdf(-d1) * spot;
  DEBUG_PRINT("Put-Call Parity = " << parity << "\n");
  return parity;
}

std::vector<double> solveQuadratic(const double &a,
                                   const double &b,
                                   const double &c)
{
  std::vector<double> roots{};
  if (pow(b, 2) < 4 * a * c)
  {
    std::cout << "solveQuadratic cannot return real roots" << std::endl;
    return roots;
  }
  else if (pow(b, 2) == 4 * a * c)
  {
    roots.push_back(-b / (2 * a));
    return roots;
  }
  else
  {
    roots.push_back((-b + std::sqrt(pow(b, 2) - 4 * a * c)) / (2 * a));
    roots.push_back((-b - std::sqrt(pow(b, 2) - 4 * a * c)) / (2 * a));
    return roots;
  }
}

double mean(const std::vector<double> &numbers)
{
  if (numbers.empty())
  {
    throw std::invalid_argument("Vector is empty");
  }
  double sum = 0;
  for (const double &number : numbers)
  {
    sum += number;
  }
  return sum / numbers.size();
}

double standardDeviation(const std::vector<double> &numbers, bool sample)
{
  if (numbers.empty())
  {
    throw std::invalid_argument("Vector is empty");
  }
  double sampleMean = mean(numbers);
  double sampleSize = numbers.size();
  double sumSquaredDiffs = 0;
  for (const double &number : numbers)
  {
    sumSquaredDiffs += pow(number - sampleMean, 2);
  }
  size_t denominator = sample ? numbers.size() - 1 : numbers.size();
  return std::sqrt(sumSquaredDiffs / denominator);
}

double min(const std::vector<double> &numbers)
{
  double min = numbers[0];
  for (const double &number : numbers)
  {
    if (number < min)
    {
      min = number;
    }
  }
  return min;
}

double max(const std::vector<double> &numbers)
{
  double max = numbers[0];
  for (const double &number : numbers)
  {
    if (number > max)
    {
      max = number;
    }
  }
  return max;
}

std::vector<double> randuniform(int n)
{
  std::vector<double> numbers{};
  for (unsigned int i{0}; i < n; ++i)
  {
    numbers.push_back((double)rand() / RAND_MAX);
  }
  return numbers;
}

std::vector<double> randn(int n)
{
  std::vector<double> randomUniformNumbers{randuniform(n)};
  std::vector<double> randomNormalNumbers{};
  for (const double &randomUniformNumber : randomUniformNumbers)
  {
    randomNormalNumbers.push_back(norminv(randomUniformNumber));
  }
  return randomNormalNumbers;
}

std::vector<double> boxMullerNormal(int n)
{
  std::vector<double> randomNormalNumbers;
  while (randomNormalNumbers.size() < n)
  {
    std::vector<double> randomUniformNumbers = randuniform(2);
    double u1 = randomUniformNumbers[0];
    double u2 = randomUniformNumbers[1];
    double r = std::sqrt(-2 * std::log(u1));
    double theta = 2 * PI * u2;

    randomNormalNumbers.push_back(r * std::cos(theta));
    if (randomNormalNumbers.size() < n)
    {
      randomNormalNumbers.push_back(r * std::sin(theta));
    }
  }
  return randomNormalNumbers;
}

double prctile(const std::vector<double> &v, double p)
{
  if (v.empty() || p < 0.0 || p > 100.0)
  {
    throw std::invalid_argument("Invalid input: vector is empty or percentile is out of range.");
  }

  std::vector<double> copy = v;
  std::sort(copy.begin(), copy.end());

  double index = (copy.size() + 1) * (p / 100.0);
  size_t lower = (size_t)index;
  size_t upper = lower + 1;
  double fraction = index - lower;

  if (upper >= copy.size())
  {
    return copy[lower];
  }
  return copy[lower] + fraction * (copy[upper] - copy[lower]);
}

///////////////////////////////////////////////
//
//   TESTS
//
///////////////////////////////////////////////

static void testNormCdf()
{
  // test bounds
  ASSERT(normcdf(0.3) > 0);
  ASSERT(normcdf(0.3) < 1);
  // test extreme values
  ASSERT_APPROX_EQUAL(normcdf(-1e10), 0, 0.001);
  ASSERT_APPROX_EQUAL(normcdf(1e10), 1.0, 0.001);
  // test increasing
  ASSERT(normcdf(0.3) < normcdf(0.5));
  // test symmetry
  ASSERT_APPROX_EQUAL(normcdf(0.3),
                      1 - normcdf(-0.3), 0.0001);
  ASSERT_APPROX_EQUAL(normcdf(0.0), 0.5, 0.0001);
  // test inverse
  ASSERT_APPROX_EQUAL(normcdf(norminv(0.3)),
                      0.3, 0.0001);
  // test well known value
  ASSERT_APPROX_EQUAL(normcdf(1.96), 0.975, 0.001);
}

static void testNormInv()
{
  ASSERT_APPROX_EQUAL(norminv(0.975), 1.96, 0.01);
}

static void testBlackScholes()
{
  // Verify put-call parity
  double strike = 100;
  double maturity = 1;
  double spot = 100;
  double volatility = 0.02;
  double rate = 0.05;

  double callPrice = blackScholesCallPrice(strike,
                                           maturity,
                                           spot,
                                           volatility,
                                           rate);
  double putPrice = blackScholesPutPrice(strike,
                                         maturity,
                                         spot,
                                         volatility,
                                         rate);

  double callMinusPut = callPrice - putPrice;
  double spotMinusPVStrike = spot - strike * std::exp(-rate * maturity);

  ASSERT_APPROX_EQUAL(callMinusPut, spotMinusPVStrike, 1e-7);
}

static void testSolveQuadratic()
{
  std::vector<double> roots;
  double a, b, c;

  a = 2;
  b = 2;
  c = 2;
  ASSERT(solveQuadratic(a, b, c).size() == 0);

  a = 0.5;
  ASSERT(solveQuadratic(a, b, c).size() == 1);

  c = 1;
  ASSERT(solveQuadratic(a, b, c).size() == 2);
}

static std::vector<double> testVector()
{
  return {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
}
static void testMean()
{
  std::vector<double> numbers = testVector();
  ASSERT_APPROX_EQUAL(mean(numbers), 4.5, 1e-7);
}

static void testStandardDeviation()
{
  std::vector<double> numbers{testVector()};
  ASSERT_APPROX_EQUAL(standardDeviation(numbers), 3.02765, 1e-4);
}

static void testMin()
{
  std::vector<double> numbers = testVector();
  ASSERT(min(numbers) == 0);
}

static void testMax()
{
  std::vector<double> numbers = testVector();
  ASSERT(max(numbers) == 9);
}

static void testRanduniform()
{
  int randomNum = rand() % 101;
  std::vector<double> randomNumbers = randuniform(randomNum);
  for (unsigned int i{0}; i < randomNum; ++i)
  {
    ASSERT(randomNumbers[i] > 0);
    ASSERT(randomNumbers[i] < 1);
  }
}

static void testRandn()
{
  std::vector<double> numbers = randn(1000);
  ASSERT_APPROX_EQUAL(mean(numbers), 0.0, 1e-2);
  ASSERT_APPROX_EQUAL(standardDeviation(numbers), 1.0, 1e-2);
}

static void testBoxMullerNormal()
{
  std::vector<double> numbers{testVector()};
  ASSERT(boxMullerNormal(numbers.size()).size() == numbers.size());
  int n{10000};
  ASSERT_APPROX_EQUAL(mean(boxMullerNormal(n)), 0, 1e-1);
  ASSERT_APPROX_EQUAL(standardDeviation(boxMullerNormal(n)), 1, 1e-2);
}

static void testPrctile()
{
  std::vector<double> numbers{};
  for (int i = 0; i <= 100; i++)
  {
    numbers.push_back(i);
  }
  ASSERT_APPROX_EQUAL(prctile(numbers, 75), 76.5, 1e-2);
}

void testMatlib()
{
  TEST(testNormInv);
  TEST(testNormCdf);
  TEST(testBlackScholes);
  TEST(testSolveQuadratic);
  TEST(testMean);
  TEST(testStandardDeviation);
  TEST(testMin);
  TEST(testMax);
  TEST(testRanduniform);
  TEST(testRandn);
  TEST(testBoxMullerNormal);
  TEST(testPrctile);
}
