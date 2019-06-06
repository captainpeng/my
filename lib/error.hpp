/*!
 * \autor captainpeng
 * \date 2019-5-13
 * \update 2019-5-13
 * \version 1.0
 * \copyright
 */

#ifndef error_hpp
#define error_hpp

#include<cerrno>
#include<cstdarg>
#include<cwchar>
#include<cstdlib>
#include"mystd.hpp"

#include<iostream>

#define MAXLINE 4096
namespace my{
    class errorDo{
    public:
	static void doit(bool errnoflag,int err,const char * fmt,va_list ap){
	    char buf[MAXLINE];
	    std::vsnprintf(buf,MAXLINE,fmt,ap);
	    if(errnoflag)
		std::snprintf(buf+std::strlen(buf),MAXLINE-std::strlen(buf),": %s",std::strerror(err));    

	    std::strcat(buf,"\n");
	    std::fflush(stdout);
	    std::fputs(buf,stderr);
	    std::fflush(NULL);
	    
	}

	static void doit(bool errnoflag,int err,const wchar_t * fmt,va_list ap){
	    wchar_t buf[MAXLINE];
	    std::vswprintf(buf,MAXLINE,fmt,ap);

	    if(errnoflag)
		std::swprintf(buf+std::wcslen(buf),MAXLINE-std::wcslen(buf),L": %ls",charLib<char>::towstr(std::strerror(err)));
	    
	    std::wcscat(buf,L"\n");
	    std::fflush(stdout);
	    std::fputws(buf,stderr);
	    std::fflush(NULL);
	}
    };
    
    template<typename CharT,
	     typename Enable=enable_wc_char_t<CharT> >
    class error{
    public:
	using charType=info_type_t<CharT>;
	
    private:
	// static void doit(bool errnoflag,int err,const charType * fmt,va_list ap){
	//     charType buf[MAXLINE];
	//     std::vsnprintf(buf,MAXLINE,fmt,ap);
	//     if(errnoflag)
	// 	switch(sizeof(charType)){
	// 	case sizeof(char):
	// 	    std::snprintf(buf+std::strlen(buf),MAXLINE-std::strlen(buf),": %s",std::strerror(err));
	// 	    break;
	// 	case sizeof(wchar_t):
		    

	//     strcat(buf,"\n");
	//     fflush(stdout);
	//     fputs(buf,stderr);
	//     fflush(NULL);
	// }
	
    public:
	error()=delete;
	
	// * Nonfatal error related to a system call. 
	// * Print a message and return.   
	static void ret(const charType *fmt, ...){  
		va_list     ap;  
  
		va_start(ap, fmt);  
		doit(true, errno, fmt, ap);  
		va_end(ap);  
	}  
	
  

	// * Fatal error related to a system call. 
	// * Print a message and terminate.   
	static void sys(const charType *fmt, ...){  
		va_list     ap;  
  
		va_start(ap, fmt);  
		errorDo::doit(true, errno, fmt, ap);  
		va_end(ap);  
		std::exit(1);  
	}  
	
  

	// * Fatal error unrelated to a system call. 
	// * Error code passed as explict parameter. 
	// * Print a message and terminate.   

	static void exit(int error, const charType *fmt, ...){  
		va_list     ap;  
  
		va_start(ap, fmt);  
		errorDo::doit(true, error, fmt, ap);  
		va_end(ap);  
		std::exit(1);  
	}  
	
  

	// * Fatal error related to a system call. 
	// * Print a message, dump core, and terminate.   

	static void dump(const charType *fmt, ...){  
		va_list     ap;  
  
		va_start(ap, fmt);  
		errorDo::doit(true, errno, fmt, ap);  
		va_end(ap);  
		abort();        /* dump core and terminate */  
		std::exit(1);        /* shouldn't get here */  
	}  
  
  

	// * Nonfatal error unrelated to a system call. 
	// * Print a message and return.   
	static void msg(const charType *fmt, ...){  
		va_list     ap;  
  
		va_start(ap, fmt);  
		errorDo::doit(false, 0, fmt, ap);  
		va_end(ap);  
	}  
	
  

	// * Fatal error unrelated to a system call. 
	// * Print a message and terminate.   
	static void quit(const charType *fmt, ...){  
		va_list     ap;  
  
		va_start(ap, fmt);  
		errorDo::doit(false, 0, fmt, ap);  
		va_end(ap);  
		std::exit(1);  
	}  
    };
}
#endif
