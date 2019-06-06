#include<ctime>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<sstream>
#include<fstream>

#include"mystd.hpp"
#include"memory.hpp"
#include"buffer.hpp"

#include"unSeq.hpp"
#include"memory.hpp"
#include"hwPtr.hpp"
#include"msgCollect.hpp"

#include"list.hpp"

#include"seq.hpp"

#include"error.hpp"

template<typename T,typename Enable=my::enable_wc_char_t<T>>
class test{
    
};
int main(){
    using namespace std;
    using namespace my;

    // digitLib<int>::abs(-100);
    // digitLib<char>::abs(-200);
    // cout<<"-----------------------------\n";
    // using type=int;
    // using constType=const int;
    // print_is_same<type,constType>();
    // print_is_same<const int,constType>();

    // cout<<"-----------------------------\n";
    
    // using ref=int &;
    // using constRef=const ref;

    // print_is_same<ref,constRef>();
    // print_is_same<int &,constRef>();
    // print_is_same<const int &,constRef>();

    // cout<<"-----------------------------\n";

    // using ptr=int *;
    // using constPtr=const ptr;
    // using constPtr1=const int *;
    // using constPtr2=ptr const;
    // print_is_same<ptr,constPtr>();
    // print_is_same<int *,constPtr>();
    // print_is_same<const int *,constPtr>();
    // print_is_same<int * const,constPtr>();
    // print_is_same<const int *,constPtr1>();
    // print_is_same<int * const,constPtr2>();

    // cout<<"-----------------------------\n";
    // using constRef1=const int &;
    // using constRef2=const type &;
    // print_is_same<const int &,constRef1>();
    // print_is_same<const int &,constRef2>();

    // unSeq<int> a;
    // a.add(1);
    // a.add(1,100);

    //cout<<a[1]<<endl;

    // unSeq<unSeq<int>> b;
    // b.add(1,std::move(a));
    // cout<<b[1][1]<<endl;
    // cout<<b<<endl;
    // unSeq<unSeq<int>> c;
    // c.add(1);
    // c.add(1,std::move(a));
    // cout<<c[1][1]<<endl;

    // int i=100;
    // int j=std::move(i);
    // unSeq<unSeq<int>> d;
    // cout<<"----------add(1)--------"<<endl;
    // d.add(1);
    // cout<<"----------add(1,200)----"<<endl;

    // unSeq<int> & ref=d[1];
    // ref.add(1,200);

    // cout<<"\n----------show d[1]---"<<endl;
    // ref.show();

    // cout<<"\n----------add(2,200)----"<<endl;
    // d[1].add(2,200);
    
    // cout<<"\n----------show d[1]---"<<endl;
    // d[1].show();

    // cout<<"\n----------show d------"<<endl;
    // d.show();

    // cout<<"\n---------show nil<unSeq<int>>-----"<<endl;
    // cout<<(*nil<unSeq<int>>())<<endl;

    // int i=100;
    // int j=digitLib<int>::abs(i);

    // buffer<string> a(10);
    // a[0]="hahah";
    // clock_t s=clock();
    // a.resize(4096);
    // cout<<a[0]<<' '<<a.size()<<endl;
    // clock_t e=clock();
    // cout<<1000.0*(e-s)/CLOCKS_PER_SEC<<"ms\n";

    // singleList<int> a;
    // a.insert(1);
    // a.insert(2,2);
    // a.show();

    // hwPtr<int> a;
    // hwPtr<int> b;

    // a.alloc();
    // std::cout<<static_cast<void*>(&a.mValue)<<std::endl;
    // std::cout<<static_cast<void*>(&b.mValue)<<std::endl;

    // std::swap(a,b);

    // int * a;
    // int * b;
    // memory<int>::alloc(&a);
    // memory<int>::exchange(&b,&a);
    // std::cout<<memory<int>::isPower(&b)<<std::endl;
    // memory<int>::free(&b);

    // msgCollect<> m("/home/captainpeng/temp/temp");
    // m.put("shabi");

    // seq<int> a{1,2,3,4,1};
    // seq<int> b{2};

    // std::cout<<"a="<<a<<std::endl;
    // std::cout<<a+b<<std::endl
    // 	     <<a+1<<std::endl
    // 	     <<a-b<<std::endl
    // 	     <<a-1<<std::endl;

    // a+=b;
    // std::cout<<"a="<<a<<std::endl;

    // a-=b;
    // std::cout<<"a="<<a<<std::endl;

    // a+=1;
    // std::cout<<"a="<<a<<std::endl;

    // a-=1;
    // std::cout<<"a="<<a<<std::endl;

    // a-=0;
    // std::cout<<"a="<<a<<std::endl;

    // a[10]=2;
    // std::cout<<"a="<<a<<std::endl;

    // std::cout<<sizeof(seq<int>)<<std::endl;

    // seq<int> a1{1,2,3};
    // seq<int> a2{1,2,3};
    // std::cout<<((a1 == a2)?"true":"false")<<std::endl;
    // std::cout<<((a1 > a2)?"true":"false")<<std::endl;

    // seq<int> a3{2};
    // std::cout<<((a1 > a3)?"true":"false")<<std::endl;
    // std::cout<<((a3 > a1)?"true":"false")<<std::endl;

    // seq<int> a4{1,2,3,4};
    // std::cout<<((a1 > a4)?"true":"false")<<std::endl;
    // std::cout<<((a4 > a1)?"true":"false")<<std::endl;

    // for(int i=0;i < 1000;++i){
    // 	if(intLib<int>::isPrime(i)){
    // 	    std::cout<<i<<',';
    // 	};
    // }

    // std::cout<<"nextPrime="<<intLib<int>::nextPrime(100)<<std::endl;
    // using nodePtr=typename memList::nodePtr;
    // int a;
    // int b;
    // int c;
    
    // memList<int> l;
    // l.insert(static_cast<void *>(&c),static_cast<void *>(&c),sizeof(int));
    
    
    // nodePtr p=l.head();
    // while(p != nullptr){
    // 	std::cout<<p->mValue<<","<<p->mPower<<","<<p->mSize<<std::endl;
    // 	p=p->mNext;
    // }

    // std::cout<<std::endl;
    // l.insert(static_cast<void *>(&a),static_cast<void *>(&a),sizeof(int));
    // p=l.head();
    // while(p != nullptr){
    // 	std::cout<<p->mValue<<","<<p->mPower<<","<<p->mSize<<std::endl;
    // 	p=p->mNext;
    // }
    
    // std::cout<<std::endl;
    // l.insert(static_cast<void *>(&b),static_cast<void *>(&b),sizeof(int));
    // p=l.head();
    // while(p != nullptr){
    // 	std::cout<<p->mValue<<","<<p->mPower<<","<<p->mSize<<std::endl;
    // 	p=p->mNext;
    // }

    // std::cout<<std::endl;
    // l.insert(static_cast<void *>(&b),static_cast<void *>(&b),sizeof(long));
    // p=l.head();
    // while(p != nullptr){
    // 	std::cout<<p->mValue<<","<<p->mPower<<","<<p->mSize<<std::endl;
    // 	p=p->mNext;
    // }

    // std::cout<<std::endl;
    // p=l.findPower(&a);
    // if(p != nullptr)
    // 	std::cout<<p->mValue<<","<<p->mPower<<","<<p->mSize<<std::endl;

    // std::cout<<std::endl;
    // p=l.find(&b);
    // if(p != nullptr)
    // 	std::cout<<p->mValue<<","<<p->mPower<<","<<p->mSize<<std::endl;

    // std::cout<<std::endl;
    // l.erase(static_cast<void *>(&b));
    // p=l.head();
    // while(p != nullptr){
    // 	std::cout<<p->mValue<<","<<p->mPower<<","<<p->mSize<<std::endl;
    // 	p=p->mNext;
    // }

    // int d[20];
    // std::cout<<std::endl;
    // l.insert(static_cast<void *>(d),static_cast<void *>(d),sizeof(int)*20);
    // p=l.head();
    // while(p != nullptr){
    // 	std::cout<<p->mValue<<","<<p->mPower<<","<<p->mSize<<std::endl;
    // 	p=p->mNext;
    // }

    // std::cout<<std::endl;
    // if(l.exist(static_cast<void *>(&d[2])))
    //    std::cout<<static_cast<void *>(&d[2])<<" exit."<<std::endl;

    // if(l.exist(static_cast<void *>(&d[21])))
    //    std::cout<<static_cast<void *>(&d[21])<<" exit."<<std::endl;

    // if(l.exist(static_cast<void *>(&d[0])))
    //    std::cout<<static_cast<void *>(&d[0])<<" exit."<<std::endl;
  
    // std::pair<int,int> e;
    // std::cout<<std::endl;
    // l.insert(static_cast<void *>(&e),static_cast<void *>(&e),sizeof(std::pair<int,int>));
    // if(l.exist(static_cast<void *>(&e.first)))
    // 	std::cout<<static_cast<void *>(&e.first)<<" exit."<<std::endl;
    
    // if(l.exist(static_cast<void *>(&e.second)))
    // 	std::cout<<static_cast<void *>(&e.second)<<" exit."<<std::endl;

    using manType=memMan;
    // buffer<int> a(10);
    // manType::ShowList();
    // std::cout<<"--------------"<<std::endl;
    // a.alloc(20);
    // manType::ShowList();
    // std::cout<<"--------------"<<std::endl;
    // buffer<int> b(std::move(a));
    // manType::ShowList();
    // std::cout<<"--------------"<<std::endl;
    // std::cout<<a.size()<<' '<<b.size()<<std::endl;

    // {
    // 	buffer<int> c(20);
    // 	manType::ShowList();
    // 	std::cout<<"--------------"<<std::endl;
    // }

    // std::pair<int,int> * p;
    // memory<std::pair<int,int>>::alloc(&p,1);
    // int * p1=&p->first;
    // memory<int>::plusCount(p1);
    // manType::ShowList();
    // std::cout<<"--------------"<<std::endl;
    // std::cout<<static_cast<void *>(p1)<<std::endl;	
    // if(memory<int>::exist(p1)){
    // 	std::cout<<"exist"<<std::endl;
    // }else{
    // 	std::cout<<"don't exist"<<std::endl;
    // }

    // int * intp;
    // memory<int>::alloc(&intp,1);
    // memory<std::pair<int,int>>::free(&p);

    // manType::ShowList();
    // std::cout<<"--------------"<<std::endl;
    // std::cout<<static_cast<void *>(p1)<<std::endl;	
    // if(memory<int>::exist(p1)){
    // 	std::cout<<"exist"<<std::endl;
    // }else{
    // 	std::cout<<"don't exist"<<std::endl;
    // }

    // memory<int>::minusCount(p1);
    // manType::ShowList();
    // std::cout<<"--------------"<<std::endl;
    // std::cout<<static_cast<void *>(p1)<<std::endl;	
    // if(memory<int>::exist(p1)){
    // 	std::cout<<"exist"<<std::endl;
    // }else{
    // 	std::cout<<"don't exist"<<std::endl;
    // }

    // buffer<int> buf{1,2,3,4,5};
    // std::cout<<buf<<std::endl;
    // buf={1,2,4,5};
    // std::cout<<buf<<std::endl;
    // std::cout<<buf.size()<<std::endl;

    // seq<int> s{1,2,3,4,5};
    // std::cout<<s<<std::endl;
    // s={1,2,3};
    // std::cout<<s.size()<<std::endl;
    // std::cout<<s.capacity()<<std::endl;
    // std::cout<<('\0' == L'\0')<<std::endl;
    // std::FILE * fp=tmpfile();
    // std::fputws(L"hahahah",fp);
    // std::rewind(fp);
    // wchar_t buf[100];
    // for(int i=0;i < 100;++i)
    // 	buf[i]=L'a';
    
    // std::fgetws(buf,100,fp);
    // std::cout<<std::wcslen(buf)<<std::endl;
    // std::cout<<static_cast<int>(buf[std::wcslen(buf)])<<std::endl;

    
    // std::wistringstream ss(L"fuck");
    // ss.read(buf,100);
    // std::cout<<ss.gcount()<<','<<std::wcslen(buf)<<std::endl;
    // buffer<int> buf{1,2,3,4,5,6};
    // for(auto it = buf.begin();it != buf.end();++it)
    // 	std::cout<<*it<<',';
    // std::cout<<std::endl;
    // for(int i=0;i < buf.size();++i)
    // 	std::cout<<buf[i]<<',';
    // std::cout<<std::endl;

    // for(int i=0;i < buf.size();++i)
    // 	std::cout<<buffer<int>::index(i,buf.begin(),buf.end())<<',';
    // std::cout<<std::endl;

    // test<int> a;
    // print_is_same<int,info_type_t<int>>();
    // print_is_same<info_ptr_t<int>,int *>();
    // print_is_same<info_ptr_t<info_ptr_t<int>>,int **>();

    // print_is_same<int const *,int * const>();
    // print_is_same<const int *,int * const>();
    // print_is_same<int const *,const int *>();

    // int a;
    // int const * p1=&a;
    // const int * p2=&a;
    // int * const p3=&a;

    // p1=p2;
    // *p3=3;

    static_assert(false,"ni ma bi");
    return 0;
    
}
