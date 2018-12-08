#CS270 - System Software

##Homework \#4

Fall 2018

Due on or before October 28 at 11:59:59 PM

For this assignment you are to build a Linux program that employs
cooperating processes to

accomplish specified tasks. We won't be able to use pipes or sockets
since we haven't covered

them yet, but it should be a fun assignment regardless. Your program
must be written in

C. Your program will be compiled and tested on
cs-course36.cs.uidaho.edu, so you should at

least test it there before you turn it in.

1 The Program

The program that you are going to build is called ptor. A brief
description of ptor follows:

usage: ptor

The ptor program is used to perform tasks that are specified by the
user. The tasks that can be

performed are described in the section titled "User Commands."

1.1 Program Options

The ptor program does not take any command-line options.

1.2 Program Mechanics

The ptor program is composed of two processes that cooperate to
accomplish tasks that are

specified by the user. The two processes are referred to in this
document as the parent and the

child. The typical ptor user has no idea that two processes are used to
accomplish the specified

tasks. The interplay between the parent and child processes are of
particular importance to

you, however, since you will be building ptor rather than just using it.
The parent and child

processes communicate via Linux signals, and send and receive data from
one another using

text files. The ptor program creates two text files, one named
"ptor-parent-NN" where NN

is replaced with the PID of the parent process, and another named
"ptor-child-NN" where

NN is replaced with the PID of the child process. These two files are
hereafter referred to as

ptor-parent-file and ptor-child-file respectively.

The following list specifies the mechanics of the interplay between the
cooperating processes

that are used to execute user commands. This interplay is very
important. You should study

this list carefully, and build your program so that it behaves as
specified in this list.

1.

2.

3.

4.

5.

6.

7.

8.

9.

10.

11.

12.

13.

14.

15.

16.

17.

18.

19.

User launches ptor on the shell command-line

Parent process executes system call to create child process

Parent process waits to receive SIGUSR1 signal from child process

Child process, when ready, sends SIGUSR1 signal to parent process

Parent process emits a command prompt of the form "cmd: " and waits for
the

user to enter a command.

User enters command.

Parent process checks command. If command is "exit", GOTO Step 16 below.

Parent process writes the specified command to ptor-parent-file.

Parent sends SIGUSR1 signal to child.

Child process, upon receiving the SIGUSR1 signal, opens ptor-parent-file

and processes the command contained therein.

Child process interprets and executes the specified command.

Child process writes the result of executing the specified command into

ptor-child-file.

Child process sends signal SIGUSR2 to parent process.

Parent process, upon receipt of the SIGUSR2 signal, opens
ptor-child-file,

reads the result contained therein, and displays the result to the user.

A newline character is appended to the result (if necessary) to keep
things

neat and tidy for the user.

GOTO Step 5 above.

Parent process sends SIGUSR2 signal to child process and waits for child

process to terminate.

Child process, upon receipt of signal SIGUSR2, terminates with an exit

status that is the count of the number of invalid commands that the user

specified during the current session.

When child process terminates, parent process emits message of the form

"ptor: terminating with status NN" where NN is replaced with the exit

status of the child process.

Parent process exits with status NN, the same exit status as the child

process.

1.3 User Commands

The following describes the tasks that ptor can be used to accomplish.
If the user specifies

any command other than those that are listed below, ptor will emit a
message of the form

"ptor: Invalid command" and continue processing commands.

$\bullet$ H fname fname2 This command is used to specify that ptor
should compute and display

the Hamming distance between the files named fname and fname2. The files
named

fname and fname2 must be the same size. If the file sizes differ, ptor
will emit a message

of the form "ptor: H: file sizes differ" to stdout.

If the file sizes do not differ, ptor will compute the bitwise Hamming
distance between

fname and fname2 and print the result to stdout. The result printed will
be of the form

"ptor: H: Hamming distance: NN", where NN is the computed bitwise
Hamming distance.

