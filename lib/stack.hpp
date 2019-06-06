/*!
 * \autor captainpeng
 * \date 2019-1-13
 * \update 2019-1-14
 * \version 1.0
 * \copyright
 */

#ifndef stack_hpp
#define stack_hpp

#include"mystd.hpp"

namespace my{

    template<typename ElementType>
    class stack{
    public:
	using elementType=info_type_t<ElementType>;
	using elementPtr=info_ptr_t<ElementType>;
	using elementRef=info_ref_t<ElementType>;
	using elementConstRef=info_constRef_t<ElementType>;
	using elementConstPtr=info_constPtr_t<ElementType>;
	    
	using bufferType=buffer<elementType>;
	
    private:
	bufferType mBuf;
	// elementPtr mHead;
	int mHead;
		
    public:
	stack(int len=0x10):mBuf(intLib<int>::abs(len)){
	    mHead=-1;
	}

	inline int size(){
	    return mHead + 1;
	}

	inline int capacity(){
	    return mBuf.size();
	}

	inline bool empty(){
	    return mHead == -1;
	}

	inline elementRef operator[](const int i){
	    return bufferType::index(i,mBuf.begin(),mBuf.begin()+mHead+1);
	}

	inline elementConstRef operator[](const int i) const {
	    return bufferType::index(i,mBuf.begin(),mBuf.begin()+mHead+1);
	}
	
	inline elementRef top(){
	    return (mHead == -1)?*nil<elementType>():mBuf[mHead];
	}

	elementType pop(){
	    if(mHead == -1) return *nil<elementType>();

	    elementType tmp=std::move(mBuf[mHead]);
	    --mHead;
	    return tmp;
	}

	bool push(const elementType & et){
	    if(mHead == mBuf.size()-1){
		if(mBuf.size() < 0x1000)
		    mBuf.resize(mBuf.size()+0x20);
		else return false;
	    }

	    mBuf[++mHead]=et;
	    return true;
	}

	bool push(elementType && et){
	    if(mHead == mBuf.size()-1){
		if(mBuf.size() < 0x1000)
		    mBuf.resize(mBuf.size()+0x20);
		else return false;
	    }
	    
	    mBuf[++mHead]=std::move(et);
	    return true;

	}

	// 转换成 vector 方便了解内部元素遍历或打印
	void toVector(std::vector<elementType> & vec){
	    elementPtr tmp=&mBuf[mHead];
	    vec.reserve(vec.size()+this->size());
	    
	    while(--tmp != mBuf.begin()-1)
		vec.push_back(*tmp);
		
	}

	void clear(){
	    mHead=-1;
	}
    };

}

#endif
