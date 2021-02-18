# WORDNET

These files are the C++ implementation of the wordnet assignment in the book *Algorithms 4th edition*

Please visit this [link](https://coursera.cs.princeton.edu/algs4/assignments/wordnet/specification.php) for more details.

## Digraph.hpp

This head file defines the directed draph class. It is implemented refer to the [Digraph.java](https://algs4.cs.princeton.edu/42digraph/Digraph.java.html). The corresponding test file is provided. The file is verified with the data in tinyDG.txt and mediumDG.txt provided on the website. You can compile the unit test with the following command:

```bash
clang++-10 test_digraph.cpp -o test_digraph --std=c++2a -lgtest -lptread -lstdc++fs
```

then run the unit test file

## SAP.hpp
This head file defines the SAP class. It conducts  Breadth First Search(BFS) in multithread. It starts parrellel BFS from multiple sources to find common ancestor in a directed graph. BFS in multithread is not necessary and there are still rooms for optimization (For example pruning the BFS when the current distance is larger than the current shortest ancestral path).The *std::mutex* library is used and a thread lock is included to ensure thread safty.

The corresponding test file is provided. You can compile the unit test with the following command:

```bash
clang++-10 test_sap.cpp -o test_sap --std=c++2a -lgtest -lpthread -lstdc++fs
```

## WordNet.hpp
This head file defines the WordNet class. It read in the files and construct a directed graph inside the class to allow various operations.
To process the read-in string rapidly, the *std::ranges* library, which is the latest features in C++20, is used. Threrefore, it requires the compiler to support this libray (such as g++-10). The corresponding unit test file is provided. You can compile the unit test with the following command:

```bash
g++-10 test_wordnet.hpp -o test_wordnet --std=c++2a -lgtest -lpthread -lstdc++fs
```
then run the unit test file.

Noted that the *wordnet_data* folder should be put under the same directory of the executed file.


## Outcast.hpp
This head file defines the Outcast class. It receives a WordNet instance and a set of words and find out the noun that are out class. The corresponding test file is provided. You can compile the unit test with the following command:

```bash
g++-10 test_outcast.hpp -o test_outcast --std=c++2a -lgtest -lpthread -lstdc++fs
```
then run the unit test file.

## outcast_client.cpp
This is the final client. Different from the assignment requirment which is implemented as a member function in the *Outcast* class, I make it an independent client. You can compile the client with the following command:

```bash
g++ outcast_client.cpp -o outcast_client --std=c++2a -lgtest -lpthread -lstdc++fs
```
To run the client, you need to provide the synset file name, the hypernym file name and noun set file name.

```bash
./outcast_client <synsets_filename> <hypernyms_filename> <noun_set_filename_1> <noun_set_filename_2> ...
```
For example suppose that, all the files are under the *wordnet_data* folder under the same directory of the execution file, the running command should be 

```bash
./outcast_client /wordnet_data/synsets.txt /wordnet_data/hypernyms.txt /wordnet_data/hypernyms.txt /wordnet_data/outcast5.txt /wordnet_data/outcast8.txt /wordnet_data/outcast11.txt
```
