# gdb notes

## build options

`CFLAGS += -g`

* `-g`: generate symbol info


`LDFLAGS += -rdynamic`

* `-rdynamic`: tell linker to put in the link tables the name of all the none static functions in your code, not just the exported ones.

## gdb usage

`gdb program`

commands:

`b main` - Puts a breakpoint at the beginning of the program

`b` - Puts a breakpoint at the current line

`b N` - Puts a breakpoint at line N

`b +N` - Puts a breakpoint N lines down from the current line

`b fn` - Puts a breakpoint at the beginning of function "fn"

`d N` - Deletes breakpoint number N

`info break` - list breakpoints

`r` - Runs the program until a breakpoint or error

`c` - Continues running the program until the next breakpoint or error

`f` - Runs until the current function is finished

`s` - Runs the next line of the program

`s N` - Runs the next N lines of the program

`n` - Like s, but it does not step into functions

`u N` - Runs until you get N lines in front of the current line

`p var` - Prints the current value of the variable "var"

`bt` - Prints a stack trace

`u` - Goes up a level in the stack

`d` - Goes down a level in the stack

`q` - Quits gdb

## segfault debug

If you write a signal handler catches `SIGSEGV`, and got `EIP` from `siginfo_t.si_addr`, then call `backtrace_symbols` to get stack trace.

If the crash point is in an `static` function, no function name would be printed out, just the function address like `0x54320`.

One way to solve this is use `gdb exe` and run `info symbol 0x54320`.