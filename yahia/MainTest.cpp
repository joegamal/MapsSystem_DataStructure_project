#include <iostream>
#include "GraphManager.cpp"
#include "UserLogin.cpp"
#include "DisplayGraph.cpp"

using namespace std;

string destructChoice(string& str) {
    str = "";
    return str;
}

void showAuthMenu(UserLogin& userSystem) {
    while (true) {
        cout << "\n===== Welcome to Mini Wasalny =====\n";
        cout << "1. Login\n2. Sign Up\n3. Exit\n";
        cout << "Choose an option: ";
        
        string choice;
        cin >> choice;
        
        if (choice == "1") {
            string phone, password;
            cout << "Phone: ";
            cin >> phone;
            cout << "Password: ";
            cin >> password;
            if (userSystem.login(phone, password)) {
                return;
            }
        } 
        else if (choice == "2") {
            string firstName, lastName, phone, password;
            cout << "First Name: ";
            cin >> firstName;
            cout << "Last Name: ";
            cin >> lastName;
            cout << "Phone: ";
            cin >> phone;
            cout << "Password: ";
            cin >> password;
        
            try {
                userSystem.signUp(firstName, lastName, phone, password);
                cout << "Registration successful! Please login.\n";
            } 
            catch (const exception& e) {
                cout << "Error: " << e.what() << "\n";
            }
        }
        else if (choice == "3") {
            exit(0);
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }
    }
}

void showMainMenu(GraphManager& graph, UserLogin& userSystem) {
    GraphDisplay display(graph);
    bool running = true;
    
    while (running) {
        string ans;
        cout << "\n===== Mini Wasalny Main Menu =====\n";
        cout << "Logged in as: " << userSystem.getCurrentUser().firstName << endl;
        cout << "Options:\n";
        cout << "add - Add city connection\n";
        cout << "dis - Display graph\n";
        cout << "del - Delete city\n";
        cout << "addE - Add edge\n";
        cout << "delE - Delete edge\n";
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
        else if (ans == "delE") {
            cout << "Enter city names to disconnect (format: city1 city2): ";
            string city1, city2;
            cin >> city1 >> city2;
            graph.DeleteEdge(city1, city2);
            cout << "Connection removed if it existed.\n";
        }
        else if (ans == "logout") {
            userSystem.logout();
            running = false;
        }
        else if (ans == "ex") {
            userSystem.logout();
            exit(0);
        }
        else {
            cout << "Invalid option. Please try again.\n";
        }
        
        destructChoice(ans);
    }
}

int main() {
    GraphManager graph;
    UserLogin userSystem;
    
    while (true) {
        if (!userSystem.isLoggedIn()) {
            showAuthMenu(userSystem);
        } else {
            showMainMenu(graph, userSystem);
        }
    }
    
    return 0;
}