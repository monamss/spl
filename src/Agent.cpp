#include "../include/Agent.h"
#include "../include/Tree.h"

using namespace std;

Agent* ContactTracer::clone() const {
    return new ContactTracer(*this);
}

Agent* Virus::clone() const {
    return new Virus(*this);
}

void ContactTracer::act(Session &session) {
    //Tree* bfsTree=session.getGraphReference().BFS(ind);
    //vector<vector<int>>* edges=session.getCurrPointer()->getEdgesPointer();
    vector<vector<int>> edges=session.getGraphReference().getEdges();
    int redNode=session.dequeueInfected();
    if(redNode!=-1) {
        Tree* tree=Tree::createTree(session,redNode);
        int indToRemove=tree->traceTree();
        for(int& elem:edges[indToRemove])//set the row to 0
            elem=0;
        for (int i = 0; i < edges.size(); ++i)//set the column to 0
            edges[i][indToRemove]=0;
        delete(tree);
    }
}

void Virus::act(Session &session) {
    Graph g=session.getGraphReference();
    if(!g.isInfected(nodeInd)) {
        g.infectNode(nodeInd);
        session.enqueueInfected(nodeInd);
    }
    int healthyNeighbor=g.healthyNeighbor(nodeInd);
    if(healthyNeighbor!=-1) {
        //
        //Virus* newVirus=new Virus(healthyNeighbor);
        session.addAgent(Virus(healthyNeighbor));
    }
}

Agent::Agent() {}
ContactTracer::ContactTracer():nodeInd(-1) {}
Virus::Virus(int nodeInd):nodeInd(nodeInd) {}

int ContactTracer::getNodeInd() {
    return nodeInd;
}

int Virus::getNodeInd() {
    return nodeInd;
}
