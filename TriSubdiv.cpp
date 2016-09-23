/** @file TriSubdiv.cpp
 @brief TriSubdiv class function definitions
 @author Sneha Belkhale
 @date September 22nd, 2016
 
 This class is modeled after the openCV::subDiv2D class that triangulates an image given a stream of points using the Delaunay Triangulation method, with insert point and draw functionalities.
 
 Instead of Delaunay Triangulation, I wanted to play around with other two other triangulation methods:
 
 Subdivision (@function insert_sd) - divides triangle containing inserted point into three new triangles
 Nearest Neighbor (@function insert_nn) - creates a triangle containing the point and its two nearest neighbors
 
 The draw functionality provides a cool animation of the triangulation. 
 
  */

#include "TriSubdiv.hpp"
#include "Triangle.hpp"
#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <stdio.h>

/** constructor for the TriSubdiv class
 @param x1 - upper left corner x-offset of rectangular region to triangulate
 @param y1 - upper left corner y-offset of rectangular region to triangulate
 @param w - width of region to triangulate
 @param h - height of region to triangulate
 **/

TriSubdiv::TriSubdiv(int x1, int y1, int w, int h){
    ULCorner= cv::Point(x1, y1);
    URCorner= cv::Point(w, y1);
    LLCorner= cv::Point(x1, h);
    LRCorner= cv::Point(w, h);
    //initialize number of triangles in the set to 0
    count=0;
}

/** insert by subdivision divides the triangle containing inserted point into three new triangles
 @param x is the cv::Point to add to the triangulation region 
 **/
void TriSubdiv::insert_sd(cv::Point x){
    //check if point is inside our triangulation region, if it is add it to our list and continue
    pointList.push_back(x);
    //if this is the first point added, must divide the rectangular region into 4 triangles
    if (count==0){
        triangleList.push_back(Triangle(ULCorner,URCorner,x));
        triangleList.push_back(Triangle(ULCorner,LLCorner,x));
        triangleList.push_back(Triangle(URCorner,LRCorner,x));
        triangleList.push_back(Triangle(LLCorner,LRCorner,x));
        count=4;
    }
    else{
        //iterate over all triangles to find out which triangle contains the point
        for (int i=0; i<triangleList.size(); i++){
            if (triangleList[i].contains(x)){
                //subdivide the containing triangle into 3 new triangles
                subdivide(i,x);
                break;
            }
        }
    }
}

/** insert by nearest neighbor creates a triangle containing the point and its two nearest neighbors
 @param x is the cv::Point to add to the triangulation region
 **/
void TriSubdiv::insert_nn(cv::Point a){
    //initialize minimum values
    double min1_Val = std::numeric_limits<double>::max();
    double min2_Val = std::numeric_limits<double>::max();
    double dist, min1_idx, min2_idx;
    //iterate through the list of points already added in search of two closest points
    for (int i=0; i<pointList.size(); i++){
        //calculate distance
        dist= sqrt((a.x - pointList[i].x)*(a.x - pointList[i].x) + (a.y - pointList[i].y)*(a.y - pointList[i].y) );
        if (dist < min1_Val){
            min2_Val = min1_Val;
            min1_Val = dist;
            min2_idx = min1_idx;
            min1_idx = i;
        }
        else if (dist < min2_Val){
            min2_Val = dist;
            min2_idx = i;
        }
    }
    //add new point to the list of points
    pointList.push_back(a);
    //add the nearest neighbor triangle to our list of triangles
    triangleList.push_back(Triangle(a,pointList[min1_Val],pointList[min2_Val]));
}

/** utility function to subdivide the i-th triangle in our list into 3 new triangles at point P
 @param i is the index of the triangle in triangleList we want to subdivide 
 @param P is the cv::Point that is the center of the subdivision
 **/
void TriSubdiv::subdivide(int i, cv::Point p){
    //insert the three new triangles in our list
    triangleList.insert(triangleList.begin()+i, Triangle(p,triangleList[i].vertex1,triangleList[i].vertex2));
    triangleList.insert(triangleList.begin()+i, Triangle(p,triangleList[i+1].vertex2,triangleList[i+1].vertex3));
    triangleList.insert(triangleList.begin()+i, Triangle(p,triangleList[i+2].vertex1,triangleList[i+2].vertex3));
    //erase the beginning inclusive triangle
    triangleList.erase (triangleList.begin()+i+3);
}

/** draw function to animate the triangle subdivision, based on order of triangles in triangleList
 @param img is the cv::Mat to draw on (passed by reference)
 @param stroke is the integer stroke weight for the triangle lines (1-2 look nice for a 500 x 500 image)
 **/
void TriSubdiv::draw(cv::Mat& img, int stroke){
    //iterate through the triangleList and draw them all white..
    for (int i=0; i< triangleList.size(); i++){
        cv::line(img, triangleList[i].vertex1, triangleList[i].vertex2, cv::Scalar(255,255,255), stroke);
        cv::line(img, triangleList[i].vertex2, triangleList[i].vertex3,cv::Scalar(255,255,255), stroke);
        cv::line(img, triangleList[i].vertex3, triangleList[i].vertex1,cv::Scalar(255,255,255), stroke);
        cv::imshow("display",img);
        //change this for animation speed.
        cv::waitKey(100);
    }



}