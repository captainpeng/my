/*!
 * \autor captainpeng
 * \date 2018-9-5
 * \update 2019-1-15
 * \version 1.0
 * \copyright
 */

#ifndef seq_hpp
#define seq_hpp

#include<queue>
#include"mystd.hpp"
#include"buffer.hpp"

namespace my{

    template<typename ElementType>
    class seq{
    private:
	using bufType=buffer<ElementType>;

    public:
	using elementType=typename bufType::elementType;
	using elementPtr=typename bufType::elementPtr;
	using elementRef=typename bufType::elementRef;
	using elementConstRef=typename bufType::elementConstRef;
	using elementConstPtr=typename bufType::elementConstPtr;
	
	using iteratorType=typename bufType::iteratorType;
	using iteratorConstType=typename bufType::iteratorConstType;

	bufType mBuf;
	elementPtr mCurEnd;

    private:
	elementRef get(const int pos){
	    int i=intLib<int>::abs(pos);
	    int cursize=size();
	    if(pos >= cursize){
		// 1. 设置要 resize 的长度 rsize ，当容量还能满足的时候 rsize 为 0
		int rsize=(i < mBuf.size())?0:i/8*8+0x10;
		// std::cout<<"size="<<size<<", i/8*8+0x10="<<i/8*8+0x10<<",mBuf.size()="<<mBuf.size()
		// 	 <<",i/8="<<i/8<<std::endl;
		// 2. 当 rsize == 0 的时候，该函数什么都不做
		mBuf.resize(rsize);

		// 3. 初始化扩展的部份
		for(;cursize <= i;++cursize)
		    mBuf[cursize]=*nil<elementType>();

		// 4. 重置 mCurEnd 指针的位置
		mCurEnd=mBuf.begin()+i+1;
	    }

	    return bufType::index(pos,mBuf.begin(),mCurEnd);
	}

	// elementRef index(const int pos,){
	//     int i=pos;
        //     // default the pos within the scope

	//     elementPtr tmp=mBuf.begin();
        //     // default is will start for mBegin
	
	//     if(pos>=ssize() && pos<size()) // check the pos
	// 	tmp=(pos>=0)?tmp:mCurEnd;
	//     // if pos is within the scope and check the ptr tmp
	//     else
	// 	i=(pos>0)?size()-1:0;
	//     // if pos isn't within the scope and check the var i

	//     return *(tmp+i);
	//     // get the right reference;

	// }
	
    public:
	seq():mBuf(),mCurEnd(nil<elementType>()){}

	seq(int length):mBuf(length),mCurEnd(mBuf.end()){}
	
	seq(const seq & s):mBuf(s.mBuf){
	    mCurEnd=mBuf.end()-(s.mBuf.end()-s.mCurEnd);
	}

	seq(seq && s):mBuf(std::move(s.mBuf)),mCurEnd(s.mCurEnd){
	    s.mCurEnd=nil<elementType>();
	}
	
	seq(const bufType & buf):mBuf(buf),mCurEnd(mBuf.end()){}
	seq(bufType && buf):mBuf(std::move(buf)),mCurEnd(mBuf.end()){}

	seq(const bufType & buf,int size):mBuf(buf),mCurEnd(mBuf.begin()+size){}
	seq(const bufType && buf,int size):mBuf(std::move(buf)),mCurEnd(mBuf.begin()+size){}
	
	seq(const std::initializer_list<elementType> & list):mBuf(list),mCurEnd(mBuf.end()){}

	seq & operator=(const seq & s){
	    mBuf=s.mBuf;
	    mCurEnd=mBuf.end()-(s.mBuf.end()-s.mCurEnd);
	    return *this;
	}

	seq & operator=(seq && s){
	    mBuf=std::move(s.mBuf);
	    mCurEnd=s.mCurEnd;
	    s.mCurEnd=nil<elementType>();
	    return *this;
	}

