[Question]
At what point in your tree of call activations will the stack depth be the
maximum (just with respect to the recursive calls)? Insert a breakpoint at a place in the code
where the stack is at its maximum size. Examine the stack and explain its contents with reference
to your code. Point out the various call activation records. Hint: you have to insert a breakpoint at
an appropriate place in the mergesort procedure, not the merge procedure.

[Answer]
When we reach the base case for mergesort, i.e., when recursion depth would be maximum, then the number of variables stored in the stack would be the highest.

Putting a breakpoint there gives out the expected result -- maximum depth of the stack.

The stack contants are the contents put by the code, i.e., the arguments from the previous recursion calls, and the stores variable that would be useful when coming back from the maximum depth -- the variables that upper levels of recursion would require.
