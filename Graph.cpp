#include<iostream>
#include<vector>
#include<fstream>
#include "GraphFiles.h"
#include <stdlib.h>
#include <time.h>


using namespace std;
using std::vector;

struct Node;
struct Edge;
int addNode(ifstream &popFile);
int findNode(string name);
void createEdge(ifstream &fileConnect);
void print();
void Recovered(Node &node);
void diseaseProb(Node &node);
int findNode(string name);
int getMaxAge();
int Dead(string name);
void DayZero(vector<Node> &popuNode);
bool simulate_prob(float prob);
int getRandomNumber (int maxValue);
void spreadInfection(vector<Node> &popuNode);
void simulation();
void printNode();
void nodeSick(Node &node);
void nodeRecovered (Node &node , vector<Node> &popuNode);
void nodeNeighbours (vector<Node> &popuNode);
void nodeDead(Node &node);
void nodeDaysInfection(Node &node);
void popuSummary();





vector<Node> popuNode;
Node node;
Edge edge;

enum states {UNINFECTED = 0, INFECTED_NOT_SICK, SICK, DEAD};


                    /*    PART  1 - Populating the graph and reading from the files      */

/*
*This is a void method reads from the data in the population file into the Node struct and pushes it into a node vector called
*popuNode. It initialises some the values not in the file to default values. After reading into the struct it determines the maximum age of the population.
*Parameters: reference to pop_file;
*
**/


void Graph :: addNode(ifstream &popFile){
    int value = 0;
    int maxAge = 0;

    cout<<"This is summary of the Node information" <<endl;
    if(popFile.is_open()){
        while(!popFile.eof()){
            popFile >> node.name;
            popFile >> node.age;
            popFile >> node.spreadProb;
            node.is_infected = false;
            node.is_alive= true;
            node.is_sick = false;
            node.daysOfInfection = value;
            node.diseaseProb = value;
            popuNode.push_back(node);
        }
    }

    else if(!popFile.is_open()){
        cerr <<"Sorry file could not be accessed in add node" <<endl;
    }
        //iterating through the vector
    for (vector<Node>::iterator it = popuNode.begin(); it!=popuNode.end(); ++it) {
        cout << "Name: " << it->name << "     Age: " << it->age << "    Spread: " << it->spreadProb << endl;
         if (maxAge < it->age){
            maxAge = it->age;
            this->maxAge = maxAge;
        }
    }
    cout << " \nThe max age of the population is " << maxAge;
    graph.resize(popuNode.size());
 }



/*
*This method stores the edges and connections of every person into a struct of Edge.
* It also finds the index position of the names read from the connection file
* and stores the names in a vector of vector of strings called graph;
*Parameters: It takes references to: conn_file
**/

void Graph :: createEdge(ifstream &fileConnect){
   if (fileConnect.is_open()){
       cout << "Summary of the connections of nodes" << endl;
        while(!fileConnect.eof()){
            fileConnect >> edge.first;
            fileConnect >> edge.second;
            int one = findNode(edge.first);
            int two = findNode(edge.second);
            graph[one].push_back(edge.second);
            graph[two].push_back(edge.first);

        }
   }
    else{
        cerr<<"Sorry file could not open in create edge" <<endl;
    }
  }


/*
*This method prints out the list of elements in the graph vector.
*It prints out a node adnd its corresponding connections to members in the community.
*/

void Graph:: print(){
    cout << "Printing graph with nodes and connections" << endl;
    for(int i = 0; i < popuNode.size(); i++){
        if(graph[i].size() != 0){
            cout << popuNode[i].name << "-> [ ";
            for(int k = 0; k < graph[i].size() - 1; k ++){
                cout << graph[i][k] << ", ";
            }
            cout << graph[i][graph[i].size() - 1];
            cout <<" ] " <<endl;
        }
        else{
            cout << popuNode[i].name;
        }
        cout << endl;
     }
 }

        /* Helping functions */


