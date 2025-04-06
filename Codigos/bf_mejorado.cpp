#include <iostream>
#include <vector>
#include <cmath>
#include "point.h"

using namespace std;

double bruteForceMinDistance(const vector<Point> &points)
{
    double minDistance = 1e9;
    int n = points.size();
    if (n = 1)
    {
        return 1e9;
    }
    else
    {
        for (int i = 0; i < n; ++i)
        {
            Point temp = points[i];
            for (int j = i + 1; j < n; ++j)
            {

                double dx = temp.x - points[j].x;
                double dy = temp.y - points[j].y;
                double dist = sqrt(dx * dx + dy * dy);

                if (dist < minDistance)
                {
                    minDistance = dist;
                }
            }
        }
    }
    return minDistance;
}
