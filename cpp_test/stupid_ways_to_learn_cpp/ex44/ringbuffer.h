//环形缓冲区是`queue`数据结构的变种. 适合实现固定大小的循环数据存储, 如流水线!

//这个头文件定义了一个ringbuffer的数据结构和操作接口.

#ifndef _RingBuffer_h
#define _RingBuffer_h

//#include <bstrlib.h>


//过 start 和 end 的动态移动实现环形结构。
typedef struct {
    char *buffer;   // 存储缓冲区数据的指针
    int length;     // 缓冲区的总长度
    int start;      // 读取操作的起始位置
    int end;        // 写入操作的终止位置
} RingBuffer;

RingBuffer *RingBuffer_create(int length);


void RingBuffer_destroy(RingBuffer *buffer);

//从缓冲区中读取 amount 字节的数据，存入 target。返回实际读取的字节数。
int RingBuffer_read(RingBuffer *buffer, char *target, int amount);

//功能: 将 length 字节的数据从 data 写入缓冲区。返回值: 实际写入的字节数。
int RingBuffer_write(RingBuffer *buffer, char *data, int length);


//检查缓冲区是否为空/满.
int RingBuffer_empty(RingBuffer *buffer);
int RingBuffer_full(RingBuffer *buffer);

//返回缓冲区中可用的数据量.
int RingBuffer_available_data(RingBuffer *buffer);
//返回缓冲区中可写入的剩余空间.
int RingBuffer_available_space(RingBuffer *buffer);



//提高效率的宏定义.
//取mod运算:
//`(B)->end + 1`将end索引
#define RingBuffer_available_data(B) (((B)->end + 1) % (B)->length - (B)->start - 1)
#define RingBuffer_available_space(B) ((B)->length - (B)->end - 1)







//获取当前读取或写入操作的指针位置。
#define RingBuffer_starts_at(B) ((B)->buffer + (B)->start)
#define RingBuffer_ends_at(B) ((B)->buffer + (B)->end)







#endif











