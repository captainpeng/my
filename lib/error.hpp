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

namespace my{
    class error{
    private:
	static void doit(bool errnoflag,int err,const char * fmt,va_list ap){
	    char buf[MAXLINE];
	    std::vsnprintf(buf,MAXLINE,fmt,ap);
	    if(errnoflag)
		std::snprintf(buf+strlen(buf),MAXLINE-strlen(buf),": %s",strerror(error));

	    strcat(buf,"\n");
	    fflush(stdout);
	    fputs(buf,stderr);
	    fflush(NULL);
	}
	
    public:
	error()=delete;
	
	// * Nonfatal error related to a system call. 
	// * Print a message and return.   
	static void ret(const char *fmt, ...){  
		va_list     ap;  
  
		va_start(ap, fmt);  
		doit(true, errno, fmt, ap);  
		va_end(ap);  
	}  
	
  

	// * Fatal error related to a system call. 
	// * Print a message and terminate.   
	static void sys(const char *fmt, ...){  
		va_list     ap;  
  
		va_start(ap, fmt);  
		doit(true, errno, fmt, ap);  
		va_end(ap);  
		exit(1);  
	}  
	
  

	// * Fatal error unrelated to a system call. 
	// * Error code passed as explict parameter. 
	// * Print a message and terminate.   

	static void exit(int error, const char *fmt, ...){  
		va_list     ap;  
  
		va_start(ap, fmt);  
		doit(true, error, fmt, ap);  
		va_end(ap);  
		exit(1);  
	}  
	
  

	// * Fatal error related to a system call. 
	// * Print a message, dump core, and terminate.   

	static void dump(const char *fmt, ...){  
		va_list     ap;  
  
		va_start(ap, fmt);  
		doit(true, errno, fmt, ap);  
		va_end(ap);  
		abort();        /* dump core and terminate */  
		exit(1);        /* shouldn't get here */  
	}  
  
  

	// * Nonfatal error unrelated to a system call. 
	// * Print a message and return.   
	static void msg(const char *fmt, ...){  
		va_list     ap;  
  
		va_start(ap, fmt);  
		doit(false, 0, fmt, ap);  
		va_end(ap);  
	}  
	
  

	// * Fatal error unrelated to a system call. 
	// * Print a message and terminate.   
	static void quit(const char *fmt, ...){  
		va_list     ap;  
  
		va_start(ap, fmt);  
		doit(false, 0, fmt, ap);  
		va_end(ap);  
		exit(1);  
	}  
    };
}
#endif
