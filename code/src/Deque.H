#ifndef _DEQUE_H_
#define _DEQUE_H_
#include "Node.H"
#include <iostream>
#define IDEBUG 0
using MY_OWN_SIZE = size_t;

template<class T> std::ostream& operator<<(std::ostream& osParam, const Deque<T>& objParam);
template<class T> class Deque
{
public:
    /*Member Types*/
    // template<class U>
    using IBM_NODE = Node<T>;
    using any_type_ref = const T&;
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    enum Direction : int8_t 
    {
        START=-1,
        END=1
    };

private:
    MY_OWN_SIZE mSize_=0;
    IBM_NODE *mHead_=nullptr;
    IBM_NODE *mTail_=nullptr;

public:
    Deque();
    Deque(const MY_OWN_SIZE& osizeParam,const_reference dataParam);
    virtual ~Deque();
    void push_back(const_reference dataParam);
    void pop_back(void);
    void push_front(const_reference dataParam);
    void pop_front(void);
    const_reference front(void) const;
    const_reference back(void) const;
    bool empty(void) const;
    MY_OWN_SIZE size(void) const;
    void resize(const MY_OWN_SIZE& osizeParam,const_reference dataParam,const int8_t& directionParam);
    void clear(void);
    const_reference operator[](MY_OWN_SIZE osizeParam) const;
    friend std::ostream& operator<< <T>(std::ostream& osParam, const Deque<T>& objParam);
    void operator=(any_type_ref dataParam) = delete; // if required, can be defined with deep copy

    //IBM_NODE* operator[](uint16_t osizeParam) const;
};

