#include <iostream>
#include <vector>
using namespace std;

// Class to represent an edge in the graph
class Edge {
public:
    int src, dest, weight;

    Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
};

// Class to represent the graph and implement Bellman-Ford
class Graph {
private:
    int vertices, edges;
    vector<Edge> graph; // Vector to store edges

    // Recursive function to relax edges
    void relaxEdges(vector<int>& distance, int remainingIterations, int currentEdge = 0) {
        if (remainingIterations == 0) return;

        if (currentEdge < edges) {
            Edge& edge = graph[currentEdge];
            if (distance[edge.src] != 1e9 && distance[edge.src] + edge.weight < distance[edge.dest]) {
                distance[edge.dest] = distance[edge.src] + edge.weight;
            }
            relaxEdges(distance, remainingIterations, currentEdge + 1);
        } else {
            relaxEdges(distance, remainingIterations - 1, 0);
        }
    }

    // Recursive function to check for negative weight cycles
    bool detectNegativeCycle(vector<int>& distance, int currentEdge = 0) {
        if (currentEdge == edges) return false;

        Edge& edge = graph[currentEdge];
        if (distance[edge.src] != 1e9 && distance[edge.src] + edge.weight < distance[edge.dest]) {
            return true;
        }
        return detectNegativeCycle(distance, currentEdge + 1);
    }

public:
    // Constructor
    Graph(int v, int e) : vertices(v), edges(e) {}

    // Add edge to the graph
    void addEdge(int src, int dest, int weight) {
        graph.push_back(Edge(src, dest, weight));
    }

    // Bellman-Ford algorithm
    void bellmanFord(int source) {
        const int INF = 1e9; // A large value to represent infinity
        vector<int> distance(vertices, INF);
        distance[source] = 0;

        // Relax edges recursively
        relaxEdges(distance, vertices - 1);

        // Detect negative weight cycle recursively
        if (detectNegativeCycle(distance)) {
            cout << "Graph contains a negative weight cycle" << endl;
            return;
        }

        // Print the results
        cout << "Vertex Distance from Source:" << endl;
        for (int i = 0; i < vertices; i++) {
            if (distance[i] == INF) {
                cout << i << ": INF" << endl;
            } else {
                cout << i << ": " << distance[i] << endl;
            }
        }
    }
};

int main() {
    int vertices, edges;
    cout << "Enter the number of vertices and edges: ";
    cin >> vertices >> edges;

    Graph graph(vertices, edges);

    cout << "Enter edges in the format (source destination weight):" << endl;
    for (int i = 0; i < edges; i++) {
        int src, dest, weight;
        cin >> src >> dest >> weight;
        graph.addEdge(src, dest, weight);
    }

    int source;
    cout << "Enter the source vertex: ";
    cin >> source;

    graph.bellmanFord(source);

    return 0;
}

