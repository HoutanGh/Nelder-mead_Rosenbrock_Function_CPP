#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

// define the rosenbrock function

float Rosenbrock(float x0, float x1) {
    float y;
	y = 100 * pow(x1 - pow(x0, 2), 2) + pow(1 - x0, 2);
    return y;
}

//initilisation of the simplex

struct Point {
    float x0, x1, value;
    Point(float x0, float x1) : x0(x0), x1(x1), value(Rosenbrock(x0, x1)) {}

    bool operator<(const Point& p) const{
        return value < p.value;
    }
};

bool terminate(const vector<Point>& simplex, int iteration, float criterion = pow(10,-8), int maxIterations = 1000) {
    if (iteration >= maxIterations) {
        return true;
    }

    float maxVal = simplex.front().value;
    float minVal = simplex.back().value;
    float delta = fabs(maxVal-minVal);

    return delta < criterion;
}

Point calculateCentroid(const vector<Point>& simplex) { 
    float sumX0 = 0, sumX1 = 0;
    for (size_t i = 0; i < simplex.size() - 1; i++) { // simplex size is 3 - number of points, done like in more dim
        sumX0 += simplex[i].x0;
        sumX1 += simplex[i].x1;
    }
    return Point(sumX0 / (simplex.size()-1), sumX1 / (simplex.size()-1));
}
//reflection of the worst point
Point reflection(const Point& worst, Point& centroid, float alpha = 1.0) { //dont rly need alpha
    float reflectedx0 = centroid.x0 + alpha * (centroid.x0 - worst.x0);
    float reflectedx1 = centroid.x1 + alpha * (centroid.x1 - worst.x1);
    
    return Point(reflectedx0, reflectedx1);
}
//contraction halfway for worst point
Point contraction(const Point& worst, Point& centroid, float beta = 0.5) {
    float contractedx0 = centroid.x0 + beta * (worst.x0 - centroid.x0);
    float contractedx1 = centroid.x1 + beta * (worst.x1 - centroid.x1);
    
    return Point(contractedx0, contractedx1);

}

Point expansion(const Point& centroid, Point& reflected, float tau = 2.0) {
    float expandedx0 = centroid.x0 + tau * (reflected.x0 - centroid.x0);
    float expandedx1 = centroid.x1 + tau * (reflected.x1 - centroid.x1);

    return Point(expandedx0, expandedx1);
}
// shrink if all else fails
void shrink(vector<Point>& simplex, float gamma = 0.5){
    const Point& bestPoint = simplex.front(); 

    for (size_t i = 1; i < simplex .size(); i++) {
        simplex[i].x0 = bestPoint.x0 + gamma * (simplex[i].x0 - bestPoint.x0);
        simplex[i].x1 = bestPoint.x1 + gamma * (simplex[i].x1 - bestPoint.x1);
        simplex[i].value = Rosenbrock(simplex[i].x0, simplex[i].x1);
        
    }       
}

int main() {
    vector<Point> simplex = {Point(0, 0), Point(2, 0), Point(0,2)};
    int iteration = 0;
    float criterion = pow(10, -8);

    ofstream file("iterations.csv")
    


    while(!terminate(simplex, iteration, criterion)) {
        sort(simplex.begin(), simplex.end());
        Point centroid = calculateCentroid(simplex);
        Point worst = simplex.back();
        Point reflected = reflection(worst, centroid);

        if (reflected.value < simplex.front().value) {
            Point expanded = expansion(centroid, reflected);
            if (expanded.value < reflected.value) {
                simplex.back() = expanded;
            } else {
                simplex.back() = reflected;
            }
        } else if (reflected.value < worst.value) {
            simplex.back() = reflected;
        } else {
            Point contracted = contraction(worst, centroid);
            if (contracted.value < worst.value) {
                simplex.back() = contracted;
            } else{
                shrink(simplex);
            }
        }
        iteration++;
    }
    cout << "minimum found at: (" << simplex.front().x0 << ", " << simplex.front().x1 << ")" << endl;
    cout << "Function value: " << simplex.front().value << endl;

    return 0;
}   


