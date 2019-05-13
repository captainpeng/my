/*!
 * \autor captainpeng
 * \date 2019-1-12
 * \update 2019-1-12
 * \version 1.0
 * \copyright
 */

#ifndef unSeq_hpp
#define unSeq_hpp

#include"mystd.hpp"

#include"buffer.hpp"
#include"unSeqNode.hpp"

namespace my{

    // unSeq 是一个不连续数组，他存在的意义是为了达到某种快速的访问某个值
    // 但是又不能花费太多的内存来存储跨度太大的空间而存在，他的意义则是
    // 利用值里面保存一个索引来达到存储跨度太大的数组
    template<typename ElementType>
    class unSeq{
    public:
	using elementType=info_type_t<ElementType>;
	using elementRef=info_ref_t<ElementType>;
	using elementConstRef=info_constRef_t<ElementType>;
	using elementPtr=info_ptr_t<ElementType>;
	using elementConstPtr=info_ptr_t<ElementType>;
	using elementMove=info_move_t<ElementType>;
	
	using nodeType=unSeqNode<elementType>;
	// unSeqNode 是一个特殊的值类似于list中的listNode他里面不仅包含了值
	// 还包含了索引，详见unSeqNode.hpp
	using bufType=std::vector<nodeType>;

	using iteratorType=typename bufType::iterator;
	using iteratorConstType=typename bufType::const_iterator;
	
	// using iteratorType=elementPtr;
	// using iteratorConstType=elementConstPtr;
	
    private:
	bufType mBuf;

	//该函数主要用来查找下一个插入的位置，如果index 存在则返回已经存在的位置
	nodeType & findAddNodePos(int index){
	    int size=mBuf.size();
	    // i 用来大概定位，如果index大于该有的长度则从最后一个开始找
	    // 如果没有则从给出来的index位置往前找
	    
	    int i=(size == 0)?-1:(index > size-1)?size-1:index;

	    for(;i != -1;--i)
		if(mBuf[i].index() < index)
		    // 如果不存在则进行夏一步的操作
		    break;
		else if(mBuf[i].index() == index){
		    // 如果index已经存在，则返回他
//		    std::cout<<"find pos : "<<index<<std::endl;
		    return mBuf[i];
		}
	    
	    nodeType tmp;
//	    std::cout<<"size="<<size<<std::endl;
	    // 这一步是数组无该索引存在，利用把index 后面所有值往后面挪
	    // 腾出一个位置来给该index
	    for(int j=i+1;j < size;++j)
		tmp.swap(mBuf[j]);
	    
//	    std::cout<<"i+1="<<i+1<<std::endl;
	    mBuf.push_back(std::move(tmp));

	    return mBuf[i+1];
	}
	
    public:
	unSeq(int len=0):mBuf(digitLib<int>::abs(len))
	{}

	elementRef at(int index){
	    if(mBuf.size() != 0){
		// i 存在的意义也是大概定位，如findAddPos
		int i=(index > mBuf.size()-1)?mBuf.size()-1:index;
		// 从i 开始往下找第一个比index小的值
		while((index < mBuf[i].index()) && --i);

		//如果找到则返回该值引用
		if(mBuf[i].index() == index)
		    return mBuf[i].value();
		
	    }
	    //如果找不到则返回nil
	    return *nil<elementType>();

	    //对于查找一个已排序的数组而言，这个利用二分法查找也许会快很多
	    //但是自己并适用大范围的unSeq ，所以暂时没有这样做。
	}

	inline elementConstRef at(int index) const {
	    return at(index);
	}

	void add(const std::initializer_list<int> indexList){
	    for(auto it=indexList.begin(),itEnd=indexList.end();
		it != itEnd; ++it)
		add((*it));
	}
	
	elementRef add(const int index,elementConstRef et=*nil<elementType>()){
	    int i=digitLib<int>::abs(index);
	    nodeType & tmp=findAddNodePos(i);
	    tmp.reset(i,et);
	    return tmp.value();
	    
            // nodeType & tmp=findAddNodePos(index);
	    // tmp.reset(index,et);
	    // std::cout<<"et="<<et<<" "
	    // 	     <<"tmp.index="<<tmp.index()<<" "
	    // 	     <<"tmp.value="<<tmp.value()<<std::endl;
	}

	elementRef add(const int index,elementMove et){
	    
	    int i=digitLib<int>::abs(index);
	    nodeType & tmp=findAddNodePos(i);
	    tmp.reset(i,std::move(et));
	    return tmp.value();
	    
	    // nodeType & tmp=findAddNodePos(index);
	    // tmp.reset(index,std::move(et));
	    // std::cout<<"move : et="<<et<<" "
	    // 	     <<"tmp.index="<<tmp.index()<<" "
	    // 	     <<"tmp.value="<<tmp.value()<<" "
	    // 	     <<"now size="<<mBuf.size()<<std::endl;
	    
	    this->show();
	}

	void reserve(const int size){
	    mBuf.reserve(digitLib<int>::abs(size));
	}
	
	bool isIndex(int index) const {
	    return !(&at(index) == nil<elementType>()); 
	}
	
	void show() const {
	    // std::cout<<"mBuf.begin() == mBuf.end()="
	    // 	     <<(mBuf.begin() == mBuf.end())
	    // 	     <<" mBuf.size()="<<mBuf.size()
	    // 	     <<" this="<<(static_cast<const void*>(this))
	    // 	     <<"#";

	    std::cout<<"[ ";
	    for(auto it=mBuf.begin(); it != mBuf.end(); ++it)
		std::cout<<"["<<(*it).index()<<","<<(*it).value()<<"] ";
	    std::cout<<" ]";
	}

	void indexList(std::vector<int> & vec) const {
	    vec.reserve(mBuf.size());
	    for(int i=0;i < mBuf.size();++i){
		vec.push_back(mBuf[i].index());
	    }
	}
    
	inline int minIndex() const {
	    return (*mBuf.begin()).index();
	}
    
	inline int maxIndex() const {
	    return (*(mBuf.end() -1)).index();
	}
    
	inline int size() const {
	    return mBuf.size();
	}
    
	inline elementRef operator[](int index){
	    return at(index);
	}

	inline elementConstRef operator[](int index) const {
	    return at(index);
	}
	
	inline iteratorType begin(){
	    return mBuf.begin();
	}
	
	inline iteratorType end(){
	    return mBuf.end();
	}

	inline iteratorConstType begin() const {
	    return mBuf.begin();
	}

	inline iteratorConstType end() const {
	    return mBuf.end();
	}
    };

    template<typename T>
    std::ostream & operator<<(std::ostream & os,const unSeq<T> & seq){
	seq.show();
	return os;
    }
    
}

#endif
