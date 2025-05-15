#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "GraphManager.h"
#include <string>
#include <unordered_map>

using namespace std;

class Dijkstra {
private:
    unordered_map<string, int> dist;
    unordered_map<string, bool> visited;
    unordered_map<string, string> prev;

public:

    // Run Dijkstra algorithm on a graph
    void dijkstra(  const GraphManager& graph,
                    const string& startCity, 
                    const string& endCity);

    // Print the shortest path and distance
    void printSolution(const string& startCity, 
        const string& endCity) const;
};

#endif // DIJKSTRA_H