	seq & operator=(const std::initializer_list<elementType> & list){
	    if(mBuf.size() >= list.size()){
		for(auto it=list.begin(),eit=list.end(),i=0;it != eit;++it,++i){
		    mBuf[i]=std::move(*it);
		}
		mCurEnd=mBuf.begin()+list.size();
	    }else
		mBuf=list;
	    return *this;
	}
	
	inline int size() const {
	    return mCurEnd-mBuf.begin();
	}

	inline int capacity() const {
	    return mBuf.size();
	}

	inline int ssize() const {
	    return mBuf.begin()-mCurEnd;
	}

	inline iteratorConstType begin() const{
	    return mBuf.begin();
	}

	inline iteratorConstType end() const{
	    return mCurEnd;
	}

	inline iteratorType begin(){
	    return mBuf.begin();
	}

	inline iteratorType end(){
	    return mCurEnd;
	}

	void resize(const int len){
	    int size=(len <= 0)?0:len;
	    int capacity=(size < mBuf.size())?0:size/8*8+0x10;
	    mBuf.resize(capacity);
	    mCurEnd=mBuf.begin()+size;
	}
	
	inline elementRef operator[](const int pos){
	    return get(pos);
	}

	inline elementConstRef operator[](const int pos) const {
	    // int i=intLib<int>::abs(pos);
	    // if(i >= size())
	    // 	return *nil<elementType>();
	    // return mBuf[pos];
	    seq & tmp=const_cast<seq & >(*this);
	    return bufType::index(tmp.mBuf,pos,tmp.mBuf.begin(),tmp.mCurEnd);
	}

	inline elementRef operator*(){
	    return *mBuf;
	}
    };

    // 这是一段关于 seq 运算的函数 包括
    // 组合 operator+ ， 把两个 seq 组合成一个 seq
    // 组合赋值 operator+= , 把右边的 seq 添加至左边里
    // 去除 operator- , 把左边 seq 中存在于右边的 seq 的元素去除掉
    // 去除赋值 operator-=  ,同上,不过会修改左边的 seq
    
    template<typename ElementType>
    seq<ElementType> operator+(const seq<ElementType> & lhs,const seq<ElementType> & rhs){
	int len=lhs.size()+rhs.size();
	buffer<ElementType> buf(len);
	for(int i=0;i < len;++i){
	    buf[i]=(i < lhs.size())?lhs[i]:rhs[i-lhs.size()];
	}

	return seq<ElementType>(std::move(buf));
    }

    template<typename ElementType>
    seq<ElementType> operator+(const seq<ElementType> & lhs,
		  const typename seq<ElementType>::elementType & rhs){
	int len=lhs.size()+1;
	buffer<ElementType> buf(len);
	for(int i=0;i < lhs.size();++i){
	    buf[i]=lhs[i];
	}
	buf[lhs.size()]=rhs;

	return seq<ElementType>(std::move(buf));
    }

    template<typename ElementType>
    seq<ElementType> operator-(const seq<ElementType> & lhs,const seq<ElementType> & rhs){
	int len=lhs.size();
	int cur=0;
	buffer<ElementType> buf(len);
	for(int i=0;i < len;++i){
	    if(std::find(rhs.begin(),rhs.end(),lhs[i]) == rhs.end())
		buf[cur++]=lhs[i];
	}

	return seq<ElementType>(std::move(buf),cur);
    }

    template<typename ElementType>
    seq<ElementType> operator-(const seq<ElementType> & lhs,
		  const typename seq<ElementType>::elementType & rhs){
	int len=lhs.size();
	int cur=0;
	buffer<ElementType> buf(len);
	for(int i=0;i < lhs.size();++i){
	    if(lhs[i] != rhs)
		buf[cur++]=lhs[i];
	}
	
	return seq<ElementType>(std::move(buf),cur);
    }

    template<typename ElementType>
    seq<ElementType> & operator+=(seq<ElementType> & lhs,const seq<ElementType> & rhs){
	for(int i=0;i < rhs.size();++i)
	    lhs[lhs.size()]=rhs[i];
	return lhs;
    }

