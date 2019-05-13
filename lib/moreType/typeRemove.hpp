/*!
 * \autor captainpeng
 * \date 2019-1-15
 * \update 2019-1-15
 * \version 1.0
 * \copyright
 */

#ifndef typeRemove_hpp
#define typeRemove_hpp

#include<type_traits>

namespace my{
    //移除指针中的值的const volatile
    
    template<typename T>
    using rm_ptrcv_t=std::add_pointer_t<
	std::remove_cv_t<std::remove_pointer_t<T>>>;

    //移除类型的引用和const volatile
    //但是并不会移除const volatitle int *的
    //因为他们修饰的并非指针而是他们的值
    template<typename T>
    using rm_refcv_t=std::remove_cv_t<std::remove_reference_t<T> >;

    //整合上面，用于清除所有ref和const volatile
    template<typename T,bool value=std::is_pointer<T>::value>
    class rm_all_refcv;

    template<typename T>
    class rm_all_refcv<T,true>{
    public:
    	using type=rm_ptrcv_t<T>;
    };

    template<typename T>
    class rm_all_refcv<T,false>{
    private:
    	using rmCvrefType=rm_refcv_t<T>;
    public:
    	using type=typename std::conditional<
    	std::is_pointer<rmCvrefType>::value,
    	rm_ptrcv_t<rmCvrefType>,
    	rmCvrefType
    	>::type;
    };

    //rm_all_cvref 的using帮助类型
    template<typename T>
    using rm_all_refcv_t=typename rm_all_refcv<T>::type;

					  
}

#endif
