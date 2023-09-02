#include <bits/stdc++.h>

enum CurveType {
  left = -1,
  right = 1,
  straight = 0
};

class Point {

  double x, y;

  public:
    Point(double x, double y) {
      this->x = x;
      this->y = y;
    };

    double distance(Point point) {
      double x = (this->x - point.x);
      double y = (this->y - point.y);

      return sqrt(x*x + y*y);
    };

    // Coeficiente da reta que passa na origem e p.
    // Inclination relative to the origin.
    double inclination() {
      return atan2(this->y, this->x);
    };
    
    // Coeficiente da reta orientada de p para q.
    // Inclination relative to another point.
    double inclination(Point other) {
      return atan2(other.y - this->y, other.x - this->x);
    };

    // Direction of a curve coming from two previous points.
    int curveType (Point prevprev, Point prev) {
      double v = prevprev.x * (prev.y - this->y) + prev.x * (this->y - prevprev.y) + this->x * (prevprev.y - prev.y);

      if (v < 0) return CurveType::left; // left.
      if (v > 0) return CurveType::right; // right.
      return CurveType::straight; // straight 
    };
};
 

int main(int argc, char** argv) {

  int verticesCount, edgesCount;

  std::cin >> verticesCount >> edgesCount;

  Point** points = nullptr;
  std::vector<int>* neighbours = nullptr;


  points = new Point*[verticesCount];
  neighbours = new std::vector<int>[verticesCount];

  for (int i = 0; i < verticesCount; i++) {
    double x, y;

    std::cin >> x >> y;
    points[i] = new Point(x, y);

    int neighboursCount;

    std::cin >> neighboursCount;

    for (int j = 0; j < neighboursCount; j++) {
      int neighbour;
      std::cin >> neighbour;

      neighbours[i].push_back(neighbour);
    }

  }
  
  return 0;
}
