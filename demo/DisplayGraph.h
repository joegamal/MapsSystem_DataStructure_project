#include "GraphManager.h"
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class GraphDisplay {
    private:
    const GraphManager& graphManager; // Reference to the GraphManager storing the data

public:
    // Constructor taking a reference to the GraphManager
    GraphDisplay(const GraphManager& gm) : graphManager(gm) {}
    void displayGraph() const;

    void displayShortestPath(const vector<string>& path, double distance) const ;


};