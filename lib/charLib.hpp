/*!
 * \autor captainpeng
 * \date 2018-12-29
 * \update 2018-12-29
 * \version 1.0
 * \copyright
 */

#ifndef charLib_hpp
#define charLib_hpp

#include<cctype>
#include<cwctype>

namespace my{
    
    template<typename CharT>
    class charLib;
	
    template<>
    class charLib<char>{
    public:
	using charType=char;

	static inline bool isalnum(charType ch){
	    return static_cast<bool>(std::isalnum(ch));
	}

	static inline bool isalpha(charType ch){
	    return static_cast<bool>(std::isalpha(ch));
	}

	static inline bool islower(charType ch){
	    return static_cast<bool>(std::islower(ch));
	}

	static inline bool isupper(charType ch){
	    return static_cast<bool>(std::isupper(ch));
	}

	static inline bool isdigit(charType ch){
	    return static_cast<bool>(std::isdigit(ch));
	}

	static inline bool isxdigit(charType ch){
	    return static_cast<bool>(std::isxdigit(ch));
	}

	static inline bool iscntrl(charType ch){
	    return static_cast<bool>(std::iscntrl(ch));
	}

	static inline bool isgraph(charType ch){
	    return static_cast<bool>(std::isgraph(ch));
	}

	static inline bool isspace(charType ch){
	    return static_cast<bool>(std::isspace(ch));
	}

	static inline bool isblank(charType ch){
	    return static_cast<bool>(std::isblank(ch));
	}

	static inline bool isprint(charType ch){
	    return static_cast<bool>(std::isprint(ch));
	}

	static inline bool ispunct(charType ch){
	    return static_cast<bool>(std::ispunct(ch));
	}

	static inline charType tolower(charType ch){
	    return static_cast<charType>(std::tolower(ch));
	}

	static inline charType toupper(charType ch){
	    return static_cast<charType>(std::toupper(ch));
	}
	
    };

    template<>
    class charLib<wchar_t>{
    public:
	using charType=wchar_t;

	static inline bool isalnum(charType ch){
	    return static_cast<bool>(std::iswalnum(ch));
	}

	static inline bool isalpha(charType ch){
	    return static_cast<bool>(std::iswalpha(ch));
	}

	static inline bool islower(charType ch){
	    return static_cast<bool>(std::iswlower(ch));
	}

	static inline bool isupper(charType ch){
	    return static_cast<bool>(std::iswupper(ch));
	}

	static inline bool isdigit(charType ch){
	    return static_cast<bool>(std::iswdigit(ch));
	}

	static inline bool isxdigit(charType ch){
	    return static_cast<bool>(std::iswxdigit(ch));
	}

	static inline bool iscntrl(charType ch){
	    return static_cast<bool>(std::iswcntrl(ch));
	}

	static inline bool isgraph(charType ch){
	    return static_cast<bool>(std::iswgraph(ch));
	}

	static inline bool isspace(charType ch){
	    return static_cast<bool>(std::iswspace(ch));
	}

	static inline bool isblank(charType ch){
	    return static_cast<bool>(std::iswblank(ch));
	}

	static inline bool isprint(charType ch){
	    return static_cast<bool>(std::iswprint(ch));
	}

	static inline bool ispunct(charType ch){
	    return static_cast<bool>(std::iswpunct(ch));
	}

	static inline charType tolower(charType ch){
	    return static_cast<charType>(std::towlower(ch));
	}

	static inline charType toupper(charType ch){
	    return static_cast<charType>(std::towupper(ch));
	}
	
    };

}

#endif
