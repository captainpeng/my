/*!
 * \autor captainpeng
 * \date 2019-3-5
 * \update 2019-3-6
 * \version 1.0
 * \copyright
 */

#ifndef memory_hpp
#define memory_hpp

#include<functional>
#include<set>
#include"mystd.hpp"

namespace my{

    template<typename T>
    class memory{
	
    public:
	using type=info_type_t<T>;
	using ptr=info_ptr_t<T>;
	using pptr=ptr*;

    private:
	using elementType=std::pair<pptr,int>;
	using bufferType=std::set<elementType,
				  std::function<
				      bool(const elementType &,
					   const elementType &)
				      >
				  >;

	static bufferType & getBuffer(){
	    // 重新定义 Compare 函数
	    static bufferType ptrBuf([](const elementType & lhs,
					const elementType & rhs) -> bool{
					 return lhs.first > rhs.first;
				     });
	    return ptrBuf;
	}

	static elementType & elementTmp(pptr p,int s=0){
	    static elementType a;
	    a.first=p;
	    a.second=s;
	    return a;
	}
	
    public:
	// 分配内存，这里参数用的是指针的指针
	static void alloc(pptr p,int size=1){
	    size=intLib<int>::abs(size);

	    if(size == 0){
		*p=nil<type>();
	    }else{
		getBuffer().insert(elementTmp(p,size));
		*p=new type[size];
	    }
	}

	// 释放内存，这里参数用的是指针的指针
	static void free(pptr p){
	    // 若它是主权指针，那它则有权利删除该内存块
	    bufferType & buf=getBuffer();
	    auto it=buf.find(elementTmp(p));
	    if(it != buf.end()){
		delete [] *p;
		buf.erase(it);
		*p=nil<type>();
		// std::cout<<"free: "<<static_cast<void*>(p)<<std::endl;
	    }
	}

	// 交换内存主权，这里参数用的是指针的指针
	static void exchange(pptr p1,pptr p2){
	    // 若它是主权指针，那它则有权利把权利赋予 p2
	    std::swap(*p1,*p2);
	    // std::cout<<"p1= "<<static_cast<void*>(p1)<<std::endl;
	    // std::cout<<"p2= "<<static_cast<void*>(p2)<<std::endl;

	    bufferType & buf=getBuffer();

	    int status=0;
	    
	    typename bufferType::iterator it[2];
	    status+=((it[0]=buf.find(elementTmp(p1))) != buf.end())?1:0;
	    status+=((it[1]=buf.find(elementTmp(p2))) != buf.end())?2:0;

	    elementType et[2];
	    pptr p[2]={p1,p2};

	    // std::cout<<"fuck: "<<status<<std::endl;
	    switch(status){
	    case 3:
		if((*it[0]).second == (*it[1]).second)
		    return ;
		else{
		    et[0]=elementTmp((*it[0]).first,(*it[1]).second);
		    et[1]=elementTmp((*it[1]).first,(*it[0]).second);
		    buf.erase(it[0]);
		    buf.erase(it[1]);
		    buf.insert(et[0]);
		    buf.insert(et[1]);
		}
		break;

	    case 1:case 2:
		// 这是一个简单的运算，当数字k 在范围0~n 之间
		// 那么(n-1)-k 就是它范围之间的补数，因为不包括n
		// 举例: 0 对应 n-1,1 对应 n-2
		et[2-status]=elementTmp(p[2-status],(*it[status-1]).second);
		buf.erase(it[status-1]);
		buf.insert(et[2-status]);
		break;

	    case 0:
		return ;

	    }
	}

	// 查看内存是否还存在，这里参数用的是指针
	static bool exist(ptr p){
	    bufferType & buf=getBuffer();
	    ptr end;
	    // 由于内存查看不仅仅是主权指针的权利
	    // 而是所有指针的权利，所以这里利用的是内存块的指针来判断
	    // 因为不是主权的指针的地址并不存在于 buffer 中
	    for(auto it:buf){
		end=(*it.first)+it.second;
		if(p >= *it.first && p < end)
		    return true;
	    }
	    return false;
	}

	// 判断一个指针是否拥有主权，这里参数用的是指针的指针
	static bool isPower(pptr p){
	    // 搜索 buffer 里面是否存在该指针（地址）
	    // 若成功搜索到，则返回 true ，否则 false 
	    bufferType & buf=getBuffer();
	    return buf.find(elementTmp(p)) != buf.end();
	}
    };
}

#endif
