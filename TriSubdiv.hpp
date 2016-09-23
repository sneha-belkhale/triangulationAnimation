/** @file TriSubdiv.hpp
 @brief TriSubdiv class declaration
 @author Sneha Belkhale
 @date September 22nd, 2016
 
 This class is modeled after the openCV::subDiv2D class that triangulates an image given a stream of points using the Delaunay Triangulation method, with insert point and draw functionalities.
 
 Instead of Delaunay Triangulation, I wanted to play around with other two other triangulation methods:
 
 Subdivision (@function insert_sd) - divides triangle containing inserted point into three new triangles
 Nearest Neighbor (@function insert_nn) - creates a triangle containing the point and its two nearest neighbors
 
 The draw functionality provides a cool animation of the triangulation.
 
 */

#ifndef TriSubdiv_hpp
#define TriSubdiv_hpp

#include <opencv2/opencv.hpp>
#include "Triangle.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <vector>

/** @class TriSubdiv
 @brief This class is modeled after the openCV::subDiv2D class that triangulates an image given a stream of points using the Delaunay Triangulation method, with insert point and draw functionalities.
 
 Instead of Delaunay Triangulation, I wanted to play around with other two other triangulation methods:
 
 Subdivision (@function insert_sd) - divides triangle containing inserted point into three new triangles
 Nearest Neighbor (@function insert_nn) - creates a triangle containing the point and its two nearest neighbors
 
 The draw functionality provides a cool animation of the triangulation.
 **/
class TriSubdiv {
public:
    //constructor, take in bounding rectangle (offsetX, offsetY, width, height)
    TriSubdiv(int x1, int y1, int w, int h);
    //insert point by subdivision method
    void insert_sd(cv::Point x);
    //utility function to subdivide triangle
    void subdivide(int i, cv::Point p);
    //insert point by nearest neighbor method
    void insert_nn(cv::Point a);
    
    //vector to hold a list of triangle objects
    std::vector<Triangle> triangleList;
    //vector to hold list of cv::points added so far
    std::vector<cv::Point> pointList;
    //function to draw onto the image
    void draw(cv::Mat& img, int stroke);
    
private:
    //holds number of triangles in list
    int count;
    //bounding rectangle poi ts of triangulation regions
    cv::Point ULCorner, LLCorner, URCorner, LRCorner;
    
};

#endif /* TriSubdiv_hpp */
