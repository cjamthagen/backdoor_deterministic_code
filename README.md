Hiding code in deterministically built binaries - Proof-of-Concept - Linux/x86
==============================================================================

What is this?
-------------
This Proof-of-Concept code shows an example methodology of how an attacker can insert hidden code that is persistent in deterministically built binaries.

Files
-----
The files in this repo include
* **assemblybackdoor.c** - This is the backdoor assembly code used. It is based on the backdoor code found at https://github.com/geyslan/SLAE/blob/master/1st.assignment/shell\_bind\_tcp.asm. The code is heavily modified to work in our case. The code will give shell access to a remote attacker connecting on TCP port 32768.
* **main.h** - Includes macro definitions, such as x86 opcodes, and data structure definitions used to implement the hidden code.
* **step1.c** - Hidden code deployed by assigning specific values in specific indices in a multi-dimensional  array.
* **step2.c** - Hidden code deployed by assigning specific values in specific struct members designed to make the compiler generate the necessary displacement values. step2.c adds a layer of obfuscation over step1.c. Struct members variable names can be changed to whatever the attacker likes, thus avoids showing an arbitrary array access as in step1.c.
* **step3.c** - Adds functionality to the program by replacing the FILLER macros with the same amount of bytes of relevant code. Additional functions are added above p1() and below epilogue(). Code placed here does not interfere with the hidden code constructs. (TODO)
* **step4.c** - Trigger based bug implemented which starts executing the HEP (Hidden Execution Path) once triggered. (TODO)

Compatability
-------------
This code only works on Linux-based OSes. Only compilers known to work with this code is GCC v4.9.1 and v4.9. 2. Other versions of GCC may or may not work.

Paper
-----
Under review.
