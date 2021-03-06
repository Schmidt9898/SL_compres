#include <iostream>
#include <bitset>
#include <vector>

#include "mybitstream.h"
#include "golom.h"



int main(){
	std::cout<<"Test main.\n";

Bitblock a;

std::cout<<a.get_size()<<" a size.\n";
std::cout<<a.capacity<<" a cap.\n";

for(int i=a.start_bit;i<a.get_size();i++)
	std::cout<<a[i];
std::cout<<"\n--------------\n";


for(int i=a.start_bit;i<10;i++)
{	a.add_bit(i%2);
}
std::cout<<a.get_size()<<" a size.\n";
std::cout<<a.capacity<<" a size.\n";
/*
for(int i=a.start_bit;i<a.get_size();i++)
	std::cout<<a[i];
*/

std::cout<<"--------------\n";
a.deque(2);
std::cout<<a.get_size()<<"bitsize\n";
std::cout<<a.get_block_size()<<"blocksize\n";
a.deque(2);
std::cout<<a.get_size()<<"\n--------------\n";
a.deque(6);
std::cout<<a.get_size()<<"\n--------------\n";


/////////////////////////////////////////////////////////////

	std::cout<<"golom test\n";
std::vector<unsigned char> data(10000000,0);
std::vector<unsigned char> data2;

srand (time(NULL));

//for(size_t i=0;i<data.size();i++)data[i]=i;
std::generate(data.begin(),data.end(),[](...){return rand() % 32;});

Bitblock out;
short m=10;
for(auto d : data)
{
	golom_encode(d,m,out);
	//for(size_t i=out.start_bit;i<out.cur_bit;i++)
	//std::cout<<out[i];
	//std::cout<<"\n";
}





//for(int i=a.start_bit;i<a.get_size();i++)
//	std::cout<<a[i];
std::cout<<data.size()<<" original--------------\n";
std::cout<<out.get_block_size()<<" compressed--------------\n";


std::vector<uchar>* bytes=out.get_data();
	std::cout<<bytes->size()<<" data write size\n";
		std::ofstream f("test.bin",'w');
		f.write((const char*)bytes->data(),bytes->size());
		f.flush();
		f.close();
		
		//delete bytes;


/////////////////////////////////////////

std::ifstream input("test.bin", std::ios::binary);
		std::vector<uchar> data_(
			(std::istreambuf_iterator<char>(input)),
			(std::istreambuf_iterator<char>()));//TODO check

std::cout<<data_.size()<<" data read size\n";
Bitblock in(data_.data(),data_.size(),0);

//in.cur_bit=out.cur_bit;
int n=memcmp ( in.bytes, out.bytes, in.capacity );	
	std::cout<<n<<" compare\n";
	std::cout<<in.capacity<<" "<<out.capacity<<" bytes\n";


//while(in.get_size()>0)
for(int i=0;i<data.size();i++)
{
uchar t_byte = golom_decode(m,in);
//std::cout<<out.get_size()<<"\n";
data2.push_back(t_byte);
//std::cout<<" a";
}

std::cout<<data2.size()<<" decompressed--------------\n";
if(data.size()==data2.size())
{

for(size_t i=0;i<data.size();i++)
{
	if(data[i]!=data2[i]){
		std::cout<< (int)data[i]<<" - "<< (int)data2[i] <<"\n";
		std::cout<<"test failed decompressed data not good\n";
		//break;
	}
}
std::cout<<"test passed\n";

}
else
std::cout<<"test failed data size not equal\n";


//std::cout<<"\n--------------\n";
//std::cout<<golom(6,5)<<"\n";
//std::cout<<golom(4,5)<<"\n";

//for(int i=0;i<255;i++){
//	std::cout<<i<<" : "<<golom(i,3)<<"\n";
//}

	return 0;
}