#include <iostream>
#include <vector>
#include <fstream>
#include <bitset>

using namespace std;

#define MB 1000000

int main(){
	cout<<"Start\n";

	vector<char> input(MB,0);
	vector<char> output(MB/16-4,0);

	ifstream in_f;
	in_f.open("samples/sample4.data");
	in_f.read(input.data(),MB);

	unsigned short idx=0;
	unsigned int out_idx=0;
	bitset<8> temp_byte;

	//4 byte is 1

	for (unsigned int i=4+1;i<MB;i+=2){
		temp_byte.set(idx,input[i]);
		
		idx++;
		if(idx>=8){
			output[out_idx]=temp_byte.to_ulong();
			out_idx++;
			idx=0;
		}
	}

	ofstream f("in4.data",'w');


	f.write(output.data(),MB/16-4);

	cout<<"Done\n";

	return 0;
}