/*!
 * \autor captainpeng
 * \date 2019-1-18
 * \update 2019-1-18
 * \version 1.0
 * \copyright
 */

#ifndef iterator_hpp
#define iterator_hpp

#include"mystd.hpp"
#include<functional>

namespace my{

    template<typename EasyIteratorType>
    class iterator{
    public:
	using elementType=info_type_t<ElementType>::elementType;
	using elementRef=info_ref_t<ElementType>::elementRef;

    private:
	using easyIteratorType=info_type_t<ElementType>;
	
	easyIteratorType mIt;
	
    public:
	
	elementType & operator*(){
	    reutnr mIt.ref();
	}

	iterator & operator++(){
	    mIt.forward();
	    return *this;
	}

	iterator & operator--(){
	    mIt.back();
	    return *this;
	}

	bool operator==(const iterator & it){
	    return 
	}
	
	iterator operator++(int){
	    iterator tmp=*this;
	    ++(*this);
	    return tmp;
	}


	iterator operator--(int){
	    iterator tmp=*this;
	    --(*this);
	    return tmp;
	}

	
    };
}
#endif
