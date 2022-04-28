#include <iostream>
#include <bitset>
#include <vector>

#include "mybitstream.h"




int main(){
	std::cout<<"Test main.\n";

Bitblock a(1);

std::cout<<a.len<<" a size.\n";
std::cout<<a.capacity<<" a cap.\n";

for(int i=0;i<a.capacity*8;i++)
	std::cout<<a[i]<<",";
std::cout<<"\n";
for(int i=0;i<a.len;i++)
	std::cout<<a[i]<<",";
std::cout<<"\n";


a.add_bit(1);
a.add_bit(1);
a.add_bit(1);
a.add_bit(0);
a.add_bit(1);
a.add_bit(0);
std::cout<<a.len<<"a size.\n";
a.add_bit(1);
a.add_bit(0);

for(int i=0;i<a.len;i++)
	std::cout<<a[i]<<",";
std::cout<<"\n";


std::cout<<a.len<<"a size.\n";




	return 0;
}