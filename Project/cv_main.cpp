#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/core/mat.hpp"
#include "golom.h"

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




//	0	0		-0
//	1	1		ceil(i/2)
//	2	-1		-i/2
//	3	2		-1
//	4	-2		/2*-1
//	5	3		-2
//	6	-3		/2*-1
//	7	4		-3
//	8	-4		/2*-1
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

int main(){


for(int i=-10;i<=10;i++)
	std::cout<<i<<"  "<<dezigzag(i)<<"  "<<zigzag(dezigzag(i))<<"\n";


//system("pause");

	std::cout<<"CV Test main.\n";

	cv::Mat I=cv::imread("./images/0.png",cv::IMREAD_GRAYSCALE);
	//cv::imwrite("./images/1.2.png",I);
	cv::Mat I2=cv::imread("./images/1.png",cv::IMREAD_GRAYSCALE);


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

	std::vector<int> decompressed;

	while(out.get_size()>0)
	{
	int diff = golom_decode(m,out);
	//std::cout<<out.get_size()<<"\n";
	decompressed.push_back(diff);
	//std::cout<<" a";
	}

	std::cout<<decompressed.size()<<" decomp size\n";



	for(int i=0;i<s;i++)
	{
		//dete[i]= (uchar)abs((int)data[i]-(int)data2[i]);
		//dete[i] = (uchar)(dezigzag((int)data[i]-(int)data2[i])>32)*200;
		dete[i] =  (uchar)  (data[i] - zigzag(decompressed[i]));//zigzag(decompressed[i]);
		//if (dete[i]!=((int)data[i] - zigzag(dete[i])))
		//	std::cout<<zigzag(dete[i])<<" "<<(int)dete[i]<<" "<<(int)data2[i]<<" \n";//<<"\n";
		//std::cout<<zigzag(decompressed[i])<<" ";//<<"\n";
		//if(!i%10)std::cout<<"\n";
	}
for(int i=0;i<s;i++)
	if (dete[i]!=data2[i])
	{
		std::cout<<"test failed\n";
		break;
	}


	std::cout<<"\n";
	int X=size.width, Y=size.height;
    int x=0, y = 0;
    int dx = 0;
    int dy = -1;

	//int j=0;
	/*
    for(int i=0;i<MAX(X, Y)*MAX(X, Y);i++)
	{
		
		if((-X/2 < x <= X/2) && (-Y/2 < y <= Y/2)){
			dete[i] = (uchar)i%255;  //(uchar)(abs((int)data[i]-(int)data2[i])>16)*200;
            //std::cout<<x<<","<< y<<"\n";
		}
        if (x == y || (x < 0 && x == -y) || (x > 0 && x == 1-y))
		{
		int t=dx;
            dx= -dy;
			 dy = t;
		}
        x = x+dx;
		y = y+dy;
	}
*/
	//std::cout<<j<<" j\n";


//spirál bejárás
//cv::imwrite("./images/tomor16.png",E);




/*
    switch(channels)
    {
    case 1:
        {
            cv::MatIterator_<uchar> it, end;
            for( it = I.begin<uchar>(), end = I.end<uchar>(); it != end; ++it)
				std::cout<<(int)*it<<" ";
                //*it = table[*it];
            break;
        }
    case 3:
        {
            cv::MatIterator_<cv::Vec3b> it, end;
            for( it = I.begin<cv::Vec3b>(), end = I.end<cv::Vec3b>(); it != end; ++it)
            {
				std::cout<<*it<<" ";
                //(*it)[0] = table[(*it)[0]];
                //(*it)[1] = table[(*it)[1]];
                //(*it)[2] = table[(*it)[2]];
            }
        }
    }*/

	cv::imshow("decomp",E);
	cv::imshow("orig",I2);
	cv::waitKey();


	return 0;
}