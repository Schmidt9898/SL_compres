#include <iostream>
#include <bitset>
#include <vector>
#include <string>
#include <math.h>

std::string golom(int codeword,int m)
{
std::string first="";
std::string sec="";
int b=ceil(log2(m));
int r = codeword%m;   
int q = int(floor(codeword/m));
for(int i=0;i<q;i++)
	first+="1";
first+="0";
if(r<(pow(2,b)-m))
{
	unsigned char r_n;
	for(int i=b-2;i>=0;i--){
	r_n=r<<(7-i);
	r_n>>=7;
		if(r_n)
			sec+="1";
		else
			sec+="0";
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
		sec+="1";
	else
		sec+="0";
	}
}

//return "";
return first+"."+sec;
}

int main(){
	std::cout<<"helo\n";

std::string emotional="";

//std::cout<<golom(6,5)<<"\n";
//std::cout<<golom(4,5)<<"\n";

for(int i=0;i<255;i++){
	std::cout<<i<<" : "<<golom(i,3)<<"\n";
}

//delev(emotional);


	return 0;
}