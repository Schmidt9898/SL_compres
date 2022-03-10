#include <iostream>
#include <vector>
#include <fstream>
#include <bitset>

using namespace std;

#define MB 1000000

int main(){
	cout<<"Start\n";

	vector<char> input(MB/8,0);
	vector<char> output(MB,0);

	ifstream in_f;
	in_f.open("in3.data");
	in_f.read(input.data(),MB/8);
	in_f.close();

	unsigned short idx=0;
	unsigned int out_idx=0;
	bitset<8> temp_byte;
	for (unsigned int i=0;i<MB/8;i++){
		temp_byte=input[i];
		for(unsigned short idx=0;idx<8;idx++){
		if(temp_byte[idx])
			output[out_idx]=1;
			else
			output[out_idx]=0;
		out_idx++;
		}
	}

	ofstream f("out.data",'w');

	f.write(output.data(),MB);

	cout<<"Done\n";

	return 0;
}