#include "charts.h"
#include "matlib.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cassert>
#include <iostream>

// Writes x and y values to a given output stream (e.g., std::cout or file)
void writeCSVChartData(std::ostream &out, const std::vector<double> &x, const std::vector<double> &y)
{
    assert(x.size() == y.size());
    for (size_t i = 0; i < x.size(); i++)
    {
        out << x[i] << "," << y[i] << "\n";
    }
}

// Writes x and y values to a CSV file
void writeCSVChart(const std::string &filename, const std::vector<double> &x, const std::vector<double> &y)
{
    std::ofstream out(filename);
    writeCSVChartData(out, x, y);
}

// Writes the top boilerplate for the HTML pie chart
static void writeTopBoilerPlateOfPieChart(std::ostream &out)
{
    out << "<html>\n";
    out << "<head>\n";
    out << "<!-- Load the AJAX API -->\n";
    out << "<script type=\"text/javascript\" src=\"https://www.google.com/jsapi\"></script>\n";
    out << "<script type=\"text/javascript\">\n";
    out << "google.load('visualization', '1.0', {'packages':['corechart']});\n";
    out << "google.setOnLoadCallback(drawChart);\n";
    out << "function drawChart() {\n";
    out << "var data = new google.visualization.DataTable();\n";
    out << "data.addColumn('string', 'Label');\n";
    out << "data.addColumn('number', 'Value');\n";
}

// Writes the bottom boilerplate for the HTML pie chart
static void writeBottomBoilerPlateOfPieChart(std::ostream &out)
{
    out << "var options = {'title': 'A Pie Chart', 'width': 400, 'height': 300};\n";
    out << "var chart = new google.visualization.PieChart(document.getElementById('chart_div'));\n";
    out << "chart.draw(data, options);\n";
    out << "}\n";
    out << "</script>\n";
    out << "</head>\n";
    out << "<body>\n";
    out << "<div id='chart_div'></div>\n";
    out << "</body>\n";
    out << "</html>";
}

// Writes fixed pie chart data as rows in the JavaScript
static void writeFixedPieChartData(std::ostream &out)
{
    out << "data.addRows([\n";
    out << "['Bananas', 100],\n";
    out << "['Apples', 200],\n";
    out << "['Kumquats', 150]\n";
    out << "]);\n";
}

// Writes dynamic pie chart data based on provided labels and values
static void writeDataOfPieChart(std::ostream &out, const std::vector<std::string> &labels, const std::vector<double> &values)
{
    assert(labels.size() == values.size());
    out << "data.addRows([\n";
    for (size_t i = 0; i < labels.size(); i++)
    {
        out << "['" << labels[i] << "', " << values[i] << "]";
        if (i != labels.size() - 1)
        {
            out << ",";
        }
        out << "\n";
    }
    out << "]);\n";
}

// Generates a dynamic pie chart in an HTML file based on labels and values
void pieChart(const std::string &file, const std::vector<std::string> &labels, const std::vector<double> &values)
{
    std::ofstream out(file);
    writeTopBoilerPlateOfPieChart(out);
    writeDataOfPieChart(out, labels, values);
    writeBottomBoilerPlateOfPieChart(out);
}

// Writes the top boilerplate for the HTML line chart
static void writeTopBoilerPlateOfLineChart(std::ostream &out)
{
    out << "<!DOCTYPE html>\n";
    out << "<html>\n";
    out << "<head>\n";
    out << "<title>Line Chart Example</title>\n";
    out << "<script type='text/javascript' src='https://www.gstatic.com/charts/loader.js'></script>\n"; // Corrected: single quotes
    out << "<script type='text/javascript'>\n";
    out << "  google.charts.load('current', {'packages':['corechart']});\n";
    out << "  google.charts.setOnLoadCallback(drawChart);\n";
    out << "  function drawChart() {\n";
    out << "    var data = new google.visualization.DataTable();\n";
    out << "    data.addColumn('number', 'X');\n";
    out << "    data.addColumn('number', 'Y');\n";
}

// Writes fixed pie chart data as rows in the JavaScript
static void writeFixedLineChartData(std::ostream &out)
{
    out << "data.addRows([\n";
    out << "[2017, 1000],\n";
    out << "[2018, 1170],\n";
    out << "[2019, 1120],\n";
    out << "[2020, 540]\n";
    out << "]);\n";
}

// Writes the bottom boilerplate for the HTML line chart
static void writeBottomBoilerPlateOfLineChart(std::ostream &out)
{
    out << "    var options = { 'title' : 'Line Chart', 'curveType' : 'function', 'legend' : {position : 'bottom'}, 'width' : 600, 'height' : 400 };\n";
    out << "    var chart = new google.visualization.LineChart(document.getElementById('chart_div'));\n"; // Corrected: LineChart
    out << "    chart.draw(data, options);\n";
    out << "  }\n";
    out << "</script>\n";
    out << "</head>\n";
    out << "<body>\n";
    out << "  <div id='chart_div' style='width: 600px; height: 400px;'></div>\n"; // Added styling
    out << "</body>\n";
    out << "</html>";
}

