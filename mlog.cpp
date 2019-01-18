#include<stdio.h>
#include"mlog.h"

namespace MyLog
{

	bool Str_equal_log(const char* str1, const char* str2)
	{
		bit32 len1 = strlen(str1);
		bit32 len2 = strlen(str2);
		if (len1 != len2 || len1 == 0 || len2 == 0)
			return false;
		for (bit32 i = 0; i < len1; i++)
			if (str1[i] != str2[i])
				return false;
		return true;
	}

	Logs::Logs(const char* path)
	{
		FILE *f = fopen(path, "r");
		if (!f)
			data = new char[M_LOG_DEFAULT_LEN],memset(data,0,M_LOG_DEFAULT_LEN),nexptr=0,len=M_LOG_DEFAULT_LEN;
		else
		{
			fseek(f, 0, SEEK_END);
			long len1 = ftell(f);
			fseek(f, 0, SEEK_SET);
			len = len1 + len1 / 2;
			len = len > M_LOG_DEFAULT_LEN ? len : M_LOG_DEFAULT_LEN;
			char *temp = new char[len];
			memset(temp, 0, len);
			fread(temp, sizeof(char), len1, f);
			data = temp;
			while (data[len1] == M_LOG_END)
			{
				len1--;
				if (len1 < 0)
				{
					break;
				}
			}
			nexptr = len1 < 0 ? 0 : len1+2;
			
		}

	}

	Logs::Logs()
	{
		nexptr = 0;
		data = new char[M_LOG_DEFAULT_LEN];
		memset(data, 0, M_LOG_DEFAULT_LEN);
		len = M_LOG_DEFAULT_LEN;
	}

	Logs::Logs(bit64 preplen)
	{
		preplen = preplen < 2 ? 2 : preplen;//
		nexptr = 0;
		data = new char[preplen];
		memset(data, 0, preplen);
		this->len = preplen;
	}

	Logs::~Logs()
	{
		if (data)
			delete[]data;
		data = nullptr;
		nexptr = 0;
	}

	Logs& Logs::push_back(const char*buff)
	{
		bit32 len1 = strlen(buff);
		if (len1 == 0)
		{
			this->data[nexptr++] = '\0';
			return *this;
		}
		bit64 temp = this->len;
		while (nexptr + len1 > this->len)
			len += len / 2;
		if (temp != len)
		{
			char* nd = new char[len];
			memset(nd, 0, len);
			memcpy(nd, data, temp);
			delete[]data;
			data = nd;
		}
		//
		memcpy(data + nexptr, buff, len1);
		nexptr += len1;
		return *this;
	}

	Logs& Logs::push_back_main_key(logkey mainkey)
	{
		if (this->Find_by_key(mainkey))
			return *this;
		char buffs[21] = { 0 };
		M_INTNB_STR_TEN(buffs, mainkey);
		bit32 len1 = strlen(buffs);
		bit64 temp = this->len;
		while (nexptr + len1+2 > this->len)
			len += len / 2;
		if (temp != len)
		{
			char* nd = new char[len];
			memset(nd, 0, len);
			memcpy(nd, data, temp);
			delete[]data;
			data = nd;
		}
		data[nexptr++] = M_LOG_START_FLAG_CHAR;
		memcpy(data + nexptr, buffs, len1);
		nexptr += len1;
		data[nexptr++] = M_LOG_AFTERKY_CHAR;
		return *this;

	}

	char* Logs::Find_by_key(logkey key)
	{
		char buff[21] = {0};
		char buff1[21] = {0};
		M_INTNB_STR_TEN(buff, key);
		// find the '#'
		if (nexptr == 0)
			return nullptr;
		bit32 flag = 0;
		bit32 i = 0;
		bit32 result = 0;
		while (flag < nexptr)
		{
			if (data[flag++] == M_LOG_START_FLAG_CHAR)
			{
				i = 0;
				result = flag;
				while ((data[flag] >= '0'&&data[flag] <= '9') || data[flag] == '-')
				{
					buff1[i++] = data[flag++];
				}
				if (Str_equal_log(buff, buff1))
				{
					return data+result;
				}
			}
		}
		return nullptr;

	}

	Logs& Logs::operator<<(const char* str)
	{
		return this->push_back(str);
	}

	Logs& Logs::operator<<(char arg)
	{
		char b[2] = { arg,'\0' };
		return this->push_back(b);
	}

	Logs& Logs::push_back_hexnb(bit64 str)
	{
		char buff[30];
		M_INTNB_STR_SIXTY(buff, str);
		return this->push_back(buff);
	}

	Logs& Logs::push_back_decnb(long long str)
	{
		char buff[40];
		M_INTNB_STR_TEN(buff, str);
		return this->push_back(buff);
	}

	Logs& Logs::push_back_floatnb(long double str)
	{
		char buff[40];
		M_FLOATNB_STR(buff, str);
		return this->push_back(buff);
	}

	Logs& Logs::operator<<(unsigned char str)
	{
		char b[2] = { str,'\0' };
		return this->push_back(b);
	}

	Logs& Logs::operator<<(short str)
	{
		char buff[20];
		M_INTNB_STR_TEN(buff,str);
		return this->push_back(buff);
	}

	Logs& Logs::operator<<(unsigned short str)
	{
		char b[20];
		M_INTNB_STR_TEN(b, str);
		return this->push_back(b);
	}

	Logs& Logs::operator<<(int str)
	{
		char buff[30];
		M_INTNB_STR_TEN(buff, str);
		return this->push_back(buff);
	}

	Logs& Logs::operator<<(unsigned int str)
	{
		char buff[30];
		M_INTNB_STR_TEN(buff, str);
		return this->push_back(buff);
	}

	Logs& Logs::operator<<(long str)
	{
		char buff[30];
		M_INTNB_STR_TEN(buff, str);
		return this->push_back(buff);
	}

	Logs& Logs::operator<<(unsigned long str)
	{
		char buff[30];
		M_INTNB_STR_TEN(buff, str);
		return this->push_back(buff);
	}

	Logs& Logs::operator<<(long long str)
	{
		char buff[40];
		M_INTNB_STR_TEN(buff, str);
		return this->push_back(buff);
	}
	
	Logs& Logs::operator<<(unsigned long long str)
	{
		char buff[40];
		M_INTNB_STR_TEN(buff, str);
		return this->push_back(buff);
	}

	Logs& Logs::operator<<(float str)
	{
		char buff[20];
		M_FLOATNB_STR(buff, str);
		return this->push_back(buff);
	}

	Logs& Logs::operator<<(double str)
	{
		char buff[30];
		M_FLOATNB_STR(buff, str);
		return this->push_back(buff);
	}

	Logs& Logs::operator<<(long double str)
	{
		char buff[40];
		M_FLOATNB_STR(buff, str);
		return this->push_back(buff);
	}

	void Logs::Write(bit8 where_flag, const char* title)
	{
		switch (where_flag)
		{
		case M_LOG_WRITE_FILE:
		{
			FILE *f = fopen(title, "w");
			fwrite(data, sizeof(char), nexptr - 1, f);
			fclose(f);
		}break;
		case M_LOG_WRITE_CONSOLE:
		{
			printf("%s\n", title);
			for (bit64 i = 0; i < nexptr - 1; i++)
			{
				if (data[i] == M_LOG_START_FLAG_CHAR)
				{
					i++;
					printf("%s", data + i);
				}
			}
	
		}break;
		default:
			break;
		}
	}


	char* Logs::C_str()
	{
		return data;
	}
}