all:
	gcc -g -ldl -shared -fPIC -o InjectedLibrary.so InjectedLibrary.c
	gcc -lX11 -o XlibExample.out XlibExample.c

distribute:
	tar -cvf tasser-dist.tar.gz ../tasser/

clean:
	rm tasser-dist.tar.gz
	rm InjectedLibrary.so
	rm InjectedLibrary.o
	rm XlibExample.out
	rm XlibExample.o
