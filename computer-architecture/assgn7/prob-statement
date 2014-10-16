CS341, Computer Architecture Lab, Lab 07

Goals

Performance benefits of data forwarding

Understanding the importance of pipeline scheduling

A simple but practical introduction to loop unrolling

Instructions

These exercises are to be done individually.

While you are encouraged to discuss with your colleagues, do not cross the fine line between discussion to understand versus discussion as a short-cut to complete your lab without really understanding.

Create a directory called <rollno>-<labno>. Store all relevant files to this lab in that directory.

In the exercises, you will be asked various questions. Note down the answers to these in a file called “<rollno>-<labno>.txt”.

In some parts of the exercises, you will have to show a demo to a TA; these are marked as such. The evaluation for each lab will be in the subsequent lab, or during a time-slot agreed upon with the TAs. For this evaluation, you need to upload your code as well.

While submitting (on moodle), you have to create a tar.gz or zip of the entire <rollno>-<labno> directory in which all your relevant files reside.

Before leaving the lab, ensure the following:

You have signed the attendance sheet

You have uploaded your submission

Things to ensure during TA evaluation of a particular lab submission:

The TA has looked at your text file with the answers to various questions

The TA has given you marks out of 10, and has entered it in the marks sheet, with his/her signature

You have counter-signed the above-mentioned marks

You have to use the MIPS conventions, unless mentioned otherwise.

House points: Some questions carry house points. For these, you are allowed to work along with others, but only if all of those working together have completed the lab and shown it to the TA. (You can work on it individually, even before finishing the lab completely, but only if you care about house points more than your own marks!). All questions related to house points have to be shown to the instructor (Bhaskar).

Benefits of data forwarding in the MIPS64 pipeline

Convert the following C code into MIPS64 code in file lab7.s

double a[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
double b[] = {2.0, 3.0, 4.0, 5.0, 6.0, 7.0};
double c[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
double d[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
int n = 6;
double alpha = 10.0; 
for (i = 0; i < n; i++) {
c[i] = a[i] * b[i];
d[i] += c[i] * alpha;
}

Question [1 mark]: Run the MIPS64 code on WinMIPS64, with data forwarding enabled. Then subsequently run the same code with data forwarding disabled. What is the number of clock cycles taken for execution in each case. What is the speedup due to data forwarding?

Question [1 mark]: If you blindly translate the C code to MIPS64 assembly code, there must be two branch instructions per loop iteration. You can optimize this to have only one branch operation per loop iteration. Do this optimization. When forwarding is enabled, what is the speedup due to this optimization?

From now onwards, for further modifications, we will always use data forwarding, and use the single-branch-per-iteration version of the code.

Code scheduling for performance improvement

For this exercise, you need to be well aware of the number of cycles taken by each of the execution units in the MIPS64 pipeline implementation. You can learn this from within WinMIPS64 itself.

Schedule the code within the loop above, such that the number of stall cycles is minimized.

Demo to TA [2 marks]: Show to your TA, the unscheduled as well as the scheduled code. And show in WinMIPS64, the performance improvement due to such scheduling.

Demo to TA [1 mark]: Clearly show through comments in your code, as to which are the stalls which you are not yet able to mask through scheduling.

Loop unrolling to reduce loop overhead

Loop unrolling is a performance enhancement technique which trades off code size for code speed. That is, it achieves better execution speed at the cost of potentially larger code size. You can read briefly about loop unrolling in your textbook or online.

You are now going to unroll the unscheduled code. Unroll it twice. That is, two iterations of the earlier loop is now effectively achieved by one iteration of this loop. In your new loop, the loop variable will be incremented by 2 for each iteration.

Demo to TA [2 marks]: Show to your TA, the code with and without loop unrolling. And show in WinMIPS64, the performance improvement due to the unrolling.

Code scheduling after unrolling

A non-trivial benefit of loop unrolling is the large number of opportunities it gives for better code scheduling, to avoid stalls. To do such scheduling, you may have to do some register renaming (find out what it is) to remove anti-dependences (find out what it is).

Demo to TA [2 marks]: Show to your TA, the code with and without scheduling, after unrolling. And show in WinMIPS64, the performance improvement due to the scheduling and unrolling.

Demo to TA [1 mark]: Clearly show through comments in your code, as to which are the stalls which you are not yet able to mask through scheduling.

House points

5 house points: unroll the loop thrice and show the performance benefits of unrolling+scheduling in this case. How does this performance improvement compare with that due to unrolling twice?

5 house points: change your code such that it can handle cases where n is not a multiple of 3. What is the performance improvement now?
