/*!
 * \autor captainpeng
 * \date 2019-5-15
 * \update 2019-5-15
 * \version 1.0
 * \copyright
 */

#ifndef memList_hpp
#define memList_hpp

#include<cassert>
#include"memListNode.hpp"

namespace my{

    // class memListIterator{
    // public:
    // 	using nodeType=memListNode;
    // 	using nodePtr=nodeType * ;
    // 	using nodeRef=nodeType & ;
    // private:
    // 	nodePtr mPtr;
	
    // public:
    // 	memListIterator(nodePtr np=nullptr):mPtr(np)
    // 	    {}

    // 	memListIterator & operator=(const memListIterator & it){
    // 	    mPtr=it.mPtr;
    // 	    return *this;
    // 	}
	
    // 	nodeRef operator*(){
    // 	    return mPtr == nullptr ? *nil<nodeType>():*mPtr;
    // 	}
	
    // 	memListIterator & operator++(){
    // 	    mPtr=mPtr == nullptr ? nullptr:mPtr->mNext;
    // 	    return *this;
    // 	}

    // 	memListIterator & operator++(int){
    // 	    return *this;
    // 	}

    // 	bool operator==(const memListIterator & it) const {
    // 	    return mPtr == it.mPtr;
    // 	}

    // 	bool operator!=(const memListIterator & it) const {
    // 	    return !(*this == it);
    // 	}

	
    // };

    class memList{
    public:
	using type=void;
	using fnAllocType=void*(*)(int);
	using fnFreeType=void(*)(type *);
	
	using nodeType=memListNode;
	using nodeRef=nodeType &;
	using nodePtr=nodeType *;
	using nodePPtr=nodePtr *;

	// using iteratorType=memListIterator;
	// using iteratorConstType=const iteratorType;

    private:
	nodePtr mHead;
	// findForward 返回指向的 mNext 的指针 
	nodePPtr findForward(type * ptr){
	    nodePPtr tmp=&mHead;
	    while(*tmp != nullptr){
		if((*tmp)->mValue == ptr)
		    return tmp;
		tmp=&(*tmp)->mNext;
	    }
			
	    return nullptr;
	}

	// findInsertPos 返回要插入的位置的 mNext 指针
	nodePPtr findInsertPos(type * ptr){
	    nodePPtr tmp=&mHead;
	    // 当 *tmp 为 nullptr 则要么是 mHead 的指针，要么是最后一个元素 mNext 指针
	    while(*tmp != nullptr){
		if((*tmp)->mValue > ptr)
		    break;
		tmp=&(*tmp)->mNext;
	    }
	    return tmp;
	}
	    
    public:
	memList():
	    mHead(nullptr)
	    {
		// xsassert((fn1 != nullptr && fn2 != nullptr));
	    }
	
	~memList(){
	    this->clear();
	}

	// 清空内存
	// 无视主权和计数器直接清空内存，用于异常退出程序或者程序 dump 的时候
	void clear(){
	    nodePtr tmp;
	    while(mHead != nullptr){
		tmp=mHead;
		mHead=mHead->mNext;
		(*tmp->mFree)(tmp->mValue);
		delete tmp;
	    }

	}
	
	// 查找 power ，不成功则返回 nullptr 
	nodePtr findPower(void * power){
	    if(power == nullptr) return nullptr;
	    
	    nodePtr tmp=mHead;
	    while(tmp != nullptr){
		if(tmp->mPower == power)
		    return tmp;
		tmp=tmp->mNext;
	    }

	    return nullptr; 
	}

	// 查找 value ，不成功则返回 nullptr
	nodePtr find(type * ptr){
	    return *findForward(ptr);
	}

	// 无主权插入函数，其主权等于它的 mValue 
	type * insertAndPlus(int size,int typesize,fnAllocType fnAlloc,fnFreeType fnFree){
	    type * ptr=(*fnAlloc)(size);
	    nodePPtr tmp=findInsertPos(ptr);
	    nodePtr tmpnode=new nodeType;
	    tmpnode->mNext=*tmp;
	    *tmp=tmpnode;

	    tmpnode->mPower=&tmpnode->mValue;
	    tmpnode->mValue=ptr;
	    tmpnode->mSize=size*typesize;
	    tmpnode->mCount=1;

	    return ptr;
	}
	
	// 插入函数，若对应的 value 已经存在则修改其值
	type * insert(void * power,int size,int typesize,fnAllocType fnAlloc,fnFreeType fnFree){
	    type * ptr=(*fnAlloc)(size);
	    nodePtr tmpnode=findPower(power);
	    
	    if(tmpnode != nullptr ){
		if(tmpnode->mCount <= 0){
		    (*tmpnode->mFree)(tmpnode->mValue);
		}else{
		    tmpnode->mPower=&tmpnode->mValue;
		    tmpnode=nullptr;
		}
	    }
	    
	    if(tmpnode == nullptr){
		// nodePPtr tmp=findInsertPos(ptr);
		nodePPtr tmp=&mHead;
		tmpnode=new nodeType;

		tmpnode->mNext=*tmp;
		*tmp=tmpnode;
	    }
	   
	    tmpnode->mPower=power;
	    tmpnode->mValue=ptr;
	    tmpnode->mSize=size*typesize;
	    tmpnode->mFree=fnFree;
	    tmpnode->mCount=0;
	    return ptr;
	    
	    // if((*tmp) != nullptr && (*tmp)->mValue == ptr){
	    // 	(*tmp)->mPower=power;
	    // 	(*tmp)->mSize=size;
	    // }else{
	    // 	nodePtr tmpnode=new nodeType;
	    // 	tmpnode->mPower=power;
	    // 	tmpnode->mValue=ptr;
	    // 	tmpnode->mSize=size;
			
	    // 	tmpnode->mNext=*tmp;
	    // 	*tmp=tmpnode;
	    // }
	}

	// 删除元素，依据 value
	// 如果计数器小于或者等于 0 的时候，才进行擦除操作
	void erase(type * ptr){
	    nodePPtr tmp=findForward(ptr);
	    if(*tmp != nullptr){
		nodePtr tmpnode=*tmp;
		*tmp=(*tmp)->mNext;
		(*tmpnode->mFree)(tmpnode->mValue);
		delete tmpnode;
	    }
	}

	// 优点: 能够把内部的参数是否存在都能计算出来
	// 缺点: 无类型即便被强制转换也不知道怎么回事
	// 返回: 如果存在，返回对应的 void * 指针，否则返回 nullptr
	nodePtr exist(void * ptr){
	    nodePtr tmp=mHead;
	    while(tmp != nullptr && tmp->mValue <= ptr){
		void * value=static_cast<void *>(static_cast<uint8_t *>(tmp->mValue)+tmp->mSize);
		// 因为类型长度至少为 1 ，所以 value 必定是大于 ptr 的
		if(value > ptr)
		    return tmp;
		tmp=tmp->mNext;
	    }
	    return nullptr;
	}
	
	nodePtr head(){
	    return mHead;
	}
	
	// iteratorType begin(){
	//     return iteratorType(mHead);
	// }

	// iteratorConstType begin() const {
	//     return iteratorType(mHead);
	// }

	// iteratorType end(){
	//     return iteratorType();
	// }

	// iteratorConstType end() const {
	//     return iteratorType();
	// }
	
    };
}

#endif
