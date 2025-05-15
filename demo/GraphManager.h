#include <string>
#include <unordered_map>
#include <list>
#include <utility>



#ifndef GRAPHMANAGER_H
#define GRAPHMANAGER_H


using namespace std;

class GraphManager { 

public:
// Public interface
const unordered_map<string, list<pair<string, int>>>& getAdjacencyList() const {
    return adjacencyList;
}

    void AddCity(const string& cityName);
    void AddEdge(const string& city1, const string& city2, int distance);

    void DeleteEdge(const string& city1, const string& city2);
    void DeleteCity(const string& cityName);
    GraphManager();
    ~GraphManager();
    void DisplayGraph() const;
    void loadFromJson(const string& filename);
    void saveToJson(const string& filename) const;

private:

    unordered_map<string, list<pair<string, int>>> adjacencyList;
};



#endif