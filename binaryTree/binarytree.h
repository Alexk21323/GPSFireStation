#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include "node.h"

enum BINARY_TREE_ERRORS {TREE_EMPTY, TREE_FULL};
enum BINARY_TREE_TRAVERSAL {IN_ORDER, PRE_ORDER, POST_ORDER};

template<typename Data>
class binaryTree
{
    public:
        binaryTree();
        binaryTree(const Data &d, int c = 1);
        ~binaryTree();
        binaryTree(const binaryTree<Data> &other);
        binaryTree<Data>& operator=(const binaryTree<Data> &other);

        bool empty();
        bool full();
        void insert(const Data &d, int c = 1);
        binaryTree<Data>& operator<<(const Data &d);
        void deleteData(const Data &d, int c = 1);
        unsigned int dataCount();
        unsigned int nodeCount();
        int height();
        BINARY_TREE_TRAVERSAL& traversal();

        template<typename d>
        friend
        std::ostream& operator<<(std::ostream& out, const binaryTree<d> &other);

        template<typename d>
        friend
        std::istream& operator>>(std::istream& out, const binaryTree<d> &other);


    private:
        node<Data> *root;
        BINARY_TREE_TRAVERSAL method;

        void copy(node<Data> *r);
        void deleteAllNodes(node<Data> *&r);
        int height(node<Data> *n);
        unsigned int nodeCount(node<Data> *n);
        unsigned int dataCount(node<Data> *n);
        void print(std::ostream &out, node<Data> *r) const;
        node<Data>* find(const Data &d, node<Data> *r, node<Data>* &parent, bool &lessThan);
        node<Data>* findSmallestOnGreaterThanSide(node<Data>* r);
        void deleteLessThanNode(node<Data>* &child,node<Data>* parent);
        void deleteGreaterThanNode(node<Data>* &child, node<Data>* parent);
        void rebalance();
};

template<typename Data>
binaryTree<Data>::binaryTree()
{
    root = nullptr;
    method = IN_ORDER;
}

template<typename Data>
binaryTree<Data>::binaryTree(const Data &d, int c)
{
    root = new node<Data>(d,c);
    method = IN_ORDER;
}

template<typename Data>
binaryTree<Data>::~binaryTree()
{
    deleteAllNodes(root);
}

template<typename Data>
binaryTree<Data>::binaryTree(const binaryTree<Data> &other)
{
    copy(other);
}

template<typename Data>
binaryTree<Data>& binaryTree<Data>::operator=(const binaryTree<Data> &other)
{
    if(this != &other)
    {
        deleteAllNodes();
        copy(other);
    }
    return *this;
}

template<typename Data>
bool binaryTree<Data>::empty()
{
    return !root;
}

template<typename Data>
bool binaryTree<Data>::full()
{
    return false;
}

template<typename Data>
void binaryTree<Data>::insert(const Data &d, int c)
{
    node<Data> *insertPoint, *newNode = new node<Data>(d,c);
    if(empty())
        root = newNode;
    else
    {
        bool cont = true;
        insertPoint = root;
        while(insertPoint && cont)
        {
            if(*newNode == *insertPoint)
            {
                *insertPoint += *newNode;
                delete newNode;
                return;
            }
            if(*newNode < *insertPoint)
            {
                if(!insertPoint->lThan)
                   cont = false;
                else
                    insertPoint = insertPoint->lThan;
             }
             else
             {
                if(!insertPoint->gThan)
                   cont = false;
                else
                    insertPoint = insertPoint->gThan;
             }
         }
         if(*newNode < *insertPoint)
             insertPoint->lThan = newNode;
         else
            insertPoint->gThan = newNode;
    }
    //rebalance();
}

template<typename Data>
binaryTree<Data>& binaryTree<Data>::operator<<(const Data &d)
{
    insert(d);
    return *this;
}

template<typename Data>
void binaryTree<Data>::deleteData(const Data &d, int c)
{
    bool lessThan;
    node<Data> *parent = nullptr, *child = find(d,root,parent, lessThan);
    if(child)
        if((child->count -= c) < 1)
        {
            if(lessThan)
                deleteLessThanNode(child, parent);
            else
                deleteGreaterThanNode(child, parent);
           // rebalance();
        }
}


template<typename Data>
void binaryTree<Data>::deleteLessThanNode(node<Data>* &child,node<Data>* parent)
{
    if(child->gThan)
    {
        parent->lThan = child->gThan;
        findSmallestOnGreaterThanSide(child->gThan)->lThan = child->lThan;
        delete child;
    }
    else
    {
        parent->lThan = child->lThan;
        delete child;
    }
}

template<typename Data>
void binaryTree<Data>::deleteGreaterThanNode(node<Data>* &child,node<Data>* parent)
{
    node<Data> *temp;
    if(parent == root)
    {
        if(root->gThan)
        {
            root = root->gThan;
            temp = findSmallestOnGreaterThanSide(root);
            temp->lThan = parent->lThan;
            delete parent;
        }
        else
        {
            root = root->lThan;
            delete parent;
        }
    }
    else
    {
        if(child->gThan)
        {
            parent->gThan = child->gThan;
            temp = findSmallestOnGreaterThanSide(child->gThan);
            temp->lThan = child->lThan;
            delete child;
        }
        else
        {
            parent->lThan = child->lThan;
            delete child;
        }
    }
}


