#include <iostream>
#include "GraphTraverse.h"
#include <vector>
#include <unordered_map>
#include <queue>
#include<list>
#include <stack>
#include <algorithm>
using namespace std;


/*
void GraphTraverse::BFS(string StartCity){
    GraphManager GM;
    vector<vector<string>>paths;
    vector<string>path;
    unordered_map<string,bool>visited;
    unordered_map<string,string>parent;
    queue<string> cities;
    const auto& adjacency_list=graphManager.getAdjacencyList();
    visited[StartCity]=true;
    parent[StartCity]="";
    cities.push(StartCity);
    while (!cities.empty())
    {
        string CurrentCity=cities.front();
        cities.pop();
        if(adjacency_list.find(CurrentCity)!=adjacency_list.end()){
            const auto& ListofPairs=adjacency_list.at(CurrentCity);
            for (const auto& pairs: ListofPairs) {
                if(!visited[pairs.first]){
                    visited[pairs.first]=true;
                    parent[pairs.first]=CurrentCity;
                    cities.push(pairs.first);
                }
            }
        }
            
    }
    for(const auto roads: parent){
        if(roads.second!=""){
            vector<string>currentpath;
        DFS(parent,path,paths,roads.first);
      }
    }
    for(auto ways:paths){
        for(int i=0;i<ways.size();i++){
            cout << ways[i];
            if (i != ways.size() - 1) cout << " -> ";
        }
        cout << endl;
    }
}



void GraphTraverse::DFS(unordered_map<string,string> graph,vector<string>path, vector<vector<string>>& paths,string startcity){
    path.push_back(startcity);
        
    if (graph[startcity] == "") {
        reverse(path.begin(), path.end());
        paths.push_back(path);
    } else {
        DFS(graph, path, paths, graph[startcity]);
    }
    path.pop_back(); 
}
*/


void GraphTraverse::BFS(string StartCity) {
    unordered_map<string, bool> visited;
    queue<string> cities;

    // Assuming GraphManager is a member of GraphTraverse
    const auto& adjacency_list = graphManager.getAdjacencyList();

    // Mark the start city as visited and enqueue it
    visited[StartCity] = true;
    cities.push(StartCity);

    // Traverse the graph using BFS
    while (!cities.empty()) {
        string CurrentCity = cities.front();
        cities.pop();

        // Visit (print) the current city
        cout << CurrentCity << endl;

        // Enqueue unvisited neighbors
        if (adjacency_list.find(CurrentCity) != adjacency_list.end()) {
            const auto& neighbors = adjacency_list.at(CurrentCity);
            for (const auto& pair : neighbors) {
                if (!visited[pair.first]) {
                    visited[pair.first] = true;
                    cities.push(pair.first);
                }
            }
        }
    }
}






void GraphTraverse::DFS(string startCity) {
    unordered_map<string, bool> visited;
    stack<string> stk;
    vector<string> traversalOrder;
    const auto& graph=graphManager.getAdjacencyList();

    stk.push(startCity);

    while (!stk.empty()) {
        string city = stk.top();
        stk.pop();

        if (!visited[city]) {
            visited[city] = true;
            traversalOrder.push_back(city);

            
            if (graph.find(city) != graph.end()) {
                const auto& neighbors = graph.at(city); 
                for (auto pairs:neighbors) {
                    if (!visited[pairs.first]) {
                        visited[pairs.first]=true;
                        stk.push(pairs.first);
                    }
                }
            }
        }
    }

    // Print traversal order
    for (size_t i = 0; i < traversalOrder.size(); ++i) {
        cout << traversalOrder[i];
        if (i != traversalOrder.size() - 1)
            cout << " -> ";
    }
    cout << endl;
}
