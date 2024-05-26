//Buffer.cpp
#include "Buffer.h"
#include <time.h>
using namespace std;
int total_write = 0;	//记录总写入
int total_read = 0;		//记录总读取
static int get_random_len() {
	return rand() % 40;
}

static int get_random_ala() {
	return rand() % 26;
}

Buffer::Buffer()
	:m_read_index(0),m_write_index(0),m_max_size(10), m_expand_par(2),m_s(nullptr)
{}

Buffer::~Buffer()
{
	delete[] m_s;
}

int Buffer::init()
{
	m_s = new char[m_max_size]();
	if (m_s == nullptr) {
		//cout << "分配m_s失败\n";
		return -1;
	}
	return 0;
}

size_t Buffer::read_from_buffer(char*dst,int read_size)
{
	size_t read_max = m_write_index - m_read_index;			//read_max存储的字节数
	if (read_size == 0 || read_max == 0)					//读取0字节和空缓存区时直接返回
		return 0;	
	if (read_size == -1) {									//全读走
		memcpy(dst, &m_s[m_read_index], read_max);
		m_read_index += read_max;
		//printf("读取完成：\t读取%d个字节\n", read_max); 
		total_read += read_max;
	}
	else if (read_size > 0) {								//读取指定字节
		if ((size_t)read_size > read_max)
			read_size = read_max;
		memcpy(dst, &m_s[m_read_index], read_size);
		m_read_index += read_size;
		//printf("读取完成：\t读取%d个字节\n", read_size);
		total_read += read_size;
	}
	return read_size;										//返回读取的字节数
}

size_t Buffer::readable_bytes()
{
	return m_write_index - m_read_index;
}

size_t Buffer::peek_write()
{
	return m_write_index;
}

size_t Buffer::peek_read()
{
	return m_read_index;
}

void Buffer::write_to_buffer(char* src)
{
	size_t used_size = m_write_index - m_read_index;	//used_size表示已经存储的字节数
	size_t remain_size = m_max_size - used_size;		//remain_size表示剩余空间
	size_t cur_size = m_max_size - m_write_index;		//cur_size表示当前能够存储的空间
	size_t size = init_random_write(&src);
	//printf("已经使用%d,剩余总长度%d,剩余当前长度%d\n", used_size, remain_size, cur_size);
	if (size > remain_size) {							//剩余空间不够
		adjust_buffer();
		expand_buffer(size);
	}
	else if (size > cur_size) {							//剩余空间够,当前存不下
		adjust_buffer();
	}
	memcpy(&m_s[m_write_index], src, size);				//存储数据
	m_write_index += size;
	delete[] src;

	//更新并打印log
	used_size = m_write_index - m_read_index;			
	remain_size = m_max_size - used_size;
	cur_size = m_max_size - m_write_index;
	//printf("写入完成：\t总存储%d,剩余空间%d,剩余当前空间%d\n", used_size, remain_size, cur_size);
}

size_t Buffer::pop_bytes(size_t size)
{
	size_t read_max = m_write_index - m_read_index;		//存储数据长度
	//test random
	if (size == -2)
		size = get_random_len();

	if (size == 0 || read_max == 0)						//缓冲区为空或丢弃0字节返回
		return 0;
	if (size == -1) {									//全丢
		m_read_index += read_max;
		//cout << "丢弃了" << read_max << "个字节" << endl;
		total_read += read_max;
		return read_max;
	}
	if (size > 0) {										//丢弃指定字节
		if (size > read_max)
			size = read_max;
		m_read_index += size;
		//cout << "丢弃了" << size << "个字节" << endl;
		total_read += size;
	}
	return size;
}

size_t Buffer::init_random_write(char** src)
{
	int size = get_random_len();
	total_write += size;
	*src = new char[size];
	char ala = get_random_ala();
	//cout << "随机写入:\t长度为" << size << " 值全是 " << (unsigned char)('a' + ala) << endl;
	for (int i = 0; i < size; i++) {
		(*src)[i] = 'a' + ala;
	}
	return size;
}

void Buffer::adjust_buffer()
{
	if (m_read_index == 0)								//数据已经在头部，直接返回
		return;
	int used_size = m_write_index - m_read_index;
	if (used_size == 0) {								//缓冲区为空，重置读写指针
		m_write_index = 0;
		m_read_index = 0;
	}
	else {
		//cout << "调整前read_index write_index" << m_read_index << " " << m_write_index << endl;
		memcpy(m_s, &m_s[m_read_index], used_size);		//将数据拷贝至头部
		m_write_index -= m_read_index;						//写指针也前移
		//cout << "调整了" << used_size << "个字节" << endl;
		m_read_index = 0;								//读指针置0
	}
	
	cout << "调整后read_index write_index" << m_read_index << " " << m_write_index << endl;
}

void Buffer::expand_buffer(size_t need_size)			//need_size需要写入的字节数
{
	size_t used_size = m_write_index - m_read_index;	//used_size表示已经存储的字节数
	size_t remain_size = m_max_size - used_size;		//remain_size表示剩余空间
	size_t expand_size = m_max_size;					
	while (remain_size < need_size) {					//剩余空间不够时扩展，用while表示直到扩展至够用
		expand_size *= m_expand_par;
		remain_size = expand_size - used_size;
		//cout << "扩展长度中... 总剩余 总长度 " << remain_size << "  " << expand_size << endl;
	}
	char* s1 = new char[expand_size]();					//申请新的空间
	memcpy(s1, m_s, m_max_size);
	free(m_s);
	m_s = s1;											//将新空间挂载到缓冲区
	m_max_size = expand_size;							//更新缓冲区总长度
	//cout << "扩展结束，总长度为" << m_max_size << endl;
}

