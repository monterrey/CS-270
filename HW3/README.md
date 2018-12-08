# CS270 - System Software

## Homework \#3

Fall 2018

Due on or before Monday, October 8 at 9:00 AM

For this assignment you are to build a small memory management library
for a local company.

The library will be called qmem, and the company would like the library
to be delivered in

a library archive file named qmem.a. Your library will be written in C,
and will serve as a

"wrapper" for functionality provided by the standard C memory management
functions. The

company expects to use your library in the development of multiple
applications. Your library

will conform to an interface that is specified by the company, and will
include functionality

requested by the company.

1 The qmem Interface

The qmem interface consists of 3 allocation functions, 1 deallocation
function, and 6 utility functions. A description of each of these
functions appears in this section. It is of paramount importance that
the interface to your library conforms precisely with the interface as
described

in this section.

1.1 Allocation Functions

1.1.1

int qmem\_alloc(unsigned num\_bytes, void \*\* rslt);

This function will attempt to allocate num bytes bytes of data and
assign the address of the

data allocated to the location whose address is stored in rslt. If the
address of the location in

which to store the result is NULL, this function will return -1. If
allocation of the memory was

successful, this function will return 0. Otherwise, this function will
return -2. A typical usage

of the qmem alloc function is shown below.

int errc;

struct qbuf { int idx; char data\[256\] };

struct qbuf \* p = NULL;

errc = qmem\_alloc(sizeof(struct qbuf), (void \*\*)&p);

if (errc != 0)

/\* an error occurred \*/

else

/\* everything is fine \*/

1.1.2

int qmem\_allocz(unsigned num\_bytes, void \*\* rslt);

This function will attempt to allocate num bytes bytes of data and
assign the address of the

data allocated to the buffer whose address is stored in rslt. If
allocation of the memory was

successful, this function will initialize all bytes of the allocated
memory to 0 and will return

0\. If the address of the location in which to store the result is NULL,
this function will return

-1. If there is any other error, this function will return -2. Please
see the usage example for the

qmem allocv function.

1.1.3

int qmem\_allocv(unsigned num\_bytes, int mark, void \*\* rslt);

This function will attempt to allocate num bytes bytes of data and
assign the address of the

data allocated to the buffer whose address is stored in rslt. If
allocation of the memory was

successful, this function will initialize all bytes of the allocated
memory to the value of mark

and will return 0. If the address of the location in which to store the
result is NULL, this function will return -1. If there was any other
error, this function will return -2. Please note that

although mark is an int, only the lower 8 bits of mark will be used to
initialize each byte of

allocated data. A typical usage of the qmem allocv function is shown
below.

int errc;

struct qbuf { int idx; char data\[256\] };

struct qbuf \* p = NULL;

errc = qmem\_allocv(sizeof(struct qbuf), 'q', (void \*\*)&p);

if (errc != 0)

/\* an error occurred \*/

else

/\* everything is fine \*/

1.2 Deallocation Functions

int qmem\_free(void \*\* data);

This function will attempt to relinquish the memory that was previously
allocated via a qmem

allocation function. A pointer to the address of the first byte of data
to be relinquished is

passed in to this function. If the memory was successfully relinquished,
this function set the

address of the first byte of data that is passed in via the data
argument to NULL and will

return 0. If the address of the first byte of data is NULL, this
function will return -1. If the

pointer to the address of the first byte of data is NULL, this function
will return -2. If the data

pointed to was not previously allocated via a qmem allocation function,
this function will return

-3 and will not attempt to relinquish the memory in question. A typical
usage of the qmem free

function is shown below.

int errc;

char \* p;

\...

errc = qmem\_free(&p);

if (errc != 0)

/\* an error occurred \*/

else {

/\* everything is fine \*/

if (p != NULL)

printf("Ooops! qmem\_free didn't set address to NULL$\backslash$n");

}

1.3 Utility Functions

1.3.1

int qmem\_cmp(void \* p1, void \* p2, int \* diff);

