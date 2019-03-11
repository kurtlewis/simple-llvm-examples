# mul_add Example
This example pulls directly from the first tutorial and modifies the code to
compile with LLVM 3.8.

http://releases.llvm.org/2.6/docs/tutorial/JITTutorial1.html

# Compiling
Compile via `make` with `$ make`.

# Running
The code can be directly run via `$ ./mul_add`.

# What Else?
There's not much else to do with this code. It is probably possible to compile
the IR to an object file and link to it, but I won't go that far with this
example.
