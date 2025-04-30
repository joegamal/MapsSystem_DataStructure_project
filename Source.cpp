// main.cpp
#include <iostream>
#include "GraphManager.h"

int main() {
    GraphManager graph;

    graph.AddCity("Cairo");
    graph.AddCity("Alexandria");
    graph.AddCity("Giza");
    graph.AddCity("Red Sea"); 
    graph.AddCity("Assuit");

    graph.AddEdge("Cairo", "Alexandria", 220);
    graph.AddEdge("Cairo", "Giza", 30);
    graph.AddEdge("Alexandria", "Giza", 250);
    graph.AddEdge("Assuit", "Cairo", 450);
    graph.AddEdge("Red Sea", "Cairo", 650);

    cout << "Initial Graph:" << endl;
    graph.DisplayGraph();


    // Deleting an edge
    graph.DeleteEdge("Cairo", "Alexandria");

    cout << "\nGraph after deleting edge between Cairo and Alexandria:" << endl;
    graph.DisplayGraph();


    // Deleting a city
    graph.DeleteCity("Giza");

    cout << "\nGraph after deleting Giza:" << endl;
    graph.DisplayGraph();


    return 0;
}
