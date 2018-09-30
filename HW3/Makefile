qmem: qmem.c
	gcc-8 -c qmem.c
clean:
	rm *.o
test: qmem.o test.c
	gcc -o rslt test.c qmem.o
	./rslt 
