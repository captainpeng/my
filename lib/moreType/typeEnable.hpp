/*!
 * \autor captainpeng
 * \date 2019-1-13
 * \update 2019-1-13
 * \version 1.0
 * \copyright
 */

#ifndef typeEnable_hpp
#define typeEnable_hpp

#include<type_traits>

namespace my{
    //enable_if 的一些封装用法，他们以 enable_ 开头且返回值都为类型用于类型参数列表
    //字符类型
    template<typename T>
    using enable_char_t=std::enable_if_t<std::is_same<T,char>::value ||
					 std::is_same<T,wchar_t>::value ||
					 std::is_same<T,signed char>::value||
					 std::is_same<T,unsigned char>::value,
					 T>;
    //char和wchar_t<字符类型
    template<typename T>
    using enable_wc_char_t=std::enable_if_t<std::is_same<T,char>::value ||
					    std::is_same<T,wchar_t>::value,
					    T>;

    //有符号数字
    template<typename T>
    using enable_digit_t=std::enable_if_t<std::is_same<T,short>::value ||
					  std::is_same<T,int>::value ||
					  std::is_same<T,long>::value ||
					  std::is_same<T,long long>::value ||
					  std::is_same<T,float>::value ||
					  std::is_same<T,double>::value,
					  T>;

    //无符号数字
    template<typename T>
    using enable_udigit_t=std::enable_if_t<
	std::is_same<T,unsigned short>::value ||
	std::is_same<T,unsigned int>::value ||
	std::is_same<T,unsigned long>::value ||
	std::is_same<T,unsigned long long>::value,
	T>;
    
}

#endif
