# Double-Linked-List-Library
Double Linked List library

There are two types of libraries in Linux environment:

1- static libraries: .a files

1.gcc -c dll.c -o dll.o

2.gcc -c dll_util.c -o dll_util.o

3.ar rs libdll.a dll.o dll_util.o

The last command uses archive (ar) to create static library with object files.

2- dynamic libraries: .so files

1.gcc -c -fPIC dll.c -o dll.o

2.gcc -c -fPIC dll_util.c -o dll_util.o

3.gcc dll.o dll_util.o -shared -o libdll.so

PIC -> position independent code

As a developer, I provide dll.h and libdll.a/libdll.so for a chicken leg developer. The chicken leg developer does not access to the implementation of dll functions but only the signature/declaration of them. They can just put their code (Let's say application.c) and libdll.a/libdll.so to the compiler to get their expected output.

1.gcc -c application.c -o application.o

2.gcc application.o -o exe -L . -ldll   (P.S.1: switch L indicates the path of the library which is current folder in this command)(P.S.2: ldll is the convention name l[nameOfTheLibrary].a instead of lib[nameOfTheLibrary].a)

The approach is the same for dynamic libraries with one step difference

1.gcc -c application.c -o application.o

2.place the libdll.so in default location of shared libraries(/usr/lib or /usr/local/lib) and run "sudo ldconfig"

3.gcc application.o -o exec -ldll

----------------
The most important feature of libraries is that they should be application agnostic, which means they should be implemented in a way that different applications with various data can use the library. This is called Delegation of Application Responsibility to Library. And this is the responsibility of the application to teach the library "how to match the application record" in a data structure which is defined in the library. In other word, the application should teach the library how to manipulate its data. In this piece of code, "search_employee_db_by_key" and "search_student_db_by_key" are the two functions which is responsible for teaching the library how to manipulate their data for employee_t and student_t data structures respectively. 
