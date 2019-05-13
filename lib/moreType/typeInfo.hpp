/*!
 * \autor captainpeng
 * \date 2019-1-15
 * \update 2019-1-15
 * \version 1.0
 * \copyright
 */

#ifndef typeInfo_hpp
#define typeInfo_hpp

#include<type_traits>

#include"typeRemove.hpp"

namespace my {
    
    //类型信息集合体
    template<typename T>
    class typeInfo{
    public:
	using type=rm_all_refcv_t<T>;
	using constType=const type;
	using ref=type &;
	using constRef=const type &;
	using ptr=type *;
	using constPtr=const type *;
	using ptrConst=type * const;
	using constPtrConst=const type * const;
	using move=type &&;
	
    };

    
    template<>
    class typeInfo<void>{
    public:
	using type=void;
	using ptr=void *;
    };

    //帮助类型
    template<typename T>
    using info_type_t=typename typeInfo<T>::type;

    template<typename T>
    using info_constType_t=typename typeInfo<T>::constType;
    
    template<typename T>
    using info_ref_t=typename typeInfo<T>::ref;

    template<typename T>
    using info_constRef_t=typename typeInfo<T>::constRef;

    template<typename T>
    using info_ptr_t=typename typeInfo<T>::ptr;

    template<typename T>
    using info_constPtr_t=typename typeInfo<T>::constPtr;

    template<typename T>
    using info_ptrConst_t=typename typeInfo<T>::ptrConst;

    template<typename T>
    using info_constPtrConst_t=typename typeInfo<T>::constPtrConst;

    template<typename T>
    using info_move_t=typename typeInfo<T>::move;
    
}

#endif
