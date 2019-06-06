/*!
 * \autor captainpeng
 * \date 2019-3-9
 * \update 2019-3-9
 * \version 1.0
 * \copyright
 */

#ifndef hwPtr_hpp
#define hwPtr_hpp

#include"mystd.hpp"

namespace my{

    template<typename ElementType>
    class hwPtr{
    private:
	using elementType=info_type_t<ElementType>;
	using elementPtr=info_ptr_t<ElementType>;
	using elementRef=info_ref_t<ElementType>;
	using elementConstRef=info_constRef_t<ElementType>;
	using elementConstPtr=info_constPtr_t<ElementType>;

	using memType=memory<elementType>;
    public:
	elementPtr mValue;

    public:
	// hwPtr():mValue(nil<elementType>()){}
	hwPtr(elementPtr p=nullptr):mValue(p){}
	hwPtr(std::nullptr_t):mValue(nullptr){}
	hwPtr(const hwPtr & p):mValue(p.mValue){}
	hwPtr(hwPtr && p){
	    memType::exchange(&mValue,&p.mValue);
	}
	
	hwPtr & operator=(const hwPtr & p){
	    if(this != &p){
		this->free();
		mValue=p.mValue;
	    }
	    return *this;
	}

	hwPtr & operator=(hwPtr && p){
	    memType::exchange(&mValue,&p.mValue);
	    return *this;
	}

	hwPtr & operator=(elementPtr p){
	    mValue=p;
	    return *this;
	}

	hwPtr & operator=(std::nullptr_t){
	    mValue=nil<elementType>();
	    return *this;
	}
	
	~hwPtr(){ this->free(); }

	inline void alloc(){
	    this->free();
	    memType::alloc(&mValue,1);
	}

	inline void free(){
	    if(mValue != nil<elementType>())
		memType::free(&mValue);
	}

	inline bool isPower(){
	    std::cout<<static_cast<void*>(&mValue)<<std::endl;
		    
	    return memType::isPower(&mValue);
	}
	
	elementPtr get() const {
	    if(mValue != nullptr && memType::exist(mValue))
	       return mValue;
	    return (*const_cast<elementPtr*>(&mValue)=nil<elementType>());
	}

	void swap(hwPtr & p){
	    memType::exchange(&mValue,&p.mValue);
	}

	explicit operator bool() const {
	    return mValue != nil<elementType>();
	}
	
	inline elementRef operator*() const {
	    return *get();
	}

	inline elementPtr operator->() const {
	    return get();
	}
	
	hwPtr & operator++(){
	    ++mValue;
	    return *this;
	}

	hwPtr & operator--(){
	    --mValue;
	    return *this;
	}

	hwPtr operator++(int){
	    hwPtr tmp(*this);
	    ++mValue;
	    return tmp;
	}

	hwPtr operator--(int){
	    hwPtr tmp(*this);
	    --mValue;
	    return tmp;
	}
	
	inline hwPtr operator+(const std::ptrdiff_t i){
	    return hwPtr(mValue+i);
	}

	inline hwPtr operator-(const std::ptrdiff_t i){
	    return hwPtr(mValue-i);
	}

	elementType & operator[](const std::ptrdiff_t i){
	    std::ptrdiff_t pos=intLib<std::ptrdiff_t>::abs(i);
	    return mValue[pos];
	}
	
	void swap(const hwPtr & p){
	    memType::exchange(&mValue,&p.mValue);
	}

    };

    template<typename T>
    inline bool operator==(const hwPtr<T> & p,std::nullptr_t){
	return p.get() == nil<T>();
    }

    template<typename T>
    inline bool operator==(std::nullptr_t,const hwPtr<T> & p){
	return p.get() == nil<T>();
    }

    template<typename T>
    inline bool operator!=(const hwPtr<T> & p,std::nullptr_t){
	return p.get() != nil<T>();
    }

    template<typename T>
    inline bool operator!=(std::nullptr_t,const hwPtr<T> & p){
	return p.get() != nil<T>();
    }

    template<typename T>
    inline bool operator==(const hwPtr<T> & p1,const hwPtr<T> & p2){
	return p1.get() == p2.get();
    }

    template<typename T>
    inline bool operator!=(const hwPtr<T> & p1,const hwPtr<T> & p2){
	return !(p1 == p2);
    }
    
    template<typename T>
    inline bool operator>(const hwPtr<T> & p1,const hwPtr<T> & p2){
	return p1.get() > p2.get();
    }

    template<typename T>
    inline bool operator>=(const hwPtr<T> & p1,const hwPtr<T> & p2){
	return (p1 > p2) || (p1 == p2);
    }
    
    template<typename T>
    inline bool operator<(const hwPtr<T> & p1,const hwPtr<T> & p2){
	return !(p1 > p2);
    }

    template<typename T>
    inline bool operator<=(const hwPtr<T> & p1,const hwPtr<T> & p2){
	return (p1 < p2) || (p1 == p2);
    }

    template<typename T>
    inline void swap(hwPtr<T> & p1,hwPtr<T> & p2){
	p1.swap(p2);
    }

    template<typename T>
    hwPtr<T> hwNil(){
	return hwPtr<T>(nil<T>());
    }
}

#endif
