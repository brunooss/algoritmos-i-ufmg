#include <bits/stdc++.h>
#include <stdio.h>

enum Color {
  finished = -1,
  visited = 0,
  notVisited = 1
};

class Point {
  public:
  
    int index;

    double x, y;
    Color color; // 1 if not visited, 0 if already visited, -1 if finished
    std::vector<int> neighbours;
    std::vector<int> sortedNeighbours;

    Point(double x, double y, std::vector<int> neighbours, int index) {
      this->x = x;
      this->y = y;
      this->neighbours = neighbours;
      this->index = index;
      this->color = Color::notVisited;
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
    long double inclination(Point other) {
      return atan2(other.y - this->y, other.x - this->x);
    };
};

std::vector<Point> G;

class Edge {
  public:
    int index;

    int a, b;
    bool visited;

    Edge(int a, int b, int index) {
      this->index = index;

      this->a = a;
      this->b = b;
      visited = false;
    }
};

Edge& getEdge(int a, int b, std::vector<Edge>& edges) {
  for (auto& edge: edges) {
    if (edge.a == a && edge.b == b) {
      return edge;
    }
  }
}

void IterativeDFS(Edge* initialEdge, std::vector<std::vector<Point>>& faces, std::unordered_map<std::string, Edge*>& edges) {

  std::stack<Edge*> stack;

  stack.push(initialEdge);

  while (!stack.empty()) {

    Edge* currentEdge = stack.top();
    stack.pop();
 
    if (!currentEdge->visited) {
      currentEdge->visited = true;
      faces[faces.size() - 1].push_back(G[currentEdge->a]);

      int next = -1;

      if (G[currentEdge->b].neighbours.size() == 1) {
        next = G[currentEdge->b].neighbours[1];
      } else {
          for (int i = 0; i < G[currentEdge->b].neighbours.size(); i++) {
            if (currentEdge->a == G[currentEdge->b].neighbours[i]) {
              next = G[currentEdge->b].neighbours[i + 1];
              break;
            }
          }
      }

      stack.push(edges[std::to_string(currentEdge->b) + " " + std::to_string(next)]);
    } else {

      faces[faces.size() - 1].push_back(faces[faces.size() - 1][0]);

      std::vector<Point> newFace;
      faces.push_back(newFace);
    }
  }
}

int main(int argc, char** argv) {

  int verticesCount, edgesCount;
  std::vector<std::vector<Point>> faces;
  std::unordered_map<std::string, Edge*> edges;

  std::cin >> verticesCount >> edgesCount;

  for (int i = 0; i < verticesCount; i++) {
    double x, y;

    scanf("%lf %lf", &x, &y);

    int neighboursCount;

    std::cin >> neighboursCount;

    std::vector<int> neighbours;

    int k = 0;

    for (int j = 0; j < neighboursCount; j++) {
      int neighbour;
      scanf("%d", &neighbour);

      neighbours.push_back(neighbour - 1);
      std::string key = std::to_string(i) + " " + std::to_string(neighbour - 1);
      edges[key] = new Edge(i, neighbour - 1, k);
      k++;
    }
    
    G.push_back(Point(x, y, neighbours, i));
  }

  for (Point& v : G) {
    std::vector<int>& neighbours = v.neighbours;

    std::sort(neighbours.begin(), neighbours.end(),
    [&v](int p, int q) { return v.inclination(G[p]) < v.inclination(G[q]); });

    neighbours.push_back(neighbours[0]);
  }

  std::vector<Point> firstFace;
  faces.push_back(firstFace);

  std::cout << edgesCount - verticesCount + 2 << std::endl;

  for (auto& edge : edges) {
    if (!edge.second->visited) {
      IterativeDFS(edge.second, faces, edges);
    }
  }

  faces.pop_back();

  for (auto& face : faces) {
    printf("%d ", face.size());
    for (auto& v : face) {
      printf("%d ", v.index + 1);
    }
    printf("\n");
  }
  
  return 0;
}

// void DFS(Edge& currentEdge, std::vector<std::vector<Point>>& faces, std::vector<Edge>& edges) {
//   faces[faces.size() - 1].push_back(G[currentEdge.a]);
//   if (currentEdge.visited) {
//     printf("%d ", faces[faces.size() - 1].size());
//     for (auto& v : faces[faces.size() - 1]) {
//       printf("%d ", v.index + 1);
//     }
//     printf("\n");
//     std::vector<Point> newFace;
//     faces.push_back(newFace);
//     return;
//   }
//   currentEdge.visited = true;
//   int next = -1;
//   if (G[currentEdge.b].neighbours.size() == 1) {
//     next = G[currentEdge.b].neighbours[1];
//   } else {
//       for (int i = 0; i < G[currentEdge.b].neighbours.size(); i++) {
//         if (currentEdge.a == G[currentEdge.b].neighbours[i]) {
//           next = G[currentEdge.b].neighbours[i + 1];
//           break;
//         }
//       }
//   }
//   DFS(getEdge(currentEdge.b, next, edges), faces, edges);
// }