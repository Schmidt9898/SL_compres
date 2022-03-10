#include <iostream>
#include <bitset>
#include <vector>


#define idx_l 12
#define len_l 4
/*
int where_char(char my_char,char* buff,int buff_size,int buff_ofsset){
	
	for(int i = 0;i<buff_ofsset;i++)
	{
		if(buff[buff_ofsset-i]==my_char){
			return i;
		}
	}
	return 0;
}
*/
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





template<int p,int k>
struct LZ77{


	size_t b_size=0;
	size_t k_size=0;
	size_t b_pos=0;
	bool is_b_full=false;
	char * buff=nullptr;

	

	LZ77()
	{
		b_size=(size_t)pow(2,p);
		k_size=(size_t)pow(2,k);

		buff = new char[b_size];

		std::cout<<b_size<<" buff size\n";
		std::cout<<k_size<<" longest substring\n";
	}
	~LZ77(){
		delete [] buff;
	}
	std::vector<Entry<p,k>> code(std::string str)
	{
		std::vector<Entry<p,k>> table;
		for(size_t i=0;i<str.length();i++)
		{
			size_t cl=0;
			size_t step_back=where(&str[i],cl,str.length());
			if(cl==0)
			add(str[i]);
			else
			add(&str[i],cl+1);
			i+=cl;
			table.push_back(Entry<p,k>(step_back,cl,str[i]));
			std::cout<<step_back<<" "<<cl<< " '"<<str[i]<<"'\n";

		}
		return table;
	}
	std::string decode(std::vector<Entry<p,k>> table)
	{
		//clear buffer or just think it is clear
		b_pos=0;
		is_b_full=false;

		std::string str="";
		for(size_t i=0;i<table.size();i++)
		{
			if(table[i].back==0)
				{
					str+=table[i].c;
					add(table[i].c);
				}
			else
				{
					//std::cout<<b_pos<<" idx\n";
					std::string sub="";
					for(size_t j =0;j<table[i].len;j++)
					{
						sub+=buff[(b_pos-table[i].back+j)%b_size];
					}
					sub+=table[i].c;
						add(&sub[0],table[i].len+1);
					str+=sub;
				}
		}
		return str;


		
	}

	void add(char * c,size_t len){
		for(size_t i =0;i<len;i++)
			add(c[i]);
	}
	void add(char c){
		buff[b_pos%b_size]=c;
		b_pos++;
		if (b_pos==b_size) 
		{
		is_b_full=true;
		std::cout<<"betelt\n";
		}		
		//if(full && pos)
	};
	size_t where(char *c,size_t &cl,size_t k_len=k_size)
	{
		k_len=std::min(k_len,std::min(k_size,b_pos));
		size_t f_p=b_pos;
		size_t max_len=0;
		if(!is_b_full)
		for (size_t i=0;i<b_pos;i++){
			if (c[0]==buff[i]){
					cl=0;
					size_t j=0;
					while(j<k_len && i+j<b_pos){
						if(c[j]!=buff[(i+j)%b_size]){
							break;
						}
							cl++;
					j++;
					}
				if(cl>max_len)
				{
				f_p=i;
				max_len=cl;
				}
				//break;
				}
		}
		else
		for (size_t i=b_pos-b_size;i<b_pos;i++){
			if (c[0]==buff[i%b_size])
				{
					cl=1;
					size_t j=1;
					while(j<k_len && i+j<b_pos){
						if(c[j]!=buff[(i+j)%b_size]){
							break;
						}
							cl++;
					j++;
					}
				if(cl>max_len)
				{
				f_p=i;
				max_len=cl;
				}
				}
		}
		cl=max_len;
		//std::cout<<c[0]<<" "<<b_pos-f_p<<" pos "<<cl<<" len\n";
		return b_pos-f_p;
	}
};

int main(){
	std::cout<<"helo\n";

	//BitWriter bitwriter(nullptr);


	std::string text="test text for lz77 ";
	LZ77<12,4> lz77;
	auto table=lz77.code(text);
	auto detext=lz77.decode(table);
	std::cout<<text<<"\n";
	std::cout<<detext<<"\n";
		std::cout<<detext.length()<<"\n";
		std::cout<<text.length()<<"\n";
	if(text==detext)
		std::cout<<" megeggyezik \n";





	return 0;
}