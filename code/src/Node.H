#ifndef _NODE_H_
#define _NODE_H_
#include <iostream>

template<class T> class Deque;

/**
 * @class Node
 * @brief A class representing a node in a doubly linked list used in the Deque implementation.
 * @details This class encapsulates the data and pointers to the previous and next nodes in the deque.
 *          It provides constructors for initializing nodes and a destructor for cleanup.
 * @tparam T The type of data stored in the node.
 */
template<class T> class Node
{
protected:
    explicit Node(const T& dataParam,const Node<T>* const prevNodeParam=nullptr,const Node<T>* const nextNodeParam=nullptr);
    Node(const Node<T> &) = delete;
    Node(Node<T> &&objParam) = delete;
    virtual ~Node();
    T mNodeData;
    Node<T> *mPrevNode=nullptr;
    Node<T> *mNextNode=nullptr;
    template<class U> friend class Deque;
};

/**
 * @brief Construct the Node object
 * @details This constructor initializes a Node object with the provided data and optional pointers to the previous and next nodes.
 * @param dataParam The data to be stored in the node.
 * @param prevNodeParam Pointer to the previous node in the deque (default is nullptr).
 * @param nextNodeParam Pointer to the next node in the deque (default is nullptr).
 * @return None
 */
template<class T> Node<T>::Node(const T& dataParam,const Node<T>* const prevNodeParam,const Node<T>* const nextNodeParam)
{
    mNodeData = dataParam;
    mPrevNode = const_cast<Node<T>*>(prevNodeParam);
    mNextNode = const_cast<Node<T>*>(nextNodeParam);
}


/**
 * @brief Destructor for Node class
 * @details This destructor cleans up the Node object by setting its pointers to null.
 *          It does not delete the pointers as they are managed by the Deque class.
 * @param None
 * @return None
 */
template<class T> Node<T>::~Node()
{
    mPrevNode = mNextNode = nullptr;
}
#endif