/*!
 * \autor captainpeng
 * \date 2019-2-28
 * \update 2019-2-28
 * \version 1.0
 * \copyright
 */

#ifndef listNode_hpp
#define listNode_hpp

#include"nil.hpp"
#include"typeLib.hpp"
#include"hwPtr.hpp"

namespace my{

    template<typename ElementType,int PtrNum>
    class listNode;

    template<typename ElementType>
    class listNode<ElementType,1>{
    public:
	using elementType=info_type_t<ElementType>;
	using elementPtr=info_ptr_t<ElementType>;
	using elementRef=info_ref_t<ElementType>;
	using elementConstRef=info_constRef_t<ElementType>;

	using nodePtr=info_ptr_t<listNode>;
	
	elementType mValue;
	nodePtr mNext;

	listNode & operator=(const elementType & et){
	    mValue=et;
	    return *this;
	}

	listNode & operator=(elementType && et){
	    mValue=std::move(et);
	    return *this;
	}
	
	void swap(listNode & n){
	    std::swap(mValue,n.mValue);
	    std::swap(mNext,n.mNext);
	}
	
    };

    template<typename ElementType>
    class listNode<ElementType,2>{
    public:
	using elementType=info_type_t<ElementType>;
	using elementPtr=info_ptr_t<ElementType>;
	using elementRef=info_ref_t<ElementType>;
	using elementConstRef=info_constRef_t<ElementType>;

	using nodePtr=info_ptr_t<listNode>;
	
	elementType mValue;
	nodePtr mNext;
        nodePtr mBack;

	listNode & operator=(const elementType & et){
	    mValue=et;
	    return *this;
	}

	listNode & operator=(elementType && et){
	    mValue=std::move(et);
	    return *this;
	}

	void swap(listNode & n){
	    std::swap(mValue,n.mValue);
	    std::swap(mNext,n.mNext);
	    std::swap(mBack,n.mBack);
	}
    };

    template<typename ElementType,int i>
    void swap(listNode<ElementType,i> & n1,listNode<ElementType,i> & n2){
	n1.swap(n2);
    }
    
}

#endif
