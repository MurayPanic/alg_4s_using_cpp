# PERMUTATION

These files are the c++ implementation of the permutation assignment in the book *Algorithms 4th edition*

Please visit this [link](https://coursera.cs.princeton.edu/algs4/assignments/queues/specification.php) for more details.



## linked_list.hpp

The dequeue container is developed using doubly linked list. The class of the doubly linked list is defined in the linked_list.hpp.  The file is tested using Google test framework written in the test_linked_list.cpp.  You can compile the unit test with the following command:

```bash
clang++-8 test_linked_list.cpp -o test_linked_list --std=c++2a -lgtest -lpthread
```

then run the unit test file



## two_queues.hpp

Both the dequeue and randomized queue is defined in this head file. The dequeue class is implemented using doubly linked list because the assignment requires all the operation has constant worst case performance. The randomized queue is implemented using dynamic array with smart pointer.

This unit test for this head file is written in the test_two_queues.cpp. Again, it uses Google test framework. You can compile the unit test file with the following command:

```bash
clang++-8 test_two_queues.cpp -o test_two_queues --std=c++2a -lgtest -lpthread
```

then run the unit test file



## Permutation.cpp

The client for permutation. The it can returns a permutation of K items from the given list. It mechanism is to read the data into a randomized queue and dequeue K objects. To compile the source file, you can use the following command: 

```bash
clang++-8 Permutation.cpp -o Permutation --std=c++2a --lfstdc++std
```

To call the file use the following command:

```bash
$ ./permutation <K> <data_file_dir>
```

For example:

```bash
$./permutation 8 ./distinct.txt
```



## Tips for implementing using C++

- Writing template function. Because the data can be any type. It can be Integer, string or container like vector.  
- Develop iterator. You can write an iterator that adopts STL style. But it seems not very necessary. You can refer to the following to links for more information:
  - [Define c++ Iterators](https://users.cs.northwestern.edu/~riesbeck/programming/c++/stl-iterator-define.html#TOC8)
  - [Defining a custom iterator in C++](https://lorenzotoso.wordpress.com/2016/01/13/defining-a-custom-iterator-in-c/)
- Use smart pointer to mange dynamic array.
- Do not use smart pointer to implement the linked list. Although it is practical, introducing smart pointer into linked list cause unnecessary complexity.