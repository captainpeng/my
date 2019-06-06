/*!
 * \autor captainpeng
 * \date 2018-9-5
 * \update 2019-1-15
 * \version 1.0
 * \copyright
 */

#ifndef buffer_hpp
#define buffer_hpp

// #include<memory>
// #include<iostream>
// #include<algorithm>
// #include<initializer_list>

// #include"nil.hpp"
// #include"intLib.hpp"
#include<cstring>
#include"mystd.hpp"

namespace my {
	
    template<typename ElementType>
    class buffer{
	
    public:
	// using elementType=typename my::typeInfo<ElementType>::type;
	// using elementPtr=typename my::typeInfo<ElementType>::ptr;
	// using elementConstPtr=typename my::typeInfo<ElementType>::constPtr;
	// using elementRef=typename my::typeInfo<ElementType>::ref;
	// using elementConstRef=typename my::typeInfo<ElementType>::constRef;
	
        using elementType=info_type_t<ElementType>;
	using elementPtr=info_ptr_t<ElementType>;
	using elementRef=info_ref_t<ElementType>;
	using elementConstRef=info_constRef_t<ElementType>;
	using elementConstPtr=info_constPtr_t<ElementType>;
	
	using iteratorType=elementPtr;
	using iteratorConstType=elementConstPtr;

    private:
	using allocatorType=std::allocator<elementType>;
	using memType=memory<elementType>;
	
     private:
	static inline allocatorType & theAlloc(){
	    static allocatorType the_alloc;
	    return the_alloc;
	}
	
	static inline elementPtr Alloc(const int size){
	    elementPtr p=theAlloc().allocate(size);
	    
	    for(int i=0;i < size;++i)
		theAlloc().construct(p+i,*nil<elementType>());

	    return p;
	}

	static inline void Dealloc(buffer & buf){
	    //std::cout<<"#46"<<(void *)buff.begin()<<std::endl;
	    int s=buf.size();
	    elementPtr p=buf.begin();
	    if(s != 0){
		for(int i=0;i<s;++i)
		    theAlloc().destroy(p+i);
		theAlloc().deallocate(p,s);
	    }
	}
			
	elementRef get(const int pos) const {
	    int i=pos;
            // default the pos within the scope

	    elementPtr tmp=mBegin;
            // default is will start for mBegin
	
	    if(pos >= ssize() && pos < size()) // check the pos
		tmp=(pos>=0)?mBegin:mEnd;
	    // if pos is within the scope and check the ptr tmp
	    else
		i=(pos>0)?size()-1:0;
	    // if pos isn't within the scope and check the var i

	    return *(tmp+i);
	    // get the right reference;

	}

	static void clone(elementPtr * begin,elementPtr * end,const buffer & buff){
	    int len=buff.size();
	    // *begin=new elementType[len]; 
	    memType::alloc(begin,len);
	    //new momery blocks
	    *end=*begin+len;
	    std::copy(buff.mBegin,buff.mEnd,*begin);
	    // copy the data
	}

    public:
	// 通用的 index 函数，可任意设置范围，但要求 begin 和 end 指针是 buf 中的一部分
	static inline elementRef index(const int pos,elementPtr begin,elementPtr end){
	    if(begin >= end) return *nil<elementType>();
	    
	    int size=end-begin;
	    int ssize=begin-end;
	    
	    int i=pos;
            // default the pos within the scope

	    elementPtr tmp=begin;
            // default is will start for mBegin
	
	    if(pos >= ssize && pos < size) // check the pos
		tmp=(pos >= 0)?tmp:end;
	    // if pos is within the scope and check the ptr tmp
	    else
		i=(pos > 0)?size-1:0;
	    // if pos isn't within the scope and check the var i

	    return *(tmp+i);
	    // get the right reference;

	}
	
    public:

	buffer():
	    mBegin(nil<elementType>()),
	    mEnd(mBegin)
	    {}

	buffer(int length){	    
	    // int len=digitLib<int>::abs(length);
	    int len=(length < 0)?0:length;
	    // mBegin=new elementType[len]; 
	    memType::alloc(&mBegin,len);
	    mEnd=mBegin+len;
	}

	buffer(const buffer & buff){
	    clone(&mBegin,&mEnd,buff);
	}
	//note: the copy constructor will create a new memory blocks.
    
