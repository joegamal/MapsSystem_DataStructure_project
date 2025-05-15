#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <list>
#include "Dijkstra.h"
#include <algorithm>
#include <iomanip>
#include <climits>


using namespace std;

void Dijkstra(const GraphManager& graphManager, const string& start,
              unordered_map<string, int>& dist, unordered_map<string, string>& prev) {
    const auto& graph = graphManager.getAdjacencyList();

    for (const auto& node : graph) {
        dist[node.first] = INT_MAX;
    }
    dist[start] = 0;

    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [currDist, currNode] = pq.top();
        pq.pop();

        if (currDist > dist[currNode]) continue;

        for (const auto& [neighbor, weight] : graph.at(currNode)) {
            int newDist = currDist + weight;
            if (newDist < dist[neighbor]) {
                dist[neighbor] = newDist;
                prev[neighbor] = currNode;
                pq.push({newDist, neighbor});
            }
        }
    }
}



void PrintSolution(const unordered_map<string, int>& dist,
                   const unordered_map<string, string>& prev,
                   const string& start, const string& end) {
    if (dist.find(end) == dist.end() || dist.at(end) == INT_MAX) {
        cout << "No path from " << start << " to " << end << " exists.\n";
        return;
    }

    // Reconstruct path
    vector<string> path;
    for (string at = end; at != ""; at = prev.count(at) ? prev.at(at) : "") {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());

    cout << "Shortest distance from " << start << " to " << end << " is " << dist.at(end) << " km\n";
    cout << "Path: ";
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i];
        if (i + 1 < path.size()) cout << " -> ";
    }
    cout << "\n";
}