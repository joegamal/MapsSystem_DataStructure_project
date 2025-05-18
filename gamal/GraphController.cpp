#include"GraphController.h"
#include <iostream>
#include <vector>
#include <fstream>
#include "json.hpp"
#include <climits>
#include <queue>


using json = nlohmann::json;
using namespace std;

GraphController::GraphController(){
    loadfromjson();
}


GraphController::~GraphController(){
    saveTojson();
}


void GraphController::addCity(string cname){
    auto it = mainMap.find(cname);
    if (it == mainMap.end()) {
        mainMap[cname] = list<pair<string, int>>();
    }
    saveTojson();
}


void GraphController::saveTojson(){

    string filename = "NegativeCities.json";
    json cityData;
        for (const auto& cityItem : mainMap) {
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


void GraphController::loadfromjson(){
    string filename = "NegativeCities.json";
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
    mainMap.clear();
    for (auto& cityItem : cityData.items()) {
        string city = cityItem.key();
        for (auto& road : cityItem.value()) {
            mainMap[city].push_back({ road["destination"], road["cost"] });
        }
    }
    cout << " Data loaded from " << filename << " successfully!\n";
}


void GraphController::addEdge(string from, string to, int weight) {
    // Ensure both cities exist.
    addCity(from);
    addCity(to);

    //make the graph directed.
    mainMap[from].push_back({ to, weight });
}


void GraphController::deleteEdge(string from ,string to){
    auto& neighbors1 = mainMap[from];
    for (auto it = neighbors1.begin(); it != neighbors1.end(); ++it) {
        if (it->first == to) {
            neighbors1.erase(it);
            break; 
        }
    }
    saveTojson();
}


void GraphController::removeCity(string cname){
    // Make sure the city exists before deleting it.
    auto it = mainMap.find(cname);
    if (it == mainMap.end()) {
        return;
    }

    //delete allits conncections
    auto it = mainMap.begin();
    for(;it != mainMap.end(); it++ ) {
        auto itt = it->second.begin();
        for(; itt != it->second.end(); itt++){
            if(itt->first == cname) {
                itt = it->second.erase(itt);
                --itt;
            }
        }
    }

    //delete the city itself
    for(;it != mainMap.end(); it++ ) {
        if(it->first == cname) {
            mainMap.erase(it);
        }
    }

    saveTojson();

}


void GraphController::DFS(unordered_map<string,string> graph,
                          vector<string>path, 
                          vector<vector<string>>& paths,
                          string startcity){

    path.push_back(startcity);
        
    if (graph[startcity] == "") {
        reverse(path.begin(), path.end());
        paths.push_back(path);
    } else {
        DFS(graph, path, paths, graph[startcity]);
    }
    path.pop_back(); 
}



void GraphController::BFS(string start){
    vector<vector<string>>paths;
    vector<string>path;
    unordered_map<string,bool>visited;
    unordered_map<string,string>parent;
    queue<string> cities;
    const auto& adjacency_list= mainMap;
    visited[start]=true;
    parent[start]="";
    cities.push(start);
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


void GraphController::display() {
    // If start is empty, pick the first city in the map as default
    string start = mainMap.begin()->first;
    
    BFS(start);
}


void GraphController::findShortestPath(string start, string end){
    unordered_map<string, int> distance;
    unordered_map<string, string> path;  // To reconstruct the path

    //make all to infinity
    for(auto it : mainMap){
        distance[it.first] = INT_MAX;
    }

    distance[start] = 0;

      for (int i = 0; i < mainMap.size() - 1; i++) {
        for (auto& cities : mainMap) {
            string current = cities.first;
            for (auto& neighbor : cities.second) {
                string neighborCity = neighbor.first;
                int weight = neighbor.second;
                if (distance[current] != INT_MAX && 
                    distance[current] + weight < distance[neighborCity]) {
                    distance[neighborCity] = distance[current] + weight;
                    path[neighborCity] = current;
                }
            }
        }
    }


    // Print the shortest distance to the destination
    cout << "Shortest distance from " << start << " to " << end << ": ";
    if (distance[end] == INT_MAX) {
        cout << "INF (no path exists)" << endl;
    } else {
        cout << distance[end] << endl;
    }

    // Reconstruct and print the path if it exists
    if (distance[end] != INT_MAX) {
        cout << "Path: ";
        vector<string> pathv;
        for (string at = end; at != ""; at = path[at]) {
            pathv.push_back(at);
        }
        reverse(pathv.begin(), pathv.end());
        
        for (size_t i = 0; i < pathv.size(); i++) {
            if (i != 0) cout << " -> ";
            cout << pathv[i];
        }
        cout << endl;
    }


}














