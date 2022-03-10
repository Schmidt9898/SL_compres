#include <iostream>
#include <vector>
#include <fstream>
#include <bitset>
#include <random>

using namespace std;

#define MB 1000000




int main(){
	cout<<"Start\n";


	vector<char> input(MB,0);

	ifstream in_f;
	in_f.open("samples/sample3.data");
	in_f.read(input.data(),MB/8);
	in_f.close();

	bool isfound=false;

	for(unsigned int i=0;i<UINT_MAX;i++){
		srand(i);
		unsigned int j=0;
		for(j=0;j<MB;j++){
			char c=rand()%2;
			//cout<<(int)c<<" "<<(int)input[j]<<" ";
			if(c !=input[j])
				break;
		}
		if(j>=MB){
			//isfound=true;
			cout<<"found it: " <<i<<" from:"<<j<<" try.\n";
			break;
		}
		//else
			//cout<<i<<" is not good tryed: " <<j<<"\n";
	}

	if(!isfound)
		cout<<" Tryed all cant find it :(\n";


	cout<<"Done\n";

	return 0;
}