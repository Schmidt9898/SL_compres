#include <iostream>
#include <bitset>
#include <vector>

std::string lev(int n){
	if(n==0) return "0";
	std::string str="";
	int C=1; //step1
	while(true){
	int m=0;
	for(int i=n;i>1;i=i>>1)m++;
	for(int i=0;i<m;i++) str=(((n>>i)&1)?"1":"0")+str;
	//std::cout<<m<<" m\n";
	if(m==0)break;
	C++;
	n=m;
	}
	std::string beg="0";
	for(int i=0;i<C;i++)beg="1"+beg;
	str=beg+str;
	return str;
} 

int delev(std::string s){
	//std::cout<<s<<"\n";
	//std::cout<<s[0]<<"\n";
std::vector<int> values;

	int l=s.length();
	int si=0;
	while(si<l){
	int ones=0;
	int result=0;
	while(s[si++]!='0'){
		ones++;
		//std::cout<<"nulla";
	}
	if(ones==0){result=0;}
	else{
		result=1;
		for(int i=0;i<ones-1;i++){
			int temp=1;
			//std::cout<<result<<"\n";

			for(int j=0;j<result;j++){
				temp = (temp<<1) | ((s[si++]=='1')?1:0);
			}
			//std::cout<<temp<<" temp \n";
			result=temp;
		}

	}
	values.push_back(result);
	std::cout<<result<<"\n";
	}
	
	return 0;
}



int main(){
	std::cout<<"helo\n";

std::string emotional="";
for(int i=0;i<20;i++){
	std::cout<<i<<" : "<<lev(i)<<"\n";
	emotional+=lev(i);
}

delev(emotional);




/*
	for(int x=0;x<10;x++){

	int q=x/M;
	int r=x%M;

	std::bitset<8> r_bits(r);
	//std::bitset<8> r_bits(r);
	std::string q_buff="0";
	for(int i=0;i<q;i++)
		q_buff="1"+q_buff;
	//unsigned short q_out=0;
	//std::bitset<8> q_buff(q_out);
	std::cout<<q_buff<<"   "<<r_bits<<"\n";
	}
	*/
	return 0;
}