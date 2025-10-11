#ifndef _DEQUE_H_
#define _DEQUE_H_
#include "Node.H"
#include <iostream>


template<class T> std::ostream& operator<<(std::ostream& osParam, const Deque<T>& objParam);

/**
 * @class Deque
 * @brief A generic double-ended queue (deque) implementation using a doubly linked list.
 * @details This class provides methods to add and remove elements from both ends of the deque,
 *          as well as methods to access elements, check size, and clear the deque.
 * @tparam T The type of elements stored in the deque.
 */
template<class T> class Deque
{
public:
    enum Direction
    {
        START  = -1,
        END    = 1
    };

protected:
    size_t mSize=0;
    Node<T> *mHead=nullptr;
    Node<T> *mTail=nullptr;

public:
    Deque();
    Deque(const size_t& osizeParam,const T& dataParam);
    virtual ~Deque();
    void pushBack(const T& dataParam);
    void popBack(void);
    void pushFront(const T& dataParam);
    void popFront(void);
    const T& front(void) const;
    const T& back(void) const;
    bool empty(void) const;
    size_t size(void) const;
    void resize(const size_t& osizeParam,const T& dataParam,const int8_t& directionParam);
    void clear(void);
    const T& operator[](size_t osizeParam) const;
    friend std::ostream& operator<< <T>(std::ostream& osParam, const Deque<T>& objParam);
    void operator=(const T& dataParam) = delete; // if required, can be defined with deep copy
};

/**
 * @brief Default Constructor for Deque class
 * @details This constructor initializes an empty Deque object with size 0 and null head and tail pointers.
 * @param None
 * @return None
 */
template<class T> Deque<T>::Deque() : mSize(0), mHead(nullptr), mTail(nullptr)
{

}

/**
 * @brief Parameterized Constructor for Deque class
 * @details This constructor initializes a Deque object with a specified size and fills it with a given default value.
 *          It creates nodes in a doubly linked list structure to represent the deque.
 * @param osizeParam The initial size of the deque.
 * @param dataParam The default value to fill the deque with.
 * @return None
 */
template<class T> Deque<T>::Deque(const size_t& osizeParam,const T &dataParam)
{
    size_t sItr;
    for(sItr=0;sItr<osizeParam;sItr++)
    {
        if(nullptr==mHead && nullptr==mTail)
        {
            mHead = new Node<T>(dataParam);
            mTail = mHead;
            mSize++;
        }
        else
        {
            mTail->mNextNode = new Node<T>(dataParam,mTail);
            mTail = mTail->mNextNode;
            mSize++;
        }
    }
}

/**
 * @brief Destructor for Deque class
 * @details This destructor cleans up the Deque object by deleting all nodes in the doubly linked list.
 *          It ensures that all dynamically allocated memory is properly released to prevent memory leaks.
 * @param None
 * @return None
 */
template<class T> Deque<T>::~Deque()
{
    if(nullptr==mHead && nullptr==mTail)
    {
        return;
    }
    else
    {
        Node<T> *sItr;
        for(sItr=mHead;sItr!=nullptr;sItr=mHead){
            mHead = mHead->mNextNode;
            delete sItr;
        }
        mHead = mTail = nullptr;
        mSize = 0;
    }
}

/**
 * @brief Adds an element to the end of the deque.
 * @details This method creates a new node with the provided data and appends it to the end of the deque.
 *          If the deque is empty, it initializes both head and tail pointers to the new node.
 * @param dataParam The data to be added to the end of the deque.
 * @return None
 */
template<class T> void Deque<T>::pushBack(const T& dataParam)
{
    if(nullptr==mHead && nullptr==mTail)
    {
        mHead = new Node<T>(dataParam);
        mTail = mHead;
        mSize++;
        return;
    }
    else
    {
        mTail->mNextNode = new Node<T>(dataParam,mTail);
        mTail = mTail->mNextNode;
        mSize++;
        return;
    }
}

