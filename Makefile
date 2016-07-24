FILES = InjectedLibrary.c InjectXCB.c 

all:
	gcc -g -ldl -lxcb -shared -fPIC -o InjectedLibrary.so $(FILES)
	gcc -lX11 -o XlibExample.out XlibExample.c

distribute:
	tar -cvf tasser-dist.tar.gz ../tasser/

clean:
	rm -f tasser-dist.tar.gz
	rm -f InjectedLibrary.so
	rm -f XlibExample.out
	rm -f *.o
	rm -f *.gch
