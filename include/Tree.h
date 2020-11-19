#ifndef TREE_H_
#define TREE_H_

#include <vector>

class Session;

class Tree{
public:
    Tree(int rootLabel);
    void addChild(const Tree& child);
    int getRootNode() const;
    static Tree* createTree(const Session& session, int rootLabel);
    virtual int traceTree()=0;
    const Tree& getChild(int) const;
    Tree* GetChild(int) const;
    void addchild(Tree* child);
    virtual Tree* clone() const=0;
    int getNumOfChildren() const;
    int getNode() const;
    std::vector<Tree*> getChildren();
    //RULE OF FIVE
    virtual ~Tree();
    Tree(const Tree& other);
    Tree& operator=(const Tree& other);
    Tree(Tree&& other);
    Tree& operator=(Tree&& other);
    void clean();
    void steal(Tree& other);
    void copy(const Tree& other);

private:
    int node;
    std::vector<Tree*> children;
};

class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    virtual int traceTree();
    virtual Tree* clone() const;

private:
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    virtual int traceTree();
    virtual Tree* clone() const;
};

class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    virtual int traceTree();
    virtual Tree* clone() const;
};

#endif