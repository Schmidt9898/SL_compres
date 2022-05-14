#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/core/mat.hpp"


int main(){
	std::cout<<"CV Test main.\n";

	cv::Mat I=cv::imread("./images/1.png",cv::IMREAD_GRAYSCALE);
	//cv::imwrite("./images/1.2.png",I);
	cv::Mat I2=cv::imread("./images/3.png",cv::IMREAD_GRAYSCALE);


	CV_Assert(I.depth() == CV_8U);

    const int channels = I.channels();
	std::cout<<channels<<" channels\n";

	uchar* data = I.data;
	uchar* data2 = I2.data;
	auto size=I.size();

	cv::Mat E = cv::Mat::zeros(size,CV_8U);
	uchar* dete = E.data;
	
	int s=size.height*size.width;
	std::cout<<s<<" s\n";
	std::cout<<I2.size()<<" size\n";


	for(int i=0;i<s-1;i++)
	{
		//dete[i]= (uchar)abs((int)data[i]-(int)data2[i]);
		dete[i] = (uchar)(abs((int)data[i]-(int)data2[i])>16)*200;
		//std::cout<<(int)dete[i]<<" ";//<<"\n";
		//std::cout<<(int)data[i]-(int)data2[i]<<" ";//<<"\n";
		//if(!i%10)std::cout<<"\n";
	}

	std::cout<<"\n";
	int X=size.width, Y=size.height;
    int x=0, y = 0;
    int dx = 0;
    int dy = -1;

	//int j=0;
    for(int i=0;i<MAX(X, Y)*MAX(X, Y);i++)
	{
		
		if((-X/2 < x <= X/2) && (-Y/2 < y <= Y/2)){
			dete[i] = (uchar)i%255;//(uchar)(abs((int)data[i]-(int)data2[i])>16)*200;
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

	cv::imshow("asd",E);
	cv::waitKey();


	return 0;
}