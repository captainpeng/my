/*!
 * \autor captainpeng
 * \date 2019-5-15
 * \update 2019-5-15
 * \version 1.0
 * \copyright
 */

#ifndef memListNode_hpp
#define memListNode_hpp

namespace my{
    
    class memListNode{
    public:
	using fnType=void(*)(void *);
	void * mPower; // 主权指针的地址
	void * mValue; // 分配内存的地址
	int mCount; // 计数器
	int mSize; // 分配内存地址的大小
	fnType mFree; //进行 delete 的函数指针
	memListNode * mNext; // 下一个元素
	
	memListNode():mValue(nullptr),mSize(-1){}

	// 交换主权指针地址，分配地址与大小并不会交换
	void swapPower(memListNode & node){
	    void * tmp;
	    tmp=mPower;
	    mPower=node.mPower;
	    node.mPower=tmp;
	}
    };

}

#endif
