/*!
 * \autor captainpeng
 * \date 2019-2-28
 * \update 2019-3-11
 * \version 1.0
 * \copyright
 */

#ifndef list_hpp
#define list_hpp

#include"mystd.hpp"
#include"listNode.hpp"

namespace my{

    template<typename ElementType,int PtrNum>
    class list;
    
    template<typename ElementType>
    class list<ElementType,1>{
    public:
	using elementType=info_type_t<ElementType>;
	using elementPtr=info_ptr_t<ElementType>;
	using elementRef=info_ref_t<ElementType>;
	using elementConstRef=info_constRef_t<ElementType>;

	using nodeType=listNode<elementType,1>;
	using nodePtr=hwPtr<nodeType>;
	
    private:
	nodePtr mHead;
	
	nodePtr findForward(const elementType & et){
	    nodePtr tmp=mHead;
	    while(tmp != nullptr){
		if((*(*tmp).mNext).mValue == et)
		    return tmp;
		tmp=(*tmp).mNext;
	    }
	    return tmp;
	}

	nodePtr findForwardByPos(const int pos){
	    int p=intLib<int>::abs(pos);
	    
	    nodePtr tmp=mHead;
	    for(int i=0;i < p-1 && (*tmp).mNext != nullptr;++i)
		tmp=(*tmp).mNext;
	    
	    return tmp;
	}

	
    public:
	list():mHead(nil<nodeType>()){}
	void insert(const elementType & et){
	    if(mHead == nullptr){
		mHead.alloc();
		(*mHead)=et;
		return ;
	    }

	    insert(mHead,et);
	}

	void insert(const elementType & et,const int pos){
	    if(pos == 0){
		nodePtr tmp=std::move(mHead);
		mHead.alloc();
		(*mHead)=et;
		(*mHead).mNext=std::move(tmp);
	    }else{
		std::cout<<"hhh"<<std::endl;
		nodePtr tmp1=findForwardByPos(pos);
		std::cout<<"bool: "<<tmp1.isPower()<<std::endl;
		insert(tmp1,et);
	    }
	}

	void insert(nodePtr p,const elementType & et){
	    nodePtr tmp;
	    tmp.alloc();
	    (*tmp)=et;

	    // std::cout<<static_cast<void*>(&tmp.mValue)<<std::endl;
	    // std::cout<<"bool: "<<tmp.isPower()<<std::endl;
	    // std::swap((*tmp).mNext,(*p).mNext);
	    tmp=(*tmp).mNext=std::move(tmp);

	    // std::cout<<"bool: "<<(*tmp).mNext.isPower()<<std::endl
	    // 	     <<"bool: "<<(*p).mNext.isPower()<<std::endl
	    // 	     <<"bool: "<<tmp.isPower()<<std::endl;
	    (*p).mNext.swap((*tmp).mNext);
	    // std::cout<<static_cast<void*>(&((*tmp).mNext).mValue)<<std::endl;
	    // std::cout<<static_cast<void*>(&(*p).mNext.mValue)<<std::endl;
	}

	elementRef find(const elementType & et){
	    return (*(*findForward(et)).mNext).mValue;
	}

	elementRef findByPos(int pos){
	    return (*(*findForwardByPos(pos)).mNext).mValue;
	}
	
	void erase(const elementType & et){
	    nodePtr tmp1=findForward(et);
	    nodePtr tmp2=(*tmp1).mNext;
	    std::swap((*tmp1).mNext,(*(*tmp1).mNext).mNext);
	    tmp2=std::move(tmp2.mNext);
	}

	void show(){
	    nodePtr tmp=mHead;
	    std::cout<<"[ ";
	    while(true){
		std::cout<<(*tmp).mValue;
		if((*tmp).mNext == nullptr){
		    std::cout<<" ]"<<std::endl;
		    break;
		}else{
		    std::cout<<",";
		}
		tmp=(*tmp).mNext;
	    }
	}
    };

    template<typename T>
    using singleList=list<T,1>;
}

#endif
