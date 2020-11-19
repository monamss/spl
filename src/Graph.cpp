#include "../include/Graph.h"
#include "../include/Session.h"

using namespace std;

Graph::Graph(std::vector<std::vector<int>> matrix):edges(matrix),infected(),yellow() {}

void Graph::infectNode(int nodeInd) {
    infected.push_back(nodeInd);
}

bool Graph::isInfected(int nodeInd) {
    for(int node:infected)
        if(node==nodeInd)
            return true;
    return false;
}

int Graph::dequeueInfected() {//maybe there's another way
    if(infected.empty())
        return -1;
    int dequeued = infected.front();
    infected.erase(infected.begin());
    return dequeued;
}

std::vector<int>& Graph::getInfectedVector() {
    return infected;
}

std::vector<std::vector<int>>& Graph::getEdges() {
    return edges;
}

int Graph::healthyNeighbor(int nodeInd,Session session) {
    int size=edges[nodeInd].size();
    for (int i = 0; i < size; ++i) {
        if((edges[nodeInd][i]==1)&&(!isInfected(i)))
            //if(edges[nodeInd][i]==1&&!session.isAgent(i))
            return i;
    }
    return -1;
}

bool Graph::isYellow(int nodeInd) {
    for(int node:yellow)
        if(node==nodeInd)
            return true;
    return false;
}

void Graph::deleteEdges(int nodeInd) {
    int size=edges.size();
    for (int i = 0; i < size; ++i) {
        edges[i][nodeInd]=0;
        edges[nodeInd][i]=0;
    }
}

Tree *Graph::BFS(int start, const Session &session) {/*
    Tree* root=Tree::createTree(session,start);
    int length=edges.size();
    vector<bool> visited(length, false);
    vector<Tree*> q;
    q.push_back(root);
    visited[start]=true;
    Tree* vis;
    while (!q.empty()){
        vis=q[0];
        // holds the current node
        q.erase(q.begin());
        // for ever adjacent vertex to the current vertex
        for (int i = 0; i < length; ++i) {
            if(edges[vis->getRootNode()][i]==1&&!visited[i]) {
                Tree *i_child = Tree::createTree(session, i);
                vis->addchild(i_child);
                q.push_back(vis->getChildren().at(vis->getNumOfChildren()-1));
                delete(i_child);
                visited[i]=true;
            }
        }
    }
    return root;*/
    Tree* root=Tree::createTree(session,start);
    vector<bool> visited=vector<bool>(edges.size(), false);
    vector<Tree*> toVisit=vector<Tree*>();
    toVisit.push_back(root);
    //visited.at(root->getRootNode())=true;
    visited[start]=true;
    while (!toVisit.empty()){
        Tree* node=toVisit.front();
        toVisit.erase(toVisit.begin());
        vector<int> neighbours=vector<int>();
        for (unsigned int i = 0; i < edges.size(); ++i)
            if(edges[node->getRootNode()][i]==1)
                neighbours.push_back(i);
        for (unsigned int i = 0; i < neighbours.size(); ++i) {
            if(!visited.at(neighbours.at(i))){
                visited.at(neighbours.at(i))=true;
                Tree* neighbour=Tree::createTree(session,i);//????
                node->addChild(*neighbour);
                toVisit.push_back(node->GetChild(node->getNumOfChildren()-1));
                delete(neighbour);
            }
        }
    }
    return root;
}

std::vector<int> &Graph::getYellow() {
    return yellow;
}