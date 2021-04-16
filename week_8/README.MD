# BASEBALL ELIMINATION

These files are the C++ implementation of the "Baseball Elimination " assignment in the book *Algorithms 4 th edition*

Please visit the [coursera](https://coursera.cs.princeton.edu/algs4/assignments/baseball/faq.php) or the [book website](https://www.cs.princeton.edu/courses/archive/spring04/cos226/assignments/baseball.html) for more details.



## FlowEdge.hpp

The FlowEdge class is used for describe an edge using residual. It is a basic element for construct the flow network. This head file is the C++ implementation of the [FlowEdge.java](https://algs4.cs.princeton.edu/code/edu/princeton/cs/algs4/FlowEdge.java.html). The corresponding test file is provided. You can compile the unit test with the following command:

```bash
$ g++-10 test_flowedge.cpp -o test_flowedge --std=c++2a -lgtest -lpthread
```

then run the unit test file.



## FlowNetwork.hpp

The FlowNetwork class describe a network using the flow edge. This head file is the C++ implementation of the [FlowNetwork.java](https://algs4.cs.princeton.edu/code/edu/princeton/cs/algs4/FlowNetwork.java.html). The corresponding test file is provided. You can compile the unit test with the following command:

```bash
$ g++-10 test_flownetwork.cpp -o test_flownetwork --std=c++2a -lgtest -lpthread
```

then run the unit test file.



## FordFulkerson.hpp

The FordFulkerson class use the Ford-Fulkerson algorithm to compute the max-flow/min-cut on a flow network. This head file is the C++ implementation of the [FordFulkerson.hpp](https://algs4.cs.princeton.edu/64maxflow/FordFulkerson.java.html) . However, due to the different characteristic of the data member storage strategy, the API of this head file is slightly different from the original java implementation. The Ford-Fulkerson algorithm requires searching on the an flow network and the flow in the network needs to be updated after finding an augmented path. This is the difficult point in C++ implementation. My implementation is not in the most efficient way. But in other to keep the API consistent with the original java implementation, I did not further optimize it. 

The corresponding test file is provided. You can compile the unit test with the following command:

```bash
$ g++-10 test_fordfulkerson.cpp -o test_fordfulkerson --std=c++2a -lgtest -lpthread -lstdc++fs
```

then run the unit test file.



## BaseballElimination.hpp

The required class file by the assignment. It construct a flow network according to the baseball match data and then calculate the max-flow/min-cut with Ford-Fulkerson algorithm to find out which team is mathematically eliminated. 

The difficulty lies in how to construct the flow network (or the graph) that describe the wins distribution between each teams.  The flow network constructed by my implementation has fixed number of nodes. That means there are isolated nodes in my network. For example, in the example in the assignment page, team Detroit is the target team. The nodes that represent the game between Detroit and other teams are also included in the flow network. Also the vertex that represents team Detroit is also included into this network.  But these above vertices are isolated and there are no edges connecting them.

The advantage of this design is that when the target team change, we just need to rearrange the edge connection without changing the representation of vertices.  For example, the first node is always the source node and the second node is always the game vertex that represent the game between team 0 and team 1 no matter which target team is. Another advantages, we can easily used the whole lower-triangle of the game matrix when construct the flow network  instead of carefully find out which row and column are need to excluded.

The corresponding test file is provided. You can compile the unit test with the following command:

```bash
$ g++-10 test_baseballelimination.cpp -o test_baseballelimination --std=c++2a -lgtest -lpthread -lstdc++fs
```

then run the unit test file.

The test cases available on the assignments website are all included into the test file.



## baseball_elimination_client.cpp

This is the client for the baseball elimination. It reads a data file and then print out whether each team in the file is mathematically eliminated. It follow the design on the assignment website. You can compile the file with the following command:

```bash
$ g++-10 baseball_elimination_client.cpp -o baseball_elimination_client --std=c++2a -lgtest -lpthread -lstdc++fs
```

You can run the application with the following command:

```bash
$ ./baseball_elimination_client <file_name>
```