/*
*This is a void method that calculates the recovery probability of a person in the population.
* After calculating the recovery probability, it updates the states of the Node.
*Parameters: reference to node;
*
**/

void Graph :: Recovered(Node &node){
    float recovery =  1 - node.diseaseProb;
    int canRecover = simulate_prob(recovery);
    if(canRecover == true){
        node.is_sick = false;
        node.is_infected = false;
        node.is_alive = true;
        node.daysOfInfection = 0;
    }
}


/*
*This method reads calculates the disease probability of a node.
*Parameters: reference to node;
*
**/

void Graph :: diseaseProb(Node &node){
    maxAge = getMaxAge();
    node.diseaseProb = static_cast<float>(node.age)/static_cast<float>(maxAge);
}


/*
*This is an accessor method that gets the maximum age in the population.
**/
int Graph :: getMaxAge(){
    return this->maxAge;
}


/*
*This method finds the index position of a person in the node vector.
*Parameters: string name
*Returns index position of the person in the node vector and -1 if not found
**/

int Graph:: findNode(string name){
    for (int i = 0; i < popuNode.size(); i++){
        if (name == popuNode.at(i).name){
           return i;
        }
    }
    return -1;
  }


/*
*This method is a display function that print a summary of the population.
*/

 void Graph :: printNode(){
    for (int i =0; i<popuNode.size(); i++){
        cout << " Name: " << popuNode.at(i).name  <<  "Age: " << popuNode.at(i).age <<endl;
        }
    }


/*
*This method simulates the probability by using the std:: random library.
* Parameters: float prob
* It return either true or false which is equivalent to 1 or 0 respectively.
*/

bool  Graph :: simulate_prob(float prob){
  prob = prob*1000;

  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> random_number(1,500); // distribution in range [1, 1000]
  if ( random_number(rng) <= prob)
    return true;

return false;

}


/*
*This method gets the Random Number which will be used to choose a person on Day 0. It calls the srand()function
*/
int Graph:: getRandomNumber (int maxValue){
    srand((unsigned) time(0));
    int randomNumber = 0;
    for(int i = 0; i < 5; i++){
        randomNumber = rand() % maxValue;
    }
    return randomNumber;
}



                 /*    PART  3A      */

    /*This method updates the state of an infected node to that of infected_sick
    *Parameters: reference to a node
    */

    void  Graph:: nodeSick(Node &node){
        int diseaseVal;
        if (node.is_infected  == true  && node.is_alive == true && node.is_sick == false){
            Graph :: diseaseProb(node);
            diseaseVal = simulate_prob(node.diseaseProb);
            if (diseaseVal !=0 && node.is_alive == true){
                node.is_sick = states:: SICK;
            }
        }
    }

    /*This method updates the state of an infected and sick node to that of uninfected. I.e the node has recovered
    *Parameters: reference to a node.
    */

    void Graph :: nodeRecovered (Node &node, vector<Node> &popuNode){
        if (node.is_sick == true && node.is_alive == true){
            Graph :: Recovered(node);
            cout << node.name << " has recovered and is uninfected. " <<endl;
        }
    }

    /*This method  print every node's neighbour.
    *Parameters: It takes a reference to a vector of nodes called popuNode
    */

    void Graph:: nodeNeighbours (vector<Node> &popuNode){
        int spreadVal;
        for (int v =0; v < popuNode.size(); v++){
            if (popuNode.at(v).is_infected == true && popuNode.at(v).is_alive == true){
                spreadVal = simulate_prob(popuNode.at(v).spreadProb);
                if (popuNode.at(v).is_alive == true && spreadVal !=0){

                  // handling a person's neighbours
                    for (int k =0; k < graph[v].size()-1; k++){
                        if (popuNode.at(findNode(graph[v][k])).is_infected == false  && node.is_alive == true){
                            popuNode.at(findNode(graph[v][k])).is_infected = states :: INFECTED_NOT_SICK;
                        }
                    }
                }
            }
          }
        }


    /*This method  checks if a node's days of infection is 7 days. If yes, the node is killed by updating its is_alive status to false.
    *Parameters: It takes a reference to a node.
    */
    void Graph:: nodeDead(Node &node){
        if (node.is_alive == true  && node.is_sick == true  && node.daysOfInfection == 7) {
               node.is_alive = false;  //person dies;
               cout << node.name <<" is dead. " <<endl;
        }
     }


    /*This method keeps a record of every Node's days of Infection. If checks if the node is sick and alive, and if the days of infection is less than 7, it increments it.
    *Parameters: It takes a reference to a node.
    */

    void Graph :: nodeDaysInfection(Node &node){
        if (node.is_alive == true && node.is_sick == true  && node.daysOfInfection < 7){
            node.daysOfInfection++;
             cout << node.daysOfInfection <<endl;
        }
    }

       /*  PART 3B  - Disease Simulation */

