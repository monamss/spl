#include "../include/Agent.h"
#include "../include/Tree.h"

using namespace std;

Agent* ContactTracer::clone() { //has a default copy constructor so that's not critical
    return new ContactTracer(*this);
}

Agent* Virus::clone() { //has a default copy constructor so that's not critical
    return new Virus(*this);
}

void ContactTracer::act(Session &session) {
    vector<vector<int>>* edges=session.getCurrPointer()->getEdgesPointer();
    int rootLabel=session.dequeueInfected();
    if(rootLabel!=-1){
        Tree* tree=Tree::createTree(session,rootLabel);
        int indToRemove=tree->traceTree();
        for(int& elem:(*edges)[indToRemove])//set the row to 0
            elem=0;
        for (int i = 0; i < edges->size(); ++i)//set the column to 0
            (*edges)[i][indToRemove]=0;
        delete(tree);
    }
}

void Virus::act(Session &session) {
    Graph g=session.getGraphReference();
    if(!g.isInfected(nodeInd)){
        g.infectNode(nodeInd);
        session.enqueueInfected(nodeInd);
    }
    int healthyNeighbor=g.healthyNeighbor(nodeInd);
    if(healthyNeighbor!=-1){
        //
        session.SetInfected((healthyNeighbor));

    }
}

ContactTracer::ContactTracer() = default;//לשאול אם ככה
Virus::Virus(int nodeInd):nodeInd(nodeInd){}