/*!
 * \autor captainpeng
 * \date 2018-12-29
 * \update 2018-12-29
 * \version 1.0
 * \copyright
 */

#ifndef activePtr_hpp
#define activePtr_hpp

#include<type_traits>

#include"nil.hpp"

namespace my{

    template<typename T>
    class activeNode{
    public:
	using elementType=std::remove_reference_t<T>;
	using elementPtr=elementType *;
	using elementPtrPtr=elementPtr *;
    private:
	elementPtrPtr mPower;
	elementPtr mPtr;

	inline void init(elementPtrPtr power,elementPtr ptr){
	    mPower=power;
	    mPtr=ptr;
	}
	
    public:
	activeNode(){
	    init(nil<elementPtr>(),nil<elementType>());
	}

	activeNode(elementPtr ptr){
	    init(nil<elementPtr>(),ptr);
	}
	
	activeNode(elementPtrPtr power,elementPtr ptr){
	    init(power,ptr);
	}

	// activeNode & operator=(elementPtrPtr power,elementPtr ptr){
	//     init(power,ptr);
	//     return *this;
	// }

	activeNode & operator=(elementPtrPtr newPower){
	    mPower=newPower;
	}
	
	bool operator==(elementPtrPtr power){
	    return power == mPower;
	}

	bool operator!=(elementPtrPtr power){
	    return *this != power;
	}

	~activeNode(){
	    if(mPower != nil<elementPtr>() && mPower != nullptr)
		delete mPtr;	
	}
	
    };
    
    template<typename T>
    class activePtr{
    public:
	using elementType=std::remove_reference_t<T>;
	using elementPtr=elementType *;

	using nodeType=activeNode<elementType>;
	using nodePtr=nodeType *;
	
    private:
	nodePtr mPtr;

	void deleteNode(typename nodeType::elementPtrPtr ptr){
	    if(
	}
	
    public:
	activePtr(){
	    mPtr=nil<nodeType>();
	}

	activePtr(const activePtr & apt){
	    mPtr=apt.mPtr;
	}

	activePtr(activePtr && apt){
	    
	}
    };
    
}

#endif
