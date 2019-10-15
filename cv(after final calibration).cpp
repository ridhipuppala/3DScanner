#include <fstream>
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <cmath>

using namespace cv;
using namespace std;
VideoCapture cap(1); 
int main()
{	
    
    int a,b,c,u;
	ifstream myfile ("test.txt");
    myfile >> u;
	cout<<u; 
	myfile.close();    
    int count=0;
    if(!cap.isOpened())  // check if we succeeded
        return -1;
 
      Mat backfinal1;
    backfinal1=imread("back.JPEG",0);
    string s=to_string(u);  
    string filename=s+".txt";
    
		ofstream yfile(filename); 
        Mat hsv,gray,frame,foreground1;
        cap >> frame;               // get a new frame from camera
        
        Mat img1(frame.rows,frame.cols,CV_8UC1);
        cvtColor(frame,gray,COLOR_BGR2GRAY);
        img1=gray;

        int i=0,j;
        while(i!=frame.rows)
        {	 //afile<<"reached";
            Mat img3=gray(Range(i,i+frame.rows/4),Range(0,frame.cols));
            GaussianBlur(img3,img3,Size(5,5),0,0);            
            threshold(img3,img3, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);            
            img1(Range(i,i+frame.rows/4),Range(0,frame.cols)) = img3; 
            i=i+frame.rows/4;
        }
        foreground1=img1-backfinal1; 
        //string s=to_string(u);     
        //cout<<s;    
        //string filename="pointset*"+s+".txt";
        //yfile.open(filename, ios::in);   

        Mat mid1(frame.rows,frame.cols,CV_8UC1,Scalar(0));
        for(i=0;i<foreground1.rows;i++)                   // This function is to remove noice from the background subtracted image for gray image
        {
            
            a=0;
            b=0;
            c=0;
            for(j=0;j<foreground1.cols;j++)
            {
                
                if(foreground1.at<uchar>(i,j)!=foreground1.at<uchar>(i,j+1))
                {
                    if(((foreground1.at<uchar>(i,j+1)+foreground1.at<uchar>(i,j+2)+foreground1.at<uchar>(i,j+3))<255*3) && ((foreground1.at<uchar>(i,j-1)+foreground1.at<uchar>(i,j-2)+foreground1.at<uchar>(i,j-3))<255*3))
                        continue;
                    
                    if(c==0)
                    {   
                        a=j+1;
                        c=c+1;
                        continue;
                        
                    }
                    if(c==1)
                    {   
                        b=j;
                        mid1.at<uchar>(i,(a+b)/2)=255;
                        double l,x,y,z,angle=1.292;
                        double d=50/tan(angle);
                        l=(mid1.cols-(a+b))/2;
                        
                        z=(d-l*0.011156)*tan(angle)/(1+l*tan(angle)*0.000939);   // angle not assigned
                        x=(l*(0.000939*z+0.011156));
                        y=((mid1.rows/2-i)*(0.000939*z+0.011156));
                        yfile << x << " " << y << " " << 50-z << " " << "\n";

                        break;
                    }
                }
               
            }
        }
                                yfile.close();
}
