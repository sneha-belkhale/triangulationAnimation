# triangulationAnimation
Experimenting with different triangulation methods and input points in order to create some pretty neat graphic animations. 

There are two methods used for triangulation so far in the TriSubdiv class:
insert_sd - triangulate the image by generating 3 new triangles (within its bounding triangle) each time a point is added to the set 
insert_nn - simply creates triangles by connecting the new point to its nearest 2 neighbors 

When executing triangulation.cpp (use cmake in current directory to compile), it takes in a command line integer argument from 1 - 10, corresponding to different sets of points 
added to the TriSubdiv object (adding different points in unique orders will give different triangulation results).
 args 1 : 7 triangulate the image using insert_sd
 args 7 : 10 simply create triangles using insert_nn
 
 
Lastly, the code displays the ~beautiful nature~ of the triangulation in an animation (some examples below)


![alt tag](https://cloud.githubusercontent.com/assets/17795014/18795786/0f51fe7a-817b-11e6-915f-8ce112c21458.gif)


![alt tag](https://cloud.githubusercontent.com/assets/17795014/18795781/0a5665aa-817b-11e6-8a14-d0c1a047c634.gif)
