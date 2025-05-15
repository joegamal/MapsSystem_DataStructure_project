#include"DisplayGraph.h"
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

    // Constructor taking a reference to the GraphManager
    /**
     * Displays all cities and their connections
     * Format:
     * City Connections:
     * - City1 → ConnectedCity (distance), ConnectedCity (distance)
     * - City2 → ConnectedCity (distance)
     */


void GraphDisplay::displayGraph() const {
    cout << "City Connections:\n";
    
    // Get the adjacency list from GraphManager
    auto adjacencyList = graphManager.getAdjacencyList();
    
    if (adjacencyList.empty()) {
        cout << "The graph is empty." << endl;
        return;
    }
    for (const auto& cityEntry : adjacencyList) {
        cout << "- " << cityEntry.first << " → ";
        
        bool firstConnection = true;
        for (const auto& connection : cityEntry.second) {
            if (!firstConnection) {
                cout << " → ";
            }
            cout << connection.first << " (" << connection.second <<" km "<< ")";
            firstConnection = false;
        }
        cout << "\n";
    }
}

    /**
     * Displays the shortest path with total distance
     * @param path - vector of city names in path order
     * @param distance - total path distance
     * Format:
     * Shortest Path:
     * Start → City → ... → Destination
     * Total distance: 123.45 units
     */


void GraphDisplay::displayShortestPath(const vector<string>& path, double distance) const {
    if (path.empty()) {
        cout << "No path exists\n";
        return;
    }
    cout << "\nShortest Path:\n";
    
    // Print path with arrows
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i != path.size()-1) cout << " → ";
    }
    // Print total distance with 2 decimal places
    cout << fixed << setprecision(2);
    cout << "\nTotal distance: " << distance << " units\n";
}
 