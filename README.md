# Simple LLVM Examples
This repo is home to a few very simple LLVM C++ examples, written for student
lectures in my compiler course. They are meant to accompany a lecture and PPT
which I will hopefully link here at a later date.

These examples have been modified by someone with only rudimentary understanding
of LLVM, and should not be taken as the best way or even good ways to do things.

## Working with these examples
These examples are divided into multiple folders, with a Makefile in each
folder. To run them, use the make file. To setup your environment to roughly
immitiate the one for which these examples are built, here are my steps:
 * install LLVM 3.8. I accomplished this through my package manager, with 
`$ sudo apt install llvm`
 * Verify you have llvm 3.8 `$ llvm-config --version`

## Attribution
These examples are sourced from a [LLVM tutorial for LLVM 2.6](http://releases.llvm.org/2.6/docs/tutorial/JITTutorial1.html).
They have been updated to compile with my version of LLVM, and in some cases
to show specific features.