// Writes dynamic line chart data based on provided labels and values
static void writeDataOfLineChart(std::ostream &out, const std::vector<double> &xValues, const std::vector<double> &yValues)
{
    assert(xValues.size() == yValues.size());
    out << "    data.addRows([\n";
    for (size_t i = 0; i < xValues.size(); i++)
    {
        out << "      [" << xValues[i] << ", " << yValues[i] << "]"; // Corrected: No quotes around xValues[i]
        if (i != xValues.size() - 1)
        {
            out << ",\n";
        }
        else
        {
            out << "\n";
        }
    }
    out << "    ]);\n";
}

// Generates a dynamic line chart in an HTML file based on labels and values
void plot(const std::string &file, const std::vector<double> &xValues, const std::vector<double> &yValues)
{
    std::ofstream out(file);
    writeTopBoilerPlateOfLineChart(out);
    writeDataOfLineChart(out, xValues, yValues);
    writeBottomBoilerPlateOfLineChart(out);
}

// Writes the top boilerplate for the HTML line chart
static void writeTopBoilerPlateOfHistorgram(std::ostream &out)
{
    out << "<!DOCTYPE html>\n";
    out << "<html>\n";
    out << "  <head>\n";
    out << "    <script type='text/javascript' src='https://www.gstatic.com/charts/loader.js'></script>\n";
    out << "    <script type='text/javascript'>\n";
    out << "      google.charts.load('current', {packages:['corechart']});\n";
    out << "      google.charts.setOnLoadCallback(drawChart);\n";
    out << "      function drawChart() {\n";
    out << "        var data = google.visualization.arrayToDataTable([\n";
}

// Writes fixed pie chart data as rows in the JavaScript
static void writeFixedHistogramData(std::ostream &out)
{
    out << "['Dinosaur', 'Length'],\n";
    out << "['Acrocanthosaurus (top-spined lizard)', 12.2],\n";
    out << "['Albertosaurus (Alberta lizard)', 9.1],\n";
    out << "['Allosaurus (other lizard)', 12.2],\n";
    out << "['Apatosaurus (deceptive lizard)', 22.9],\n";
    out << "['Archaeopteryx (ancient wing)', 0.9],\n";
    out << "['Argentinosaurus (Argentina lizard)', 36.6],\n";
    out << "['Baryonyx (heavy claws)', 9.1],\n";
    out << "['Brachiosaurus (arm lizard)', 30.5],\n";
    out << "['Ceratosaurus (horned lizard)', 6.1],\n";
    out << "['Coelophysis (hollow form)', 2.7],\n";
    out << "['Compsognathus (elegant jaw)', 0.9],\n";
    out << "['Deinonychus (terrible claw)', 2.7],\n";
    out << "['Diplodocus (double beam)', 27.1],\n";
    out << "['Dromicelomimus (emu mimic)', 3.4],\n";
    out << "['Gallimimus (fowl mimic)', 5.5],\n";
    out << "['Mamenchisaurus (Mamenchi lizard)', 21.0],\n";
    out << "['Megalosaurus (big lizard)', 7.9],\n";
    out << "['Microvenator (small hunter)', 1.2],\n";
    out << "['Ornithomimus (bird mimic)', 4.6],\n";
    out << "['Oviraptor (egg robber)', 1.5],\n";
    out << "['Plateosaurus (flat lizard)', 7.9],\n";
    out << "['Sauronithoides (narrow-clawed lizard)', 2.0],\n";
    out << "['Seismosaurus (tremor lizard)', 45.7],\n";
    out << "['Spinosaurus (spiny lizard)', 12.2],\n";
    out << "['Supersaurus (super lizard)', 30.5],\n";
    out << "['Tyrannosaurus (tyrant lizard)', 15.2],\n";
    out << "['Ultrasaurus (ultra lizard)', 30.5],\n";
    out << "['Velociraptor (swift robber)', 1.8]]);\n";
}

// Writes the bottom boilerplate for the HTML line chart
static void writeBottomBoilerPlateOfHistogram(std::ostream &out)
{
    out << "        var options = {\n";
    out << "          title: 'Lengths of dinosaurs, in meters',\n";
    out << "          legend: { position: 'none' },\n";
    out << "        };\n";
    out << "        var chart = new google.visualization.Histogram(document.getElementById('chart_div'));\n";
    out << "        chart.draw(data, options);\n";
    out << "      }\n";
    out << "    </script>\n";
    out << "  </head>\n";
    out << "  <body>\n";
    out << "    <div id='chart_div' style='width: 900px; height: 500px;'></div>\n";
    out << "  <body>\n";
    out << "  <body>\n";
    out << "</html>\n";
}

