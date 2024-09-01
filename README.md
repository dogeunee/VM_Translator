# VM_Translator
VM_Translator for Project7 and 8 of Nand2Tetris.

## Successfully passed all testes provided from the official Nand2Tetris IDE.

There are much better Cpp based VM_translater that has good error handeling, organized code and overall better optimazation.
Hope this helps as a somewhat different surplus sorce to anybody out there.
Here are some small errors I found while I was debugging

## TIPS
### 1.BasicLoop, FibonacciSeries, SimpleFunction
These are realitivly easy because it only tests branching and function, return which is straight foward if u read and write as mentiond in the course. if ur not sure just check my code.

### 2.NestedCall
I used R13 and R14 instead of Temp(RAM0,1,2...) u could only use those as the other temp could be used and possibly cause overwriting.

### 3.FibonacciElement
I replaced JGT into JNE. I was confused with true and false which are -1 and 0 respectfully. Or was it the other way? I forgot please check by doing a simple test with the VMemulator.

### 4.StaticsTest
I was having problems that the fstream operations were not picking up the last line. In the function hasMoreLines in Parser.cpp I used the ofile object itself instead of ifile.eof().
