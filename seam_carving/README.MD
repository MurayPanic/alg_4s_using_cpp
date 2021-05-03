# SEAM CARVING

These files are the C++ implementation of the seam carver assignment in the book *Algorithms 4th edition*

Please visit this [link](https://coursera.cs.princeton.edu/algs4/assignments/seam/specification.php) for more details.

## Picture.hpp

This head file defines the Picture class. It is corresponding to the [Picture.java](https://algs4.cs.princeton.edu/code/javadoc/edu/princeton/cs/algs4/Picture.html) used in the requirement. It is essentially a wrapper of some OpenCV data type and methods. THe corresponding unit test file using Google tes framework is provided. You can compile the unit test with the following command:

```bash
g++-10 test_picture.cpp -o test_picture --std=c++2a -lgtest -lpthread -lstdc++fs `pkg-config opencv4 --libs --cflags`
```

then run the unit test file to see the result:

```
./test_picture
```

## SeamCarver.hpp
This head file defines the SeamCarver class. Its public API is according to the requirement of the assignment. It use dynamic programming to find the minimum energy seam. 

The class first calculate the dual gradient and restores the gradients in the *energy_map*.

This class use two auxiliary matrices ( *distTo* and *edgeTo*) in the calculation. The value in each entry of the *disTo* matrix represents the minimum energy of the path from one of the entries in the first row to this entry. 

The values in the entires of the *edgeTo* matrix are limited to ${-1,0,1}$. The value suggests that which entry in the previous row is connected to the current entry to form the minimum energy path.

The seam is obtained by back tracking start from the last row of the *energy_map*. It obtains points of the seam on energy map according to the *edgeTo* matrix.

The above procedure is used for calcuate the vertical seams. In terms of the horizontal seams, the class first transpose the image, then re-calculate the energy map and calculate the seams using the above procedure.

The corresponding unit test file using Google test framework is provided. One can use the following command to compiel the file:

```bash
g++-10 test_seamcarver.cpp -o test_seamcarver --std=c++2a -lgtest -lpthread -lstdc++fs `pkg-config opencv4 --libs --cflags`
```

then run the unit test and see the result:

```bash
./test_seamcarver
```

## Tips for implmenting using C++

- To visualize the energy map, you need to convert a one-channel matrix with double datatype to  a three-channel matrix with CV_8U3C data type.
- The coordinate system of some methods in the Picture class is different from the OpenCV. When you want to describe the coordinates of a Pixel, try to ask yourself which row and col does the pixel locate?


