#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include "Graph.h"

class Agent;

enum TreeType{
  Cycle,
  MaxRank,
  Root
};

class Session{
public:
    Session(const std::string& path):g(std::vector<std::vector<int>>());
    
    void simulate();
    void addAgent(const Agent& agent); //not copy constructor, will be in a different node, regular constructor
    void setGraph(const Graph& graph);
    
    void enqueueInfected(int);
    void SetInfected(int);
    int dequeueInfected();
    TreeType getTreeType() const;
    
private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
}

#endif
