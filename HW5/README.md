CS270 - System Software

Homework \#5

Fall 2018

Due on or before November 30 at 11:59:59 PM

For this assignment you are to modify and extend an existing Linux
program that uses sockets

to connect to a given http server. The program that you are to modify
and extend is located on

the course website. Your program will be compiled and tested on
cs-course36.cs.uidaho.edu,

so you should at least test it there before you turn it in.

1 The Current Program

The program that you are going to modify and extend is currently called
get-ex. The get-ex

program uses sockets to open a connection to www.example.com port 80 and
read the / resource

located on that site. If you compile and run get-ex on
cs-course36.cs.uidaho.eduyou will

see the following:

-bash-4.1\$ gcc get-ex.c -o get-ex

-bash-4.1\$ ./get-ex

HTTP/1.1 200 OK

Cache-Control: max-age=604800

Content-Type: text/html; charset=UTF-8

Date: Thu, 01 Nov 2018 21:53:55 GMT

Etag: "1541025663+ident"

Expires: Thu, 08 Nov 2018 21:53:55 GMT

Last-Modified: Fri, 09 Aug 2013 23:54:35 GMT

Server: ECS (oxr/8313)

Vary: Accept-Encoding

X-Cache: HIT

Content-Length: 1270

Connection: close

$<$!doctype html$>$

$<$html$>$

$<$head$>$

$<$title$>$Example Domain$<$/title$>$

$<$meta charset="utf-8" /$>$

$<$meta http-equiv="Content-type" content="text/html; charset=utf-8"
/$>$

$<$meta name="viewport" content="width=device-width, initial-scale=1"
/$>$

$<$style type="text/css"$>$

body {

background-color: \#f0f0f2;

margin: 0;

padding: 0;

font-family: "Open Sans", "Helvetica Neue", Helvetica, Arial,
sans-serif;

}

div {

width: 600px;

margin: 5em auto;

padding: 50px;

background-color: \#fff;

border-radius: 1em;

}

a:link, a:visited {

color: \#38488f;

text-decoration: none;

}

\@media (max-width: 700px) {

body {

background-color: \#fff;

}

div {

width: auto;

margin: 0 auto;

border-radius: 0;

padding: 1em;

}

}

$<$/style$>$

$<$/head$>$

$<$body$>$

$<$div$>$

$<$h1$>$Example Domain$<$/h1$>$

$<$p$>$This domain is established to be used for illustrative examples
in documents. You may u

domain in examples without prior coordination or asking for
permission.$<$/p$>$

$<$p$>$$<$a href="http://www.iana.org/domains/example"$>$More
information\...$<$/a$>$$<$/p$>$

$<$/div$>$

$<$/body$>$

$<$/html$>$

final status: 0.

read 1611 chars.

-bash-4.1\$

You should ensure that get-ex behaves as shown above before you begin
working on this

assignment. Dates and times will change depending on when you run the
command, but the

rest should be very similar.

2 Your Program

The current get-ex program is not very generalized and is contained
within a single function.

Your goal in this assignment is to modify and extend get-ex to produce a
program named

get-any. Your get-any program will be able to initialize and connect to
any valid website

specified by the user and perform a HTTP GET to request any valid
resource specified by the

user on that website. The current get-ex program only uses HTTP 1.1. You
can continue to

use this, or can change your code to use HTTP 2.0.

Your get-any program will display to stdout the HTTP data that is
received from the requested

website, just as the current get-ex program does. In addition to
displaying the requested data,

your program will gather information about the data received or perform
transformations on

that data.

2.1 Program Options

The syntax of the get-any program is as follows:

get-any hostname resource -\[FIS\]

The hostname and resource arguments are required and must be specified
in the order shown.

The hostname argument is the name of the web server that the user wants
to connect to. The

resource argument is the name of the resource that the user wants to
retrieve from the requested server. The other arguments to get-any are
optional, but if any appear, only one may

appear at any given time. These options specify which transformations
are to be performed on

the data, or which information about the data is to be gathered and
presented. These options

are:

$\bullet$ F This option is used to specify that a frequency count of all
bytes of data retrieved from

the host is to be calculated and displayed to stdout after the data that
was retrieved is

displayed to stdout.

$\bullet$ I This option is used to specify that an inverted sequence of
all bytes of data retrieved

from the host is to be displayed to stdout after the data that was
retrieved is displayed

