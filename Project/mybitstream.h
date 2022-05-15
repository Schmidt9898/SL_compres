#ifndef MYBITSTREAM
#define MYBITSTREAM

#include <filesystem>
#include <fstream>
#include <iostream>

/*

blc 0 idx 0 ,  blc 1		blc 2
0000 0000 , 0000 0001 , 0000 0010 , 

*/
typedef unsigned char uchar;

//like a bitset but bigger much much biger
//template<int b>
class Bitblock{

uchar * bytes=nullptr;
public:
size_t cur_bit=0; //end bit or current bit to write	current bit to write into in case of writing
size_t start_bit=0; //start bit 			in case of remove from start or read startbit will move to next simbol start pos
unsigned int capacity=0;//in byte
//unsigned int size=0;//in bits cur-start

//Bitblock();
Bitblock();
Bitblock(uchar* data_,size_t data_s,int fill_bits);
~Bitblock();

//only get
bool operator[](size_t i);
//bool operator[]=(int i,bool val);
//void setbit(size_t i,bool val);
//unsigned int get_capacity();
size_t get_size();
size_t get_block_size();

//Bitblock(Bitblock &a);

void expand(unsigned int n=1);
//int offset=0;
void deque(size_t n);//remove n bit from start
bool remove_bit();//remove from start and deque 1 if empty false
//void match();//find first bigest match
//void add_bits(Bitblock bits);
void add_bit(bool val_);                          
//void set_bit(unsigned int idx,bool b);                          
};

#endif