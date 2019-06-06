/*!
 * \autor captainpeng
 * \date 2019-3-5
 * \update 2019-3-6
 * \version 1.0
 * \copyright
 */

#ifndef memory_hpp
#define memory_hpp

#include<cstdlib>
#include"memory/memFunc.hpp"
#include"memory/memMan.hpp"
#include"mystd.hpp"

namespace my{
	
    template<typename T,typename ManType=memMan>
    class memory{
    public:
	using type=info_type_t<T>;
    	using ptr=info_ptr_t<T>;
    	using pptr=ptr*;
	using manType=info_type_t<ManType>;
	using memFn=memFunc<type>;
	using listType=typename manType::listType;
	using nodePtr=typename listType::nodePtr;
	memory()=delete;
	
    public:
	// 分配内存，这里参数用的是指针的指针
	static void alloc(pptr p,int size=1){
	    if(p != nullptr && size >= 1){
		// 察看 p 是否为 power,是的话 free 掉其中的内存块
		// insert 操作会自动执行
		listType & l=manType::GetList();
		*p=static_cast<type *>(l.insert(static_cast<void *>(p),size,sizeof(type),memFn::Alloc,memFn::Free));
	    }else if(p != nullptr){
		*p=nil<type>();
	    }
	}

	// 释放内存，这里参数用的是指针的指针
	// 因为加入了计数器，所以当计数器不是 <=0 的时候，我们不会释放内存
	// 而是把主权改为 mValue 独有，这样是标记这内存是靠计数器来释放的
	static void free(pptr p){
	    if(p == nullptr || *p == nullptr) return ;
	    
	    listType & l=manType::GetList();
	    nodePtr tmp=l.findPower(static_cast<void *>(p));
	    if(tmp != nullptr){
		if(tmp->mCount <= 0)
		    l.erase(tmp->mValue);
		else
		    tmp->mPower=&tmp->mValue;
	    }
	    *p=nil<type>();
	}

	// 交换内存主权，这里参数用的是指针的指针
	// 注意函数同时也会通过解引用交换指针的值
	static void exchange(pptr p1,pptr p2){
	    listType & l=manType::GetList();
	    nodePtr tmp1=l.findPower(static_cast<void *>(p1));
	    nodePtr tmp2=l.findPower(static_cast<void *>(p2));
	    
	    if(tmp1 != nullptr){
		if(tmp2 != nullptr)
		    tmp1->swapPower(*tmp2);
		else
		    tmp1->mPower=static_cast<void *>(p2);
	    }else if(tmp2 != nullptr)
		tmp2->mPower=static_cast<void *>(p1);
	    
	    std::swap(*p1,*p2);
	}
	
	// 查看内存是否还存在，这里参数用的是指针
	// 注意函数除了判断分配的内存还有其成员或者数组内部的指针也会被判断
	static bool exist(ptr p){
	    return manType::GetList().exist(static_cast<void *>(p)) != nullptr;
	}

        // 判断一个指针是否拥有主权，这里参数用的是指针的指针	
	static bool isPower(pptr p){
	    return manType::GetList().findPower(static_cast<void *>(p));
	}

	// 更改计数器的值，值 +1
	static void plusCount(ptr p){
	    if(p == nullptr || p == nil<type>()) return ;
	    
	    listType & l=manType::GetList();
	    typename listType::nodePtr value=l.exist(static_cast<void *>(p));
	    if(value != nullptr){
		value->mCount=(value->mCount <= 0)?1:value->mCount+1;
	    }
	}

	// 更改计数器的值，值 -1
	static void minusCount(ptr p){
	    if(p == nullptr || p == nil<type>()) return ;
	    
	    listType & l=manType::GetList();
	    typename listType::nodePtr value=l.exist(static_cast<void *>(p));
	    if(value != nullptr){
		--(value->mCount);
	        if(value->mCount <= 0 && value->mPower == &value->mValue){
		    l.erase(value->mValue);
		}
	    }
	}

    };

    // 以下是旧版，有着很多错误和未完善的地方，所以弃用改为上述的。
    // 但是呢，下面还有些有用的算法可以参考，如下。
    // template<typename T>
    // class memory{
	
    // public:
    // 	using type=info_type_t<T>;
    // 	using ptr=info_ptr_t<T>;
    // 	using pptr=ptr*;

    // private:
    // 	using elementType=std::pair<pptr,int>;
    // 	using bufferType=std::set<elementType,
    // 				  std::function<
    // 				      bool(const elementType &,
    // 					   const elementType &)
    // 				      >
    // 				  >;

