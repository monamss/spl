#include "../include/Session.h"
#include "../include/Agent.h"
#include <iostream>
#include <fstream>
#include "../include/json.hpp"
//RULE OF FIVE
using json=nlohmann::json;
using namespace std;

Session::Session(const std::string& path):g({}),cycleNum(0),treeType(),agents(){
    ifstream file("config1.json");
    json input;
    file>>input;
    //file.close();
    g=Graph(input["graph"]);
    string type=input["tree"];
    if(type=="C")
        treeType=Cycle;
    else if(type=="M")
        treeType=MaxRank;
    else if(type=="R")
        treeType=Root;
    for(pair<string,int> agent:input["agents"]){
        if(agent.first=="V")
            agents.push_back(new Virus(agent.second));
        else
            agents.push_back(new ContactTracer());
    }
}

//copy constructor
Session::Session(const Session& other):g(other.g),cycleNum(other.cycleNum),treeType(other.treeType),agents(){
    for (int i = 0; i < other.agents.size(); ++i) {
        agents.push_back(other.agents[i]->clone());
    }
}

Session & Session::operator=(const Session& other) {
    if(this!=&other) {
        //delete (this);???
        agents.clear();
        g=other.g;
        cycleNum=other.cycleNum;
        treeType=other.treeType;
        for (Agent *agent:other.agents)
            agents.push_back(agent->clone());
    }
    return *this;
}

Session::Session(Session&& other):g(other.g),cycleNum(other.cycleNum),treeType(other.treeType),agents(){
    for(Agent* agent:other.agents) {
        agents.push_back(agent->clone());
        delete(agent);
    }
}

Session & Session::operator=(Session && other) {//CHECK
    if(this!=&other){
        agents.clear();
        g=other.g;
        cycleNum=other.cycleNum;
        treeType=other.treeType;
        for(Agent* agent:other.agents) {
            agents.push_back(agent->clone());
            delete(agent);
        }
    }
    return *this;
}

Session::~Session() {
    for (int i = 0; i < agents.size(); ++i)
        if(agents[i]!=nullptr){delete (agents[i]);}
}

void Session::setGraph(const Graph &graph) {g=graph;}

Graph & Session::getGraphReference() {return g;}

void Session::addAgent(const Agent &agent) {
    agents.push_back(agent.clone());
}

TreeType Session::getTreeType() const {return treeType;}

int Session::getNumofCycle() const {
    return cycleNum;
}

void Session::simulate() {
    bool terminate=false;
    while (!terminate) {
        for (Agent *agent:agents)
            agent->act(*this);//*this?
        cycleNum++;
        terminate=isFinished();
    }
    json output;
    output["graph"]=g.getEdges();
    output["infected"]=g.getInfectedVector();
    string path("output.json");
    ofstream outputFile(path);
    outputFile<<output<<std::endl;
}

bool Session::isFinished() {
    // each connected component is either fully infected or doesn't have a virus in it
    for(Agent* agent:agents)
        if(agent->getNodeInd()!=-1)
            if(g.healthyNeighbor(agent->getNodeInd())!=-1)
                return false;
    return true;
}

void Session::SetInfected(int nodeInd) {
    g.infectNode(nodeInd);
}

void Session::enqueueInfected(int nodeInd) {
    g.getInfectedVector().push_back(nodeInd);
}

int Session::dequeueInfected() {
    return g.dequeueInfected();
}
