#include <iostream>
#include <vector>
#include <cmath>
#include "point.h"

using namespace std;


double bruteForceMinDistance(const vector<Point>& points) {
    double minDistance = 1e9;
    int n = points.size();


    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {

            double dx = points[i].x - points[j].x;
            double dy = points[i].y - points[j].y;
            double dist = sqrt(dx * dx + dy * dy);

            if (dist < minDistance) {
                minDistance = dist;
            }
        }
    }
    return minDistance;
}
