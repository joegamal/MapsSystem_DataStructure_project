#include "json.hpp"
#include <iostream>
#include <fstream>
#include "GraphController.cpp"


using json = nlohmann::json;
using namespace std;


/*
void saveToJson(const string& filename, const unordered_map<string,list<pair<string, int>>>& mainMap) {
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

void loadFromJson(const string& filename, unordered_map<string,list<pair<string, int>>>& mainMap){
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


void loadFromJson(const string& filename, unordered_map<string,list<pair<string, int>>>& mainMap){
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
*/

int main() {



    GraphController gc;

    gc.addCity("alex");
    gc.addCity("cairo");
    


    loadFromJson("Neg.json", gc.getMap());

    // Save the data to a JSON file
    saveToJson("Neg.json", gc.getMap());
    // Load the data from the JSON file

    gc.addEdge("alex", "cairo", 200);


    return 0; 
}