This function will attempt to compare the contents of the memory pointed
to by p1 with the

contents of the memory pointed to by p2. Both regions of memory (p1 and
p2) must have

previously been allocated using a qmem allocation function. The number
of bytes compared in

the two regions will be the smaller in size of the two regions that are
passed in as arguments.

If the pointer p1 is NULL, this function will return -1. If the pointer
p2 is NULL, this function

will return -2. If the region of memory pointed to by p1 has not been
allocated using a qmem

allocation function, this function will return -3. If the region of
memory pointed to by p2 has

not been allocated using a qmem allocation function, this function will
return -4. If this function

is able to perform the requested comparison, it will return 0 and the
difference between the

first pair of bytes that differ in p1 and p2 will be written into the
location pointed to by the diff

argument. If the contents of the regions of memory is equivalent, a 0
will be written into the

location pointed to by the diff argument. A typical usage example of
this function is shown

below.

int errc;

int difference;

errc = qmem\_cmp(buff1, buff2, &difference);

\...

if (errc != 0)

/\* an error occurred \*/

else

/\* everything is fine \*/

printf("difference between buff1 and buff2: %d$\backslash$n",
difference);

1.3.2

int qmem\_cpy(void \* dst, void \* src);

This function will attempt to copy the contents of the region of memory
pointed to by src into

the region pointed to by dst. Both src and dst must point to regions of
memory that were

previously allocated using a qmem allocation function. The sizes of the
regions of memory

pointed to by src and dst must be the same. If the copy was successful,
this function will

return 0. If the pointer dst is NULL, this function will return -1. If
the pointer src is NULL,

this function will return -2. If the region of memory pointed to by dst
has not been allocated

using a qmem allocation function, this function will return -3. If the
region of memory pointed

to by src has not been allocated using a qmem allocation function, this
function will return -4. If

both src and dst refer to the same region of memory, this function will
return -5. If the size of

the region pointed to by src is not the same size as the region pointed
to by dst, this function

will return -6.

1.3.3

int qmem\_scrub(void \* data);

This function will attempt to initialize the contents of the memory
pointed to by data to 0.

The pointer data must refer to a region of memory that was allocated
using a qmem allocation

function. If this function was able to successfully initialize to 0 all
the memory in the region

pointed to by data, this function will return 0. If the pointer data is
NULL, this function will

return -1. If the region of memory pointed to by data was not previously
allocated using a

qmem allocation function, this function will return -2. A typical usage
example of this function

is shown below.

int errc;

struct qbuf { int idx; char data\[256\] };

struct qbuf \* p = NULL;

errc = qmem\_alloc(sizeof(struct qbuf), (void \*\*)&p);

if (errc != 0)

/\* an error occurred \*/

else

{

/\* everything is fine \*/

errc = qmem\_scrub(p);

if (errc != 0)

printf("Couldn't scrub %p. Reason: %d$\backslash$n", p, errc);

}

1.3.4

int qmem\_scrubv(void \* data, int mark);

This function will attempt to initialize the contents of the memory
pointed to by data to the

value of the argument mark. Please note that although mark is an int,
only the lower 8 bits

of mark will be used to initialize each byte of the contents of memory
pointed to by data.

The pointer data must refer to a region of memory that was allocated
using a qmem allocation

function. If this function was able to successfully initialize to mark
all the memory in the region

pointed to by data, this function will return 0. If the pointer data is
NULL, this function will

return -1. If the region of memory pointed to by data was not previously
allocated using a

qmem allocation function, this function will return -2. A typical usage
example of this function

is shown below.

int errc;

struct qbuf { int idx; char data\[256\] };

struct qbuf \* p = NULL;

errc = qmem\_alloc(sizeof(struct qbuf), (void \*\*)&p);

if (errc != 0)

/\* an error occurred \*/

else

{

/\* everything is fine \*/

errc = qmem\_scrubv(p, 'q');

if (errc != 0)

printf("Couldn't scrub %p to 'q'. Reason: %d$\backslash$n", p, errc);

}