    template<typename ElementType>
    seq<ElementType> & operator+=(seq<ElementType> & lhs,
		     const typename seq<ElementType>::elementType & rhs){
	lhs[lhs.size()]=rhs;
	return lhs;
    }

    template<typename ElementType>
    seq<ElementType> & operator-=(seq<ElementType> & lhs,const seq<ElementType> & rhs){
	// 一个可以把存在于 rhs 的元素后挪到 lhs 的最后面
	// 1.队列 q 用来纪录最新的存在于 rhs 元素的位置
	std::queue<int> q;

	// 2.遍历 lhs 所有元素
	for(int i=0;i < lhs.size();++i){
	    // 3.若存在于 rhs 则把该位置入队列 q
	    if(std::find(rhs.begin(),rhs.end(),lhs[i]) != rhs.end()){
		q.push(i);
	    // 4.若不存在且队列 q 不为空，交换队列第一个位置和当前位置的元素
	    }else if(!q.empty()){
		std::swap(lhs[q.front()],lhs[i]);
		q.pop();
		q.push(i);
	    }
	}
	// 5.若最后队列也不为空，则更改 lhs 的 size
	if(!q.empty()) lhs.resize(q.front());
	return lhs;
    }

    template<typename ElementType>
    seq<ElementType> & operator-=(seq<ElementType> & lhs,
		     const typename seq<ElementType>::elementType & rhs){
	//同上
	std::queue<int> q;
	
	for(int i=0;i < lhs.size();++i){
	    if(lhs[i] == rhs){
		q.push(i);
	    }else if(!q.empty()){
		std::swap(lhs[q.front()],lhs[i]);
		q.pop();
		q.push(i);
	    }
	}

	if(!q.empty()) lhs.resize(q.front());
	return lhs;
    }

    // 比较运算符重载
    template<typename ElementType>
    bool operator==(const seq<ElementType> & lhs,const seq<ElementType> & rhs){
	bool flag=(lhs.size() == rhs.size());
	for(auto itl=lhs.begin(),itr=rhs.begin();flag && itl!=lhs.end();++itl,++itr){
	    flag = ((*itl) == (*itr));
	}

	return flag;
    }

    template<typename ElementType>
    bool operator!=(const seq<ElementType> & lhs,const seq<ElementType> & rhs){
	return !(lhs == rhs);
    }

    template<typename ElementType>
    bool operator>(const seq<ElementType> & lhs,const seq<ElementType> & rhs){
	// 1.当 lhs 某一个元素大于 rhs 的时候，返回 true
	// 2.当 lhs 结束后，rhs 仍然继续，返回 false
	
	bool flag=false;
	bool cflag=true;
	
	for(auto itl=lhs.begin(),itr=rhs.begin();cflag && itl != lhs.end() && itr != rhs.end();++itl,++itr){
	    flag = (*itl) > (*itr);
	    cflag = !flag && ((*itl) == (*itr));

	    // if((*itl) > (*itr))
	    // 	return true;
	    // else if((*itl == (*itr)))
	    // 	continue;
	    // else return false;
	}

	// std::cout<<flag<<','<<cflag<<std::endl;
	flag = flag || (cflag && lhs.size() > rhs.size());
	return flag;
    }

    template<typename ElementType>
    bool operator>=(const seq<ElementType> & lhs,const seq<ElementType> & rhs){
	return (lhs == rhs) || (lhs > rhs);
    }

    template<typename ElementType>
    bool operator<(const seq<ElementType> & lhs,const seq<ElementType> & rhs){
	return !(lhs >= rhs);
    }

    template<typename ElementType>
    bool operator<=(const seq<ElementType> & lhs,const seq<ElementType> & rhs){
	return !(lhs > rhs);
    }
    
    template<typename ElementType>
    std::ostream & operator<<(std::ostream & os,const seq<ElementType> & rhs){
	os<<'{';
	for(auto it=rhs.begin();it != rhs.end();++it){
	    if(it == rhs.end()-1)
		os<<(*it);
	    else
		os<<(*it)<<',';
	}
	return os<<'}';
    }
}
#endif
