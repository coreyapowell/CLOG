# CLOG
a CLOGGER and a FLOGGER for CLOGGING

CLOG is a c preprocessor macro to log that certain code has been reached.
FLOG is a c preprocessor macro to explain every intricuit step of the code. FLOGs emit the line number.
They are both only printf functions .....however! .....

a CLOGGER is a preprocessor #define of a standard pipe. The default standard pipe is stderr, but your program can immediately redefine that to be a null FILE. If CLOGGER is null, then we don't CLOG until a value is established.
CLOGGING is a flag that indicates whether or not we are CLOGGING at all. If the CLOGGING flag is undefined or set to 0, and the file #include "CLOG.h" is loaded again, then the CLOG and FLOG macros become undefined. Well, rather than 'undefined' they become empty.

unclog is a program that scans a file (the first parameter), let's say a file.mess.c ... a mess.c file full of CLOGs. it writes a second file, the second parameter, which would be a normal c file. the third parameter is a comma separated list of macro qualifier names ... like "CLOG,FLOG,BLOG". unclog strips out any lines that include any of the macro qualifiers. Those are the CLOGS, and unclog removes any lines that contain them. Also, unclog removes any following lines until the ; terminator is found. The entire lines are removed, so CLOGs can be multiple lines, but they should not share any lines with code you don't want removed.

The end result is three levels of indirection. Complicated code can be riddled with CLOGS, a rightly disorderly mess.c file! 
1) Redefining the CLOGGING flag and including the file before an inspected function and then after the function will only activate the CLOGS in that body of code. In this case, no code is emitted except the inspected code.
2) Defining CLOGGER allows modules to assign a CLOGGER that CLOGS or not. Setting CLOGGER to null silences the CLOGS. In this case, code branches around the FILE handle status. But it also allows shared libraries to join their CLOGGERS together.
3) Removing the macros entirely makes your code ready for deployment, robbed and comment free! That also leaves base code in a state that other macros can be assigned to these values to generate documentation and modules, etc etc.

It's a simple home-rolled logging system, but it's quicker than tacking through a debugger. It's also funny the first time someone finds it in the code.
