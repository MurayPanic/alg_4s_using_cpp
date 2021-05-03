# COLLINEAR POINTS

These files are c++ implementation of the assignment in the book *Algorithm 4th edition*

Please visit this link for more detials

## BruteCollinearPoints.hpp

This file find the collinear points with brute force search. It is only suitable for the situations that no more than 3 points that are collinear. If more than 3 points are collinear the output result may be duplicate. The corresponding test file is provided. You can compile the unit test with following command:

```bash
clang++-10 test_brute_collinear_points.cpp -o test_brute_collinear_points --std=c++2a -lgtest -lpthread
```





## FastCollinearPoints.hpp

This file find collinear points based on sorting. The sorting method used by default is the default sorting function provided in C++. In addition I also writed several sorting methods taught in the course and they can be applied by setting the flags. The corresponding test file is also provided. You can compile the unit test with the following command:

```bash
clang++-10 test_fast_collinear_points.cpp -o test_fast_collinear_points --std=c++2a
-lgtest -lpthread
```



## collinear_point_client.cpp

This is the source code for the client. It first run find the collinear points with the brute force search then use the sorting-based method. The results by the sorting-based method will be visualized.  The visualization is achieved with the matplotlib-cpp library. Therefore, it requires python, numpy and matplotlib library. To compile the file, you need to provide the address of numpy library. The numpy library address can be achieved with:

```python
import numpy as np
np.get_included()
```

  You can compile the client with the following command:

```bash
clang++-10 collinear_point_client.cpp -o collinear_point_client --std==c++2a --lstdc++fs -I/usr/local/lib/python3.6/dist-packages/numpy/core/include `pkg-config --cflags --libs python3`
```

The complied application can be run with the following command:

```bash
.\collinear_point_client .\input8.txt
```

The *input8.txt* and *input6.txt* are the files that store the points for detection. 



## custom_sort.hpp

This files contains the custom sorting method written by myself. The corresponding unit test file is provided. You can compile the unit test file with the following command:

```bash
clang++-10 test_custom_sort.hpp -o test_custom_sort --std=c++2a -lgtest -lpthread
```

Then run the unit test.

However I can not guarantee the sorting methods are completely correct. I just write them with my understanding.

All these sorting methods are written in a STL style. That is , they operate on iterators. Using iterators in the sorting seems to be a little bit more complicated than using the indexes. Especially when you need to determine whether you have reached the end of a list, you need to be careful. If you use index, the end of list can be easily determined by the numeric value of the index. If you use iterator, in many situation, you can not increment the iterator to larger than the last element, because it may cause undefined error.  My solution is: quit the loop when I reach the last element , and handle the last element independently.  

Another important point is to notice that the end() iterator of STL containers is in fact pointing to the one over the last element.  

The index processing in merge_sort and quick_sort are difficult!! You have to handle carefully / test several times to handle some boundary situations.



## Point.hpp  & LineSegment.hpp

The geometric object class files. Corresponding test files are also provided. You can compiled the test files with the following commands:

```bash
clang++10 test_point.cpp -o test_point --std=c++2a -lgtest -lpthread;
clang++10 test_line_segment.cpp -o test_line_segment --std=c++2a -lgtest -lpthread
```



## draw.hpp

The visualization function are not embedded into the *Point* class and *LineSegment* class. This is a little bit different from the original requirements. It visualized the points with the matplotlib library using the matplotlib-cpp. The [matplotlib-cpp](https://github.com/lava/matplotlib-cpp)  library is included. I compiled my files with python 3.6.

The command for compiling unit test is :

```bash
clang++10 test_draw.cpp -o test_draw --std=c++2a -lgtest -lpthread -I/usr/local/lib/python3.6/dist-packages/numpy/core/include `pkg-config --cflags --libs python3`
```

