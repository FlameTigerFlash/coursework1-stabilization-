#include <iostream>
#include <vector>
#include <cmath>

double angleWithOY(const std::pair<double, double>& center, const std::pair<double, double>& point) {
    double deltaY = point.second - center.second;
    double deltaX = point.first - center.first;
    return atan2(deltaX, deltaY);
}

// finding the intersection points of two circles
std::vector<std::pair<double, double>> intersectionPoints(double x0, double y0, double r0,
                                                          double x1, double y1, double r1) {
    std::vector<std::pair<double, double>> points;
    double d = hypot(x1 - x0, y1 - y0);
    if (d > r0 + r1 || d < fabs(r0 - r1)) {
        return points; 
    }
    double a = (r0 * r0 - r1 * r1 + d * d) / (2 * d);
    double h = sqrt(r0 * r0 - a * a);
    double x2 = x0 + a * (x1 - x0) / d;
    double y2 = y0 + a * (y1 - y0) / d;
    double x3 = x2 + h * (y1 - y0) / d;
    double y3 = y2 - h * (x1 - x0) / d;
    double x4 = x2 - h * (y1 - y0) / d;
    double y4 = y2 + h * (x1 - x0) / d;
    points.push_back({x3, y3});
    points.push_back({x4, y4});
    return points;
}

// main function

std::vector<double> findAngles(double x0, double y0, double r0,
                               double x1, double y1, double r1) {
    std::vector<double> angles;
    auto points = intersectionPoints(x0, y0, r0, x1, y1, r1);
    if (points.empty()) {
        std::cout << "Окружности не пересекаются." << std::endl;
        return angles;
    }
    
    std::pair<double, double> intersection = (points[0].first > points[1].first) ? points[0] : points[1];
    
    angles.push_back(angleWithOY({x0, y0}, intersection));
    //angles.push_back(angleWithOY(intersection, {x0, y0}));
    angles.push_back(angleWithOY(intersection, {x1, y1}));
    return angles;
}

int main() {
    double x0, y0, r0, x1, y1, r1;
    
    x0 = 0; y0 = 0; r0 = 5;
    x1 = 0; y1 = 1; r1 = 5;

    auto angles = findAngles(x0, y0, r0, x1, y1, r1);
    for (double angle : angles) {
        std::cout << angle << " ";
    }
    return 0;
}
