#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Class to represent an edge in the graph
class Edge {
public:
    int u, v, weight;

    Edge(int u, int v, int weight) : u(u), v(v), weight(weight) {}
};

// Comparison function for sorting edges
bool compareEdges(Edge& a, Edge& b) {
    return a.weight < b.weight;
}

// Class to represent the Disjoint Set Union (DSU)
class DSU {
private:
    vector<int> parent, rank;

public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    // Find the root of a set with path compression
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    // Union two sets by rank
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

// Function to implement Kruskal's algorithm
void Kruskal(int n, vector<Edge> &edges) {
    // Sort edges using the traditional comparison function
    sort(edges.begin(), edges.end(), compareEdges);

    DSU dsu(n);

    vector<Edge> mst; // To store the edges of the MST
    int mstWeight = 0;

    for (size_t i = 0; i < edges.size() && mst.size() < n - 1; i++) {
        Edge edge = edges[i];
        if (dsu.find(edge.u) != dsu.find(edge.v)) {
            dsu.unite(edge.u, edge.v);
            mst.push_back(edge);
            mstWeight += edge.weight;
        }
    }

    // Print the MST
    cout << "Minimum Spanning Tree edges:\n";
    for (size_t i = 0; i < mst.size(); i++) {
        cout << mst[i].u << " -- " << mst[i].v << " == " << mst[i].weight << "\n";
    }
    cout << "Total weight of MST: " << mstWeight << endl;
}

int main() {
    int n, m;
    cout << "Enter the number of vertices: ";
    cin >> n;
    cout << "Enter the number of edges: ";
    cin >> m;

    vector<Edge> edges;
    for (int i = 0; i < m; i++) {
        int u, v, weight;
        cout << "Enter edge " << i + 1 << " (u, v, weight): ";
        cin >> u >> v >> weight;
        edges.push_back(Edge(u, v, weight));
    }

    Kruskal(n, edges);

    return 0;
}

