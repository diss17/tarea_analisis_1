#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

double calculateDistance(std::pair<double, double> p1, std::pair<double, double> p2)
{
    return sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
}
double minDistance(std::vector<std::pair<double, double>> points, int n)
{
    double min_dist = std::numeric_limits<double>::max();
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            double dist = calculateDistance(points[i], points[j]);
            if (dist < min_dist)
            {
                min_dist = dist;
            }
        }
    }
    return min_dist;
}
int main(int argc, char const *argv[])
{
    int n = 5; // Number of points
    vector<pair<double, double>> points = {
        {0.0, 0.0},
        {1.0, 1.0},
        {2.0, 2.0},
        {3.0, 3.0},
        {4.0, 4.0}};
    minDistance(points, n);
    cout << "Minimum distance: " << minDistance(points, n) << endl;
    return 0;
}
