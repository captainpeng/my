/*!
 * \autor captainpeng
 * \date 2019-1-13
 * \update 2019-1-15
 * \version 1.0
 * \copyright
 */

#ifndef typeIs_hpp
#define typeIs_hpp

#include<cstdio>
#include<type_traits>

namespace my{
    
    //用来判断是否为void nullptr_t 算术类型 和指针
    template<typename T>
    constexpr bool is_ptr_basics_v=std::is_fundamental<T>::value ||
	std::is_pointer<T>::value;

}

#endif
