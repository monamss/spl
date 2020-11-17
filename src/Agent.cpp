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
    int redNode=session.dequeueInfected();
    if(redNode!=-1) {
        session.getGraphReference().getYellow().push_back(redNode);//////
        Tree* tree=session.getGraphReference().BFS(redNode,session);
        int indToRemove=tree->traceTree();
        session.getGraphReference().deleteEdges(indToRemove);
        delete(tree);
    }
}

void Virus::act(Session &session) {
    Graph g=session.getGraphReference();
    if(!g.isInfected(nodeInd)&&!g.isYellow(nodeInd)) {
        //g.infectNode(nodeInd);
        session.enqueueInfected(nodeInd);
    }
    int healthyNeighbor=g.healthyNeighbor(nodeInd,session);
    if(healthyNeighbor!=-1) {
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
