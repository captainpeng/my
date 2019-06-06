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
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<cwchar>

namespace my{
    
    template<typename CharT>
    class charLib;
	
    template<>
    class charLib<char>{
	charLib() = delete;
    public:
	using charType=char;
	using charPtr=char *;
	using intType=int;
	
	static const intType empty='\0';
	static const intType enter='\n';
	static const intType eof=EOF;
	
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

	static inline wint_t towchar(intType c){
	    return std::btowc(c);
	}
	
	static inline const wchar_t * towstr(const charType * src){
	    static wchar_t buf[4096];
	    std::mbstowcs(buf,src,4096);
	    return buf;
	}

	// 字符串操作
	static inline int strlen(const charPtr src){
	    return std::strlen(src);
	}

	static inline const charType * strchg(const char * src){
	    return src;
	}
	
	// IO 操作
	static inline intType fputc(std::FILE * fp,intType c){
	    return std::putc(c,fp);
	}

	static inline intType fgetc(std::FILE * fp){
	    return std::getc(fp);
	}

	static inline bool fputs(std::FILE * fp,const charPtr src){
	    return std::fputs(src,fp) != EOF;
	}
	
	static inline int fgets(std::FILE * fp,charPtr src,int size){
	    return std::fgets(src,size,fp) != NULL;
	}

    };

    template<>
    class charLib<wchar_t>{
	charLib() = delete;
    public:
	using charType=wchar_t;
	using charPtr=wchar_t *;
	using intType=wint_t;

	static const intType empty=L'\0';
	static const intType enter=L'\n';
	static const intType eof=WEOF;
	
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

	// 字符串操作
	static inline int strlen(const charPtr src){
	    return std::wcslen(src);
	}

	static inline const charType * strchg(const char * src){
	    return charLib<char>::towstr(src);
	}
	
	// IO 操作
	static inline intType fputc(std::FILE * fp,intType c){
	    return std::putwc(c,fp);
	}

	static inline intType fgetc(std::FILE * fp){
	    return std::getwc(fp);
	}

	static inline bool fputs(std::FILE * fp,const charPtr src){
	    return std::fputws(src,fp) != EOF;	
	}
	
	static inline bool fgets(std::FILE * fp,charPtr dst,int size){
	    return std::fgetws(dst,size,fp) != NULL;
	}
    };

}

#endif