/**
 * @brief Removes an element from the end of the deque.
 * @details This method removes the last node from the deque and updates the tail pointer accordingly.
 *          If the deque is empty, it does nothing. If there is only one element, it clears both head and tail pointers.
 * @param None
 * @return None
 */
template<class T> void Deque<T>::popBack(void)
{
    if(nullptr==mHead && nullptr==mTail)
    {
        return;
    }
    else if(mHead==mTail)
    {
        delete mHead;
        mHead = mTail = nullptr;
        mSize--;
        return;
    }
    else
    {
        Node<T>* sTemp = mTail;
        mTail = mTail->mPrevNode;
        mTail->mNextNode = nullptr;
        delete sTemp;
        mSize--;
        return;
    }
}

/**
 * @brief Adds an element to the front of the deque.
 * @details This method creates a new node with the provided data and inserts it at the front of the deque.
 *          If the deque is empty, it initializes both head and tail pointers to the new node.
 * @param dataParam The data to be added to the front of the deque.
 * @return None
 */
template<class T> void Deque<T>::pushFront(const T& dataParam)
{
    if(nullptr==mHead && nullptr==mTail)
    {
        pushBack(dataParam);
        return;
    }
    else
    {
        mHead->mPrevNode = new Node<T>(dataParam,nullptr,mHead);
        mHead = mHead->mPrevNode;
        mSize++;
        return;
    }
}

/**
 * @brief Removes an element from the front of the deque.
 * @details This method removes the first node from the deque and updates the head pointer accordingly.
 *          If the deque is empty, it does nothing. If there is only one element, it clears both head and tail pointers.
 * @param None
 * @return None
 */
template<class T> void Deque<T>::popFront(void)
{
    if(nullptr==mHead && nullptr==mTail)
    {
        return;
    }
    else if(mHead==mTail)
    {
        delete mHead;
        mHead = mTail = nullptr;
        mSize--;
        return;
    }
    else
    {
        mHead = mHead->mNextNode;
        delete mHead->mPrevNode;
        mHead->mPrevNode = nullptr;
        mSize--;
        return;
    }
}

/**
 * @brief Accesses the first element of the deque.
 * @details This method returns a constant reference to the data stored in the head node of the deque.
 *          If the deque is empty, it returns a default-constructed object of type T.
 * @param None
 * @return A constant reference to the data of the first element in the deque, or a default-constructed T if empty.
 */
template<class T> const T& Deque<T>::front(void) const
{
    if(nullptr==mHead && nullptr==mTail)
    {
        return T();  // we can use std::optional if allowed
    }
    return mHead->mNodeData;
}

/**
 * @brief Accesses the last element of the deque.
 * @details This method returns a constant reference to the data stored in the tail node of the deque.
 *          If the deque is empty, it returns a default-constructed object of type T.
 * @param None
 * @return A constant reference to the data of the last element in the deque, or a default-constructed T if empty.
 */
template<class T> const T& Deque<T>::back(void) const
{
    if(nullptr==mHead && nullptr==mTail)
    {
        return T();  // we can use std::optional if allowed
    }
    return mTail->mNodeData;
}

/**
 * @brief Checks if the deque is empty.
 * @details This method returns true if both head and tail pointers are null, indicating that the deque has no elements.
 *          Otherwise, it returns false.
 * @param None
 * @return true if the deque is empty, false otherwise.
 */
template<class T> bool Deque<T>::empty(void) const
{
    if(nullptr==mHead && nullptr==mTail)
        return true;
    else
        return false;
}

/**
 * @brief Returns the number of elements in the deque.
 * @details This method returns the current size of the deque, which is maintained as a member variable.
 * @param None
 * @return The number of elements in the deque.
 */
template<class T> size_t Deque<T>::size(void) const
{
    return mSize;
}

/**
 * @brief Resizes the deque to a new size, adding or removing elements as necessary.
 * @details This method adjusts the size of the deque to the specified new size. If the new size is greater than
 *          the current size, it adds elements with the provided default value at the specified direction (START or END).
 *          If the new size is smaller, it removes elements from the specified direction.
 * @param osizeParam The new size of the deque.
 * @param dataParam The default value to use when adding new elements.
 * @param directionParam The direction from which to add or remove elements (1 for END, -1 for START).
 * @return None
 */
