#include <string>
#include <unordered_map>
#include <list>
#include <utility>

using namespace std;

class GraphManager {

public:

    void AddCity(const string& cityName);
    void AddEdge(const string& city1, const string& city2, int distance);

    void DeleteEdge(const string& city1, const string& city2);
    void DeleteCity(const string& cityName);

    void DisplayGraph() const;

private:

    unordered_map<string, list<pair<string, int>>> adjacencyList;
};





