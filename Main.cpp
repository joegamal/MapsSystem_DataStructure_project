// main.cpp
#include <iostream>
#include "GraphController.cpp"



string destructChoice(string& str)
{
    str = "";
    return str;
}

int main() {
    GraphManager graph;



    bool choice = true;

    cout<<"--------------------------Welcome to the Mini Wasalny--------------------------\n";

    while (choice)
    {
        string ans;
        cout<<"for adding city and distance between them enter (add)\n";
        cin>>ans;
        if(ans == "add")
        {
            cout<<"enter city name and distance between them\n";
            string city1,city2;
            int distance;
            cin>>city1>>city2>>distance;
            graph.AddEdge(city1,city2,distance);
        }else{}

        destructChoice(ans);

        cout<<"for displaying city and distance between them enter (dis)\n";
        cin>>ans;
        if(ans == "dis")
        {
            graph.DisplayGraph();
        }else{}

        destructChoice(ans);


        cout<<"for deleting city enter (del)\n";
        cin>>ans;
        if(ans == "del")
        {
            cout<<"enter city name\n";
            string city1;
            cin>>city1;
            graph.DeleteCity(city1);
        }else{}

        destructChoice(ans);


        cout<<"for adding edge enter (addE)\n";
        cin>>ans;
        if(ans == "addE")
        {
            cout<<"enter cities names and distance between them\n";
            string city1,city2;
            int distance;
            cin>>city1>>city2>>distance;
            graph.AddEdge(city1,city2,distance);
        }else{}
            destructChoice(ans);

        cout<<"for deleting edge enter (delE)\n";
        cin>>ans;
        if(ans == "delE")
        {
            cout<<"enter cities names\n";
            string city1,city2;
            cin>>city1>>city2;
            graph.DeleteEdge(city1,city2);
        }else{}

        destructChoice(ans);


        cout<<"for exit enter (ex)\n";
        cin>>ans;
        if(ans == "ex")
        {
            choice = false;
        }

    }



    return 0;
}