template<typename Data>
node<Data>* binaryTree<Data>::find(const Data &d, node<Data> *r, node<Data>* &parent, bool &lessThan)
{
     parent = r;
     lessThan = true;
     bool cont = true;
     while(r && cont)
     {
         std::cout<<"r contains: "<<*r<<std::endl;
         if(d < r->data)
         {
             parent = r;
             r = r->lThan;
         }
         if(d == r->data)
         {
            lessThan = r == parent->lThan;
            cont = false;
         }
         if(d > r->data)
         {
             parent = r;
             r = r->gThan;
         }
     }
     return r;
}

template<typename Data>
node<Data>* binaryTree<Data>::findSmallestOnGreaterThanSide(node<Data> *r)
{
    for(; r->lThan != nullptr; r = r->lThan);
    return r;
}

template<typename Data>
unsigned int binaryTree<Data>::dataCount()
{
    return dataCount(root);
}

template<typename Data>
unsigned int binaryTree<Data>::nodeCount()
{
    return nodeCount(root);
}

template<typename Data>
int binaryTree<Data>::height()
{
    return height(root);
}

template<typename Data>
int binaryTree<Data>::height(node<Data> *n)
{
    return !n ? 0 : 1 + std::max(height(n->lThan), height(n->gThan));
//    return n == nullptr ? 0 : 1 + max(height(n.lThan), height(n.gThan));

}

template<typename Data>
unsigned int binaryTree<Data>::nodeCount(node<Data> *n)
{
    return !n ? 0 : 1 + nodeCount(n->lThan) + nodeCount(n->gThan);
}

template<typename Data>
unsigned int binaryTree<Data>::dataCount(node<Data> *n)
{
    return !n ? 0 : n->count + dataCount(n->gThan) + dataCount(n->lThan);
}

template<typename Data>
BINARY_TREE_TRAVERSAL& binaryTree<Data>::traversal()
{
    return method;
}

template<typename Data>
void binaryTree<Data>::copy(node<Data> *r)
{
    if(r)
    {
        insert(r->data, r->count);
        copy(r->lThan);
        copy(r->gThan);
    }
}

template<typename Data>
void binaryTree<Data>::deleteAllNodes(node<Data>* &r)
{
    if(r)
    {
        deleteAllNodes(r->lThan);
        deleteAllNodes(r->gThan);
        delete r;
        r = nullptr;
    }
}


template<typename Data>
void binaryTree<Data>::print(std::ostream &out, node<Data> *r) const
{
    if(r)
    {
        if(method == PRE_ORDER)
            out<<r->data<<"["<<r->count<<"] ";
        print(out, r->lThan);
        if(method == IN_ORDER)
            out<<r->data<<"["<<r->count<<"] ";
        print(out, r->gThan);
        if(method == POST_ORDER)
            out<<r->data<<"["<<r->count<<"] ";
    }
}

template<typename Data>
void binaryTree<Data>::rebalance()
{
    node<Data> *unbalancedPoint = root, *toMove;
    if(!root || abs(static_cast<double>(height(root->lThan) - height(root->gThan))) <= 1)
        return;
/*
 * Try to find where tree looks like:
 *
 *    node          node                node            node
 *        \            \                 /               /
 *        node         node            node             node
 *        /              \             /                  \
 *       node             node       node                 node
 */
    while(abs(static_cast<double>(height(unbalancedPoint->lThan) - height(unbalancedPoint->gThan))) >= 2)
    {
        unbalancedPoint = height(unbalancedPoint->lThan) - height(unbalancedPoint->gThan) > 0
                          ?
                          unbalancedPoint->lThan : unbalancedPoint->gThan;
    }
    if(height( unbalancedPoint->lThan) == 0)  //See if heavier on the greather than size
/*
 * Tree must look like
 *     node                 node
 *         \                    \
 *          node      or         node
 *         /                       \
 *      node                        node
 */
        if(unbalancedPoint->gThan->gThan)
        {
            toMove = unbalancedPoint->gThan->gThan;
            unbalancedPoint->gThan = toMove->gThan;
            unbalancedPoint->lThan = toMove;
            toMove->gThan = nullptr;
            toMove->swap(*unbalancedPoint);
        }
        else
        {
            toMove = unbalancedPoint->gThan->lThan;
            unbalancedPoint->lThan = toMove;
            unbalancedPoint->lThan = nullptr;
            toMove->swap(*unbalancedPoint);
        }
    else
/*
 * Tree must look like if we are here
 *          node                 node
 *          /                    /
 *        node      or         node
 *          \                  /
 *           node            node
 */
        if(unbalancedPoint->lThan->lThan)
        {
            toMove = unbalancedPoint->lThan;
            unbalancedPoint->lThan = toMove->lThan;
            toMove->lThan = nullptr;
            unbalancedPoint->gThan = toMove;
            toMove->swap(*unbalancedPoint);
        }
        else
        {
            toMove = unbalancedPoint->lThan->gThan;
            unbalancedPoint->gThan = toMove;
            unbalancedPoint->gThan = nullptr;
            toMove->swap(*unbalancedPoint);
        }
}


template<typename d>
std::ostream& operator<<(std::ostream& out, const binaryTree<d> &other)
{
    other.print(out, other.root);
    return out;
}

template<typename d>
std::istream& operator>>(std::istream& in, binaryTree<d> &other)
{
    node<d> temp;
    other.deleteAllNodes(other.root);
    while(in>>temp)
         other.insert(temp.data,temp.count);
    return in;
}

#endif // BINARYTREE_H
