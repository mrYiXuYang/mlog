#pragma once
#include<memory>
#ifndef MLOG
#define MLOG
#else
#error havs been defined MLOG
#endif // !MLOG

/*
	this log file program can't save the log witch has '#'.'\0' char
*/

namespace MyLog
{


	typedef unsigned char byte, bit8;
	typedef unsigned short bit16;
	typedef unsigned int bit32;
	typedef unsigned long long bit64;
	typedef long long llong;
	typedef long double ldouble;
	typedef int logkey;

#define M_FLOAT_SAVE_FLAG 8//the float can save 8 point

#define M_FLOAT_EQUAL_FLAG 0.0001f //float compare 

#define	M_INTNB_STR_TEN(buff,nb) do{char nbf[sizeof(buff)]={0};memset(buff,0,sizeof(buff));\
llong arg=nb;int begin=0,sz=0; if(arg<0){arg=-arg;buff[0]='-';begin=1;}\
while(true){if(arg/10==0){nbf[sz]='0'+(arg%10);break;}\
else nbf[sz++]='0'+arg%10,arg/=10;}\
for(int i=begin,j=sz;i<=(begin==0?sz:sz+1);i++,j--){buff[i]=nbf[j];}}while(0);//inteager number to the decimal string ,buff must be the char[];

#define M_INTNB_STR_SIXTY(buff,nb) do{char nbf[sizeof(buff)]={0};memset(buff,0,sizeof(buff));\
llong arg=nb;int sz=0,temp=0;buff[0]='0',buff[1]='x';\
while(true){temp=arg&0x0f;nbf[sz++]=temp>=10?'a'+(temp-10):'0'+temp;\
if((arg>>=4)==0){break;}}\
for(int i=2,j=sz-1;i<sz+2;i++,j--){buff[i]=nbf[j];}}while(0);//inteager number to the hex string ,buff must be the char[];

#define M_FLOATNB_STR(buff,nb) do{\
	memset(buff,0,sizeof(buff));\
	char nbf1[sizeof(buff)]={0};\
	char nbf2[M_FLOAT_SAVE_FLAG+1]={0};\
	llong temp=(llong)nb;\
	ldouble arg1=nb<0?temp-nb:nb-temp;\
	int start=0;\
	if(temp==0&&nb<0){nbf1[0]='-',nbf1[1]='0';start=2;}\
	else{M_INTNB_STR_TEN(nbf1,temp);start=strlen(nbf1);}\
	memcpy(buff,nbf1,start);buff[start]='.',start++;\
	int len=0;\
	do{arg1*=10;temp=(llong)arg1;arg1-=temp;nbf2[len++]='0'+temp;}while(len<=M_FLOAT_SAVE_FLAG||arg1==0);\
	for(int i=start,j=0;i<start+len-1;i++,j++){buff[i]=nbf2[j];}\
	}while(0);//float number to the string,buff must be the char[];

#define M_LOG_DEFAULT_LEN (1024*1024) //the defualt logs memory len is 1m

#define M_LOG_START_FLAG_CHAR '#'
#define M_LOG_END '\0'
#define M_LOG_ENTER '\n'
#define M_LOG_AFTERKY_CHAR ':'
#define LENDL '\n'<<'\0'

#define M_LOG_WRITE_FILE 0x01 //write to the file
#define M_LOG_WRITE_CONSOLE 0x02//write to the console

	bool Str_equal_log(const char* str1, const char* str2);
/*
	atuor:yixuyang 
	telphone:18225227554
	becarefor:
		this logs class can save a log beigain with main_key,the main_key can't have the same for the log
		this logs can't save this string witch have char '#' '\0' ':'
		this logs will not save msg when you prep save a the same main_ky log
*/
	class Logs
	{
	private:
		bit64 len;
		bit32 nexptr;
		char* data;
		bool saveflag;
	public:
		Logs();//default logs length 1m
		Logs(bit64 preplen);//preplen logs length
		Logs(const char* logflpath);//load other logs from file
		virtual ~Logs();

		Logs& push_back_main_key(logkey key);//add main key
		Logs& push_back_main_key(const char* str);//add main key


		//add mesages to the log
		Logs& push_back(const char* str);
		Logs& push_back_hexnb(bit64 arg);//save with hex
		Logs& push_back_decnb(long long arg);//save with decimal
		Logs& push_back_floatnb(long double arg);
		Logs& operator<<(const char* str);
		Logs& operator<<(char arg);
		Logs& operator<<(unsigned char arg);
		Logs& operator<<(short arg);
		Logs& operator<<(unsigned short arg);
		Logs& operator<<(int arg);
		Logs& operator<<(unsigned int arg);
		Logs& operator<<(long arg);
		Logs& operator<<(unsigned long arg);
		Logs& operator<<(long long arg);
		Logs& operator<<(unsigned long long arg);
		Logs& operator<<(float arg);
		Logs& operator<<(double arg);
		Logs& operator<<(long double arg);

		//write
		void Write(bit8 where_flag, const char* title);
		//find 
		char* Find_by_key(logkey key);
		char* Find_by_key(const char* key);

		//get the log data char ptr
		char* C_str();
	};
}

