#include <iostream>
#include <unordered_map>
#include <list>
#include <string>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

class CityGraph {
public:
    unordered_map<string, list<pair<string, int>>> cityMap;

    void loadFromJson(const string& filename) {
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

        cityMap.clear();
        for (auto& cityItem : cityData.items()) {
            string city = cityItem.key();
            for (auto& road : cityItem.value()) {
                cityMap[city].push_back({ road["destination"], road["cost"] });
            }
        }

        cout << " Data loaded from " << filename << " successfully!\n";
    }

    void saveToJson(const string& filename) const {
        json cityData;
        for (const auto& cityItem : cityMap) {
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

    void addRoad(const string& city1, const string& city2, int cost) {
        auto& roads1 = cityMap[city1];
        auto& roads2 = cityMap[city2];

        // Check for duplicate roads between cities
        bool exists = false;
        for (const auto& road : roads1) {
            if (road.first == city2) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            roads1.push_back({ city2, cost });
        }

        bool exists2 = false;
        for (const auto& road : roads2) {
            if (road.first == city1) {
                exists2 = true;
                break;
            }
        }
        if (!exists2) {
            roads2.push_back({ city1, cost });
        }
    }

    void printGraph() const {
        cout << "Cities {\n";
        for (const auto& cityItem : cityMap) {
            string city = cityItem.first;
            cout << "    " << city << " -> ";
            for (const auto& road : cityItem.second) {
                cout << "(" << road.first << ", cost: " << road.second << ") ";
            }
            cout << endl;
        }
        cout << "}\n";
    }
};

int main() {
    CityGraph cities;

    cities.loadFromJson("cities.json");

    cities.addRoad("Cairo", "Alexandria", 200);
    cities.addRoad("Cairo", "Giza", 50);
    cities.addRoad("Alexandria", "Marsa Matruh", 300);
    cities.addRoad("Giza", "Fayoum", 100);

    cities.printGraph();

    cities.saveToJson("cities.json");

    return 0;
}
