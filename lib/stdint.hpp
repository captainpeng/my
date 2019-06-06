/*!
 * \autor captainpeng
 * \date 2019-5-31
 * \update 2019-5-31
 * \version 1.0
 * \copyright
 */

#ifndef stdint_hpp
#define stdint_hpp

#include<cstdint>
#include<stdint.h>

namespace my{

    template<int Size>
    class stdint;

    template<>
    class stdint<8>{
    public:
	using intType=int8_t;
	using uintType=uint8_t;
	using fastType=int_fast8_t;
	using ufastType=uint_fast8_t;
	using leastType=int_least8_t;
	using uleastType=uint_least8_t;

	static const intType IntMax=INT8_MAX;
	static const intType IntMin=INT8_MIN;
	static const uintType UIntMax=UINT8_MAX;
	static const uintType UIntMin=0;
	static const fastType FastMax=INT_FAST8_MAX;
	static const fastType FastMin=INT_FAST8_MIN;
	static const ufastType UFastMax=UINT_FAST8_MAX;
	static const ufastType UFastMin=0;
	static const leastType LeastMax=INT_LEAST8_MAX;
	static const leastType LeastMin=INT_LEAST8_MIN;
	static const uleastType ULeastMax=UINT_LEAST8_MAX;
	static const uleastType ULeastMin=0;
    };

    template<>
    class stdint<16>{
    public:
	using intType=int16_t;
	using uintType=uint16_t;
	using fastType=int_fast16_t;
	using ufastType=uint_fast16_t;
	using leastType=int_least16_t;
	using uleastType=uint_least16_t;

	static const intType IntMax=INT16_MAX;
	static const intType IntMin=INT16_MIN;
	static const uintType UIntMax=UINT16_MAX;
	static const uintType UIntMin=0;
	static const fastType FastMax=INT_FAST16_MAX;
	static const fastType FastMin=INT_FAST16_MIN;
	static const ufastType UFastMax=UINT_FAST16_MAX;
	static const ufastType UFastMin=0;
	static const leastType LeastMax=INT_LEAST16_MAX;
	static const leastType LeastMin=INT_LEAST16_MIN;
	static const uleastType ULeastMax=UINT_LEAST16_MAX;
	static const uleastType ULeastMin=0;
    };

    template<>
    class stdint<32>{
    public:
	using intType=int32_t;
	using uintType=uint32_t;
	using fastType=int_fast32_t;
	using ufastType=uint_fast32_t;
	using leastType=int_least32_t;
	using uleastType=uint_least32_t;

	static const intType IntMax=INT32_MAX;
	static const intType IntMin=INT32_MIN;
	static const uintType UIntMax=UINT32_MAX;
	static const uintType UIntMin=0;
	static const fastType FastMax=INT_FAST32_MAX;
	static const fastType FastMin=INT_FAST32_MIN;
	static const ufastType UFastMax=UINT_FAST32_MAX;
	static const ufastType UFastMin=0;
	static const leastType LeastMax=INT_LEAST32_MAX;
	static const leastType LeastMin=INT_LEAST32_MIN;
	static const uleastType ULeastMax=UINT_LEAST32_MAX;
	static const uleastType ULeastMin=0;
    };

    template<>
    class stdint<64>{
    public:
	using intType=int64_t;
	using uintType=uint64_t;
	using fastType=int_fast64_t;
	using ufastType=uint_fast64_t;
	using leastType=int_least64_t;
	using uleastType=uint_least64_t;

	static const intType IntMax=INT64_MAX;
	static const intType IntMin=INT64_MIN;
	static const uintType UIntMax=UINT64_MAX;
	static const uintType UIntMin=0;
	static const fastType FastMax=INT_FAST64_MAX;
	static const fastType FastMin=INT_FAST64_MIN;
	static const ufastType UFastMax=UINT_FAST64_MAX;
	static const ufastType UFastMin=0;
	static const leastType LeastMax=INT_LEAST64_MAX;
	static const leastType LeastMin=INT_LEAST64_MIN;
	static const uleastType ULeastMax=UINT_LEAST64_MAX;
	static const uleastType ULeastMin=0;
    };

}
#endif
