#include <bits/stdc++.h>

using namespace std;

std::string letter (int a) {
  switch (a) {
    case 1:
    return "a";
      break;
    case 2:
    return "b";
      break;
    case 3:
    return "c";
      break;
    case 4:
    return "d";
      break;
    case 5:
    return "e";
      break;
    case 6:
    return "f";
      break;
    case 7:
    return "g";
      break;
    case 8:
    return "h";
      break;
    case 9:
    return "i";
      break;
    case 10:
    return "j";
      break;
    case 11:
    return "k";
      break;
    case 12:
    return "l";
      break;
    case 13:
    return "m";
      break;
    default:
      return "abc";
  }
}


class Vertex;

class Edge {
public:
    Vertex* from;
    Vertex* to;
    double angle;
    bool visited = false;
    Edge* next = nullptr;
    Edge* reverse = nullptr;

    Edge(Vertex* from, Vertex* to);

    std::string toString();
};

class Vertex {
public:
    int index;
    long double x, y;

    std::vector<Edge*> neighbourEdges;
    std::vector<int> neighbourIndexes;

    Vertex(int index, int x, int y, std::vector<int> neighbours);

    void addEdge(Edge* edge);

    void sortEdges();

    std::string toString();
};

// Implementações

Edge::Edge(Vertex* from, Vertex* to) : from(from), to(to) {
    this->angle = atan2(to->y - from->y, to->x - from->x);
    from->addEdge(this);
}

std::string Edge::toString() {
    return std::to_string(this->from->index) + " -> " + std::to_string(this->to->index);
}

Vertex::Vertex(int index, int x, int y, std::vector<int> neighbours) : index(index), x(x), y(y), neighbourIndexes(neighbours) {}

void Vertex::addEdge(Edge* edge) {
    this->neighbourEdges.push_back(edge);
}

void Vertex::sortEdges() {
  std::sort(this->neighbourEdges.begin(), this->neighbourEdges.end(),
    [](Edge* e1, Edge* e2) { return e1->angle < e2->angle; });

  cout << "O MENOR DO PONTO " << letter(this->index + 1) << " é " << letter(this->neighbourEdges[0]->to->index + 1) << endl;

  // Edge* prev = this->neighbourEdges.back();
  // for (Edge* edge : this->neighbourEdges) {
  //   edge->next = prev;
  //   prev = edge;
  // }
}

std::string Vertex::toString() {
    return std::to_string(this->index);
}

std::vector<Vertex*> G;

void DFS(Edge* currentEdge, std::vector<Edge>& face) {
  currentEdge->visited = true;

  if (currentEdge->visited) {

    // std::cout << "ACHOU UMA FACE: " << std::endl << std::endl;
    // for (auto p : faces[faces.size() - 1]) {
    //   std::cout << letter(p.index + 1) << " ";
    // }
    // std::cout << std::endl << std::endl;

    // std::vector<Point> newFace;

    // faces.push_back(newFace);

    return;
  }

  
  int nextIndex = -1;

  // if (G[currentEdge.b].neighbours.size() == 1) {
  //   nextIndex = currentPoint.neighbours[0];
  // } else {

  //   bool hasRight = false;

  //   for (int neighbour : currentPoint.neighbours) {
  //     if (neighbour == parentPoint.index) continue;

  //     if (nextIndex == -1) nextIndex = neighbour;
      
  //     if (!hasRight && TipoCurva(parentPoint, currentPoint, G[neighbour]) == Curve::right) {
  //       if (currentPoint.inclination(G[neighbour]) <
  //           (currentPoint.inclination(G[nextIndex]))) {
  //         nextIndex = neighbour;
  //       }
  //       std::cout << "Opção" << letter(currentPoint.index + 1) << "->" << letter(neighbour + 1) << " Left Angle: " << ((2* M_PI) - angleBetweenEdges(currentEdge, getEdge(G[neighbour], currentPoint, edges), G)) << std::endl;
  //     }
  //     if (TipoCurva(parentPoint, currentPoint, G[neighbour]) != Curve::right) {

  //       if (hasRight == false) {
  //         nextIndex = neighbour;
  //       }

  //       hasRight = right;
  //       if (currentPoint.inclination(G[neighbour]) <
  //           (currentPoint.inclination(G[nextIndex]))) {
            
  //         nextIndex = neighbour;
  //       }
  //       std::cout << "Opção: " << letter(currentPoint.index + 1) << "->" << letter(neighbour + 1) << " Right Angle: " << (angleBetweenEdges(currentEdge, getEdge(G[neighbour], currentPoint, edges), G)) << std::endl;
  //     }
  //   }
  //   std::cout << letter(currentPoint.index + 1) << "-->" << letter(nextIndex + 1) << std::endl;
  // }
  
  DFS(getEdge(currentPoint, G[nextIndex], edges), faces, edges);
}

int main(int argc, char** argv) {

  int verticesCount, edgesCount;
  std::vector<Edge*> edges;

  std::cin >> verticesCount >> edgesCount;

  for (int i = 0; i < verticesCount; i++) {
    long double x, y;

    std::cin >> x >> y;

    int neighboursCount;

    std::cin >> neighboursCount;

    std::vector<int> neighbours;

    for (int j = 0; j < neighboursCount; j++) {
      int neighbour;
      std::cin >> neighbour;

      neighbours.push_back(neighbour - 1);
    }
    
    G.push_back(new Vertex(i, x, y, neighbours));
  }

  for (int i = 0; i < verticesCount; i++) {
    Vertex* v = G[i];
    auto& vNeighbourIndexes = G[i]->neighbourIndexes;

    for (int neighbour : vNeighbourIndexes) {

      Vertex* from = G[i];
      Vertex* to = G[neighbour];

      Edge* edge = new Edge(from, to);
      Edge* reverse = new Edge(to, from);

      edge->reverse = reverse;
      reverse->reverse = edge;

      edges.push_back(edge);
      edges.push_back(reverse);
    }
  }

  for (Vertex* vertex : G) {
    vertex->sortEdges();
  }

  std::vector<std::vector<Edge*>> faces;

  for (auto edge : edges) {
    if (!edge->visited) {
      
      std::vector<Edge*> face;

      faces.push_back(face);
      Edge* e = edge;
      do {
          face.push_back(e);
          e->visited = true;
          e = e->reverse->next;
      } while (e != edge);

      for (Edge* e : face) {
          std::cout << letter(e->from->index + 1) << " ";
      }
      std::cout << std::endl;
    }
  }

  // faces.pop_back();
  // std::cout<< faces.size() << std::endl;

  // for (auto& f : faces) {
    
  //   std::cout << f.size() << " ";
  //   for (auto& v : f) {
  //     std::cout << v.index + 1 << " ";
  //   }
  //   std::cout << std::endl;
  // }
  
  return 0;
}