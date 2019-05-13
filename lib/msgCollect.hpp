/*!
 * \autor captainpeng
 * \date 2019-3-13
 * \update 2019-3-13
 * \version 1.0
 * \copyright
 */

#ifndef msgCollect_hpp
#define msgCollect_hpp

#include<cstdio>

#include"mystd.hpp"

namespace my{

    template<typename CharT=char>
    class msgCollect;

    template<>
    class msgCollect<char>{
    public:
	using charType=char;
	using stringType=std::basic_string<charType>;
	using filePtr=std::FILE *;
    private:
	filePtr file;

	void init(const char * filename,const char * mode){
	    if((file=std::fopen(filename,mode)) == NULL){
		std::cerr<<"File "<<filename<<" opening "
			 <<mode<<" failed"<<std::endl;
		file=stdout;
	    }
		    
	}

	
    public:
	msgCollect():file(stdout){}
	
	msgCollect(const std::string & filename){
	    init(filename.c_str(),"a+");
	}

	msgCollect(msgCollect && mc){
	    file=mc.file;
	    mc.file=stdout;
	}
	
	msgCollect & operator=(const std::string & filename){
	    close();
	    init(filename.c_str(),"a+");
	    return *this;
	}

	msgCollect & operator=(msgCollect && mc){
	    if(this != &mc){
		close();
		file=mc.file;
		mc.file=stdout;
	    }
	    return *this;
	}

	FILE * fp(){
	    return file;
	}
	
	bool close(){
	    if(file != stdout || file != stdin || file != stderr){
		std::fclose(file);
	    }
	    return (std::fclose(file)==0);
	}

	// bool printf(const stringType & format, ... ){
	//     return std::fprintf(file,format.c_str(), ... ) > 0;
	// }

	bool put(const charType c){
	    return std::fputc(c,file) != EOF;
	}
	
	bool put(const stringType & str){
	    return std::fputs(str.c_str(),file) != EOF;
	}

	// bool get(charType & c){
	//     return (c = fget(file)) != EOF;
	// }

	// bool gets(stringType & str){
	//     char buf[1024];
	//     str.clear();
	//     int size=str.capacity();

	//     while(size > 0){
	// 	if(fgets(buf,(size > 1024)?1024:size,file) !=NULL){
	// 	    str.append(buf);
	// 	}else{
	// 	    return std::feof(file) != 0;
	// 	}
	// 	size-=1024;
	//     }
	// }
	
	~msgCollect(){
	    close();
	}
    };

    template<>
    class msgCollect<wchar_t>{
    public:
	using charType=wchar_t;
	using stringType=std::basic_string<charType>;
	using filePtr=std::FILE *;
    private:
	filePtr file;

	void init(const char * filename,const char * mode){
	    if((file=std::fopen(filename,mode)) == NULL){
		std::fwide(file,1);
		std::cerr<<"File "<<filename<<" opening"
			 <<mode<<" failed"<<std::endl;
		file=stdout;
	    }
		    
	}

	
    public:
	msgCollect():file(stdout){}
	
	msgCollect(const std::string & filename){
	    init(filename.c_str(),"a+");
	}

	msgCollect(msgCollect && mc){
	    file=mc.file;
	    mc.file=stdout;
	}
	
	msgCollect & operator=(const std::string & filename){
	    close();
	    init(filename.c_str(),"a+");
	    return *this;
	}

	msgCollect & operator=(msgCollect && mc){
	    if(this != &mc){
		close();
		file=mc.file;
		mc.file=stdout;
	    }
	    return *this;
	}

	FILE * fp(){
	    return file;
	}
	
	bool close(){
	    if(file != stdout || file != stdin || file != stderr){
		    fclose(file);
	    }
	    return (std::fclose(file)==0);
	}

	bool put(const charType c){
	    return std::fputwc(c,file) != EOF;
	}
	
	bool put(const stringType & str){
	    return std::fputws(str.c_str(),file) != EOF;
	}

	// bool get(charType & c){
	//     return (c = fget(file)) != EOF;
	// }

	// bool gets(stringType & str){
	//     char buf[1024];
	//     str.clear();
	//     int size=str.capacity();

	//     while(size > 0){
	// 	if(fgets(buf,(size > 1024)?1024:size,file) !=NULL){
	// 	    str.append(buf);
	// 	}else{
	// 	    return std::feof(file) != 0;
	// 	}
	// 	size-=1024;
	//     }
	// }
	
	~msgCollect(){
	    close();
	}
    };

}

#endif
