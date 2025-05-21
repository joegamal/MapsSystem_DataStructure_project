#include <string>
#include <unordered_map>
#include <list>
#include <utility>
#include <stack>
#ifndef GRAPHMANAGER_H
#define GRAPHMANAGER_H
using namespace std;

class GraphManager { 
    
    unordered_map<string, int> dist;
    unordered_map<string, string> prev;
    unordered_map<string, list<pair<string, int>>> adjacencyList;
    
public: 
    //unordered_map<string, list<pair<string, int>>>& getAdjacencyList() const;
    void AddCity(const string& cityName);
    void AddEdge(const string& city1, const string& city2, int distance);
    void DeleteEdge(const string& city1, const string& city2);
    void DeleteCity(const string& cityName);
    GraphManager();
    ~GraphManager();
    void DisplayGraph() const;
    void loadFromJson(const string& filename);
    void saveToJson(const string& filename) const;
    void dijkstra(string start,string end);
    void aStar(string start, string end);
    void floyd(string &start, string &end);
    bool topologicalSortUtil(const string& city, unordered_map<string, bool>& visited, stack<string>& Stack, unordered_map<string, bool>& recStack);
    bool isCyclic();
    void TPshortestPath(const string& src);
    const unordered_map<string, list<pair<string, int>>>& getAdjacencyList() const {
        return adjacencyList;
    }    
    void PrintSolution(string start, string end);
};
#endif