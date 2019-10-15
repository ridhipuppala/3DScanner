#include <fstream>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>
#include <unistd.h>

using namespace cv;
using namespace std;
VideoCapture cap(1); 
int main(int argc,const char** argv)
{
	if(!cap.isOpened())  // check if we succeeded
        return -1;
    Mat back,back1,back2;
    cap >> back;
    cvtColor(back,back2,COLOR_BGR2GRAY);
    int count=0;
    Mat backslice;
    while(count!=back.rows)
    {
    	backslice=back2(Range(count,count+back.rows/4),Range(0,back.cols));
        GaussianBlur(backslice,backslice,Size(5,5),0,0);            
        threshold(backslice,backslice, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);            
        count=count+back.rows/4;
    }
    
    imwrite("back.JPEG",back2);
	cout<<"U can see a new image in the folder.press esc if u agree with us";
    while(1)
    {
    	//imshow("finalback", finalback);
    	imshow("back2", back2);
    	//imshow("backslice", backslice);
        if(waitKey(30) == 27) 
            break;

    }
    }
