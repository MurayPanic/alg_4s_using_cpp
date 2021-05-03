# Kd-Tree

These files are C++ implementation of the assignment from the course "Algorithms Part I"  on Cousera.

Please visit this [link](https://coursera.cs.princeton.edu/algs4/assignments/kdtree/specification.php) for more details



## Point2D.hpp

This file defines a two-dimension points. Its API is the same as that on the assignment pages. The corresponding test file is provided.  You can compile it with the following command

```bash
clang++-10 test_point2d.cpp -o test_point2d --std=c++2a -lgtest -lpthread
```

Then you can run the test_point2d to conduct the test.



## RectHV.hpp

This file defines aligned rectangle which has edges parallel to X and Y axis. Its API is the same as that on the assignment pages and support intersection judgment and contains judgment. The corresponding test file is provided. You can compile it with the following command

```bash
clang++-10 test_recthv.cpp -o test_recthv --std=c++2a -lgtest -lpthread
```

Then you can run the test_recthv to conduct the test.



## PointSET.hpp

This file implement the range search and nearest neighbor point search with brute force method. Its API is identical to that on the assignment pages. The corresponding test file is provided. You can compile it with the following command 

```bash
clang++-10 test_pointset.cpp -o test_pointset --std=c++2a -lgtest -lpthread
```

Then you can run the test_pointset to conduct the test.

## KdTree.hpp

This file implement the range search and nearest neighbor point search with Kd tree. Its API is the same as that on the assignment pages. According to the assumption,  the coordinates of the 2D points are assumed to be between 0 and 1. 

The `draw()` member function visualize the Kd-Tree using the OpenCV pacakges. The canvas is set to be $600 \times 600$. 

The corresponding test file is provided and it includes some basic examples.  You can compile the test file with the following command:  

```bash
clang++-10 test_kdtree.cpp -o test_kdtree --std=c++2a -lgtest -lpthread `pkg-config opencv4 --cflags --libs`
```

Then you can run the *test_kdtree* to conduct the test. Noted that the visualization of the Kd Tree will block the process. Therefore, you need to press enter several times to finish the test.



## KdTree_verify_client.cpp

This file implements a client to verify the correctness of the KdTree implementation.  The verification is conducted by comparing the result generated by the PointSET  and KdTree. The point data are from the course. It first visualize the KdTree then conduct the comparison using both fixed/random point and rectangles. The comparison is conducted under Google test framework So far from my experiments, results from the PointSET and KdTree are consistent. I also time the process with the `chrono` library in C++. Results show that my implementation in KdTree has advantages over PointSET in large amount of point. 

You can compile the client with the following command:

```bash
clang++-10 KdTree_verify_client.cpp -o KdTree_verify_client --std=c++2a -lstdc++fs -lgtest -lpthread `pkg-config opencv4 --cflags --libs` 
```

The you can run the client by providing the data file. For example, suppose that the data point file has the path `./kdtree/input10.txt`

```bash
./KdTree_verify_client ./kdtree/input10.txt
```

Noted that is still required in the test process.