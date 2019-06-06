/*!
 * \autor captainpeng
 * \date 2019-1-15
 * \update 2019-1-15
 * \version 1.0
 * \copyright
 */

#ifndef typeGen_hpp
#define typeGen_hpp

namespace my{

    template<int Value>
    class int2type{
    public:
	static const int value=Value;
    };

    template<bool Value>
    class bool2type{
    public:
	static const bool value=Value;
    };

    
}

#endif
