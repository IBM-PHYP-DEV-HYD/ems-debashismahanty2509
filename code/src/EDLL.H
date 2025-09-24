#ifndef _EDLL_H_
#define _EDLL_H_
#include <iostream>
//class Declaration 
template<class T>class Deque;

/**
 * @brief Extended Double Linked List (EDLL) class that inherits from Deque.
 * @details This class extends the functionality of the Deque class by adding methods to insert and remove elements from the middle of the list.
 * @tparam T The type of elements stored in the EDLL.
 */
template<class T>
class EDLL : public Deque<T>
{
    public:
    EDLL();
    EDLL(const size_t& osizeParam,const T &dataParam);
    virtual ~EDLL() = default;
    void addElementMiddle(const T& dataParam,size_t posParam);
    void remElementMiddle(size_t osizeParam);
};

template<class T> EDLL<T>::EDLL(): Deque<T>()
{

}

template<class T> EDLL<T>::EDLL(const size_t& osizeParam,const T &dataParam) : Deque<T>(osizeParam,dataParam)
{

}

template<class T> void EDLL<T>::addElementMiddle(const T& dataParam, size_t posParam)
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
        if(posParam>mSize)
        {
            pushBack(dataParam);
            return;
        }
        Node<T>* sItr = mHead;
        for(size_t sItrIdx=0;sItrIdx<posParam-1;sItrIdx++)
        {
            sItr = sItr->mNextNode;
        }
        new Node<T>(dataParam,sItr,sItr->mNextNode);
        mSize++;
        return;
    }
}

template<class T> void EDLL<T>::remElementMiddle(size_t posParam)
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
        size_t tempCount=0;
        if(posParam>=mSize/2)
        {
            tempCount = mSize;
            Node<T> *sItr;
            for(sItr=mTail;sItr!=nullptr;sItr=sItr->mPrevNode)
            {
                if(tempCount--==posParam)
                {
                    sItr->mPrevNode->mNextNode = sItr->mNextNode;
                    if(nullptr!=sItr->mNextNode)
                        sItr->mNextNode->mPrevNode = sItr->mPrevNode;
                    delete sItr;
                    mSize--;
                    return;
                }
            }
        }
        Node<T> *sItr;
        for(sItr=mHead;sItr!=nullptr;sItr=sItr->mNextNode)
        {
            if(++tempCount==posParam)
            {
                sItr->mPrevNode->mNextNode = sItr->mNextNode;
                if(nullptr!=sItr->mNextNode)
                    sItr->mNextNode->mPrevNode = sItr->mPrevNode;
                delete sItr;
                mSize--;
                return;
            }
        }
    }
}
#endif
