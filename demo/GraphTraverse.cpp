#include <iostream>
#include "GraphTraverse.h"
#include <vector>
#include <unordered_map>
#include <queue>
#include<list>
#include <stack>
#include <algorithm>
using namespace std;

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