// Writes the data for the histogram (correctly using addRows)
static void writeDataOfHistogram(std::ostream &out, const std::vector<std::string> &labels, const std::vector<double> &xValues)
{
    assert(labels.size() == xValues.size());

    out << "        var data = google.visualization.arrayToDataTable([\n"; // Start the array

    out << "['Label', 'Value'],\n"; // Header row (important!)

    for (size_t i = 0; i < xValues.size(); i++)
    {
        out << "        ['" << labels[i] << "', " << xValues[i] << "]";
        if (i != xValues.size() - 1)
        {
            out << ",\n";
        }
        else
        {
            out << "\n";
        }
    }
    out << "        ]);\n"; // Close the array for arrayToDataTable
}

// Generates a dynamic line chart in an HTML file based on labels and values
void hist(const std::string &file, const std::vector<std::string> &labels, const std::vector<double> &xValues)
{
    std::ofstream out(file);
    writeTopBoilerPlateOfLineChart(out);
    writeDataOfHistogram(out, labels, xValues);
    writeBottomBoilerPlateOfHistogram(out);
}

///////////////////////////////////////////////
//
//   TESTS
//
///////////////////////////////////////////////

// Generates a fixed pie chart in an HTML file
static void testFixedPieChart()
{
    std::ofstream out("FixedPieChart.html");
    writeTopBoilerPlateOfPieChart(out);
    writeFixedPieChartData(out);
    writeBottomBoilerPlateOfPieChart(out);
}

// Tests the dynamic pie chart data writing function
static void testPieChartData()
{
    std::stringstream out;
    std::vector<std::string> labels = {"A Label 0", "A Label 1", "A Label 2"};
    std::vector<double> vals = {0.0, 1.0, 2.0};

    writeDataOfPieChart(out, labels, vals);

    std::string asString = out.str();
    std::stringstream expected;
    expected << "data.addRows([\n";
    expected << "['A Label 0', 0],\n";
    expected << "['A Label 1', 1],\n";
    expected << "['A Label 2', 2]\n";
    expected << "]);\n";

    assert(asString == expected.str());
}

// Generates a fixed pie chart in an HTML file
static void testFixedLineChart()
{
    std::ofstream out("FixedLineChart.html");
    writeTopBoilerPlateOfLineChart(out);
    writeFixedLineChartData(out);
    writeBottomBoilerPlateOfLineChart(out);
}

// Tests the dynamic pie chart data writing function
static void testLineChartData()
{
    std::stringstream out;
    std::vector<double> xVals = {0.0, 1.0, 2.0};
    std::vector<double> yVals = {0.0, 1.0, 4.0};

    writeDataOfLineChart(out, xVals, yVals);

    std::string asString = out.str();
    std::stringstream expected;
    expected << "data.addRows([\n";
    expected << "[0, 0],\n";
    expected << "[1, 1],\n";
    expected << "[2, 4]\n";
    expected << "]);\n";

    assert(asString == expected.str());
}

// Generates a fixed histogram in an HTML file
static void testFixedHistogramData()
{
    std::ofstream out("FixedHistogram.html");
    writeTopBoilerPlateOfHistorgram(out);
    writeFixedHistogramData(out);
    writeBottomBoilerPlateOfHistogram(out);
}

// Test function to verify all functionalities
void testCharts()
{
    // Test CSV chart data
    std::vector<double> x = {1, 2, 3, 4};
    std::vector<double> y = {10, 20, 30, 40};
    writeCSVChart("chart.csv", x, y);

    // Test fixed pie chart
    testFixedPieChart();

    // Test dynamic pie chart
    std::vector<std::string> labels = {"Category A", "Category B", "Category C"};
    std::vector<double> values = {30.0, 50.0, 20.0};
    pieChart("DynamicPieChart.html", labels, values);

    // Test fixed line chart
    testFixedLineChart();

    // Test dynamic line chart
    std::vector<double> xValues = {100.0, 200.0, 200.0};
    std::vector<double> yValues = {30.0, 50.0, 20.0};
    plot("DynamicChart.html", xValues, yValues);

    // Test fixed histogram
    testFixedHistogramData();

    // Test dynamic histogram
    std::vector<std::string> histogramLabels = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
    std::vector<double> histogramValues = randuniform(histogramLabels.size());
    std::cout << "Labels size: " << histogramLabels.size() << std::endl;
    std::cout << "Values size: " << histogramValues.size() << std::endl;
    for (size_t i = 0; i < histogramLabels.size(); ++i)
    {
        std::cout << histogramLabels[i] << ": " << histogramValues[i] << std::endl;
    }
    hist("DynamicHistogram.html", histogramLabels, histogramValues);
}
