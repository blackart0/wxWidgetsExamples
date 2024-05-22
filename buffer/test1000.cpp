#include "Buffer.h"
#include <time.h>
#include <iostream>
#include <stdio.h>
int main() {
	srand((unsigned)time(NULL));		//调试需要初始化随机种子
	Buffer* pbuffer = new Buffer();		//创建Buffer对象
	if (pbuffer->init() != 0)			//init函数分配缓冲区
		return 0;
	char* s = nullptr;				//s是指向随机数据的指针
	char* read = new char[1000];	//读取时将数据存储到的指针read
	size_t read_size = 0;			//本次读取到的字节数
	unsigned long long time = 0;	//调试的循环次数
	while (1) {
		pbuffer->write_to_buffer(s);
		read_size = pbuffer-> read_from_buffer(read, -1);
		pbuffer->write_to_buffer(s);
		pbuffer->write_to_buffer(s);
		pbuffer->pop_bytes(-2);
		read_size = read_size = pbuffer-> read_from_buffer(read, 0);
		pbuffer->write_to_buffer(s);
		pbuffer->pop_bytes(-2);
		pbuffer->write_to_buffer(s);
		read_size = pbuffer-> read_from_buffer(read, -1);
		pbuffer->write_to_buffer(s);
		pbuffer->write_to_buffer(s);
		read_size = pbuffer-> read_from_buffer(read, 22);
		pbuffer->write_to_buffer(s);
		pbuffer->write_to_buffer(s);
		read_size = pbuffer-> read_from_buffer(read, -1);
		pbuffer->pop_bytes(-2);
		pbuffer->pop_bytes(-2);
		pbuffer->write_to_buffer(s);
		pbuffer->write_to_buffer(s);
		read_size = pbuffer-> read_from_buffer(read, 2);
		pbuffer->write_to_buffer(s);
		read_size = pbuffer-> read_from_buffer(read, 17);
		pbuffer->write_to_buffer(s);
		pbuffer->pop_bytes(-2);
		pbuffer->write_to_buffer(s);
		pbuffer->write_to_buffer(s);
		pbuffer->read_from_buffer(read, 18);

		cout << "总写入\t" << total_write << endl;;
		cout << "总读取\t" << total_read << endl;
		cout << "目前写入" << total_write - total_read << endl;
		cout << "可读取\t" << pbuffer->readable_bytes()<< endl;
		printf(" write %d read %d \n", pbuffer->peek_write(),pbuffer->peek_read());
		if (total_write - total_read != pbuffer->readable_bytes()) {	//根据总写入-总读取和一共存储的字节数判断是否存储正确
			cout << "error!!!" << endl;
			break;
		}
		if (time == 1000000){
			cout << "1000000 ok!!!" << endl;
			break;
		}
		cout << time++ << " is ok\n\n\n";
	}
	delete s;
	delete[] read;
	delete pbuffer;
	return 0;
}
