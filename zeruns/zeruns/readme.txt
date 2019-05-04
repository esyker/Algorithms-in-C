This project solves a binary puzzle automatically ( rules can be found here-> http://binarypuzzle.com/rules.php ).
Build the project using makefile (with the command make).
Create a text file with the puzzles you want to solve ( the file must have the .puz extension).
File example (for example, puzzle.puz):

10 2
1 9 9 9 9 9 9 1 9 9
9 9 9 9 9 9 9 9 9 1
9 9 1 1 9 1 9 0 0 9
9 9 9 9 9 9 9 9 9 9
0 9 9 0 9 9 9 9 0 9
9 9 9 9 9 9 1 9 9 9
9 1 1 9 9 9 9 9 9 1
9 9 9 9 9 9 1 9 9 9
9 9 9 9 0 9 1 9 0 0
9 9 9 9 9 0 9 9 0 0

4 1
9 9 1 9
9 9 1 9
0 0 9 9
9 1 9 9

As you can see, you create a new binary puzzle and fill it with 0's 1's and the incognites 9's.
Before each puzzle you enter the puzzle dimensions (for example 4 or 10) followed by a number (1 or 2) that represents the restritions you want for the program.
If you choose 2 the program will force each row and column to have equal numbers of 1's and 0's ( the matrix dimensions will have to be 
pair, also). If you choose 1, this condition won't need to be satisfied. Note that the standard binary puzzle has this restrition, this is,
if you want to solve the binary puzzle according to the standard rules you should use this restrition ( write a 2 after the matrix 
dimensions).
Run the program with ./zeruns <filename>.puz .
A file will be generated with the solutions for the puzzle.
