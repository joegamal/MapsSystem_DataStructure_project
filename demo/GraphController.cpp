#include"GraphController.h"
#include <iostream>
#include <vector>
#include <fstream>
#include "json.hpp"
#include <climits>
#include <queue>


using json = nlohmann::json;
using namespace std;



unordered_map<string,list<pair<string, int>>>& GraphController::getMap() const {
    return const_cast<unordered_map<string,list<pair<string, int>>>&>(mainMap);
}


unordered_map<string, list<pair<string, int>>> deserializeMainMap(const string& filename, unordered_map<string, list<pair<string, int>>>& mainMap) {

    mainMap.clear();

    // Open and parse the file
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return mainMap;
    }

    json j;
    inFile >> j;

    // Deserialize each key-value pair
    for (auto& [key, listJson] : j.items()) {
        list<pair<string, int>> pairList;

        for (const auto& item : listJson) {
            string str = item.at("first");
            int num = item.at("second");
            pairList.push_back({str, num});
        }

        mainMap[key] = pairList;
    }

    return mainMap;
}


void loadFromJson(const string& filename, unordered_map<string,list<pair<string, int>>>& mainMap){
    
    mainMap.clear();

    mainMap = deserializeMainMap("Neg.json", mainMap);

}


json serializeMainMap(const unordered_map<string, list<pair<string, int>>>& mainMap) {
    json j;

    for (const auto& [key, pairList] : mainMap) {
        json listJson = json::array();
        for (const auto& [str, num] : pairList) {
            listJson.push_back({{"first", str}, {"second", num}});
        }
        j[key] = listJson;
    }

    return j;
}


void saveToJson(const string& filename, const unordered_map<string,list<pair<string, int>>>& mainMap) {
   
    json result = serializeMainMap(mainMap);

    std::ofstream outFile("Neg.json");
    outFile << result.dump(4); 
    outFile.close();

}


GraphController::GraphController(){
    
    loadFromJson("NegativeCities.json", getMap());
}


GraphController::~GraphController(){
    saveToJson("NegativeCities.json", getMap());
}


void GraphController::addCity(string cname){
    
    mainMap[cname] = list<pair<string, int>>();
    saveToJson("NegativeCities.json", getMap());    
}


void GraphController::addEdge(string from, string to, int weight) {
    
    //make the graph directed.
    mainMap[from].push_back({ to, weight });
    saveToJson("Neg.json", getMap());
}


void GraphController::deleteEdge(string from ,string to){
    auto& neighbors1 = mainMap[from];
    for (auto it = neighbors1.begin(); it != neighbors1.end(); ++it) {
        if (it->first == to) {
            neighbors1.erase(it);
            break; 
        }
    }
    saveToJson("Neg.json", getMap());
}


void GraphController::removeCity(string cname){
    // Make sure the city exists before deleting it.
    auto it = mainMap.find(cname);
    if (it == mainMap.end()) {
        return;
    }

    //delete allits conncections
    auto it2 = mainMap.begin();
    for(;it2 != mainMap.end(); it2++ ) {
        auto itt = it2->second.begin();
        for(; itt != it2->second.end(); itt++){
            if(itt->first == cname) {
                itt = it2->second.erase(itt);
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

    saveToJson("Neg.json", getMap());

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
    for (const auto& [key, pairList] : mainMap) {
        cout << "Key: " << key << endl;
        for (const auto& [firstStr, secondInt] : pairList) {
            cout << "  (" << firstStr << ", " << secondInt << ")" << endl;
        }
        cout << endl;
    }
}




void bellman(
    const unordered_map<string, list<pair<string, int>>>& mainMap,
    const string& source,
    const string& destination)
{
    const int INF = numeric_limits<int>::max();
    unordered_map<string, int> distance;
    unordered_map<string, string> parent;

    // Initialize distances and parents
    for (const auto& [node, _] : mainMap) {
        distance[node] = INF;
        parent[node] = "";
    }
    distance[source] = 0;

    int V = mainMap.size();

    // Relax edges V-1 times
    for (int i = 1; i < V; ++i) {
        for (const auto& [u, edges] : mainMap) {
            if (distance[u] == INF) continue;

            for (const auto& [v, weight] : edges) {
                if (distance[v] > distance[u] + weight) {
                    distance[v] = distance[u] + weight;
                    parent[v] = u;
                }
            }
        }
    }

    // Check for negative cycles
    for (const auto& [u, edges] : mainMap) {
        if (distance[u] == INF) continue;

        for (const auto& [v, weight] : edges) {
            if (distance[v] > distance[u] + weight) {
                cerr << "Graph contains a negative-weight cycle.\n";
                return;
            }
        }
    }

    // If destination unreachable
    if (distance[destination] == INF) {
        cout << "No path from " << source << " to " << destination << ".\n";
        return;
    }

    // Reconstruct path from destination to source
    vector<string> path;
    string current = destination;
    while (!current.empty()) {
        path.push_back(current);
        current = parent[current];
    }

    // Reverse path to get correct order from source to destination
    reverse(path.begin(), path.end());

    // Display path with weights
    cout << "Shortest path from " << source << " to " << destination << ":\n";
    int total = 0;
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i];
        if (i + 1 < path.size()) {
            // Find edge weight between path[i] and path[i+1]
            for (const auto& [neighbor, weight] : mainMap.at(path[i])) {
                if (neighbor == path[i + 1]) {
                    cout << " --(" << weight << ")--> ";
                    total += weight;
                    break;
                }
            }
        }
    }
    cout << "\nTotal Cost: " << total << "\n";
}



void GraphController::findShortestPath(string start, string end){
    
    bellman(mainMap, start, end);

}

