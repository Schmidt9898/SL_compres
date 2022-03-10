#include <iostream>
#include <bitset>
#include <vector>


#define idx_l 12
#define len_l 4

template<int p,int k>
struct Entry{
	size_t back :p;
	size_t len :k;
	char c;
	Entry(int b,int l,char c_):back(b),len(l),c(c_){};
	std::string to_string(){
		return std::to_string(step_back)+" "+std::to_string(cl)+" '"+c+"'";
	}
};





int main(){
	std::cout<<"helo\n";

	//BitWriter bitwriter(nullptr);


	std::string text="test text for arbitary ";
//	auto table=lz77.code(text);
//	auto detext=lz77.decode(table);
	std::cout<<text<<"\n";
//	std::cout<<detext<<"\n";
//		std::cout<<detext.length()<<"\n";
//		std::cout<<text.length()<<"\n";
//	if(text==detext)
//		std::cout<<" megeggyezik \n";





	return 0;
}