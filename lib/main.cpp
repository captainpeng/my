#include<ctime>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>

#include"mystd.hpp"
#include"buffer.hpp"

#include"unSeq.hpp"
#include"memory.hpp"
#include"hwPtr.hpp"
#include"msgCollect.hpp"

#include"list.hpp"

#include"seq.hpp"

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

    for(int i=0;i < 1000;++i){
	if(intLib<int>::isPrime(i)){
	    std::cout<<i<<',';
	};
    }

    std::cout<<"nextPrime="<<intLib<int>::nextPrime(100)<<std::endl;
    return 0;
}
