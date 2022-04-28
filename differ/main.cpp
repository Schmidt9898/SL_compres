#include <iostream>
#include <vector>
#include <fstream>
#include <bitset>
#include <filesystem>

using namespace std;

int main(){
	string 	file1_name="../lession0/out.data",
			file2_name="../lession0/samples/sample4.data";

	ifstream file1,file2;
	file1.open(file1_name);
	file2.open(file2_name);
	unsigned int file1_size=filesystem::file_size(file1_name);
	unsigned int file2_size=filesystem::file_size(file2_name);
	
	cout<<"different sizes f1 "<<file1_size<<" f2 "<<file2_size<<"\n";
	if(file1_size!=file2_size){
		cout<<"different sizes f1 "<<file1_size<<" f2 "<<file2_size<<"\n";
		return 0;
	}
	vector<char> file1_buff(file1_size,1),file2_buff(file1_size,0);

	
	//file1.seekg(0);
	//file2.seekg(0);




	file1.read(file1_buff.data(),file1_size);
	file2.read(file2_buff.data(),file2_size);
	file1.close();
	file2.close();


	for(unsigned int i=0;i<200;i++){
			std::cout<<(int)file1_buff[i];
		
		
		/*if(file1_buff[i]!=file2_buff[i])
		{
			std::cout<<"X";
		}*/




	}





	std::cout<<"done\n";
	return 0;
}