#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/core/mat.hpp"
#include "golom.h"
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;


//TODO
/*
for loop for files 
copy filled bytes from bitblock 
add mask byte at end
save compressed data as file

read compressed files
remove mask byte
add to bitblock
decompres create original file

automatate with script python
*/

//	0	0	
//	1	1	
//	2	-1	
//	3	2	
//	4	-2	
//	5	3	
//	6	-3	
//	7	4	
//	8	-4	
int zigzag(int u)
{
	if(u%2)
		return 1+ceil(u/2);
	else
		return -u/2;
}
int dezigzag(int u)
{
	if(u>0)
		return 2*u-1;
	else
		return u*-2;
}





void compress(std::string src,std::string dest){
	std::vector<fs::path> files;
	cv::Mat _im0;

	for (const auto & entry : fs::directory_iterator(src))
	{
		if(!fs::is_directory(entry.path()))
		{
			std::string path = entry.path().u8string();
			if(entry.path().filename().u8string()=="0.png")
				_im0=cv::imread(path,cv::IMREAD_GRAYSCALE);
			else if (entry.path().filename().u8string().find(".png") != std::string::npos)
				files.push_back(path);
		}
	}

	cv::imwrite((fs::path(dest)/"0.png").u8string(),_im0);
	uchar * _data0 = _im0.data;
	int m=5;

	for(auto path : files)
	{
		cv::Mat I=cv::imread(path.u8string(),cv::IMREAD_GRAYSCALE);
		size_t size=I.size().height*I.size().width;
		uchar * _I = I.data;
		
		Bitblock out;
		for(int i=0;i<size;i++)
		{		
			golom_encode(dezigzag((int)_data0[i]-(int)_I[i]),m,out);
		}
		std::vector<uchar>* bytes=out.get_data();
		std::ofstream f(dest/path.filename(),'w');
		f.write((const char*)bytes->data(),bytes->size());
		f.flush();
		f.close();
		delete bytes;
		//break;
	}
}
void decompress(std::string src,std::string dest){
	std::vector<fs::path> files;
	cv::Mat _im0;

	for (const auto & entry : fs::directory_iterator(src))
	{
		if(!fs::is_directory(entry.path()))
		{
			std::string path = entry.path().u8string();
			if(entry.path().filename().u8string()=="0.png")
				_im0=cv::imread(path,cv::IMREAD_GRAYSCALE);
			else if (entry.path().filename().u8string().find(".png") != std::string::npos)
				files.push_back(path);
		}
	}
	
	cv::imwrite((fs::path(dest)/"0.png").u8string(),_im0);

	uchar * _data0 = _im0.data;
	int m=5;

	for(auto path : files){
	cv::Mat I = cv::Mat::zeros(_im0.size(),CV_8U);
	size_t size=I.size().height*I.size().width;
	uchar * _I = I.data;

		//std::cout<<path<<" path \n";
		std::ifstream input(path, std::ios::binary);
		std::vector<uchar> data_(
			(std::istreambuf_iterator<char>(input)),
			(std::istreambuf_iterator<char>()));//TODO check
		input.close();

		Bitblock out(data_.data(),data_.size(),0);
		
		std::vector<int> decompressed;
		//while(out.get_size()>0)
		for(int i=0;i<size;i++)
		{
		int diff = golom_decode(m,out);
		//std::cout<<out.get_size()<<"\n";
		decompressed.push_back(diff);
		//std::cout<<" a";
		}

		//std::cout<<decompressed.size()<<" decomp size\n";
		for(int i=0;i<size;i++)
		{
			_I[i] =  (uchar)  (_data0[i] - zigzag(decompressed[i]));
		}
		cv::imwrite((fs::path(dest)/path.filename()).u8string(),I);
		//cv::imshow("asd", I);
		//cv::waitKey();
	}


}




int main(int argc, char** argv)
{
//std::cout << "You have entered " << argc-1 << " arguments:" << "\n";
  
if(argc<4){
std::cout << "at least 3 arguments needed! \n";
return 0;
}
char mode = *argv[1];
std::string src(argv[2]);
std::string dest(argv[3]);


std::cout<<mode<<"  "<<src<<"  "<<dest<<"\n";


if(mode == 'c')
	compress(src,dest);
else if(mode == 'd')
	decompress(src,dest);
else{//test
	std::cout<<"test mode\n";




	std::cout<<"CV Test main.\n";

	cv::Mat I=cv::imread("./images/0.png",cv::IMREAD_GRAYSCALE);
	cv::Mat I2=cv::imread("./images/1.png",cv::IMREAD_GRAYSCALE);
	//cv::imwrite("./images/1.2.png",I);


	CV_Assert(I.depth() == CV_8U);

    const int channels = I.channels();
	std::cout<<channels<<" channels\n";

	uchar* data = I.data;
	uchar* data2 = I2.data;
	auto size=I.size();

	cv::Mat E = cv::Mat::zeros(size,CV_8U);
	uchar* dete = E.data;
	
	int s=size.height*size.width;


	short m = 5;

	Bitblock out;
	for(int i=0;i<s;i++)
	{		
		//dete[i] =dezigzag((int)data[i]-(int)data2[i]);
		golom_encode(dezigzag((int)data[i]-(int)data2[i]),m,out);
		//std::cout<<dezigzag((int)data[i]-(int)data2[i])<<" "<<  (int)data[i]-(int)data2[i]<<" decomp size\n";
	}

	//for(int i=0;i<s;i++)
	std::cout<<s<<" s\n";
	std::cout<<out.get_block_size()<<" comp\n";
	std::cout<<I2.size()<<" size\n";

		std::vector<uchar>* bytes=out.get_data();
	std::cout<<bytes->size()<<" data write size\n";
		std::ofstream f("test.bin",'w');
		f.write((const char*)bytes->data(),bytes->size());
		f.flush();
		f.close();
		
		//delete bytes;


/////////////////////////////////////////

std::ifstream input("test.bin", std::ios::binary);
		std::vector<uchar> data_(
			(std::istreambuf_iterator<char>(input)),
			(std::istreambuf_iterator<char>()));//TODO check

	Bitblock in(data_.data(),data_.size(),0);



	std::vector<int> decompressed;

	//while(in.get_size()>0)
	for(int i=0;i<s;i++)
	{
	int diff = golom_decode(m,in);
	decompressed.push_back(diff);
	//std::cout<<" a";
	}

	std::cout<<decompressed.size()<<" decomp size\n";



	for(int i=0;i<s;i++)
	{
		//dete[i]= (uchar)abs(zigzag(decompressed[i]));
		
		dete[i] =  (uchar)  (data[i] - zigzag(decompressed[i]));
		
		//dete[i] =  (uchar)  (data[i] - zigzag(decompressed[i]));
		
		

	}
for(int i=0;i<s;i++)
	if (dete[i]!=data2[i])
	{
		std::cout<<(int)dete[i]<<" "<<(int)data2[i]<<" error ";
		std::cout<<"test failed\n";
		break;
	}

		cv::imwrite("reconstract.png",E);
		cv::imshow("asd", E);
		cv::waitKey();


	std::cout<<"\n";
	int X=size.width, Y=size.height;
    int x=0, y = 0;
    int dx = 0;
    int dy = -1;
}
	return 0;
}

