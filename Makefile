TARGET: exe
exe: application.o libdll.a
	gcc -g application.o -o exe -L . -ldll
application.o: application.c
	gcc -g -c -I . application.c -o application.o
libdll.a: dll.o
	ar rs libdll.a dll.o
dll.o: dll.c
	gcc -g -c -I . dll.c -o dll.o

clean:
	rm *.o
	rm libdll.a
	rm exe
