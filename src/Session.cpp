#include "../include/Session.h"
#include "../include/Agent.h"
#include <iostream>
#include <fstream>
#include "../include/json.hpp"
//RULE OF FIVE
using json=nlohmann::json;
using namespace std;

Session::Session(const std::string& path):g({}),cycleNum(0),treeType(),agents(){
    ifstream file(path);
    json j;
    file>>j;
    //file.close();
    g=Graph(j["graph"]);
    string type=j["tree"];
    if(type=="C")
        treeType=Cycle;
    else if(type=="M")
        treeType=MaxRank;
    else if(type=="R")
        treeType=Root;
    for(pair<string,int> agent:j["agents"]){
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

int Session::getNumOfCycle() const {
    return cycleNum;
}

void Session::simulate() {
    bool terminate=false;
    while (!terminate) {
        int size=agents.size();
        for (int i = 0; i < size; ++i) {
            agents[i]->act(*this);
        }
        cycleNum++;
        terminate=isFinished();
    }
    for (int i = 0; i < g.getInfectedVector().size(); ++i) {
        g.getYellow().push_back(g.getInfectedVector()[i]);
    }
    json output;
    output["graph"]=g.getEdges();
    output["infected"]=g.getYellow();
    string path("output.json");
    ofstream outputFile(path);
    outputFile<<output<<std::endl;
}

std::vector<Agent *> Session::getAgents() {return agents;}

bool Session::isAgent(int node) {
    for(Agent*agent:agents)
        if(node==agent->getNodeInd())
            return true;
    return false;
}

bool Session::isFinished() {
    // each connected component is either fully infected or doesn't have a virus in it
    for(Agent* agent:agents)
        if(agent->getNodeInd()!=-1)
            if(g.healthyNeighbor(agent->getNodeInd(),*this)!=-1)
                return false;
    return true;
}

void Session::enqueueInfected(int nodeInd) {
    g.infectNode(nodeInd);
}

int Session::dequeueInfected() {
    return g.dequeueInfected();
}