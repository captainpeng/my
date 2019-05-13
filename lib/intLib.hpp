/*!
 * \autor captainpeng
 * \date 2018-12-28
 * \update 2018-12-28
 * \version 1.0
 * \copyright
 */

#ifndef intLib_hpp
#define intLib_hpp
#include<cmath>

namespace my{

    
    template<typename INT>
    class intLib{
    private:
	using intType=INT;
	using intPtr=intType *;
	
    public:

	static intType max(const intPtr ptr,int len){
	    intType maxValue=*ptr;
	    
	    for(int i=1;i < len;++i)
		maxValue=(ptr[i] > maxValue)?ptr[i]:maxValue;

	    return maxValue;
	}
	
	static inline intType max(const intType i,const intType j){
	    return (i > j)?i:j;
	}

	static intType min(const intPtr ptr,const int len){
	    intType minValue=*ptr;

	    for(int i=1;i < len;++i)
		minValue=(ptr[i] > minValue)?minValue:ptr[i];

	    return minValue;
	}
	
	static inline intType min(const intType i,const intType j){
	    return (i > j)?j:i;
	}

	static inline intType abs(const intType i){
	    return (i > 0)?i:-i;
	}

	static inline bool isPrime(const intType i){
	    // flag 用于控制是否需要进行的标志，若 flag 为 false 则无需继续下去
	    bool flag=(i >= 2 && i%2 != 0);
	    // 质数只要判断到其平方根即可
	    int threshold=(flag)?std::sqrt(i):0;
	    
	    for(int j=3;j <= threshold && flag;j+=2){
		flag=(i%j != 0);
	    }

	    // 当 flag 为 false 的时候，i 有可能等于 2 且 2 是质数
	    return flag || i == 2;
	}

	static intType nextPrime(const intType i){
	    bool flag=(i >= 2);
	    intType result=(flag)?i-static_cast<int>(i%2 == 0):2;
	    while(flag){
		result+=2;
		// 这里取反因为当 result 不是质数的时候要继续进行
		flag=!isPrime(result);
	    }
	    
	    return result;
	}
    };
    
}

#endif
