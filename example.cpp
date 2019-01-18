#include"mlog.h"


using namespace MyLog;//logs namespace

int main()
{
	Logs log(1024);//make memory size is 1024*sizeof(char)
	//Logs log("test");//load other's logs

	//a log must have a main key,the main_key enable is 'int' or string,it must be end with 'LENDL' 
	log.push_back_main_key("100") << " the world" << LENDL;//add a main key is'100' log
	log.push_back_main_key(100) << " shen mei gui" << LENDL;//it can't be added because of the 100='100' in logs memory
	log.push_back_main_key("test") << " da wo a" << LENDL;//add a mian key is 'test' log
	
	log.Write(M_LOG_WRITE_FILE, "test");//wirte logs to the file,the file name is'test'
	log.Write(M_LOG_WRITE_CONSOLE, "test");//write logs to the console,the logs title is 'test'

	printf("this is find:%s", log.Find_by_key("test"));//to find the main key is 'test' log and then return this log's string
	printf("this is find:%s", log.Find_by_key(100));//to find the main key is '100' log and then return this log's string

	getchar();
	return 0;
}