1.3.5

int qmem\_size(void \* data, unsigned \* rslt);

This function will attempt to determine the number of bytes that were
allocated to the region

pointed to by data. The region pointed to by data must have been
previously allocated using

a qmem allocation function. If successful, this function will write the
number of bytes that were

allocated to the region pointed to by data into the buffer pointed to by
rslt and will return

0\. If the pointer data is NULL, this function will return -1. If the
pointer rslt is NULL, this

function will return -2. If the region pointed to by data was not
previously allocated using a

qmem allocation function, this function will return -3. A typical usage
of this function is shown

below.

int errc; unsigned n;

struct qbuf { int idx; char data\[256\] };

struct qbuf \* p = NULL;

errc = qmem\_alloc(sizeof(struct qbuf), (void \*\*)&p);

if (errc != 0)

/\* an error occurred \*/

else

{

errc = qmem\_size(p, &n);

if (errc != 0)

printf("Couldn't get size of p. Reason: %d$\backslash$n", errc);

else if (n != sizeof(struct qbuf))

printf("Sizes don't match.$\backslash$n");

else

/\* everything is fine \*/

}

1.3.6

int qmem\_stats(unsigned long \* num\_allocs, unsigned long \*
num\_bytes\_alloced);

This function will attempt to produce statistics regarding qmem usage at
the time of the call

to this function. If successful, this function will write the total
number of allocations that

have been made for all qmem allocation functions into the region of
memory pointed to by

num allocs and the total number of bytes allocated for those allocations
at the time of the

call to this function into the region of memory pointed to by num bytes
alloced and will

return 0. If the pointer num allocs is NULL, this function will return
-1. If the pointer

num bytes alloced is NULL, this function will return -2. A typical usage
of this function

is shown below.

unsigned long u1, u2;

errc = qmem\_stats(&u1, &u2);

if (errc != 0)

/\* an error occurred \*/

else

{

printf("Total \#allocations so far: %ld$\backslash$n, u1);

printf("Total \#bytes allocated so far: %ld$\backslash$n", u2);

}

2 The qmem Implementation

Your customer has no particular requirements for your implementation of
the qmem library. As

long as your interface meets the specified requirements, your customer
will be happy. You

are, however, prohibited from placing an artificial limit on the number
of allocations or deallocations that can be performed using your qmem
library. As long as sufficient memory exists

on a given system, programs built with your qmem library should grant
allocation or deallocation requests. You are encouraged to be creative
and experiment with different approaches to

solving the problems at hand within the implementation of qmem.

3 Requirements

Your customer wants a library named qmem.a as the primary deliverable.
They will be building

programs using your library, and will link against the contents of the
library that you provide.

You must build your qmem.a library using the Linux ar command. A typical
command that

they will use to compile a program using your library is shown below.

\$ gcc product.c qmem.a -o product

Your customer also wants a header file named qmem.h containing all the
interface functions for

your qmem library so that they can \#include "qmem.h" when compiling
programs using your

library.

In addition to the required deliverables requested by the company, you
are to submit all source

code files that you used to build your library, along with a complete
and working Makefile to

your instructor. This Makefile must correctly build all source code and
the qmem.a library. You

should create a .tar archive named hw3.tar to submit these deliverables
to your instructor.

Please do not compress your program using zip, gzip, winzip, winrar, or
any other compression tool before or after making a .tar archive for
submission. When you have finished testing

your program, please use cscheckin to submit the hw3.tar file to your
instructor.

4 Grading

You must do your own work for this assignment. This is not a "team
programming" exercise.

All code submitted for this assignment must be entirely your own. Your
library must behave

precisely as specified in this assignment. Your source code will be
evaluated for completeness,

clarity, efficiency, and compliance with the specified requirements. You
should comment your

code clearly, and include your name in a comment at the top of the
qmem.h interface file. Your

program will be compiled using gcc and tested on wormulon, so you should
at least test your

program on wormulon.
