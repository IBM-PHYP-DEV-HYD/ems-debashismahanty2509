#ifndef _NODE_H_
#define _NODE_H_
#include <iostream>

template<class T> class Deque;
template<class T> class Node
{
    private:
    explicit Node(const T& dataParam,const Node<T>* const prevNodeParam=nullptr,const Node<T>* const nextNodeParam=nullptr);
    Node(const Node<T> &) = delete;
    Node(Node<T> &&objParam);
    virtual ~Node();
    T mNodeData_;
    Node<T> *mPrevNode_=nullptr;
    Node<T> *mNextNode_=nullptr;
    template<class U> friend class Deque;
};

template<class T> Node<T>::Node(const T& dataParam,const Node<T>* const prevNodeParam,const Node<T>* const nextNodeParam)
{
    mNodeData_ = dataParam;
    mPrevNode_ = const_cast<Node<T>*>(prevNodeParam);
    mNextNode_ = const_cast<Node<T>*>(nextNodeParam);
}
template<class T> Node<T>::Node(Node<T> &&objParam)
{
    mNodeData_ = objParam.mNodeData_;
    mPrevNode_ = objParam.mPrevNode_;
    mNextNode_ = objParam.mNextNode_;
    objParam.mPrevNode_ = objParam.mNextNode_ = nullptr;
}
template<class T> Node<T>::~Node()
{
    mPrevNode_ = mNextNode_ = nullptr;
}
#endif