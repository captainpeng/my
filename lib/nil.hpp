/*!
 * \autor captainpeng
 * \date 2018-9-5
 * \update 2018-12-29
 * \version 1.0
 * \copyright
 */

#ifndef nil_hpp
#define nil_hpp

#include<type_traits>

namespace my {
    
    template<typename T,
	     bool is_cv=std::is_const<T>::value || std::is_volatile<T>::value
	     >
    struct remove_cv_ref{};

    template<typename T>
    struct remove_cv_ref<T,true>{
	using type=typename std::remove_reference<std::remove_cv_t<T>>::type;
	static const bool value=true;
    };

    template<typename T>
    struct remove_cv_ref<T,false>{
	using type=typename std::remove_reference<T>::type;
	static const bool value=false;
    };

    template<typename T,
	     bool is_ptr=std::is_pointer<T>::value
	     >
    struct theNil{};

    template<typename T>
    struct theNil<T,true>{
	using type=T;
	using element_type=typename std::remove_pointer<T>::type;
	static const bool value=true;
    
	T * operator()(){
	    // theNil<element_type> func;
	    static T nil_value=theNil<element_type>()();
	    return & nil_value;
	}
    };

    template<typename T>
    struct theNil<T,false>{
	using type=T;
	static const bool value=false;

	T * operator()(){
	    static T nil_value;
	    return & nil_value;
	}
    };

    template<typename T,
	     typename D=typename remove_cv_ref<T>::type
	     >
    T * nil(){
	static theNil<D> nil_func;
	return nil_func();
    }

    template<>
    void * nil<void>(){
	return nullptr;
    }

}
#endif
