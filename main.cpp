#include <iostream>
#include <random>
#include "GraphFiles.h"
#include "Graph.cpp"
#include <vector>

using std::vector; //rule


/*
* This is the main function that calls every function defined in the Graph class.
* It also takes input from the user.
*/
int main(){
    //int days_to_simulate = 100;

    /* Ask the user for the population and
    connections files */

    cout << "Welcome to CoronaSim!" << endl;
    string pop_file, conn_file;
    cout << "Enter population file name: ";
    cin >> pop_file;
    cout << "Enter connections file name: ";
    cin >> conn_file;

    Graph obj;
    ifstream fileConnect;
    fileConnect.open(conn_file);
    ifstream popFile;
    popFile.open(pop_file);
    cout << endl;


    while(true){

        int choice;

        /* Print menu of things that your application can do*/
        cout << "*** *** *** *** *** *** *** *** *" << endl;
        cout << "What would you like to do?" << endl;
        cout << "1. Print population" << endl;
        cout << "2.  print graph" << endl;
        cout << "3. Simulate" << endl;
        cout << "4. Summarize population" << endl;
        cout << "5. Exit" << endl;
        cout << "*** *** *** *** *** *** *** *** *" << endl;
        cout << "Your selection: ";


        cin >> choice;

        switch(choice){

            case 1:
                obj.addNode(popFile);
                cout << "\n\n";
                obj.createEdge(fileConnect);
                break;

            case 2:
                obj.print();
                break;

            case 3:
                obj.simulation();

                break;

            case 4:
                obj.popuSummary();

                break;

            case 5:
                cout << "Thank you for using the coronavirus simulator" <<endl;

                return 0;
        }
    }
return 0;
}



    // obj.print();
    // cout << endl;
    // obj.spreadInfection();
    // cout << endl;
    // obj.simulation();
    // obj.printNode();
     //obj.printMembers();

