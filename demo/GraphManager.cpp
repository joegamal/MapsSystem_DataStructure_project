#include "GraphManager.h"
#include <iostream>
#include <vector>
#include <fstream>
#include "json.hpp"
#include <climits>
#include <queue>

using json = nlohmann::json;
using namespace std;

void GraphManager::AddCity(const string& cityName) {

    // Only add the city if it doesn't already exist
    // unordered_map<string, list<pair<string, int>>>::iterator it = adjacencyList.find(cityName); ==   auto it = adjacencyList.find(cityName);
    auto it = adjacencyList.find(cityName);
    if (it == adjacencyList.end()) {
        adjacencyList[cityName] = list<pair<string, int>>();
    }
    saveToJson("cities.json");
}

void GraphManager::loadFromJson(const string& filename){
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << " File " << filename << " not found. Using new data.\n";
        return;
    }
    json cityData;
    try {
        inFile >> cityData;
        inFile.close();
    }
    catch (...) {
        cout << " Error reading JSON data.\n";
        return;
    }
    adjacencyList.clear();
    for (auto& cityItem : cityData.items()) {
        string city = cityItem.key();
        for (auto& road : cityItem.value()) {
            adjacencyList[city].push_back({ road["destination"], road["cost"] });
        }
    }
    cout << " Data loaded from " << filename << " successfully!\n";
}

GraphManager::GraphManager(){
    loadFromJson("cities.json");
}

void GraphManager::saveToJson(const string& filename)const {
    json cityData;
        for (const auto& cityItem : adjacencyList) {
            string city = cityItem.first;
            for (const auto& road : cityItem.second) {
                cityData[city].push_back({ {"destination", road.first}, {"cost", road.second} });
            }
        }

        ofstream outFile(filename);
        if (!outFile.is_open()) {
            cout << " Error opening file " << filename << "!\n";
            return;
        }

        outFile << cityData.dump(4);
        outFile.close();
        cout << " Data saved to " << filename << " successfully!\n";
}

GraphManager::~GraphManager() {
    saveToJson("cities.json");
}

void GraphManager::AddEdge(const string& city1, const string& city2, int distance) {

    // Ensure both cities exist
    AddCity(city1);
    AddCity(city2);

    // Add the edge in both directions (undirected graph)
    adjacencyList[city1].push_back({ city2, distance });
    adjacencyList[city2].push_back({ city1, distance });
    saveToJson("cities.json");

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
    saveToJson("cities.json");

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
    saveToJson("cities.json");

}

void GraphManager::PrintSolution(string start,string end) {
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

void GraphManager::dijkstra(string start,string end){
    

    for (const auto& node : adjacencyList) {
        dist[node.first] = INT_MAX;
    }
    dist[start] = 0;

    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [currDist, currNode] = pq.top();
        pq.pop();

        if (currDist > dist[currNode]) continue;

        for (const auto& [neighbor, weight] : adjacencyList.at(currNode)) {
            int newDist = currDist + weight;
            if (newDist < dist[neighbor]) {
                dist[neighbor] = newDist;
                prev[neighbor] = currNode;
                pq.push({newDist, neighbor});
            }
        }
    }
    PrintSolution(start,end);
}



void GraphManager::aStar(string start, string end) {
    // Simple heuristic: zero for now (acts like Dijkstra)
    auto heuristic = [](const string& a, const string& b) {
        return 0;
    };

    dist.clear();
    prev.clear();

    for (const auto& node : adjacencyList) {
        dist[node.first] = INT_MAX;
    }

    dist[start] = 0;

    // Priority queue with (f_score, node)
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> openSet;
    openSet.push({ heuristic(start, end), start });

    while (!openSet.empty()) {
        auto [fScore, current] = openSet.top();
        openSet.pop();

        if (current == end) break;

        for (const auto& [neighbor, weight] : adjacencyList[current]) {
            int tentative_gScore = dist[current] + weight;
            if (tentative_gScore < dist[neighbor]) {
                dist[neighbor] = tentative_gScore;
                prev[neighbor] = current;
                int f = tentative_gScore + heuristic(neighbor, end);
                openSet.push({ f, neighbor });
            }
        }
    }

  PrintSolution(start, end);
}

// youssefRagheb Work start here
void GraphManager::floyd(string& startCity, string& endCity) {

    const unordered_map<string, list<pair<string, int>>> distList = getAdjacencyList();
    unordered_map<string, unordered_map<string, int>> distMatrixMap;
    vector<string> cities ;
    // hena bgm3 el kol cities elly fe el adjacency list as key
    for (auto it : distList) {
        cities.push_back(it.first);
    }

    // hnInitialize el adjacency matrix
    for (auto it : cities) {
        for (auto it2 : cities) {
            distMatrixMap[it][it2] = (it == it2) ? 0 : INT_MAX;
        }
    }

    // han5le el adjacency list tb2a adjacency map b3d ma handlnaha 
    for(auto it1 : distList) {
        string city = it1.first;
        list<pair<string, int>> neighborsList = it1.second;
        for(auto it2 : neighborsList) {
            string neighbor = it2.first;
            int distance = it2.second;
            distMatrixMap[city][neighbor] = distance;
        }
    }  

    // Apply Floyd-Warshall algorithm
    for (auto k : cities) {
        for (auto i : cities) {
            for (auto j : cities) {
                if (distMatrixMap[i][k] != INT_MAX && distMatrixMap[k][j] != INT_MAX) {
                    if (distMatrixMap[i][j] > distMatrixMap[i][k] + distMatrixMap[k][j]) {
                        distMatrixMap[i][j] = distMatrixMap[i][k] + distMatrixMap[k][j];
                    }
                }
            }
        }
    }

    if (distMatrixMap[startCity][endCity] == INT_MAX) {
        cout << "there is no path between " << startCity << " and " << endCity << endl;
    } else {
        cout << "the shortest distance between " << startCity << " to " << endCity << " is: " 
             << distMatrixMap[startCity][endCity] << endl;
    }
}