template<class T> Deque<T>::Deque()
{
    if(nullptr==mHead_ && nullptr==mTail_)
    {
        mHead_ = new IBM_NODE(T());
        mTail_ = mHead_;
        mSize_++;
    }
    else
    {
        mTail_->mNextNode_ = new IBM_NODE(T(),mTail_);
        mTail_ = mTail_->mNextNode_;
        mSize_++;
    }
}
template<class T> Deque<T>::Deque(const MY_OWN_SIZE& osizeParam,const T &dataParam)
{
    for(MY_OWN_SIZE i=0;i<osizeParam;i++)
    {
        if(nullptr==mHead_ && nullptr==mTail_)
        {
            mHead_ = new IBM_NODE(dataParam);
            mTail_ = mHead_;
            mSize_++;
        }
        else
        {
            mTail_->mNextNode_ = new IBM_NODE(dataParam,mTail_);
            mTail_ = mTail_->mNextNode_;
            mSize_++;
        }
    }
}
template<class T> void Deque<T>::push_back(const_reference dataParam)
{
    if(nullptr==mHead_ && nullptr==mTail_)
    {
        mHead_ = new IBM_NODE(dataParam);
        mTail_ = mHead_;
        mSize_++;
        return;
    }
    else
    {
        mTail_->mNextNode_ = new IBM_NODE(dataParam,mTail_);
        mTail_ = mTail_->mNextNode_;
        mSize_++;
        return;
    }
}
template<class T> void Deque<T>::pop_back(void)
{
    if(nullptr==mHead_ && nullptr==mTail_)
    {
        #if IDEBUG == 1
        std::cout<<"Queue is empty, cannot pop_back"<<std::endl;
        #endif
        return;
    }
    else if(mHead_==mTail_)
    {
        delete mHead_;
        mHead_ = mTail_ = nullptr;
        mSize_--;
        return;
    }
    else
    {
        IBM_NODE* sTemp = mTail_;
        mTail_ = mTail_->mPrevNode_;
        mTail_->mNextNode_ = nullptr;
        delete sTemp;
        mSize_--;
        return;
    }
}
template<class T> void Deque<T>::push_front(const_reference dataParam)
{
    if(nullptr==mHead_ && nullptr==mTail_)
    {
        push_back(dataParam);
        return;
    }
    else
    {
        mHead_->mPrevNode_ = new IBM_NODE(dataParam,nullptr,mHead_);
        mHead_ = mHead_->mPrevNode_;
        mSize_++;
        return;
    }
}
template<class T> void Deque<T>::pop_front(void)
{
    if(nullptr==mHead_ && nullptr==mTail_)
    {
        #if IDEBUG == 1
        std::cout<<"Queue is empty, cannot pop_front"<<std::endl;
        #endif
        return;
    }
    else if(mHead_==mTail_)
    {
        delete mHead_;
        mHead_ = mTail_ = nullptr;
        mSize_--;
        return;
    }
    else
    {
        mHead_ = mHead_->mNextNode_;
        delete mHead_->mPrevNode_;
        mHead_->mPrevNode_ = nullptr;
        mSize_--;
        return;
    }
}
template<class T> typename Deque<T>::const_reference Deque<T>::front(void) const
{
    if(nullptr==mHead_ && nullptr==mTail_)
    {
        #if IDEBUG == 1
        std::cerr<<"Queue is empty, cannot return front"<<std::endl;
        #endif
        return T();  // we can use std::optional if allowed
    }
    return mHead_->mNodeData_;
}
template<class T> typename Deque<T>::const_reference Deque<T>::back(void) const
{
    if(nullptr==mHead_ && nullptr==mTail_)
    {
        #if IDEBUG == 1
        std::cerr<<"Queue is empty, cannot return back"<<std::endl;
        #endif
        return T();  // we can use std::optional if allowed
    }
    return mTail_->mNodeData_;
}
template<class T> bool Deque<T>::empty(void) const
{
    if(nullptr==mHead_ && nullptr==mTail_)
        return true;
    else
        return false;
}
template<class T> MY_OWN_SIZE Deque<T>::size(void) const
{
    return mSize_;
}
template<class T> void Deque<T>::resize(const MY_OWN_SIZE& osizeParam,const_reference dataParam,const int8_t& directionParam)
{
    if(static_cast<Direction>(directionParam)==Direction::END)
    {
        if(osizeParam>mSize_)
        {
            for(MY_OWN_SIZE i=mSize_;i<osizeParam;i++)
            {
                push_back(dataParam);
            }
        }
        else if(osizeParam<mSize_)
        {
            for(MY_OWN_SIZE i=mSize_;i>osizeParam;i--)
            {
                pop_back();
            }
        }
        return;
    }
    else if(static_cast<Direction>(directionParam)==Direction::START)
    {
        if(osizeParam>mSize_)
        {
            for(MY_OWN_SIZE i=mSize_;i<osizeParam;i++)
            {
                push_front(dataParam);
            }
        }
        else if(osizeParam<mSize_)
        {
            for(MY_OWN_SIZE i=mSize_;i>osizeParam;i--)
            {
                pop_front();
            }
        }
        return;
    }
        
}
template<class T> void Deque<T>::clear(void)
{
    if(nullptr==mHead_ && nullptr==mTail_)
    {
        return;
    }
    else
    {
        for(IBM_NODE *sItr=mHead_;sItr!=nullptr;sItr=mHead_){
            mHead_ = mHead_->mNextNode_;
            delete sItr;
        }
        mHead_ = mTail_ = nullptr;
        mSize_ = 0;
        return;
    }
}
template<class T> typename Deque<T>::const_reference Deque<T>::operator[](MY_OWN_SIZE osizeParam) const
{
    if((osizeParam>mSize_) || (nullptr==mHead_))
    {
        #if IDEBUG == 1
        std::cerr<<"Queue is empty or trying out of index"<<std::endl;
        #endif
        return T(); // we can use std::optional if allowed
    }
    MY_OWN_SIZE temp_count=0;
    if(osizeParam>=mSize_/2)
    {
        temp_count = mSize_;
        for(IBM_NODE *sItr=mTail_;sItr!=nullptr;sItr=sItr->mPrevNode_)
        {
            if(temp_count--==osizeParam)
                return sItr->mNodeData_;
        }
    }
    for(IBM_NODE *sItr=mHead_;sItr!=nullptr;sItr=sItr->mNextNode_)
    {
        if(++temp_count==osizeParam)
            return sItr->mNodeData_;
    }
}
template<class T> Deque<T>::~Deque()
{
    if(nullptr==mHead_ && nullptr==mTail_)
    {
        return;
    }
    else
    {
        for(IBM_NODE *sItr=mHead_;sItr!=nullptr;sItr=mHead_){
            mHead_ = mHead_->mNextNode_;
            delete sItr;
        }
        mHead_ = mTail_ = nullptr;
        mSize_ = 0;
    }
}

template<class T> std::ostream& operator<<(std::ostream& osParam, const Deque<T>& objParam)
{
    if(nullptr==objParam.mHead_ && nullptr==objParam.mTail_)
    {
        osParam<<"Queue is empty!"<<std::endl;
        return osParam;
    }
    else
    {
        for(typename Deque<T>::IBM_NODE *sItr=objParam.mHead_;sItr!=nullptr;sItr=sItr->mNextNode_)
        {
            osParam<<sItr->mNodeData_<<" ";
        }
        osParam<<std::endl;
        return osParam;
    }
}
#endif