	buffer(buffer && buff){
		memType::exchange(&mBegin,&buff.mBegin);
		mEnd=buff.mEnd;

		buff.mEnd=buff.mBegin=nil<elementType>();
	}

	buffer(const std::initializer_list<elementType> & list){
		using ptr_type=typename std::initializer_list<elementType>::iterator;

		memType::alloc(&mBegin,list.size());
		mEnd=mBegin+list.size();
			    
		for(auto it=list.begin(),eit=list.end(),i=0;it != eit;++it,++i)
		    mBegin[i]=std::move(*it);

	}
    
	buffer & operator=(const buffer & buff){
	    if(&buff != this){
		this->free();
		clone(&mBegin,&mEnd,buff);
	    }
	    return *this;
	}

	buffer & operator=(buffer && buff){
	    if(&buff == this)
		return *this;

	    // int len1=this->size();
	    // int len2=buff.size();

	    memType::exchange(&mBegin,&buff.mBegin);
	    std::swap(mEnd,buff.mEnd);
	    
	    // elementPtr tmpBegin=mBegin;
	    // elementPtr tmpEnd=mEnd;
	    
	    // mBegin=buff.mBegin;
	    // mEnd=buff.mEnd;

	    // buff.mBegin=tmpBegin;
	    // buff.mEnd=tmpEnd;
	    return *this;
	}

	buffer & operator=(const std::initializer_list<elementType> & list){
	    memType::alloc(&mBegin,list.size());
	    mEnd=mBegin+list.size();
	    
	    for(auto it=list.begin(),eit=list.end(),i=0;it != eit;++it,++i){
		mBegin[i]=std::move(*it);
	    }
	    return *this;
	}
	
	~buffer(){
	    this->free();
	}

	void alloc(int len){
	    memType::alloc(&mBegin,len);
	    mEnd=mBegin+len;
	}

	void free(){
	    if(mBegin != nil<elementType>()){
		memType::free(&mBegin);
		mEnd=nil<elementType>();
	    }
	}

	inline void clear(){
	    free();
	}
	
	inline int size() const {
	    return mEnd-mBegin;
	}
	//size of buffer
    
	inline int ssize() const {
	    return mBegin-mEnd;
	}
	//equal to -size()
    
	inline iteratorType begin(){
	    return mBegin;
	}

	inline iteratorType end(){
	    return mEnd;
	}

	inline iteratorConstType begin() const {
	    return mBegin;
	}

	inline iteratorConstType end() const {
	    return mEnd;
	}
	
	void resize(const int length){
	    int len=intLib<int>::abs(length);
	    if(len < size()) return ;

	    elementPtr tmp;
	    memType::alloc(&tmp,len);
	    //当数组为空的时候，不需要move 和析构操作
	    if(mBegin != nil<elementType>()){
		std::move(mBegin,mEnd,tmp);
		// theAlloc().deallocate(mBegin,size());
		memType::free(&mBegin);	    
	    }

	    memType::exchange(&mBegin,&tmp);
	    mEnd=mBegin+len;
	}
		
	inline elementRef operator[](const int pos){
	    return get(pos);
	}

	inline elementConstRef operator[](const int pos) const {
	    return get(pos);
	}

	inline elementRef operator*(){
	    return *mBegin;
	}

	inline elementConstRef operator*() const {
	    return *mBegin;
	}
	
    private:
	elementPtr mBegin;
	elementPtr mEnd;
    };

    // 比较运算符重载
    template<typename ElementType>
    bool operator==(const buffer<ElementType> & lhs,const buffer<ElementType> & rhs){
	if(lhs.size() != rhs.size())
	    return false;
	
	for(auto it1=lhs.begin(),it2=rhs.begin();
	    it1 != lhs.end() && it2 != rhs.end();
	    ++it1,++it2){
	    if((*it1) != (*it2)) return false;
	}

	return true;
    }

    template<typename ElementType>
    bool operator!=(const buffer<ElementType> & lhs,const buffer<ElementType> & rhs){
	return !(lhs == rhs);
    }

    
    template<typename ElementType>
    std::ostream & operator<<(std::ostream & os,const buffer<ElementType> & buffer){
	os<<"{ ";
	for(int i=0;i < buffer.size()-1;++i)
	    os<<buffer[i]<<", ";
				
	return os<<*(buffer.end()-1)<<" }";
    }
}
#endif