/*
*This method infects  a random person on day Zero and prints out the name of the random person selected.
*
*/

void Graph :: DayZero(vector<Node> &popuNode){

        int randomValue  = getRandomNumber(popuNode.size());
        Node personZero = popuNode.at(randomValue);
        popuNode.at(randomValue).is_infected = states :: INFECTED_NOT_SICK;
        cout <<personZero.name << " is selected and infected. " <<endl;
    }



/*
*This method infects models the spread of the disease from an infected node to its  unifected neighbours directly connected to it.
* It  checks the various states (infected_but_not sick, infected_sick, dead) of every node and updates it accordingly.
*/

void Graph:: spreadInfection(vector<Node> &popuNode){

    for (int v =0; v < popuNode.size(); v++){
        if (popuNode.at(v).is_alive == true  && popuNode.at(v).is_infected == true){
            Graph :: nodeSick(popuNode.at(v));
            Graph :: nodeNeighbours(popuNode);
            Graph :: nodeDaysInfection(popuNode.at(v));
            Graph :: nodeDead(popuNode.at(v));
            Graph :: nodeRecovered (popuNode.at(v), popuNode);
        }
    }
}



/*
*The simulation method simulates the disease in 100 days.
*It calls the DayZero function before the simulation starts and the spreadDisease function is called once the simulation starts.
*/

void Graph:: simulation(){
    Graph :: DayZero(popuNode);
    cout << " Simulation has started. " <<endl;
    for (int day =0; day < 100; day++){
       Graph:: spreadInfection(popuNode);
       cout << "\n------Day "  << day <<  "  ------  " <<endl;
    }
   Graph :: popuSummary();
}



/* This function prints a summary of the population  */

void Graph :: popuSummary(){
    cout << "---------------Population  summary of coronavirus simulation ----------------" <<endl;
     int personNum = 0; int death = 0; int infect = 0;  int notInfect =0;  int sick =0;
    for (int h =0; h < popuNode.size(); h++){

            if (popuNode.at(h).is_alive == true){
                 personNum++;
                if (popuNode.at(h).is_infected == true ){
                    infect ++;
                }
                else if (popuNode.at(h).is_infected == false){
                    notInfect++;
                }

                else if (popuNode.at(h).is_sick == true){
                    sick++;
                }
            }
            else if (popuNode.at(h).is_alive == false){
                death++;
            }
        }
        cout <<"There are " <<popuNode.size() << " people in the population " <<endl;
        cout << " \nThe number of infected people are:  "  << infect <<endl;
        cout << " \nThe number of uninfected people are:  "  << notInfect  << endl;
        cout << " \nThe number of people who are sick:  "  <<  sick << endl;
        cout << " \nThe number of people who have recovered are: "  <<  personNum << endl;
        cout << "\n The number of people alive are: " <<  personNum++;
        cout  << " \n The number of dead people are: "<< death << endl;
    }



 /* Destructor * - Defined destructor for the code*/
// void Graph::  ~Graph(){
//     cout << "Thank you for using the coronavirus simulator" <<endl;
// }



