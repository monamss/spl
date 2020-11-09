#include "../include/Session.h"
#include <iostream>
#include <fstream>
#include "json.hpp"
//RULE OF FIVE
using json=nlohmann::json;
using namespace std;

Session::Session(const std::string& path):g({}),treeType(),agents() {
    std::ifstream temp(json.hpp);//temp(path)
    json input;
    temp>>input;
    g=Graph(input["graph"]);
    std::string c=input["tree"];
    std::vector<std::vector<int>> matrix=input["graph"];
    //vector<Agent*> agents(input["agent"]);
}

//copy constructor
Session::Session(const& Session other):g(other.g),treeType(other.treeType),agents(){
    for (int i = 0; i < other.agents.size(); ++i) {
        agents.push_back(other.agents[i]->clone());
    }
}

void Session::setGraph(const Graph &graph) {g=graph;}

Graph & Session::getGraphReference() {return g;}

void Session::addAgent(const Agent &agent) {
    Agent* Clone=agent.clone(); //heap
    //add to agent vector
}

void Session::simulate() {
    for(auto& agent:agents)
        agent->act(this);//*this?
}