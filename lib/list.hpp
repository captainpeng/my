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
#include"stack.hpp"

namespace my{
    
    template<typename ElementType,int PtrNum>
    class list{
    public:
	using elementType=info_type_t<ElementType>;
	using elementPtr=info_ptr_t<ElementType>;
	using elementRef=info_ref_t<ElementType>;
	using elementConstRef=info_constRef_t<ElementType>;
	using elementMove=info_move_t<ElementType>;
	
	using nodeType=listNode<elementType,PtrNum>;
	using nodePtr=info_ptr_t<nodeType>;
	using nodePPtr=info_ptr_t<nodePtr>;

	using memType=memory<nodeType>;
    private:
	nodePtr mHead;
	int mSize;
	
	nodePPtr findForward(const elementType & et){
	    nodePPtr tmp=&mHead;
	    while(*tmp != nullptr){
		if((*tmp)->mValue == et){
		    return tmp;
		}
		tmp=&(*tmp)->mNext;
	    }
	    return tmp;
	}

	nodePPtr findForwardByPos(const int pos){
	    // int p=intLib<int>::abs(pos);

	    nodePPtr tmp=&mHead;
	    for(int i=0;i < pos && *tmp != nullptr;++i)
		tmp=&(*tmp)->mNext;
	    
	    return tmp;
	}

	// 分配内存块并插入当前的位置
	// 函数执行后，若无异常，则 *p 则是当前新分配的 node
	inline void AllocAndInsert(nodePPtr p,int2type<1>){
	    nodePtr tmpnode;
	    memType::alloc(&tmpnode);
	    memType::exchange(&tmpnode->mNext,p);
	    memType::exchange(&tmpnode,p);
	    ++mSize;
 	}

	inline void AllocAndInsert(nodePPtr p,int2type<2>){
	    nodePtr tmpnode;
	    memType::alloc(&tmpnode);
	    if(*p != nullptr){
		tmpnode->mBack=(*p)->mBack;
		(*p)->mBack=tmpnode;
	    }else{
		tmpnode->mBack=nullptr;
	    }
	    memType::exchange(&tmpnode->mNext,p);
	    memType::exchange(&tmpnode,p);
	    ++mSize;
	}

	// 删掉 node 并释放内存块
	inline void EraseAndFree(nodePPtr p,int2type<1>){
	    if(*p != nullptr){
		nodePtr tmpnode;
		memType::exchange(&tmpnode,p);
		memType::exchange(&(tmpnode->mNext),p);
		memType::free(&tmpnode);
		--mSize;
	    }

	}

	inline void EraseAndFree(nodePPtr p,int2type<2>){
	    if(*p != nullptr){
		nodePtr tmpnode;
		memType::exchange(&tmpnode,p);
		memType::exchange(&(tmpnode->mNext),p);

		if(*p != nullptr){
		    (*p)->mBack=tmpnode->mBack;
		}

		memType::free(&tmpnode);
		--mSize;
	    }
	}
	
    public:
	list():mHead(nullptr),mSize(0){}

	~list(){
	    clear();
	}
	
	int size(){
	    return mSize;
	}
	
	void insert(elementConstRef et){
	    AllocAndInsert(&mHead,int2type<PtrNum>());
	    mHead->mValue=et;
	}

	void insert(elementMove et){
	    AllocAndInsert(&mHead,int2type<PtrNum>());
	    mHead->mValue=std::move(et);
	}
	
	void insert(elementConstRef et,const int pos){
	    nodePPtr tmp=findForwardByPos(pos);
	    AllocAndInsert(tmp,int2type<PtrNum>());
	    (*tmp)->mValue=et;
	}

	void insert(nodePtr p,elementConstRef et){
	    if(p == nullptr) return ;
	    
	    AllocAndInsert(&(p->mNext),int2type<PtrNum>());
	}

	bool exist(nodePtr p){
	    nodePtr tmp=mHead;
	    while(tmp != nullptr){
		if(tmp == p)
		    return true;
		tmp=tmp->mNext;
	    }
	    return false;
	}
	
	elementRef find(elementConstRef et){
	    return (*findForward(et))->mValue;
	}

	elementRef findByPos(int pos){
	    return (*findForwardByPos(pos))->mValue;
	}
	
	void erase(elementConstRef et){
	    nodePPtr tmp=findForward(et);
	    EraseAndFree(tmp,int2type<PtrNum>());
	}

	void clear(){
	    nodePPtr tmp=&mHead;
	    stack<nodePPtr> s(mSize);
	    while(*tmp != nullptr){
		s.push(tmp);
		tmp=&(*tmp)->mNext;
 	    }
	    
	    // std::cout<<"statck capacity = "<<s.capacity()<<std::endl;
	    while(!s.empty()){
		memType::free(s.pop());
	    }

	    mHead=nullptr;
	    mSize=0;
	}
	
	void show(std::ostream & os=std::cout) const {
	    nodePtr tmp=mHead;
	    os<<"{";
	    while(tmp != nullptr){
		os<<tmp->mValue;
		if(tmp->mNext != nullptr)
		    os<<',';
		tmp=tmp->mNext;
	    }
	    os<<"}";
	}
    };

    template<typename Type,int Value>
    std::ostream & operator<<(std::ostream & os,const list<Type,Value> l){
	l.show(os);
	return os;
    }
    
    template<typename T>
    using slist=list<T,1>;

    template<typename T>
    using dlist=list<T,2>;
    
}

#endif
