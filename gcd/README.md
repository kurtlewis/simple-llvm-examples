# Main example
This example elaborates on the previous two examples by showing an implementation of 
a recursive greatest common denominator (gcd) function. 

This builds IR for the following C code:
```
unsigned gcd(unsigned x, unsigned y) {
  if (x == y) {
    return x;
  } else if (x < y) {
    return gcd(x, y - x);
  } else {
    return gcd(x-y, y);
  }
}
```

# Compiling
See the `Makefile` for compiling instructions. Run with `$ make`

# Running
Generate the IR using `$ ./gcd`. 

Write it to a file by piping stdout, `$ ./gcd > main.ll`.

# Compiling to Assembly
You can use the `llc` command to compile LLVM IR to assembly,
`$ llc main.ll -o main.s`.

# Compiling the Outputted Assembly
Once `llc` has generated assembly, you can compile it using `gcc`.
`$ gcc main.s -o main`

You can check that it works by running it and outputting the return code.
`$ ./main || echo $?`.

# Running the LLVM
You can also directly run the LLVM using the command `lli`, which interprets the
LLVM IR Just In Time (JIT). `$ lli main.ll`. Check that it worked via the
return code, `$ echo $?`.
