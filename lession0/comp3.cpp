#include <iostream>
#include <vector>
#include <fstream>
#include <bitset>

using namespace std;

#define MB 1000000

int main(){
	cout<<"Start\n";

	vector<char> bytes(MB,0);
	vector<char> input(MB,0);
	vector<char> output(MB/8,0);

	ifstream in_f;
	in_f.open("samples/sample3.data");
	in_f.read(input.data(),MB);

	unsigned short idx=0;
	unsigned int out_idx=0;
	bitset<8> temp_byte;
	for (unsigned int i=0;i<MB;i++){
		temp_byte.set(idx,input[i]);
		
		idx++;
		if(idx>=8){
			output[out_idx]=temp_byte.to_ulong();
			out_idx++;
			idx=0;
		}
	}

	ofstream f("in3.data",'w');

	f.write(output.data(),MB/8);

	cout<<"Done\n";

	return 0;
}