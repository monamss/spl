#ifndef GRAPH_H_
#define GRAPH_H_
// should have BFS
#include <vector>
#include "Tree.h"

class Graph{
public:
    Graph(std::vector<std::vector<int>> matrix);
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
    std::vector<int>& getInfectedVector();
    void deleteEdges(int nodeInd);
    int dequeueInfected();
    std::vector<std::vector<int>>& getEdges();
    int healthyNeighbor(int,Session);
    Tree* BFS(int start,const Session& session);
    bool isYellow(int);
    std::vector<int>& getYellow();

private:
    std::vector<std::vector<int>> edges;
    std::vector<int> infected;
    std::vector<int> yellow;
};

#endif