#include <vector>
#include <iostream>
using namespace std;


#ifndef GraphFiles_H
#define GraphFiles_H


/*
* This is a struct which holds the name, age, spreadProbability, daysOfInfection, diseaseProbability,
   disease states: is_alive, is_infected, is_sick for every member of the population.
*/

struct Node {
    string name;
    int age;
    float spreadProb;
    int daysOfInfection;
    float diseaseProb;
    bool is_infected;
    bool is_alive;
    bool is_sick;


};


/*
* This is a struct Edge which holds information the connections of every member of the population has.
*/

struct Edge {
    string first;
    string second;
 };


/*
* This is my graph class which forwards declares every fucntion used so that it can be easily accessed by other files.
*/
    class Graph{
        private:
        int maxAge;


        public:
            vector<Node> popuNode;
            Node node;
            Edge edge;
            vector<Edge>DiseaseProb;
            vector<vector<string>> graph;
            void print();
            int  getMaxAge();
            void diseaseProb(Node &node);
            void Recovered(Node &node);
            void createEdge(ifstream &fileConnect);
            int  findNode(string name);
            void addNode(ifstream &popFile);
            void DayZero(vector<Node> &popuNode);
            bool simulate_prob(float prob);
            void printMembers();
            int  getRandomNumber (int maxValue);
            void spreadInfection(vector<Node> &popuNode);
            void simulation();
            void printNode();
            void nodeSick(Node &node);
            void nodeRecovered (Node &node , vector<Node> &popuNode);
            void nodeNeighbours (vector<Node> &popuNode);
            void nodeDead(Node &node);
            void nodeDaysInfection(Node &node);
            void popuSummary();


};

#endif
