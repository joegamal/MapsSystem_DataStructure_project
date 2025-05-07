#include "GraphManager.h"
#include <iostream>
#include <vector>
using namespace std;

void GraphManager::AddCity(const string& cityName) {

    // Only add the city if it doesn't already exist
    // unordered_map<string, list<pair<string, int>>>::iterator it = adjacencyList.find(cityName); ==   auto it = adjacencyList.find(cityName);
    auto it = adjacencyList.find(cityName);
    if (it == adjacencyList.end()) {
        adjacencyList[cityName] = list<pair<string, int>>();
    }
}

void GraphManager::AddEdge(const string& city1, const string& city2, int distance) {

    // Ensure both cities exist
    AddCity(city1);
    AddCity(city2);

    // Add the edge in both directions (undirected graph)
    adjacencyList[city1].push_back({ city2, distance });
    adjacencyList[city2].push_back({ city1, distance });
}


void GraphManager::DeleteEdge(const string& city1, const string& city2) {

    // Remove city2 from city1's neighbors
    auto& neighbors1 = adjacencyList[city1];
    for (auto it = neighbors1.begin(); it != neighbors1.end(); ++it) {
        if (it->first == city2) {
            neighbors1.erase(it);
            break; 
        }
    }

    // Remove city1 from city2's neighbors
    auto& neighbors2 = adjacencyList[city2];
    for (auto it = neighbors2.begin(); it != neighbors2.end(); ++it ) {
        if (it->first == city1) {
            neighbors2.erase(it);
            break;
        }
    }
}

void GraphManager::DeleteCity(const string& cityName) {

    // Make sure the city exists before deleting it.
    auto it = adjacencyList.find(cityName);
    if (it == adjacencyList.end()) {
        return;
    }

    // Remove the city from the neighbor lists of all other cities
    vector<string> connectedCities;
    for (const auto& neighbor : adjacencyList[cityName]) {
        connectedCities.push_back(neighbor.first);
    }

    for (const auto& otherCity : connectedCities) {
        DeleteEdge(cityName, otherCity);
    }

    // Delete the city itself
    adjacencyList.erase(cityName);
}
/** 
void GraphManager::DisplayGraph() const {

    // Check if the graph is empty
    if (adjacencyList.empty()) {
        cout << "The graph is empty." << endl;
        return;
    }

    // Iterate through each city in the adjacency list
    for (const auto& cityPair : adjacencyList) {
        const string& city = cityPair.first;
        const list<pair<string, int>>& neighbors = cityPair.second;

    // Print the current city and its neighbors
    cout << city << " -> ";
    for (const auto& neighbor : neighbors) {
        cout << "(" << neighbor.first << ", " << neighbor.second << " km) ";
    }
    cout << endl;
    }
}
    */