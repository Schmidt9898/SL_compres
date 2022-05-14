#include <iostream>
#include <bitset>
#include <vector>

#include "mybitstream.h"




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
std::cout<<a.get_size()<<"\n--------------\n";
a.deque(2);
std::cout<<a.get_size()<<"\n--------------\n";
a.deque(6);
std::cout<<a.get_size()<<"\n--------------\n";


/*
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

*/


	return 0;
}