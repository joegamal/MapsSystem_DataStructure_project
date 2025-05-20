#include <iostream>
#include "GraphManager.cpp"
#include "UserLogin.cpp"
#include "DisplayGraph.cpp"
#include "GraphTraverse.cpp"
#include "GraphController.cpp"

using namespace std;

string destructChoice(string& str) {
    str = "";
    return str;
}


void showMainMenu(GraphManager& graph,GraphController negGraph) {
    GraphDisplay display(graph);
    GraphTraverse TG(graph);
    bool running = true;
    
    while (running) {

        string ans;
        cout << "\n===== Mini Wasalny Main Menu =====\n";

        //gamal's work start.
        cout << "Your MAP has a negative weights or not [y/n]\n";
        cin >> ans;
        if(ans == "y") {
            cout << "Options:\n";
            cout << "add - Add city\n";
            cout << "dis - Display graph\n";
            cout << "del - Delete city\n";
            cout << "addE - Add edge\n";
            cout << "delE - Delete edge\n";
            cout << "blman - apply bellman to find shortest path\n";
            cout << "logout - Log out\n";
            cout << "ex - Exit\n";
            cout << "Enter your choice: ";
            cin >> ans;

            if(ans == "add") {
                string cname;
                cout<<"enter the city name: ";
                cin >> cname;
                negGraph.addCity(cname);
                cout << "City added successfully!\n";
            }else if(ans == "addE"){
                
                cout << "Enter city names and distance (format: city1 city2 distance): ";
                string city1, city2;
                int distance;
                cin >> city1 >> city2 >> distance;
                negGraph.addEdge(city1, city2, distance);
                cout << "Connection added successfully!\n";
        
            }else if(ans == "dis"){
                negGraph.display();
            }else if(ans == "del"){
                cout << "Enter city name to delete: ";
                string city;
                cin >> city;
                negGraph.removeCity(city);
                cout << "City deleted if it existed.\n";
            }else if(ans == "delE") {
                cout << "Enter city names to disconnect (format: city1 city2): ";
                string city1, city2;
                cin >> city1 >> city2;
                negGraph.deleteEdge(city1, city2);
                cout << "Con2nection removed if it existed.\n";
            }else if(ans == "blman"){
                string start, end;
                cout<<"enter your current location first: ";
                cin >> start;
                cout<<"Enter your destination: ";
                cin>> end;
                negGraph.findShortestPath(start, end);
            }else if (ans == "ex") {
                //userSystem.logout();
                exit(0);
            }else if (ans == "logout") {
                //userSystem.logout();
                running = false;
            }
            else {
                cout << "Invalid option. Please try again.\n";
            }
        
            destructChoice(ans);
        //gamal's work end.



        }else{
            destructChoice(ans);
            cout << "Options:\n";
            cout << "add - Add city connection\n";
            cout << "dis - Display graph\n";
            cout << "del - Delete city\n";
            cout << "addE - Add edge\n";
            cout << "delE - Delete edge\n";
            cout << "dks - for dijkstra short path calculation\n";
            cout << "astar - for A* short path calculation\n";
            cout << "Fld - apply floid to find the shortest path between any cities\n";
            cout << "TG - Traverse current graph\n";
            cout << "logout - Log out\n";
            cout << "ex - Exit\n";
            cout << "Enter your choice: ";
            
            cin >> ans;
            
            if (ans == "add" || ans == "addE") {
                cout << "Enter city names and distance (format: city1 city2 distance): ";
                string city1, city2;
                int distance;
                cin >> city1 >> city2 >> distance;
                graph.AddEdge(city1, city2, distance);
                cout << "Connection added successfully!\n";
            }
            else if (ans == "dis") {
                display.displayGraph();
            }
            else if (ans == "del") {
                cout << "Enter city name to delete: ";
                string city;
                cin >> city;
                graph.DeleteCity(city);
                cout << "City deleted if it existed.\n";
            }
            else if(ans == "dks"){

                cout << "enter your current loaction: ";
                string city;
                cin >> city;



                cout << "enter your destination : ";
                string city2;
                cin >> city2;
                cout << endl;


                graph.dijkstra(city, city2);

            }
            else if(ans == "astar") {
                string start, end;
                cout << "Enter your current location: ";
                cin >> start;
                cout << "Enter your destination: ";
                cin >> end;
                graph.aStar(start, end);

            }
            else if(ans == "Fld"){
                char ans;
                string start , end;
                do {
                    cout<<"Enter any begining city: ";
                    cin >> start;
                    cout<<"Enter any destination city: ";
                    cin>> end;
                    graph.floyd(start, end);
                    cout << "another try? [y/n]: ";
                    cin >> ans;
                }while(ans == 'y');

            }
            else if(ans =="TG"){
                cout<<"Enter the city you want to traverse: ";
                string city;cin>>city;
                TG.BFS(city);
            }
            else if (ans == "delE") {
                cout << "Enter city names to disconnect (format: city1 city2): ";
                string city1, city2;
                cin >> city1 >> city2;
                graph.DeleteEdge(city1, city2);
                cout << "Connection removed if it existed.\n";
            }
            else if (ans == "logout") {
                //userSystem.logout();
                running = false;
            }
            else if (ans == "ex") {
                //userSystem.logout();
                exit(0);
            }
            else {
                cout << "Invalid option. Please try again.\n";
            }

            destructChoice(ans);
        }   
    }
}

int main() {
    GraphManager graph;
    UserLogin userSystem;
    GraphController gc;
    
    while (true) {
        showMainMenu(graph, gc);
    }
    
    return 0;
}