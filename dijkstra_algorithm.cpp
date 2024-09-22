#include <iostream>
#include <vector>
#include <limits.h>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

class Graph {
public: 
    // Adjacency list to store graph edges and weights
    map<char, map<char, int>> adjList; 

    // Function to add an edge between two nodes with a weight
    void addEdge(char u, char v, int weight) {
        adjList[u][v] = weight;
    }

    // Dijkstra's Algorithm implementation
    pair<int, vector<char>> dijkstra(char start, char end) {
        map<char, int> distances; // To store the shortest distances from start
        map<char, char> previous; // To store the path history
        set<pair<int, char>> nodes; // Sorted set to choose the smallest distance

        // Initialize distances
        for (auto vertex : adjList) {
            if (vertex.first == start) {
                distances[vertex.first] = 0;
            } else {
                distances[vertex.first] = INT_MAX; // Unknown distances set to infinity
            }
            nodes.insert({distances[vertex.first], vertex.first});
        }

        // Dijkstra's algorithm main loop
        while (!nodes.empty()) {
            auto smallest = *nodes.begin();
            nodes.erase(nodes.begin()); // Remove the node with the smallest distance

            char current = smallest.second;

            // If we reached the destination, reconstruct the path
            if (current == end) {
                vector<char> path;
                int total_cost = distances[current];
                while (previous.find(current) != previous.end()) {
                    path.push_back(current);
                    current = previous[current];
                }
                path.push_back(start);
                reverse(path.begin(), path.end());
                return {total_cost, path}; // Return total cost and path
            }

            // If the smallest distance is infinity, exit
            if (distances[current] == INT_MAX) {
                break;
            }

            // Process each neighbor of the current node
            for (auto neighbor : adjList[current]) {
                char neighborNode = neighbor.first;
                int weight = neighbor.second;
                int alternative = distances[current] + weight;

                // Only consider this new path if it's better
                if (alternative < distances[neighborNode]) {
                    nodes.erase({distances[neighborNode], neighborNode}); // Erase the old distance
                    distances[neighborNode] = alternative; // Update with new distance
                    previous[neighborNode] = current; // Record the path
                    nodes.insert({alternative, neighborNode}); // Re-insert with the new distance
                }
            }
        }
        return {INT_MAX, vector<char>()}; // Return no path if unreachable
    }
};
int main() {
    Graph g;

    // Adding edges for an undirected graph
    g.addEdge('A', 'B', 10);
    g.addEdge('B', 'A', 10); // Reverse direction
    g.addEdge('A', 'E', 3);
    g.addEdge('E', 'A', 3); // Reverse direction
    g.addEdge('E', 'B', 1);
    g.addEdge('B', 'E', 1); // Reverse direction
    g.addEdge('E', 'C', 4);
    g.addEdge('C', 'E', 4); // Reverse direction
    g.addEdge('B', 'C', 2);
    g.addEdge('C', 'B', 2); // Reverse direction
    g.addEdge('C', 'D', 2);
    g.addEdge('D', 'C', 2); // Reverse direction
    g.addEdge('B', 'D', 7);
    g.addEdge('D', 'B', 7); // Reverse direction

    char start, end;
    cout << "Enter start node: ";
    cin >> start;
    cout << "Enter end node: ";
    cin >> end;

    // Running Dijkstra's algorithm
    auto result = g.dijkstra(start, end);
    int cost = result.first;
    vector<char> path = result.second;

    if (cost == INT_MAX) {
        cout << "No path exists from " << start << " to " << end << endl;
    } else {
        cout << "The shortest path cost from " << start << " to " << end << " is: " << cost << endl;
        cout << "The path is: ";
        for (char node : path) {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}
