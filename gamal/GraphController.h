#include <unordered_map>
#include <vector>
#include <string>
#include <list>
using namespace std;
class GraphController {
    unordered_map<string,list<pair<string, int>>> mainMap;

public:
    GraphController();
    ~GraphController();
    void addCity(string);
    void saveTojson();
    void loadfromjson();
    void addEdge(string,string, int);
    void deleteEdge(string,string);
    void removeCity(string);
    void display();
    void findShortestPath(string,string);
    void DFS(unordered_map<string,string> graph,
             vector<string>path, 
             vector<vector<string>>& paths,
             string startcity);
    void BFS(string);
};