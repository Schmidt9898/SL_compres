#include "mybitstream.h"





Bitblock::Bitblock(){
	expand(1);
}
Bitblock::Bitblock(bool b){
	expand(1);
	add_bit(b);
}
Bitblock::Bitblock(unsigned char* b,int bit_len){
	expand(len/8 + 1);
	memcpy(bits[len/8],bits,capacity);
	bits[len/8]

}

bool Bitblock::operator[](int i){
char c=bits[i/8];
return c >> (7 - i%8) & 1;
};

void Bitblock::add_bits(Bitblock bits)
{

};

void Bitblock::expand(unsigned int n)
{
std::cout<<"expand\n";

	auto new_bits=new unsigned char[capacity+n];
	if(bits!=nullptr){
		memcpy(new_bits,bits,capacity);
		delete bits;
	}
	bits=new_bits;
	capacity+=n;
}

void Bitblock::set_bit(unsigned int idx,bool b)
{
if (b)
	bits[idx/8] |= (unsigned int)1 << (7-(idx%8));
else 
	bits[idx/8] &= ~((unsigned int)1 << (7-(idx%8)));
};

void Bitblock::add_bit(bool b)
{
if(len==capacity*8)
	expand(1);
set_bit(len,b);
len++;
};


template<int b>
void MyBitstreamWriter<b>::Write_bits(const char* buff,int len){

}
template<int b>
void MyBitstreamWriter<b>::setbit(){

}
template<int b>
void MyBitstreamWriter<b>::Flush(){

}
template<int b>
void MyBitstreamWriter<b>::Close(){

}









template<int b>
MyBitstreamReader<b>::MyBitstreamReader(){
	
	
}

template<int b>
void MyBitstreamReader<b>::open(std::string filename){
	ifstream in;
	auto file_size = std::filesystem::file_size(filename);
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    //return in.tellg();
	file_buffer=std::vector<char>()
	
	in.read(file_buffer.data(),file_size);
	in.close();

}
template<int b>
void MyBitstreamReader<b>::bit_read(int offset){
	
}
template<int b>
bool MyBitstreamReader<b>::getbit(int i){
	
}