#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class GraphManager {
private:
  
    unordered_map<string, unordered_map<string, int>> adjacencyList;

public:

    void AddCity(const string& cityName);


    void AddEdge(const string& city1, const string& city2, int distance);


    void DeleteEdge(const string& city1, const string& city2);


    void DeleteCity(const string& cityName);


    bool CityExists(const string& cityName) const;


    bool EdgeExists(const string& city1, const string& city2) const;


    vector<string> GetAllCities() const;


    unordered_map<string, int> GetAdjacentCities(const string& cityName) const;
};

