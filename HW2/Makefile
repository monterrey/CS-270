#Homework assignment #2

program: hw2.o quickSort.o bubbleSort.o insertionSort.o
	gcc -o hw2 -Wl,-M hw2.o quickSort.o bubbleSort.o insertionSort.o > hw2.map
hw2.o: hw2.c
	gcc -c hw2.c
quickSort.o: quickSort.c
	gcc -c quickSort.c 
bubbleSort.o: bubbleSort.c
	gcc -c bubbleSort.c 
insertionSort.o: insertionSort.c
	gcc -c insertionSort.c 
run:
	./hw2