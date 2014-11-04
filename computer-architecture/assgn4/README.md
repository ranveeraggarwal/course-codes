CS341, Computer Architecture Lab, Lab 04

Goals

Using a gcc cross-compiler to generate MIPS assembly code

Using the SPIM simulator to do instruction execution counts

Answering performance related questions using measurements

Instructions

These exercises are to be done individually.

While you are encouraged to discuss with your colleagues, do not cross the fine line between discussion to understand versus discussion as a short-cut to complete your lab without really understanding.

Create a directory called <rollno>-<labno>. Store all relevant files to this lab in that directory.

In the exercises, you will be asked various questions. Note down the answers to these in a file called “<rollno>-<labno>.txt”.

In some parts of the exercises, you will have to show a demo to a TA; these are marked as such. The evaluation for each lab will be in the subsequent lab, or during a time-slot agreed upon with the TAs. For this evaluation, you need to upload your code as well.

While submitting (on BodhiTree), you have to create a tar.gz or zip of the entire <rollno>-<labno> directory in which all your relevant files reside.

Before leaving the lab, ensure the following:

You have signed the attendance sheet

You have uploaded your submission

Things to ensure during TA evaluation of a particular lab submission:

The TA has looked at your text file with the answers to various questions

The TA has given you marks out of 10, and has entered it in the marks sheet, with his/her signature

You have counter-signed the above-mentioned marks

You have to use the MIPS conventions, unless mentioned otherwise.

House points: Some questions carry house points. For these, you are allowed to work along with others, but only if all of those working together have completed the lab and shown it to the TA. (You can work on it individually, even before finishing the lab completely, but only if you care about house points more than your own marks!). All questions related to house points have to be shown to the instructor (Bhaskar).

Getting warmed up with the cross compiler

Question [1 mark]: What is a cross-compiler? What is the host platform? What is the target platform? You can use the Internet to learn these.

A gcc cross-compiler for the MIPS target machine has been compiled (yes, the compiler itself was compiled) and made available to you. You should see it in the folder /opt/mips-cross/bin in the NSL machines. Note: gcc stands for GNU C Compiler.

Add the folder /opt/mips-cross/bin to your PATH environment variable.

Important note: you should not use any C or C++ library routines, including I/O routines. The MIPS cross compiler available in the NSL lab does not have support for these.

Download the gcd.c code given in moodle. Make sure you understand the logic.

Compile the above program using the cross compiler mips-linux-gcc, using the “-S” option. The “-S” option specifies that the output of the compiler should be assembly code. You should now have “gcd.s”.

The assembly code in “gcd.s” needs a few modifications before it can be run on spim or xspim.

There are a few assembler directives which spim/xspim do not understand. Use the program “remove_asm_directives.pl”, available on moodle, to remove these. Call the new file as “gcd-noopt.s”.

GCC labeling convention [5 house points]: I don't yet know what the gcc convention is for making labels; if you are the first to find out and tell me, you will get 5 house points (see the rules about working for house points).

You should also define “result” in the data segment. And also define the “syscall_print” procedure. You can use the “asmutils.s” file for these. You can load the files “asmutils.s” and “gcd-noopt.s” one after another in xspim or qtspim.

Demo to TA [1 mark]: You should now be able to load the program on spim or xspim and run it. Run it and show a demo to the TA.

Demo to TA [1 mark]: Comment the gcd-noopt.s assembly code. Specifically comment on the various parts of the stack frame for the gcd function (there may be some parts of the frame which you cannot identify, that is ok). Show the code with the comments to the TA.

Complete frame identification [Upto 5 house points]: If you can identify the entire frame convention (perhaps by using other example programs), you will get 5 house points.

Getting the instruction execution count

Demo to TA [1 mark]: Learn to use “spim” (not xspim or qtspim) from the command-line, and to give commands to make it run “gcd-noopt.s”. Show a demo of this to the TA.

Demo to TA [1 mark]: You can get spim to print each executed instruction by using “step” with a numeric argument. From this output of the spim execution above, get the exact instruction execution count for your program (there may be a few instructions before and after your program, be sure to not count these).

Script to get instruction count [upto 5 house points]: Manually counting the lines from spim's output can be painful. Use the “script” command to automatically copy all printed stuff on the screen to a file (don't use cut-paste from screen, that's a bit painful too). Then write a bash script (python or perl would be an overkill) to count the required number of executed instructions.

GCC compiler optimization

When you look at the compiler generated assembly code, it is obvious that it is inefficient. But it is not so bad as it seems. The compiler has many optimization options. (You can read about these by using “man gcc” if you are interested).

Now compile gcd.c using the “-O1” option; this specifies optimization level-1. You will also have to use the “-fno-delayed-branch” option. As earlier, use “remove_asm_directives.pl” and “asmutils.s”, to generate an assembly file ready for execution in SPIM. Call this new assembly file “gcd-opt.s”.

Demo to TA [1 mark]: Show that this new optimized version works correctly. Also show “gcd-opt.s” with your appropriate comments added.

Question [1 mark]: Compute the instruction execution count for “gcd-opt.s”. How much faster is it compared to “gcd-noopt.s”?

Delayed branches [Upto 5 house points]: Now compile gcd.c with the -O1 option, but without the “-fno-delayed-branch” option. This results in uncovering an optimization feature called delayed branches. Learn at a high level, what delayed branches are (we will learn them in detail anyway later in the course). Observe the use of the delayed branch option. Now by default, the simulation will NOT work correctly. Observe this. Can you use an appropriate SPIM command-line option to execute your code correctly? (I couldn't quite make it work correctly).

Higher optimization levels [Upto 10 house points]: Understand the code produced by optimization flags “-O2” or “-O3”. Get them to execute on SPIM if possible, or explain why it would not be possible.

Answering performance related questions

We now want to use the simulator to compare the performance of a single cycle implementation with a multi-cycle implementation of the MIPS ISA. Assume that a multi-cycle implementation uses a clock which is 5 times faster than a single cycle implementation. Also assume that in a multi-cycle implementation, the number of cycles taken for lw is 5, for sw is 4, for all types of branch instructions is 3, and for all other instructions is 4.

Write a python script (or in any other language, preferably scripting language), which takes the sequence of executed instructions output by using the “step” command in spim in an input file, and computes the number of cycles taken by the MIPS program. The script should compute both (a) the number of cycles taken in a single cycle implementation, as well as (b) the number of cycles taken in a multi-cycle implementation. The script should print these cycle counts, and also how much faster a multi-cycle implementation is compared to a single cycle implementation.

Demo to TA [2 marks]: Show the running of the above script, on the output of “gcd-noopt.s”.

Demo to TA [1 mark]: Show the running of the above script, on the output of “gcd-opt.s”.

More house points

Merge-sort [Upto 10 house points]: Take a C code version of merge-sort. Compile into MIPS assembly code and get it to run correctly.



