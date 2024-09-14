/*****************************************************************************
TITLE: Claims																																
AUTHOR: VISHWAS S - 2201CS78
Declaration of Authorship
This txt file, claims.txt, is part of the assignment of CS209 at the 
department of Computer Science and Engg, IIT Patna . 
*****************************************************************************/

Files:
==========
*All the files I submitted, asm.cpp, emu.cpp and claims.txt, have my name and student id at the start, along with a declaration of authorship.

*The evidence for Assembler including the output files from the 4  test examples has also been uploaded. They are test1(3 output files), test2(3 output files), test3(3 output files) and MyBubbleSort(3 output files). All the test files have been tested and work properly.

*Both of my c++ programs did not show any errors and warnings when I compiled it with g++ asm.cpp -o asm and g++ emu.cpp -o emu.

*Two programs are compilable with g++ asm.cpp -o asm and g++ emu.cpp -o emu.


=============================
Program format and structure:
=============================
1. The assembler:

    * uses a single routine for both passes.
    * detects label erros.
    * consistent and sensible formatting with sensible program structure. 
    * sensible variable, function & type names with explanatory comments.
		* advanced listing file.
		* assembles test programs.
	  * can implements and demonstrates the instruction SET.

2. The emulator:


    * loads object file, 
    * by giving the instructions like "-befor/-after" , the program can produce memory dump before/after execution. Using -isa shows what all the commands mean and -read/-write can be used 	to check the memory reads and writes
    * by giving the instruction like "-trace", the program prints the result of program executed.
    * detects errant programs.

=============================
Testing:
=============================
 
1. The assembler:

I have tested  4 examples and the ones given in the pdf. The errors only occurred in the files test2.asm given and the programs immediately stopped on the second pass and .o file was not created. 

The others were tested without any errors detected and produced three output files, listing file, 
error log file and machine readable object file, for each example.


1)
#Input: ./asm test1.asm
#Output: 
a. test1.lst
b. test1.log (without any error messages)
c. test1.o

2)
#Input:./asm test2.asm
#Output: 
a. test2.lst
b. test2.log (without any error messages)
c. test2.o

3)
#Input:./asm test3.asm
#Output: 
a. test3.lst
b. test3.log (without any error messages)
c. test3.o

4)
#Input:./asm MyBubbleSort.asm
#Output: 
a. MyBubbleSort.lst
b. MyBubbleSort.log (without any error messages)
c. MyBubbleSort.o


2. The emulator:

I have tested all the 4 examples as well as the ones given in the pdf
We can run the following commands in the command prompt to use the emulator
Commands are
-trace  show instruction trace
-read   show memory reads
-write  show memory writes
-before show memory dump before execution
-after  show memory dump after execution
-wipe   wipe written flags before execution
-isa    display ISA

the format to use the emulator is as follows
Expected format << ./emu [command] filename.o

1)INPUT:.o test01.o
./emu -trace test08.o
PC = 00000001, SP = 00000000, A = 00000002, B = 00000000 ldc 00000002
PC = 00000002, SP = 00000000, A = 00000004, B = 00000002 ldc 00000004
PC = 00000003, SP = 00000000, A = 00000006, B = 00000002 add
PC = 00000004, SP = 00000000, A = 00000002, B = 00000002 stl 00000000
PC = 00000005, SP = 00000000, A = 00000002, B = 00000002 HALT
Program execution finished!
OUTPUT:Trace File Generated: test08.trace
and so on
