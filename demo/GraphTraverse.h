#include"GraphManager.h"
#include<iostream>
#include <vector>
#include <iomanip>
#include<unordered_map>
using namespace std;
class GraphTraverse
{
    private:
    const GraphManager& graphManager; // Reference to the GraphManager storing the data

public:
    // Constructor taking a reference to the GraphManager
    GraphTraverse(const GraphManager& gm) : graphManager(gm) {}
    void BFS(string StartCity);
    void DFS(string startcity);
};