$\bullet$ O u This command is used to determine the next number that
contains the same number

of '1' bits as u, where u is an unsigned integral number (in decimal)
that is less than or

equal to 1,073,741,824.

The following is an example of this command in action:

-bash-4.1\$ ./ptor

cmd: O 4

ptor: O: 8

cmd: O 17

ptor: O: 18

cmd: O 10

ptor: O: 12

cmd: exit

ptor: terminating with status 0

-bash-4.1\$

$\bullet$ R fname This command is used to specify that ptor should
identify the longest run (as

per Run-Length Encoding, or RLE) of bytes contained in fname. ptor
prints the 0-based

location of the byte that starts the run, the value of the byte
contained within the run,

and the 1-based length of the run to stdout. The location of the run and
the length of the

run are printed in base 10, while the value of the byte contained within
the run is printed

in base 16.

The following is an example of the output by this option when invoked on
a file in which

the longest run starts at 0-based byte 72. The run has a length of 113
bytes, and the value

of the byte contained within the run is the space (32 or 0x20)
character:

ptor: R: 72 0x20 113

$\bullet$ X fname This command is used to specify that ptor should
calculate and print the checksum of the bytes in the file named fname.
The checksum calculated by ptor for this option is a "modular summation"
checksum. This checksum is calculated by summing all

the bytes in the file fname, ignoring any overflow, and then performing
a two's complement of the sum to produce the final result. The result
calculated by this option is printed

to stdout and will be of the form: "ptor: X: 0xXX" where XX (base 16) is
the calculated

checksum for the file fname.

$\bullet$ + b1 b2 This command is used to specify that ptor should add
the two binary numbers

b1 and b2 and print the result. The binary numbers b1 and b2 need not be
the same

length. You may assume that each operand to this command will contain no
more than

2047 bits. However, you must ensure that the algorithm that you use to
perform this

summation does not rely upon this upper bound. The result calculated by
this command

is printed to stdout and will be of the form: "ptor: +: bb" where bb
(base 2) is the

calculated sum. The following is an example of this command in action:

-bash-4.1\$ ./ptor

cmd: + 11101 1

ptor: +: 11110

cmd: +
111111111111111111111111111111111111111111111111111111111111111111 1

ptor: +:
1000000000000000000000000000000000000000000000000000000000000000000

cmd: exit

ptor: terminating with status 0

-bash-4.1\$

$\bullet$ ! This command is used to specify that ptor should emit a
message containing the count

of valid and invalid commands that have been encountered in the current
session. The

message emitted by this command will be of the form: "ptor: !: X valid Y
invalid"

where X and Y are the count of valid and invalid commands, respectively,
that have been

encountered so far. This count includes the ! command that is currently
executing. The

following is an example of this command in action:

-bash-4.1\$ ./ptor

cmd: R /tmp/ktpg.svg

ptor: R: file not found

cmd: R \~/tmp/ktpg.svg

ptor: R: 148915 0xec 2177

cmd: x \~/tmp/ktpg.svg

ptor: Invalid command

cmd: X /tmp/kipg.svg

ptor: X: 0x3a

cmd: !

ptor: !: 4 valid 1 invalid

cmd: exit

ptor: terminating with status 1

-bash-4.1\$

2 Submitting Your Program

You must submit your program using cscheckin. You must create and submit
a Makefile

with your source code. This Makefile will be used to build your program.
Please place

your code files and Makefile in a tar archive named hw4.tar. Please do
not compress your

program using zip, gzip, winzip, winrar, or any other compression tool
before or after making a tar archive for submission. When you have
finished testing your program, please use

cscheckin to submit the hw4.tar file to your instructor.

3 Grading

You must do your own work for this assignment. This is not a "team
programming" exercise.

All code submitted for this assignment must be entirely your own. Your
program must use

cooperating processes and behave precisely as specified in this
assignment. Your program will

be evaluated for completeness, clarity, efficiency, and compliance with
the specified requirements.
