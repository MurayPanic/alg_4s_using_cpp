## PERCOLATION
These files are the C++ implementation of the percolation assignment in the book *Algorithms 4th edition*.

Please visit this [link](https://coursera.cs.princeton.edu/algs4/assignments/percolation/specification.php) for more details.

## UFclass.hpp
The quick find and quick union algorithms are implemented in the UFclass.hpp. To test the algorithm you can compile with the follow command:

```bash
clang++-8 client_api.cpp -o client_api --std=c++2a -lstdc++fs
```
then run the client_api.

## percolation.hpp
The percolation class and the experiment class are implemented in the percolation.hpp. To conduct the monte calo experiments, you can revised the test_percolation.cpp with the following command:

```bash
clang++-8 test_percolation.cpp -o test_percolation --std=c++2a 
```

then run the test_percolation program.