/*!
 * \autor captainpeng
 * \date 2019-5-23
 * \update 2019-5-23
 * \version 1.0
 * \copyright
 */

#ifndef memMan_hpp
#define memMan_hpp

#include<iostream>
#include"memList.hpp"

namespace my{
    class memMan{
    public:
	using listType=memList;
	using nodePtr=typename listType::nodePtr;
	
	static listType & GetList(){
	    static listType list;
	    return list;
	}

	static void ShowList(){
	    nodePtr p=GetList().head();
	    while(p != nullptr){
		std::cout<<"[ "<<p->mPower<<","<<p->mValue<<","<<p->mCount<<','<<p->mSize<<" ]"<<std::endl;
		p=p->mNext;
	    }
	}

	static void ClearList(){
	    GetList().clear();
	}
    };
}

#endif