to stdout.

$\bullet$ S This option is used to specify that an sorted sequence of
all bytes of data retrieved

from the host is to be displayed to stdout after the data that was
retrieved is displayed

to stdout.

2.2 Examples

This section contains examples describing how your get-any program
should behave. Please

examine these examples closely and do your best to mimic the behavior
shown herein.

2.2.1

-bash-4.1\$ get-any www.wut.com /public.html

This command will provoke get-any to open a connection to www.wut.com on
port 80 and attempt to retrieve the resource /public.html. The get-any
command will then display whatever the result of the HTTP GET is to the
computer screen and immediately exit. An example of

what might appear as a result of using this command is shown below.

-bash-4.1\$ get-any en.wikipedia.org /

HTTP/1.1 301 TLS Redirect

Date: Thu, 01 Nov 2018 22:51:49 GMT

Server: Varnish

X-Varnish: 865522146

X-Cache: cp2013 int

X-Cache-Status: int-front

Set-Cookie:
WMF-Last-Access=01-Nov-2018;Path=/;HttpOnly;secure;Expires=Mon, 03 Dec
2018 12:00:

Set-Cookie:
WMF-Last-Access-Global=01-Nov-2018;Path=/;Domain=.wikipedia.org;

X-Client-IP: 98.145.187.19

Location: https://www.wut.com/

Content-Length: 0

Connection: close

-bash-4.1\$

2.2.2

-bash-4.1\$ get-any www.doesntexist.com /index.html -F

This command will provoke get-any to open a connection to
www.doesntexist.com on port

80 and attempt to retrieve the resource /index.html. The get-any command
will then display

whatever the result of the HTTP GET is to the computer screen, will then
display a line of the

form "get-any: F:" and will then display a frequency count of all bytes
that were contained

in the data that was retrieved. This frequency count is of the form

value=count

value=count

value=count

\...

and is listed in descending order based upon the count field. An example
of what might

appear as a result of using this command is shown below.

-bash-4.1\$ get-any www.freqfreq.org /public.html -F

HTTP/1.1 301 Moved Permanently

get-any: F:

1=3

e=3

P=2

T=2

\...

-bash-4.1\$

Use linked list then

sort using merge

sort

2.2.3

-bash-4.1\$ get-any www.memecenter.com /index.html -I

This command will provoke get-any to open a connection to
www.memecenter.com on port 80

and attempt to retrieve the resource /index.html. The get-any command
will then display

whatever the result of the HTTP GET is to the computer screen, will then
display a line of the

form "get-any: I:" and will then display the inverted data to the
computer screen. An

example of what might appear as a result of using this command is shown
below.

-bash-4.1\$ get-any www.memecenter.com /index.html -I

HTTP/1.1 301 Moved Permanently

get-any: I:

yltnenamreP devoM 103 1.1/PTTH

-bash-4.1\$

2.2.4

-bash-4.1\$ get-any www.sortsort.net /index -S

This command will provoke get-any to open a connection to
www.sortsort.net on port 80

and attempt to retrieve the resource /index. The get-any command will
then display whatever the result of the HTTP GET is to the computer
screen, will then display a line of the form

"get-any: S:" and will then display the sorted data to the computer
screen. An example of

what might appear as a result of using this command is shown below.

-bash-4.1\$ get-any www.sortsort.com /index.html -S

HTTP/1.1 301 Moved Permanently

get-any: S:

./01113HMPPTTadeeelmnnortvy

-bash-4.1\$

3 Submitting Your Program

You must submit your program using cscheckin. You must create and submit
a Makefile

with your source code. This Makefile will be used to build your program.
Please place

your code files and Makefile in a tar archive named hw5.tar. Please do
not compress your

program using zip, gzip, winzip, winrar, or any other compression tool
before or after making a tar archive for submission. When you have
finished testing your program, please use

cscheckin to submit the hw5.tar file to your instructor.

4 Grading

You must do your own work for this assignment. This is not a "team
programming" exercise.

All code submitted for this assignment must be entirely your own. Your
program will be evaluated for completeness, clarity, efficiency, and
compliance with the specified requirements.

Please ensure that you comment your code and include your name and
course information in

at least one comment at the top of the file in which your main function
appears. Something

like this would be nice:

/\*

\* Your Name

\* CS 270

\* Homework 5

\* The date

\*/
