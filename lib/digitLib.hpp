/*!
 * \autor captainpeng
 * \date 2019-1-14
 * \update 2019-1-14
 * \version 1.0
 * \copyright
 */

#ifndef digitLib_hpp
#define digitLib_hpp

namespace my{

    template<typename DigitType,typename Enable=enable_digit_t<DigitType>>
    class  digitLib{
    private:
	using digitType=info_type_t<DigitType>;
	using digitConstType=info_constType_t<DigitType>;
	using digitPtr=info_ptr_t<DigitType>;
	using digitConstPtr=info_constPtr_t<DigitType>;
	
    public:

	static inline digitType max(digitConstPtr ptr,int len){
	    digitType maxValue=*ptr;
	    
	    for(int i=1;i < len;++i)
		maxValue=(ptr[i] > maxValue)?ptr[i]:maxValue;

	    return maxValue;
	}
	
	static inline digitType max(digitConstType i,digitConstType j){
	    return (i > j)?i:j;
	}

	static inline digitType min(digitConstPtr ptr,int len){
	    digitType minValue=*ptr;

	    for(int i=1;i < len;++i)
		minValue=(ptr[i] > minValue)?minValue:ptr[i];

	    return minValue;
	}
	
	static inline digitType min(digitConstType i,digitConstType j){
	    return (i > j)?j:i;
	}

	static inline digitType abs(digitConstType i){
	    return (i > 0)?i:-i;
	}

    };
    
}

#endif