template<class T> void Deque<T>::resize(const size_t& osizeParam,const T& dataParam,const int8_t& directionParam)
{
    if(static_cast<Direction>(directionParam)==Direction::END)
    {
        if(osizeParam>mSize)
        {
            size_t sItr;
            for(sItr=mSize;sItr<osizeParam;sItr++)
            {
                pushBack(dataParam);
            }
        }
        else if(osizeParam<mSize)
        {
            size_t sItr;
            for(sItr=mSize;sItr>osizeParam;sItr--)
            {
                popBack();
            }
        }
        return;
    }
    else if(static_cast<Direction>(directionParam)==Direction::START)
    {
        if(osizeParam>mSize)
        {
            size_t sItr;
            for(sItr=mSize;sItr<osizeParam;sItr++)
            {
                pushFront(dataParam);
            }
        }
        else if(osizeParam<mSize)
        {
            size_t sItr;
            for(sItr=mSize;sItr>osizeParam;sItr--)
            {
                popFront();
            }
        }
        return;
    }
        
}

/**
 * @brief Clears all elements from the deque.
 * @details This method removes all nodes from the deque, effectively resetting it to an empty state.
 *          It deletes each node to free up memory and sets the head and tail pointers to null, with size set to 0.
 * @param None
 * @return None
 */
template<class T> void Deque<T>::clear(void)
{
    if(nullptr==mHead && nullptr==mTail)
    {
        return;
    }
    else
    {
        Node<T> *sItr;
        for(sItr=mHead;sItr!=nullptr;sItr=mHead){
            mHead = mHead->mNextNode;
            delete sItr;
        }
        mHead = mTail = nullptr;
        mSize = 0;
        return;
    }
}

/**
 * @brief Accesses an element at a specific index in the deque.
 * @details This method returns a constant reference to the data stored in the node at the specified index.
 *          If the index is out of bounds or the deque is empty, it returns a default-constructed object of type T.
 * @param osizeParam The index of the element to access (0-based).
 * @return A constant reference to the data of the element at the specified index, or a default-constructed T if out of bounds or empty.
 */
template<class T> const T& Deque<T>::operator[](size_t osizeParam) const
{
    if((osizeParam>mSize) || (nullptr==mHead))
    {
        return T(); // we can use std::optional if allowed
    }
    size_t temp_count=0;
    if(osizeParam>=mSize/2)
    {
        temp_count = mSize;
        Node<T> *sItr;
        for(sItr=mTail;sItr!=nullptr;sItr=sItr->mPrevNode)
        {
            if(temp_count--==osizeParam)
                return sItr->mNodeData;
        }
    }
    Node<T> *sItr;
    for(sItr=mHead;sItr!=nullptr;sItr=sItr->mNextNode)
    {
        if(++temp_count==osizeParam)
            return sItr->mNodeData;
    }
    return T();
}

/**
 * @brief Overloads the output stream operator to print the contents of the deque.
 * @details This function iterates through the nodes of the deque and outputs their data to the provided output stream.
 *          If the deque is empty, it outputs a message indicating that the deque is empty.
 * @param osParam The output stream to which the deque contents will be written.
 * @param objParam The Deque object whose contents are to be printed.
 * @return A reference to the output stream after writing the deque contents.
 */
template<class T> std::ostream& operator<<(std::ostream& osParam, const Deque<T>& objParam)
{
    if(nullptr==objParam.mHead && nullptr==objParam.mTail)
    {
        osParam<<"Queue is empty!"<<std::endl;
        return osParam;
    }
    else
    {
        Node<T> *sItr;
        for(sItr=objParam.mHead;sItr!=nullptr;sItr=sItr->mNextNode)
        {
            osParam<<sItr->mNodeData<<" ";
        }
        osParam<<std::endl;
        return osParam;
    }
}
#endif