    // 	static bufferType & getBuffer(){
    // 	    // 重新定义 Compare 函数
    // 	    static bufferType ptrBuf([](const elementType & lhs,
    // 					const elementType & rhs) -> bool{
    // 					 return lhs.first > rhs.first;
    // 				     });
    // 	    return ptrBuf;
    // 	}

    // 	static elementType & elementTmp(pptr p,int s=0){
    // 	    static elementType a;
    // 	    a.first=p;
    // 	    a.second=s;
    // 	    return a;
    // 	}
	
    // public:
    // 	// 分配内存，这里参数用的是指针的指针
    // 	static void alloc(pptr p,int size=1){
    // 	    size=intLib<int>::abs(size);

    // 	    if(size == 0){
    // 		*p=nil<type>();
    // 	    }else{
    // 		getBuffer().insert(elementTmp(p,size));
    // 		*p=new type[size];
    // 	    }
    // 	}

    // 	// 释放内存，这里参数用的是指针的指针
    // 	static void free(pptr p){
    // 	    // 若它是主权指针，那它则有权利删除该内存块
    // 	    bufferType & buf=getBuffer();
    // 	    auto it=buf.find(elementTmp(p));
    // 	    if(it != buf.end()){
    // 		delete [] *p;
    // 		buf.erase(it);
    // 		*p=nil<type>();
    // 		// std::cout<<"free: "<<static_cast<void*>(p)<<std::endl;
    // 	    }
    // 	}

    // 	// 交换内存主权，这里参数用的是指针的指针
    // 	static void exchange(pptr p1,pptr p2){
    // 	    // 若它是主权指针，那它则有权利把权利赋予 p2
    // 	    std::swap(*p1,*p2);
    // 	    // std::cout<<"p1= "<<static_cast<void*>(p1)<<std::endl;
    // 	    // std::cout<<"p2= "<<static_cast<void*>(p2)<<std::endl;

    // 	    bufferType & buf=getBuffer();

    // 	    int status=0;
    //      // 有用的算法hhh
    // 	    typename bufferType::iterator it[2];
    // 	    status+=((it[0]=buf.find(elementTmp(p1))) != buf.end())?1:0;
    // 	    status+=((it[1]=buf.find(elementTmp(p2))) != buf.end())?2:0;

    // 	    elementType et[2];
    // 	    pptr p[2]={p1,p2};

    // 	    // std::cout<<"fuck: "<<status<<std::endl;
    // 	    switch(status){
    // 	    case 3:
    // 		if((*it[0]).second == (*it[1]).second)
    // 		    return ;
    // 		else{
    // 		    et[0]=elementTmp((*it[0]).first,(*it[1]).second);
    // 		    et[1]=elementTmp((*it[1]).first,(*it[0]).second);
    // 		    buf.erase(it[0]);
    // 		    buf.erase(it[1]);
    // 		    buf.insert(et[0]);
    // 		    buf.insert(et[1]);
    // 		}
    // 		break;

    // 	    case 1:case 2:
    // 		// 这是一个简单的运算，当数字k 在范围0~n 之间
    // 		// 那么(n-1)-k 就是它范围之间的补数，因为不包括n
    // 		// 举例: 0 对应 n-1,1 对应 n-2
    // 		et[2-status]=elementTmp(p[2-status],(*it[status-1]).second);
    // 		buf.erase(it[status-1]);
    // 		buf.insert(et[2-status]);
    // 		break;

    // 	    case 0:
    // 		return ;

    // 	    }
    // 	}

    // 	// 查看内存是否还存在，这里参数用的是指针
    // 	static bool exist(ptr p){
    // 	    bufferType & buf=getBuffer();
    // 	    ptr end;
    // 	    // 由于内存查看不仅仅是主权指针的权利
    // 	    // 而是所有指针的权利，所以这里利用的是内存块的指针来判断
    // 	    // 因为不是主权的指针的地址并不存在于 buffer 中
    // 	    for(auto it:buf){
    // 		end=(*it.first)+it.second;
    // 		if(p >= *it.first && p < end)
    // 		    return true;
    // 	    }
    // 	    return false;
    // 	}

    // 	// 判断一个指针是否拥有主权，这里参数用的是指针的指针
    // 	static bool isPower(pptr p){
    // 	    // 搜索 buffer 里面是否存在该指针（地址）
    // 	    // 若成功搜索到，则返回 true ，否则 false 
    // 	    bufferType & buf=getBuffer();
    // 	    return buf.find(elementTmp(p)) != buf.end();
    // 	}
    // };
    
}

#endif
