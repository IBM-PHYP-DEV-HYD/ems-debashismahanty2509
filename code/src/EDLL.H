#ifndef _EDLL_H_
#define _EDLL_H_

//class Declaration 
template<class T>class Deque;

template<class T>
class EDLL : public Deque<T>
{
    public:
    EDLL();
    EDLL(const size_t& osizeParam,const T &dataParam);
    void addElementMiddle(const T& dataParam);
    void remElementMiddle(void);
};

template<class T> EDLL<T>::EDLL(): Deque<T>()
{

}

template<class T> EDLL<T>::EDLL(const size_t& osizeParam,const T &dataParam) : Deque<T>(osizeParam,dataParam)
{

}

template<class T> void EDLL<T>::addElementMiddle(const T& dataParam)
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
        size_t sMid = mSize/2;
        Node<T>* sItr = mHead;
        for(size_t sItrIdx=0;sItrIdx<sMid-1;sItrIdx++)
        {
            sItr = sItr->mNextNode;
        }
        new Node<T>(dataParam,sItr,sItr->mNextNode);
        mSize++;
        return;
    }
}

template<class T> void EDLL<T>::remElementMiddle(void)
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
        size_t sMid = mSize/2;
        Node<T>* sItr = mHead;
        for(size_t sItrIdx=0;sItrIdx<sMid-1;sItrIdx++)
        {
            sItr = sItr->mNextNode;
        }
        Node<T>* sTemp = sItr->mNextNode;
        sItr->mNextNode = sTemp->mNextNode;
        if(sTemp->mNextNode)
            sTemp->mNextNode->mPrevNode = sItr;
        delete sTemp;
        mSize--;
        return;
    }
}
#endif
