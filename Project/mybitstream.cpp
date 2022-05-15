#include "mybitstream.h"


Bitblock::~Bitblock(){
delete [] bytes;
}


Bitblock::Bitblock(){
expand(1024);//TODO 1024
start_bit=cur_bit=0;

}
Bitblock::Bitblock(uchar* data_,size_t data_s,int fill_bits){
bytes=new uchar[data_s];
capacity=data_s;
memcpy(bytes,data_,capacity);
cur_bit=capacity*sizeof(uchar)-fill_bits;
start_bit=0; // may change
}


bool Bitblock::operator[](size_t i){
size_t block = i/sizeof(uchar);
uchar bit = i%sizeof(uchar);
uchar c=bytes[block];
return c >> (7 - bit) & 1;
};

bool Bitblock::remove_bit()
{
	bool t= (*this)[start_bit];
	this->deque(1);
	return t;
}

void Bitblock::expand(unsigned int n)
{
//std::cout<<"expand with "<<n<<"\n";

	auto new_bytes=new uchar[capacity+n];
	if(bytes!=nullptr){
		memcpy(new_bytes,bytes,capacity);
		delete[] bytes;
	}
	bytes=new_bytes;
	capacity+=n;
}

size_t Bitblock::get_size(){
	return cur_bit-start_bit;///sizeof(uchar) + 1;
}
size_t Bitblock::get_block_size(){
	return ceil((cur_bit-start_bit)/8);
}
void Bitblock::deque(size_t n) //remove n bit from start
{
	if (start_bit+n>cur_bit)
	{
		std::cout<<start_bit<<"   "<<cur_bit<<" WTF\n"; //TODO remove
		start_bit=cur_bit;
	}
	else
		start_bit+=n;
/*
if start_bit is greater than a treshold reallocate
*/


}


void Bitblock::add_bit(bool val_)
{
size_t block = cur_bit/sizeof(uchar);
uchar bit = cur_bit%sizeof(uchar);
if(block>=capacity) //need expand
	expand(capacity);
if(val_)
	bytes[block] |= (128>>bit);
else
	bytes[block] &= ~(128>>bit);
cur_bit++;
};

/*
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
*/
