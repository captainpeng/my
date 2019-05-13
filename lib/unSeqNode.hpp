/*!
 * \autor captainpeng
 * \date 2019-1-12
 * \update 2019-2-28
 * \version 1.0
 * \copyright
 */

#ifndef unSeqNode_hpp
#define unSeqNode_hpp

#include"nil.hpp"
#include"typeLib.hpp"

namespace my{

   //unSeqNode 加入了判断使得基础数据类型和enum型不需要指针，而是直接用值存储在类里面
   template<typename ElementType,
	    bool IsBasicType=is_ptr_basics_v<rm_all_refcv_t<ElementType>>
	    || std::is_enum<rm_all_refcv_t<ElementType>>::value
	     >
    class unSeqNode;

    //普通类的特例化
    template<typename ElementType>
    class unSeqNode<ElementType,false>{
    public:
	using elementType=info_type_t<ElementType>;
	using elementPtr=info_ptr_t<ElementType>;
	using elementRef=info_ref_t<ElementType>;
	using elementConstRef=info_constRef_t<ElementType>;
	
    private:
	int mIndex;
	elementPtr mValue;

    public:
	unSeqNode(){
	    mIndex=0;
	    mValue=nil<elementType>();
	}

	unSeqNode(const unSeqNode & node){
	    elementPtr v=(node.mValue == nil<elementType>())?
		nil<elementType>():new elementType(*node.mValue);
	    
	    mIndex=node.mIndex;
	    mValue=v;
	}

	unSeqNode & operator=(const unSeqNode & node){
	    
	    mIndex=node.mIndex;

	    if(mValue == nil<elementType>())
		mValue=new elementType(*node.mValue);
	    else
		*mValue=*node.mValue;

	    return *this;
	}
    
	unSeqNode(unSeqNode && node){
	    mIndex=node.mIndex;
	    mValue=node.mValue;

	    node.mIndex=0;
	    node.mValue=nil<elementType>();
	}

	unSeqNode & operator=(unSeqNode && node){
	    if(&node == this)
		return *this;

	    if(&mValue != nil<elementType>())
		delete mValue;

	    mIndex=node.mIndex;
	    mValue=node.mValue;

	    node.mIndex=0;
	    node.mValue=nil<elementType>();

	    return *this;
	}

	~unSeqNode(){
	    if(mValue != nil<elementType>())
		delete mValue;
	}
    
	unSeqNode & operator=(const elementType & et){
	    if(&et != nullptr || &et != nil<elementType>()){
		(*mValue)=et;
	    }

	    return *this;
	}

	unSeqNode & operator=(elementType && et){
	    if(&et != nullptr || &et != nil<elementType>()){
		(*mValue)=std::move(et);
	    }
	
	    return *this;
	}
    
	inline int index() const {
	    return mIndex;
	}

	inline elementRef value(){
	    return *mValue;
	}

	inline elementConstRef value() const {
	    return *mValue;
	}
	
	inline void setIndex(int i){
	    mIndex=(i >= 0)?i:mIndex;
	}
    
	void swap(unSeqNode & node){
	    mIndex ^= node.mIndex;
	    node.mIndex ^= mIndex;
	    mIndex ^=node.mIndex;

	    elementType * tmp=mValue;
	    mValue=node.mValue;
	    node.mValue=tmp;
	
	}

	void reset(int i,const elementType & v){
	    if(mValue == nil<elementType>())
		mValue=new elementType(v);
	    else
		*mValue=v;
	    this->setIndex(i);
	}

	void reset(int i,elementType && v){
	    if(mValue == nil<elementType>())
		mValue=new elementType(std::move(v));
	    else
		*mValue=std::move(v);
	    this->setIndex(i);
	}
    };

    //基本类型特例化
    template<typename ElementType>
    class unSeqNode<ElementType,true>{
    public:
	using elementType=info_type_t<ElementType>;
	using elementPtr=info_ptr_t<ElementType>;
	using elementRef=info_ref_t<ElementType>;
	using elementConstRef=info_constRef_t<ElementType>;

    private:
	int mIndex;
	elementType mValue;
	
    public:
    
	unSeqNode operator=(const elementType & et){
	    mValue=et;
	    return *this;
	}

	unSeqNode operator=(elementType && et){
	    mValue=std::move(et);
	    return *this;
	}
    
	inline int index() const {
	    return mIndex;
	}

	inline elementRef value(){
	    return mValue;
	}
	
	inline elementConstRef value() const {
	    return mValue;
	}
	
	inline void setIndex(int i){
	    mIndex=(i >= 0)?i:mIndex;
	}
    
	void swap(unSeqNode & node){
	    mIndex ^= node.mIndex;
	    node.mIndex ^= mIndex;
	    mIndex ^=node.mIndex;

	    elementType tmpValue=mValue;
	    mValue=node.mValue;
	    node.mValue=tmpValue;
	    
	}

	void reset(int i,const elementType & v){
	    this->setIndex(i);
	    *this=v;

//	    std::cout<<"copy:this->mValue "<<this->mValue<<std::endl;
	}

	void reset(int i,elementType && v){
	    this->setIndex(i);
	    *this=std::move(v);

//	    std::cout<<"move:this->mValue "<<this->mValue<<std::endl;
	    
	}
	
    };

    //void 和 nullpt_t 版本
    template<>
    class unSeqNode<void,true>;

    template<>
    class unSeqNode<std::nullptr_t,true>;


    template<typename T>
    std::ostream & operator<<(std::ostream & os,const unSeqNode<T> & node){
	return os<<"["<<node.index()<<","<<node.value()<<"]";
    }
}

#endif
