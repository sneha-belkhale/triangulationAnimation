/** @file Triangle.hpp
 @brief Triangle class declaration
 @author Sneha Belkhale
 @date September 22nd, 2016
 
 This class provides a simple structure for a triangle shape object.
 */

#ifndef Triangle_hpp
#define Triangle_hpp

#include <stdlib.h>

#include <stdio.h>
#include <opencv2/opencv.hpp>
/** @class Triangle
 @brief This class provides a simple structure for a triangle shape opject. including variables for the three vertices and utility functions to check whether a point lies within the triangle
 */
class Triangle{
public:
    //constructor
    Triangle(cv::Point x, cv::Point y, cv::Point z);
    //check whether p lies in the triangle
    bool contains(cv::Point p);
    //vertices
    cv::Point vertex1;
    cv::Point vertex2;
    cv::Point vertex3;
};
#endif /* Triangle_hpp */
