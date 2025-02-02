#pragma once

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>

void writeCSVChartData(std::ostream &out,
                       const std::vector<double> &x,
                       const std::vector<double> &y);

void writeCSVChart(const std::string &filename,
                   const std::vector<double> &x,
                   const std::vector<double> &y);

void pieChart(const std::string &file,
              const std::vector<std::string> &labels,
              const std::vector<double> &values);

void plot(const std::string &file,
          const std::vector<double> &xValues,
          const std::vector<double> &yValues);

void hist(std::ostream &out,
          const std::vector<std::string> &labels,
          const std::vector<double> &xValues);

void testCharts();
