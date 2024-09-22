
#include <iostream>
#include <vector>
#include <limits.h>
#include <map>
#include <set>
using namespace std;

class Graph {
public:
    map<char, map<char, int>> adjList; // Adjacency list to store graph edges and weights

    void addEdge(char u, char v, int weight) {
        adjList[u][v] = weight;
    }

    pair<int, vector<char>> dijkstra(char start, char end) {
        map<char, int> distances;
        map<char, char> previous;
        set<pair<int, char>> nodes;

        // Initialize distances
        for (auto vertex : adjList) {
            if (vertex.first == start) {
                distances[vertex.first] = 0;
            } else {
                distances[vertex.first] = INT_MAX;
            }
            nodes.insert({distances[vertex.first], vertex.first});
        }

        while (!nodes.empty()) {
            auto smallest = *nodes.begin();
            nodes.erase(nodes.begin());

            char current = smallest.second;

            if (current == end) {
                vector<char> path;
                int total_cost = distances[current];
                while (previous.find(current) != previous.end()) {
                    path.push_back(current);
                    current = previous[current];
                }
                path.push_back(start);
                reverse(path.begin(), path.end());
                return {total_cost, path};
            }

            if (distances[current] == INT_MAX)
                break;

            for (auto neighbor : adjList[current]) {
                char neighborNode = neighbor.first;
                int weight = neighbor.second;
                int alternative = distances[current] + weight;

                if (alternative < distances[neighborNode]) {
                    nodes.erase({distances[neighborNode], neighborNode});
                    distances[neighborNode] = alternative;
                    previous[neighborNode] = current;
                    nodes.insert({alternative, neighborNode});
                }
            }
        }
        return {INT_MAX, vector<char>()}; // If no path exists
    }
};

int main() {
    Graph g;

    // Hardcoded graph from the example
    g.addEdge('A', 'B', 10);
    g.addEdge('A', 'E', 3);
    g.addEdge('E', 'B', 1);
    g.addEdge('E', 'C', 4);
    g.addEdge('B', 'C', 2);
    g.addEdge('C', 'D', 2);
    g.addEdge('B', 'D', 7);

    char start, end;
    cout << "Enter start node: ";
    cin >> start;
    cout << "Enter end node: ";
    cin >> end;

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
