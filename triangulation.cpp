/** @file triangulation.cpp
 @brief Main function to test different input points and triangulation methods in the TriSubdiv class.
 @author Sneha Belkhale
 @date September 22nd, 2016
 
 When executing this file, it takes in a command line integer argument from 1 - 10, corresponding to the different points and patterns.
 args 1 : 7 triangulate the image by generating 3 new triangles each time a point is added to the set
 args 7 : 10 simply create triangles by connecting the new point to its nearest 2 neighbors
 
 Displays the ~beautiful nature~ of the triangulation in an animation.

 */

#include <iostream>
#include "TriSubdiv.hpp"
#include "Triangle.hpp"
#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>


#define PI 3.14159265

/* Comparator to sort two cv::Points based on distance to a point
 @param a first cv::Point to compare
 @param b second cv::Point to compare
 @return -1, 0, or 1 
 
 */
int centerCompare(cv::Point a, cv::Point b){
    int x=250; //290
    int y=250; //115
    //int distA= sqrt((a.x - x)^2 + (a.y - y)^2 );
    //int distB = sqrt((b.x - x)^2 + (b.y - y)^2);
    int distA= sqrt((a.x - x)*(a.x - x) + (a.y - y)*(a.y - y));
    int distB = sqrt((b.x - x)*(b.x - x) + (b.y - y)*(b.y - y));
    if (distA<distB)
    return -1;
    if (distA>distB)
    return 1;
    else
        return 0;
}


/* main function */
int main(int argc, const char * argv[]) {
    
    //initialize command line argument
    std::string arg=argv[1];
    //initialize black background of size 500 x 500 for tests
    cv::Mat img(500,500, CV_8U);
    img=cv::Scalar(0,0,0);
    //initialize triangle subdivision object
    TriSubdiv myTri= TriSubdiv(0,0,500,500);
    
    
    //adding unique sets of points to the subdivision object results in cool unique patterns ...
    
    //************************ PATTERNS WITH INSERT_SD **************************//
    
     /** pattern 1: symmetrical pattern **/
    if (arg=="1"){
   
        for (double j=0; j<500; j+=30){
            for (double i=0; i<4; i++){
                if (i==0)
                    myTri.insert_sd(cv::Point(250+j,250));
                if (i==1)
                    myTri.insert_sd(cv::Point(250,250+j));
                if (i==2)
                    myTri.insert_sd(cv::Point(250-j,250));
                else
                    myTri.insert_sd(cv::Point(250,250-j));
            }
        }
    }

     /** pattern 2: cool spiral pattern thing **/
    if (arg=="2"){
        for (double i=0; i<8*PI; i+=0.1){
            myTri.insert_sd(cv::Point(25*i*cos(i)+250,25*i*sin(i)+250));
        }
    }
    
    /** pattern 3: circle thing **/
    if (arg=="3"){
        for (double i=0; i<2*PI; i+=0.1){
            myTri.insert_sd(cv::Point(100*cos(i)+250,100*sin(i)+250));
        }
    }
    
     /**pattern 4: symmetrical triangles **/
    if (arg=="4"){
        for (double j=20; j<500; j+=30){
            //myTri.insert_sd(cv::Point(j,2*j));
            //myTri.insert_sd(cv::Point(j,0.5*j));
            myTri.insert_sd(cv::Point(250,j));
            myTri.insert_sd(cv::Point(10,j));
            myTri.insert_sd(cv::Point(490,j));
        }
    }
    
    /** pattern 5: import 68 facial landmark features, and triangulate **/
    if (arg=="5"){
        cv::Mat img2=cv::imread("michaelcera.jpg");
        // read in points from a file
        std::vector<cv::Point> points;
        std::ifstream ifs("points.txt");
        int x,y;
        while (ifs >> x >> y){
            points.push_back(cv::Point(x,y));
        }
         //sort points by distance from center..
        std::sort(points.begin(), points.end(), centerCompare);
    
        for (int i=0; i<points.size(); i++){
            myTri.insert_sd(points[i]);
        }

        myTri.draw(img2,1);
        cv::waitKey(0);
        return 0;
    }
    
    /** pattern 6: swagness **/
    if (arg=="6"){
        std::vector<cv::Point> points;
        for (int i=0; i<500; i+=40){
            for (int j=0; j<500; j+=40){
                points.push_back(cv::Point(i,j));
            }
        }
        std::sort(points.begin(), points.end(), centerCompare);
        for (int i=0; i<points.size(); i++){
            cv::circle(img,points[i],4,cv::Scalar(255,255,255));
            cv::imshow("window",img);
            cv::waitKey(100);
            myTri.insert_sd(points[i]);
        }
    }
    
    //************************ PATTERNS WITH INSERT_NN **************************//
    
    /** pattern 7: spiral with insert_nn **/
    if (arg=="7"){
        for (double i=0; i<12*PI; i+=0.4){
            myTri.insert_nn(cv::Point(15*i*cos(i)+250,15*i*sin(i)+250));
        }
    }
    
    /** pattern 8: import 68 facial landmark features and triangulate with insert_nn **/
    if (arg=="8"){
        cv::Mat img2=cv::imread("michaelcera.jpg");
        // read in points from a file
        std::vector<cv::Point> points;
        std::ifstream ifs("points.txt");
        int x,y;
        while (ifs >> x >> y){
            points.push_back(cv::Point(x,y));
        }
        //sort points by distance from center..
        std::sort(points.begin(), points.end(), centerCompare);
        
        for (int i=0; i<points.size(); i+=2){
            myTri.insert_nn(points[i]);
        }
        //draw triangles
        myTri.draw(img2,1);
        cv::waitKey(0);
        return 0;
    }
        
    
    
    
    //draw the triangulation pattern
    myTri.draw(img, 1);
    //pause and admire :0
    cv::waitKey(0);
        
    return 0;
}


