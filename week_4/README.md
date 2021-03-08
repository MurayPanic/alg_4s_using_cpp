# 8 PUZZLE

These files are C++ implementation of the assignment from the course "Introduction Algorithm" on Cousera.

Please visit this [link](https://coursera.cs.princeton.edu/algs4/assignments/collinear/specification.php) for more details

## Board.hpp

This file defines the Board API. The corresponding test file is provided. You can compile the unit test with the following command

```
clang++-10 test_board.cpp -o test_board --std=c++2a -lgtest -pthread
```

Then run the test_board to conduct the test.



## Solver.hpp

The solver for the puzzle is defined in this file.  The *Solver* class solves the puzzle with *A* * search. The implementation uses priority queue and manage intermediate result with unordered set. The final result is obtained through back tracing on a linked list.  Whether a puzzle is solvable or not is determined by solving two puzzles who are twins to each other simultaneously.  This is achieved with the C++ concurrency library (*thread* and *future*).

The unit test file is also provided and in the unit test, I only test several cases to verify my implementation. However, there may be potential bug.

The unit test file  can be compiled with the following command:

```c++
clang++-10 test_solver.cpp -o test_solver --std=c++2a -lgtest -lpthread
```



## PuzzleChecker.cpp

This is a client for running test on the test cases provided in the course. However, my machine is out of date and lacked sufficient memory to go through all the test. But it seems that it can solve all the $3 \times 3$ puzzle and part of the $4 \times 4$ and $5 \times 5$ puzzles. I only check the length of the minimum solution. They seems all correct. But still, there is possibility that I may make some mistakes.

The client can be complied with the following command. Noted that because the C++ concurrency library is used, please add *-pthread* in the compile command:

```bash
clang++-10 PuzzleChecker.cpp -o PuzzleChecker --std=c++2a -lstdc++fs -lpthread
```

To run the test, please provide the address for holding the test cases:

```bash
./PuzzleChecker ./8puzzle
```



## Some comments in the development

- When controlling several multiple threads, you need to design a safe mechanism to let the thread stop itself. You can not stop a thread from external. C++ does not provide such a function. In this case, I use a flag *stop_thread* that shared by two threads. Once the flag is set to be true, two threads will stop.
- To use *unordered_set* for custom classes, you need to provide customized hash function. Also, to use priority queue for customized function, you need to provide the compare function (which is wrapped in a class).
- To use min oriented priority queue, you need to provide a "larger than" function. So that the priority queue will return the minimum when you do the pop operation.
- For some tutorials on c++ concurrency library, please refer to [C++11 Concurrency Tutorial - Part 5: Futures](https://baptiste-wicht.com/posts/2017/09/cpp11-concurrency-tutorial-futures.html). 

