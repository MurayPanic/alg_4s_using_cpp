#BOGGLE

These files are the C++ implementation of the "Baseball Elimination " assignment in the book *Algorithms 4 th edition*

Please visit the [coursera](https://coursera.cs.princeton.edu/algs4/assignments/boggle/specification.php) or the [book website](https://www.cs.princeton.edu/courses/archive/spring04/cos226/assignments/puzzle.html) for more details.

## BoggleBoard.hpp

The BoggleBoard class is used for representing a Boggle board. This head file is the C++ implementation of the [BoggleBoard.java](https://coursera.cs.princeton.edu/algs4/assignments/boggle/files/BoggleBoard.java). THe corresponding test file is provided. You can compile the unit test with the following command:

```bash
$ g++-10 test_boggleboard.cpp -o test_boggleboard --std=c++2a -lgtest -lpthread
```

then run the unit test file.

## TernaryTriesNode.hpp

The TernaryTreeNode class defines the node that used for constructing a ternary search tree. It is a basic element of ternary search tree for string. The corresponding test file is provided. You can compile the unit test with the following command:
```bash
$ g++-10 test_ternarytrienode.cpp -o test_ternarytrienode --std=c++2a -lgtest -lpthread
```
then run the unit test file.



## PrefixTree.hpp

The PrefixTree class is used for constructing a ternary search tree based on a given dictionary. This class support prefix query operation: check whether there are any words start with the given prefix. The prefix query operation is provided with the *has_word_with_prefix* methord.

The prefix query operation is implemented by first search the path that represent the prefix in the ternary trie, then conduct board first search from the last node from the path. The BFS stops when it finds a node that has positive integral value and return true.

 You can compile the unit test with the following command:
```bash
$ g++-10 test_prefixtree.cpp -o test_prefixtree --std=c++2a -lgtest -lpthread
```
then run the unit test file.

## BoggleSolver.hpp

The BoggleSolver is the required class by the assignment. It receive a dictionary as a parameter for initialization. The dictionary is restored in an unordered set which is implemented using hash map in C++. A prefix tree is constructed based on the dictionary to allow prefix query operation.

This class solve the boggle by conducting depth first search(DFS) on the Boggle board. At each step when a new word is obtained based on the previeous step, it will check whether the word is contained in the dictionary, and whether there are any other words in the dictionary that use the current word as prefix. If ther are no any other words that use the current word as prefix, the DFS will return and will not extend the current path. 

 You can compile the unit test with the following command:
```bash
$ g++-10 test_bogglesolver.cpp -o test_bogglesolver --std=c++2a -lgtest -lpthread -lstdc++fs
```
then run the unit test file.

The test cases available on the assignments website are all included into the test file.

## BoggleSolver_client.cpp

This is the client for the boggle solver. It receives a dictionary and a board for parameters and then print out all the valide words and the total scores. It follow the design on the assigment website. You can compile the file with the following command:

```bash
$ g++-10 BoggleSolver_client.cpp -o BoggleSolver_client --std=c++2a -lgtest -lpthread -lstdc++fs
```

You can run the application with the following command:

```bash
$ ./BoggleSolver_client <dictionary_file_name> <board_name>
```