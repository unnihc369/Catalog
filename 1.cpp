#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

// Function to decode the base-encoded value into base 10
long long decode_value(string value, int base)
{
    return stoll(value, nullptr, base);
}

// Function to perform Lagrange interpolation and find the constant term 'c'
double lagrange_interpolation(const vector<pair<int, double>> &points)
{
    int k = points.size();
    double result = 0;

    // Lagrange interpolation formula
    for (int i = 0; i < k; ++i)
    {
        double term = points[i].second; // Start with the y-value
        for (int j = 0; j < k; ++j)
        {
            if (i != j)
            {
                term *= (0.0 - points[j].first) / (points[i].first - points[j].first);
            }
        }
        result += term;
    }

    return result; // This will be the constant term 'c'
}

// Helper function to trim whitespace from both ends of a string
string trim(const string &str)
{
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

int main()
{
    // Open the input file containing the JSON-like data
    ifstream file("input.txt");
    if (!file.is_open())
    {
        cerr << "Error opening file" << endl;
        return 1;
    }

    string line;
    vector<pair<int, double>> points;
    int n, k;

    // Simple parsing loop
    while (getline(file, line))
    {
        line = trim(line);

        if (line.find("\"n\":") != string::npos)
        {
            // Extract the number of points n
            n = stoi(line.substr(line.find(":") + 1));
        }
        else if (line.find("\"k\":") != string::npos)
        {
            // Extract the minimum number of points k
            k = stoi(line.substr(line.find(":") + 1));
        }
        else if (line.find("\"base\":") != string::npos)
        {
            // Extract base value
            int base = stoi(line.substr(line.find(":") + 1));

            // Read the next line to get the value
            getline(file, line);
            line = trim(line);
            string value = line.substr(line.find(":") + 2);
            value.pop_back(); // Remove the trailing quote

            // The x-value is stored before the base-value, extract it from the earlier line
            int x = points.size() + 1;

            // Decode the y-value from the given base
            long long y = decode_value(value, base);

            // Store the point (x, y)
            points.push_back({x, static_cast<double>(y)});
        }
    }

    file.close();

    // Use Lagrange interpolation to find the constant term 'c'
    double secret = lagrange_interpolation(points);

    // Print the constant term (the secret)
    cout << "The secret (constant term 'c') is: " << secret << endl;

    return 0;
}
