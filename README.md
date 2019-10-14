# BPlusTrees
Implementation of B+ Trees for indexing

A B+ tree is a balanced binary search tree that follows a multi-level index format. The leaf nodes of a B+ tree denote actual data pointers. B+ tree ensures that all leaf nodes remain at the same height, thus balanced. Additionally, the leaf nodes are linked using a link list; therefore, a B+ tree can support random access as well as sequential access.

It can handle the following queries:

1. INSERT x - insert x into the B+tree
2. FIND x - print YES if x is already inserted , else NO
3. COUNT x - print number of occurrences of x in B+tree
4. RANGE x y - print number of elements in range x to y ( both x and y included)

To run:

##### Compile:

g++ -std=c++11 btree.cpp

##### Run: 

./a.out inputFile number_of_buffers buffer_size
  
where number of buffers is >= 2.

Eg: ./a.out input.txt 4 16 > result.txt

##### Verify:

diff result.txt output.txt
