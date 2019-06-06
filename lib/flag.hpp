/*!
 * \autor captainpeng
 * \date 2019-5-31
 * \update 2019-5-31
 * \version 1.0
 * \copyright
 */

#ifndef flag_hpp
#define flag_hpp

#include"mystd.hpp"

namespace my{

    template<int Size>
    class flag{
    public:
	static_assert(((Size % 8) == 0) && (Size < 64),"Size must be {8,16,32,64}");
	using type=typename stdint<Size>::uintType;

	static constexpr type GenValue(const int f){
	    static_assert(f >= Size,"Don't out of range");
	    return 1<<f;
	}

	static void RmValue(type & v,const type f){
	    v&=~f;
	}

    };
}

#endif
