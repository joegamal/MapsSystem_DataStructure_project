#include <iostream>
#include <vector>
#include <string>

using namespace std;

class GraphDisplay {
public:
    /**
     * Displays all cities and their connections in a formatted way.
     * 
     * Output format:
     * City Connections:
     * - [City1] -> [ConnectedCity1] (distance), [ConnectedCity2] (distance), ...
     * - [City2] -> [ConnectedCity3] (distance), [ConnectedCity4] (distance), ...
     * ...
     */
    void displayGraph() {
        // Implementation would depend on how the graph data is stored
        // This is a placeholder implementation
        
        cout << "City Connections:\n";
        for (const auto& city : cities) {
            cout << "- " << city << " -> ";
            // Here you would display connections for each city with distances
            // For example:
            // for (const auto& connection : getConnections(city)) {
            //     cout << connection.city << " (" << connection.distance << "), ";
            // }
            cout << "\n";
        }
    }

    /**
     * Displays the shortest path between cities and the total distance.
     * 
     * @param path A vector of strings representing the cities in the shortest path
     * @param totalDistance The total distance of the shortest path
     * 
     * Output format:
     * Shortest Path:
     * [City1] -> [City2] -> [City3] -> ... -> [Destination]
     * Total distance: X units
     */
    void displayShortestPath(const vector<string>& path, double totalDistance) {
        if (path.empty()) {
            cout << "No path available.\n";
            return;
        }

        cout << "\nShortest Path:\n";
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i];
            if (i != path.size() - 1) {
                cout << " -> ";
            }
        }
        
        // Display total distance
        cout << "\nTotal distance: " << totalDistance << " units\n";
    }

private:
    // This would be replaced with your actual graph data structure
    vector<string> cities; // Example member variable
};