# CS270 - System Software

## Homework \#2

Spring 2018

Due on or before Thursday, September 20 at 9:00 AM

Write a C program that has an array containing 256K (262144) strings,
reads data from a file

named hw2data.txt to populate the array, and sorts the array using three
different methods:

the bubble sort, the insertion sort and the quicksort. The data file
hw2data.txt that your program

most read from is found on the course website. Each string in your array
should contain no

more than 256 characters, including a terminal NUL. Your program should
re-populate the

array from the file hw2data.txt each time that it is to be sorted. Write
each sort as a separate

function, and place each sort function (as well as main and any other
functions) in its own file.

Placing each function in a separate file will make it easier for you to
answer the questions in

this assignment. The array of strings should be "global" in order to
make it more visible in the

resulting ELF file.

Compile your test program (using gcc on Linux) and generate the linker
map for each separate

function, and for the complete executable. Then determine the following:

1\. The size of each function, in decimal.

2\. The address where each function is located in memory, in hexadecimal.

3\. The name and address of the entry point for the entire program.

4\. The locations and names of any functions from "standard" C libraries
that are linked

with your file.

5\. The locations and sizes (in decimal) of the data sections used by
your program.

6\. The time (in seconds) that each of your sort functions takes to sort
the data. You'll want

to instrument your program code to determine these times. You might
consider using

the time system call and the difftime library function to accomplish
this.

After you have answered these questions, recompile your program using
the -O ("dash-oh")

option, then answer the same questions as above.

In order to submit your results, you must create a subdirectory named
hw2 containing your

source files and a short report of your findings as described above. In
your report, please be

clear and concise, and use complete English sentences where possible.

When you are finished, use the Linux tar command to create an archive (a
.tar file) of the

entire hw2 subdirectory containing your program files, your report, and
a complete Makefile

sufficient for building your program. Please use cscheckin to submit the
hw2.tar file to your

instructor.
