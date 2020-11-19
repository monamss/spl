#include "../include/Tree.h"
#include "../include/Session.h"
using namespace std;

Tree::Tree(int rootLabel):node(rootLabel),children(vector<Tree*>(0)) {}

Tree & Tree::operator=(const Tree &other) {
    if(this!=&other) {
        clean();
        copy(other);
    }
    return *this;
}

Tree & Tree::operator=(Tree &&other) {
    if (this != &other) {
        clean();
        steal(other);
    }
    return *this;
}

Tree::~Tree() {clean();}

Tree::Tree(Tree &&other):node(other.node),children(vector<Tree*>(0)) {steal(other);}

Tree::Tree(const Tree &other):node(other.node),children(vector<Tree*>(0)) {copy(other);}

void Tree::clean() {
    int size=children.size();
    for (int i = 0; i < size; ++i) {
        delete (children[i]);
        children.at(i)= nullptr;
    }
}

void Tree::copy(const Tree &other) {
    int size=other.children.size();
    for (int i = 0; i < size; ++i) {
        children.push_back(other.children[i]->clone());
    }
}

void Tree::steal(Tree &other) {
    int size=other.children.size();
    for (int i = 0; i < size; ++i) {
        children.push_back(other.children[i]->clone());
        delete (children[i]);
        children[i]= nullptr;
    }
}

Tree * Tree::createTree(const Session &session, int rootLabel) {
    TreeType type=session.getTreeType();
    if(type==Cycle)
        return new CycleTree(rootLabel, session.getNumOfCycle());
    else if(type==MaxRank)
        return new MaxRankTree(rootLabel);
    else
        return new RootTree(rootLabel);
}

void Tree::addChild(const Tree &child) {
    children.push_back(child.clone());
}

int Tree::getRootNode() const {
    return node;
}

void Tree::addchild(Tree *child) {
    children.push_back(child->clone());
}

int Tree::getNumOfChildren() const {
    return children.size();
}

int Tree::getNode() const {
    return children.front()->node;
}

const Tree & Tree::getChild(int i) const {
    return *children.at(i);
}

std::vector<Tree *> Tree::getChildren() {return children;}

Tree* Tree::GetChild(int i) const {
    return children.at(i);
}

CycleTree::CycleTree(int rootLabel, int currCycle):Tree(rootLabel),currCycle(currCycle) {}
Tree * CycleTree::clone() const {
    CycleTree* cloned=new CycleTree(getRootNode(),currCycle);
    for (int i = 0; i < getNumOfChildren(); ++i) {
        cloned->addChild(*GetChild(i));
    }
    return cloned;
}
int CycleTree::traceTree() {/*
    const Tree* currentTree=this;
    int curr=0;
    while((curr<currCycle)&&(currentTree->getNumOfChildren()!=0)) {
        currentTree=&currentTree->getChild(0);
        curr++;
    }
    return currentTree->getRootNode();*/

    const Tree* currentTree=this;
    int curr=currCycle;
    for (int i = 0; i < curr; ++i) {
        if(currentTree->getNumOfChildren()!=0){
            currentTree=currentTree->GetChild(0);
        }
    }
    return currentTree->getRootNode();

}

MaxRankTree::MaxRankTree(int rootLabel):Tree(rootLabel) {}
Tree * MaxRankTree::clone() const {
    MaxRankTree* cloned=new MaxRankTree(getRootNode());
    for (int i = 0; i < getNumOfChildren(); ++i) {
        cloned->addChild(*GetChild(i));
    }
    return cloned;
}
int MaxRankTree::traceTree() {/*
    queue<const Tree*> que;
    que.push(this);
    int childrenNum=getNumOfChildren();
    int nodeValue=getRootNode();
    while(!que.empty()){
        const Tree* help=que.front();
        que.pop();
        if(help->getNumOfChildren()>childrenNum){
            childrenNum=help->getNumOfChildren();
            //delete?
            nodeValue=help->getRootNode();
        }
        else if(help->getNumOfChildren()==childrenNum&nodeValue)
        for (int i = 0; i < help->getNumOfChildren(); ++i) {
            que.push(&help->getChild(i));
        }
    }
    return nodeValue;*/
    int nodeVal=getRootNode();
    int depth=0;
    int currDepth=1;
    int maxRank=getNumOfChildren();
    vector<MaxRankTree> trees=vector<MaxRankTree>();
    MaxRankTree curr=MaxRankTree(0);
    trees.push_back(*this);
    while(!trees.empty()){
        curr=trees.at(0);
        for (int i = 0; i < curr.getNumOfChildren(); ++i) {
            int children=curr.getChild(i).getNumOfChildren();
            int currRoot=curr.getChild(i).getRootNode();
            if((children>maxRank)|((children==maxRank)&(currDepth==depth)&(currRoot<nodeVal))){
                nodeVal=currRoot;
                depth=currDepth;
                maxRank=children;
            }
            trees.push_back(curr);
        }
        currDepth++;
        trees.erase(trees.begin());
    }
    return nodeVal;
}

RootTree::RootTree(int rootLabel):Tree((rootLabel)) {}
Tree * RootTree::clone() const {
    RootTree* cloned=new RootTree(getRootNode());
    for (int i = 0; i < getNumOfChildren(); ++i) {
        cloned->addChild(*GetChild(i));
    }
    return cloned;
}
int RootTree::traceTree() {return this->getRootNode();}