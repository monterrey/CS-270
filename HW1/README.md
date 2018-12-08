# CS270 - System Software

## Homework \#1

Fall 2018

Due on or before Thursday, September 6 at 11:59:59 PM

Write a single C function that will separate a line of input into words
(or tokens). Your function

must have the following prototype:

int makearg(char \*s, char \*\*\*args); // or int makearg(char s\[\],
char \*\*args\[\]);

The prototype of this function is correct. You may not change the
prototype of this function

for any reason. This function must accept a C string and a pointer to a
pointer to a pointer

to char (i.e., a pointer to the same type as argv in a C program). Your
function will "return"

the pointer defined to point to an array which points to the separate
tokens that were found

in the line of input, and will explicitly return an int which will be
the number of tokens your

makearg function found in the input string. If some problem occurred
during the operation of

your makearg function, it should return the value -1.

For example, if you were to call your makearg function using the
following code:

char \*\*argv, str\[\] = "ls -l file";

int argc;

argc = makearg(str, &argv);

your makearg function should produce the following situation in memory:

You should build a program that contains a main function as well as the
specified makearg

function. Your main function will act as the "driver" of the makearg
function. Your main

function should be built so that it reads a line of data from the user
and then calls the makearg

function, passing the line of data read, and the address of the place
where the makearg function

is to store the tokens it finds. When the makearg function finishes,
your main function must

print the number of arguments returned by makearg, followed by each word
(or token) placed

into the buffer by your makearg function. Your main function must print
each word, on a

separate line, that was found by the makearg function.

The printing of words must appear within the main function. If you print
words within the

makearg function you will likely fail this assignment. Printing the
words in main is necessary

to prove that the correct sequence of tokens has been properly passed
from makearg back to

main. The passing of arguments into and out of makearg is an integral
part of this assignment.

Note that, as in the example above, the value of the argv pointer
argument is undefined when

it is passed to the makearg function. Your makearg function must
allocate any dynamic memory necessary for use when parsing the input
string. The array used for the "unparsed" string

need not be dynamically allocated.

Your main function should look very similar to this:

int main()

{

int argc;

char \*\*argv;

char input\_line\[256\];

printf("Gimme a line of input: ");

/\*

\* Place your code to read a line of input here\...

\*/

argc = makearg(input\_line, &argv);

printf("That line contains %d words. Here they are:$\backslash$n",
argc);

/\*

\* Place your code to print each "word" on a separate line here\...

\*/

return 0;

}

The following is an example of how your program should behave:

-bash-4.1% ./a.out

Gimme a line of input: gcc myfile.o -Wl,-M -o myhw1

That line contains 5 words. Here they are:

gcc

myfile.o

-Wl,-M

-o

myhw1

-bash-4.1%

You must do your own work for this assignment. This is not a "team
programming" exercise.

All code submitted for this assignment must be entirely your own.

Please place your code in a single file named hw1.c. Your program will
be compiled using

gcc and tested on wormulon, so you should at least test your program on
wormulon. When

you have finished testing your program, please use cscheckin to submit
the hw1.c file to your

instructor.
