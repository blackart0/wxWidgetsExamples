#pragma once
//Buffer.h
#ifndef __MyBuffer_H__
#define __MyBuffer_H__
#include<iostream>
class Buffer {
public:
	Buffer();									//构造
	~Buffer();									//析构
	int init();									//分配缓冲区
	void write_to_buffer(char* src);			//写数据
	size_t pop_bytes(size_t bytes);				//丢弃数据
	size_t read_from_buffer(char *dst,int bytes);//读数据
	size_t readable_bytes();					//得到存储数据的字节数

	size_t peek_read();							//指向准备读的位置（调试用）
	size_t peek_write();						//指向准备写的位置（调试用）
private:	
	void adjust_buffer();						//调整数据位置至缓冲区头
	void expand_buffer(size_t need_size);		//扩展缓冲区长度

	size_t init_random_write(char** src);			//随机初始化一段数据（调试用）
private:
	char* m_s;									//缓冲区指针
	size_t m_read_index;						//读指针位置
	size_t m_write_index;						//写指针位置
	size_t m_max_size;							//缓冲区长度
	size_t m_expand_par;						//扩展因子
};
#endif