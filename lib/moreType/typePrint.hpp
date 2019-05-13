/*!
 * \autor captainpeng
 * \date 2019-1-15
 * \update 2019-1-15
 * \version 1.0
 * \copyright
 */

#ifndef typePrint_hpp
#define typePrint_hpp

#include<cstdio>
#include<type_traits>

namespace my{

    
    template<typename T1,typename T2>
    void print_is_same(){
	if(std::is_same<T1,T2>::value)
	    std::printf("true\n");
	else
	    std::printf("false\n");
    }

}

#endif
