#include "../include/Graph.h"
#include "../include/Session.h"

using namespace std;

Graph::Graph(std::vector<std::vector<int>> matrix):edges(matrix) {}

void Graph::infectNode(int nodeInd) {
    infected.push_back(nodeInd);
}

bool Graph::isInfected(int nodeInd) {
    for (int i = 0; i < infected.size(); ++i) {
        if(infected[i]==nodeInd)
            return true;
    }
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
    for (int i = 0; i < edges[nodeInd].size(); ++i) {
        //if(edges[nodeInd][i]==1&&!isInfected(i))
        if(edges[nodeInd][i]==1&&!session.isAgent(i))
            return i;
    }
    return -1;
}

bool Graph::isYellow(int node) {
    for (int i = 0; i < yellow.size(); ++i) {
        if(yellow[i]==node)
            return true;
    }
    return false;
}

void Graph::deleteEdges(int nodeInd) {
    for (int i = 0; i < edges.size(); ++i) {
        edges[i][nodeInd]=0;
        edges[nodeInd][i]=0;
    }
}

int Graph::getInfectedNode() {
    return dequeueInfected();
}

Tree *Graph::BFS(int start, const Session &session) {
    Tree* root=Tree::createTree(session,start);
    int length=edges.size();
    vector<bool> visited(length, false);
    vector<Tree*> q;
    q.push_back(root);
    visited[start]=true;
    Tree* vis;
    while (!q.empty()){
        vis=q[0];
        // print the current node
        q.erase(q.begin());
        // for ever adjacent vertex to the current vertex
        for (int i = 0; i < length; ++i) {
            if(edges[vis->getRootNode()][i]==1&&!visited[i]) {
                Tree *i_child = Tree::createTree(session, i);
                vis->addchild(i_child);
                q.push_back(i_child);
                visited[i]=true;
            }
        }
    }
    return root;
}

std::vector<int> &Graph::getYellow() {
    return yellow;
}
