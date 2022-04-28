#ifndef MYBITSTREAM
#define MYBITSTREAM

#include <filesystem>
#include <fstream>
#include <iostream>


//like a bitset but bigger
class Bitblock{
unsigned char * bits=nullptr;
public:
unsigned int capacity=0;//in byte
int len=0;
Bitblock();
Bitblock(bool b);
Bitblock(unsigned char* b,int bit_len);

//only get
bool operator[](int i);
//bool operator[]=(int i,bool val);
//unsigned int get_size();
//unsigned int get_capacity();

//Bitblock(Bitblock &a);

void expand(unsigned int n=1);
//int offset=0;
void deque(int n);//remove n bit from start
//void match();//find first bigest match
void add_bits(Bitblock bits);
void add_bit(bool b);                          
void set_bit(unsigned int idx,bool b);                          
};



template<int b>
class MyBitstreamWriter{

std::vector<char> buffer;
	int offset=0;
public:
void Write_bits(const char* buff,int len);
void setbit();
void Flush();
void Close();

};

template<int b>
class MyBitstreamReader{
	int offset= 0;
public:
std::vector<char> buffer;
std::vector<char> file_buffer;
MyBitstreamReader();
void open(std::string filename);
void bit_read(int offset=0);
bool getbit(int i);
//unsigned int Read_bits(,size_t length);
};







#endif