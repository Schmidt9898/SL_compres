#include <iostream>
#include <bitset>
#include <vector>
#include <string>
#include <math.h>
#include "golom.h"

void golom_encode(int codeword,short m,Bitblock &bitblock)
{
//std::string first="";
//std::string sec="";
int b=ceil(log2(m));
int r = codeword%m;   
int q = int(floor(codeword/m));
for(int i=0;i<q;i++)
	bitblock.add_bit(1); //first+="1";
bitblock.add_bit(0);		//first+="0";
if(r<(pow(2,b)-m))
{
	unsigned char r_n;
	for(int i=b-2;i>=0;i--){
	r_n=r<<(7-i);
	r_n>>=7;
		if(r_n)
			bitblock.add_bit(1);
		else
			bitblock.add_bit(0);
	}
}else{
	unsigned char r_n,r_nn=r+(pow(2,b)-m);
	for(int i=b-1;i>=0;i--){
	r_n=r_nn<<(7-i);
	r_n>>=7;
	//std::cout<<b<<7-i<<" "<<(int)r_n<<"-\n";
	// 0000 0011
	// 00000 001 >>1
	// 00000 001 <<

	if(r_n)
		bitblock.add_bit(1);
	else
		bitblock.add_bit(0);
	}
}

return;
//return first+"."+sec;
}

int golom_decode(short m,Bitblock &bitblock){

int b=ceil(log2(m));
//int r = codeword%m;   
//int q = int(floor(codeword/m));

//find 0
int q=0;
for(size_t i=bitblock.start_bit;i<bitblock.cur_bit;i++){
		if(!bitblock.remove_bit())break;
		q++;
	}
//bitblock.deque(q+1);
//read b bits

uchar r_=0;
for(size_t i=0;i<b-1;i++){
	if(bitblock.remove_bit())
		r_ |= 1<<(b-2-i);
}
if(r_<(pow(2,b)-m))
{
	return q*m+r_;
}else
{
	r_ <<=1; 
	r_ |= (uchar)bitblock.remove_bit();
	r_ = r_ - pow(2,b) + m;
	return q * m + r_;
}
std::cout<<"error not supose to be here\n";
	return 0;
}


