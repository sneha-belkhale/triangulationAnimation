/** @file Triangle.cpp
 @brief Triangle class function definitions
 @author Sneha Belkhale
 @date September 22nd, 2016
 
 This class provides a simple structure for a triangle shape opject.
 */

#include "Triangle.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>

/** constructor for the Triangle class
 @param x - cv::point of the first vertex
 @param y - cv::point of the second vertex
 @param z - cv::point of the third vertex
 **/
Triangle::Triangle(cv::Point x, cv::Point y, cv::Point z){
    //assign the vertices
    this->vertex1 = x;
    this->vertex2 = y;
    this->vertex3 = z;
}


/** function that checks whether a point lies inside the triangle
 @param P - cv::Point corresponding to point of interest 
 @return - true if the point is in the triangle
 **/
bool Triangle::contains(cv::Point P)
{
    float denominator= ((vertex2.y - vertex3.y)*(vertex1.x - vertex3.x) + (vertex3.x - vertex2.x)*(vertex1.y - vertex3.y));
    float a = ((vertex2.y - vertex3.y)*(P.x - vertex3.x) + (vertex3.x - vertex2.x)*(P.y - vertex3.y)) / denominator;
    float b = ((vertex3.y - vertex1.y)*(P.x - vertex3.x) + (vertex1.x - vertex3.x)*(P.y - vertex3.y)) / denominator;
    float c = 1 - a - b;
    
    return 0 <= a && a <= 1 && 0 <= b && b <= 1 && 0 <= c && c <= 1;
}