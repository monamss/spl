#include "../include/Session.h"
#include <iostream>
#include <fstream>
#include "../include/json.hpp"
//RULE OF FIVE
using json=nlohmann::json;
using namespace std;

Session::Session(const std::string& path):g({}),treeType(),agents() {
    ifstream file("config1.json");
    json input;
    file>>input;
    g=Graph(input["graph"]);
    std::string c=input["tree"];
    std::vector<std::vector<int>> matrix=input["graph"];
    //vector<Agent*> agents(input["agent"]);
    queue<int> infected;
}

//copy constructor
Session::Session(const Session& other):g(other.g),treeType(other.treeType),agents(){
    for (int i = 0; i < other.agents.size(); ++i) {
        agents.push_back(other.agents[i].clone());
    }
}

Session & Session::operator=(const Session& other) {
    if(this==&other)
        return *this;

}

Session::Session(Session&& other):g(other.g),treeType(other.treeType),agents(){
    for(Agent *agent:other.agents) {
        agents.push_back(agent->clone());
        delete(agent);
    }
}//delete other?

Session & Session::operator=(Session && other) {
    if(this==&other)
        return *this;

}

Session::~Session() {
    for (int i = 0; i < agents.size(); ++i)
        if(agents[i]!=nullptr){delete (agents[i]);}
}

void Session::setGraph(const Graph &graph) {g=graph;}

Graph & Session::getGraphReference() {return g;}

void Session::addAgent(const Agent &agent) {
    Agent* cloned=agent.clone(); //heap
    //add to agent vector
}

TreeType Session::getTreeType() const {return treeType;}

void Session::simulate() {
    for(Agent* agent:agents)
        agent->act(this);//*this?
}

void Session::SetInfected(int nodeInd) {
    g.infectNode(nodeInd);
}

void Session::enqueueInfected(int nodeInd) {
    infected.push(nodeInd);
}

int Session::dequeueInfected() {//maybe there's another way
    int dequeued = infected.front();
    infected.pop();
    return dequeued;
}