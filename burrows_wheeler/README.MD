# Burrows Wheeler

These files are the C++ implementation of the "Burrows Wheeler" assignment in the book *Algorithms 4 th edition*

Please visit the [coursera](https://coursera.cs.princeton.edu/algs4/assignments/burrows/specification.php) or the [book website](https://www.cs.princeton.edu/courses/archive/spring04/cos226/assignments/burrows.html) for more details.

# CircularSuffixArray.hpp

The CircularSuffixArray class is used for manage the circular suffix array of a string. It follows the suggestion on the [possible progress steps](https://coursera.cs.princeton.edu/algs4/assignments/burrows/faq.php). It implements a less than operator(<) for sorting the circular suffix. The corresponding test file is provided. You can compile the unit test with the following command:

```bash
$ g++-10 test_circularsuffixarray.cpp -o test_circularsuffixarray --std=c++2a -lgtest -lpthread
``` 
then run the unit test file.

As mentioned on the website, this implementation is clean but not the fastest way. The sorting of the circular suffix takes quite lot of time. 

# BurrowsWheeler.cpp

The BurrowsWheeler class implement the Burrows-Wheeler transform. It read in files in bytes and conduct the transformation. One can compile the file with the following command:
```bash
$ g++-10 BurrowsWheeler.cpp -o BurrowsWheeler --std=c++2a
```
The program receives input and present result on standard I/O. A simple command line order for transform is as follow:
```bash
$ ./BurrowsWheeler - < ./burrows/abra.txt > abra_output.bwt
```
To conduct inverse transform, please use a plus ("+") in argument.
```bash
$ ./BurrowsWheeler + < ./abra_output.bwt > abra_copy.txt
```


# MoveToFront.cpp
The MoveToFront class implement the move-to-front transfrom. It read in files in bytes and conduct the transformation. One can compile the file with the following command:
```bash
$ g++-10 MoveToFront.cpp -o MoveToFront --std=c++2a
```
The program receives input and present result on standard I/O. A simple command line order for transform is as follow:
```bash
$ ./MoveToFront - < ./burrows/abra.txt > abra_output.mtf
```
To conduct inverse transform, please use a plus ("+") in argument.
```bash
$ ./MoveToFront + < ./abra_output.mtf > abra_copy.txt
```

# Huffman.cpp
The Huffman class implement the Huffman compression. It is not required by the assignment but is necessary for the complete Burrow-Wheelers data compression. This head file is the C++ implementation of the [Huffman.java](https://algs4.cs.princeton.edu/code/edu/princeton/cs/algs4/Huffman.java.html). One can compile the file with the following command:
```bash
$ g++-10 Huffman.cpp -o Huffman --std=c++2a
```

The program receives input and present result on standard I/O. A simple command line order for transform is as follow:
```bash
$ ./Huffman - < ./burrows/abra.txt > abra_output.huf
```
To conduct inverse transform, please use a plus ("+") in argument.
```bash
$ ./Huffman  + < ./abra_output.huf > abra_copy.txt
```

The C++ implemenation is nearly the same as its Java implementation except that it does not use the Binary [input](https://algs4.cs.princeton.edu/code/javadoc/edu/princeton/cs/algs4/BinaryStdIn.html) and [output](https://algs4.cs.princeton.edu/code/javadoc/edu/princeton/cs/algs4/BinaryStdIn.html) library. Under Unix system, C++ open files in binary mode and *std::cin.get()* can read input in byte (8 bits). In this file, the read-in string will be converted to binary representation using *std::bitset* library befor further process.

But this file may not work on Windows system because it may not receive inpu in binary mode.

# General Performance
The above implementation of transformations works for both text data and non-text data. You can verify by trying to conduct Burrows-Wheeler data compression on different types of file with following command

For text data compression:
```bash
$ ./BurrowsWheeler - < ./mobydick.txt | ./MoveToFront - | ./Huffman - > mobydick_output.bwt.mtf.huf
```

For text data decompression:
```bash
$ ./Huffman + < ./mobydick_output.bwt.mtf.huf | ./MoveToFront + | ./BurrowsWheeler + > mobydick_copy.txt
```

For non-text data compression:
```bash
$ ./BurrowsWheeler - < ./burrows/us.gif | ./MoveToFront - | ./Huffman - > us_output.bwt.mtf.huf
```

For non-text data decompression:
```bash
$  ./Huffman + < ./us_output.bwt.mtf.huf | ./MoveToFront + | ./BurrowsWheeler + > us_copy.gif
```

There are still rooms for improvement for thie C++ implementation. It takes approximately 4.5 seconds to compress the **mobydick.txt**. But it takes only 1.4 seconds for the example on the [website](https://coursera.cs.princeton.edu/algs4/assignments/burrows/faq.php).

```bash
$ time ./BurrowsWheeler - < ./mobydick.txt | ./MoveToFront - | ./Huffman - > mobydick_output.bwt.mtf.huf

real    0m4.489s
user    0m4.713s
sys     0m0.048s
```

The bottleneck is in the sorting of the circular suffix.

## Tips for implementing using C++
- Store the input bytes using *unsigned int* variables to read in bytes overflow. This is important to enable the transformation work for non-text data;
- The Huffman compression need to proceed the input bit by bit;
- Avoid unecessary copy and use reference more can help to improve the run-time efficiency.