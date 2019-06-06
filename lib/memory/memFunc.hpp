/*!
 * \autor captainpeng
 * \date 2019-5-15
 * \update 2019-5-15
 * \version 1.0
 * \copyright
 */

#ifndef memFunc_hpp
#define memFunc_hpp

namespace my{
    template<typename Type>
    class memFunc{
    public:
	using type=Type;
	using fnAllocType=void*(*)(int);
	using fnFreeType=void(*)(void *);

	memFunc() = delete;

	static void * Alloc(int size){
	    return static_cast<void *>(new type[size]);
	}
	
	static void Free(void * p){
	    delete [] static_cast<type *>(p);
	}

    };
}

#endif
