# DNA Sequence Generator

## Chase Toyofuku-Souza
> 2296478

> toyofukusouza@chapman.edu

----
### About
A C++ program designed to accept a name of a text file as a command line argument, then commpute the sum, mean, variance, and standard deviation of the length of the DNA strings in the file. It will also compute the relative probability of each nucleotide, as well as nucleotide bigram. It will then generate a new DNA sequence with the same statistics as the user-provided one.

### Files
- DNA.h
- DNA.cpp
- main.cpp
- Makefile
- sample.txt

### Instructions
- Run 'make all'
- Run './dna.exe' folllowed by the name of a file you wish to base a sequence off of
- After a new sequence is generated, you may repeat the above process by entering another file name
- Open "output.txt" to view the results

### Notes
In this context, DNA strings are any string in the format of any combination of words containing A, T, C and G.

The length of a string is denoted by the number of characters in that line. 

### References
- http://www.cplusplus.com/reference/cstdlib/rand/
- https://stackoverflow.com/questions/9878965/rand-between-0-and-1
- https://stackoverflow.com/questions/2393345/how-to-append-text-to-a-text-file-in-c
- http://www.cplusplus.com/doc/tutorial/files/
- http://www.cplusplus.com/reference/cctype/toupper/
- https://docs.microsoft.com/en-us/cpp/cpp/header-files-cpp?view=vs-2017
- http://www.cplusplus.com/reference/cmath/
- https://www.tutorialspoint.com/cplusplus/cpp_constructor_destructor.htm
- https://kb.iu.edu/d/aqsj