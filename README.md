# What It Does #
This project is a port in C of my 2018 project [Java Offline Movie Database](https://github.com/TJEEPOT/Java-OMDB). This port allowed me to understand how C differs from Java and explore more low-level programming concepts outside of OOP.
The program itself takes the same input and provides the same output as the Java variant, but internally it uses struts instead of objects and classes and dynamically allocates memory for holding those structs. 

# What I Learned #
* Use of basic C constructs such as types, expressions, selection, loops, functions, file I/O etc, and how they differ from Java's implementation.
* Use of pointers in addressing memory directly.
* Use of dynamic memory allocation to allow for mutable data structures.
* Use of "class-like" structs to allow abstract data types to be stored with some level of safety.

# Usage Notes #
Ensure films.txt is in your root and compile on your OS of choice. Execute from command line and the results of some given queries will be pushed over standard output. There are no command line arguments for this program.
