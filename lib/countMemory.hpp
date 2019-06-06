/*!
 * \autor captainpeng
 * \date 2019-5-23
 * \update 2019-5-23
 * \version 1.0
 * \copyright
 */

#ifndef countMemory_hpp
#define countMemory_hpp

#include"memory/memFunc.hpp"
#include"memory/memMan.hpp"
#include"mystd.hpp"
#include"buffer.hpp"

namespace my{
    
    template<typename Type,typename ManType=memMan>
    class countMemory{
    public:
	using type=info_type_t<T>;
    	using ptr=info_ptr_t<T>;
    	using pptr=ptr*;
	using manType=info_type_t<ManType>;
	using memFn=memFunc<type>;
	using listType=typename manType::listType;
	using nodePtr=typename listType::nodePtr;
	countMemory()=delete;
	
	static void countPlus(ptr p){
	    listType & l=manType::GetList();
	    typename listType::nodePtr value=l.exist(static_cast<void *>(p));
	    if(value != nullptr){
		value->mCount=(value->mCount <= 0)?1:value->mCount+1;
	    }
	}

	static void countMinus(ptr p){
	    listType & l=manType::GetList();
	    void * value=l.exist(static_cast<void *>(p));
	    if(value != nullptr){
		--(value->mCount);
	        if(value->mCount <= 0 && ref.mPower == &value->mValue){
		    l.erase(value->mValue);
		}
	    }
	}
    };
}

#endif
