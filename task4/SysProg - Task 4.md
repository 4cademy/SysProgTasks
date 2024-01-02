# SysProg - Task 4
## Output of a terminal session to find password:
``` shell
marcel@MarcelsPC:~/SysProgTasks/task4$ gdb ./simple_login
GNU gdb (Ubuntu 12.1-0ubuntu1~22.04) 12.1
Copyright (C) 2022 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from ./simple_login...
(gdb) disassemble main
Dump of assembler code for function main:
   0x08048433 <+0>:     lea    0x4(%esp),%ecx
   0x08048437 <+4>:     and    $0xfffffff0,%esp
   0x0804843a <+7>:     push   -0x4(%ecx)
   0x0804843d <+10>:    push   %ebp
   0x0804843e <+11>:    mov    %esp,%ebp
   0x08048440 <+13>:    push   %ecx
   0x08048441 <+14>:    sub    $0x24,%esp
   0x08048444 <+17>:    movl   $0x804856f,(%esp)
   0x0804844b <+24>:    call   0x8048308 <puts@plt>
   0x08048450 <+29>:    call   0x80483a4 <verify_password>
   0x08048455 <+34>:    mov    %eax,-0x8(%ebp)
   0x08048458 <+37>:    cmpl   $0x0,-0x8(%ebp)
   0x0804845c <+41>:    jne    0x8048473 <main+64>
   0x0804845e <+43>:    movl   $0x804858b,(%esp)
   0x08048465 <+50>:    call   0x8048308 <puts@plt>
   0x0804846a <+55>:    movl   $0x1,-0x18(%ebp)
   0x08048471 <+62>:    jmp    0x8048486 <main+83>
   0x08048473 <+64>:    movl   $0x8048598,(%esp)
   0x0804847a <+71>:    call   0x8048308 <puts@plt>
   0x0804847f <+76>:    movl   $0x0,-0x18(%ebp)
   0x08048486 <+83>:    mov    -0x18(%ebp),%eax
   0x08048489 <+86>:    add    $0x24,%esp
   0x0804848c <+89>:    pop    %ecx
   0x0804848d <+90>:    pop    %ebp
   0x0804848e <+91>:    lea    -0x4(%ecx),%esp
   0x08048491 <+94>:    ret
End of assembler dump.
(gdb) disassemble verify_password
Dump of assembler code for function verify_password:
   0x080483a4 <+0>:     push   %ebp
   0x080483a5 <+1>:     mov    %esp,%ebp
   0x080483a7 <+3>:     push   %edi
   0x080483a8 <+4>:     push   %esi
   0x080483a9 <+5>:     sub    $0xf0,%esp
   0x080483af <+11>:    lea    -0xd0(%ebp),%eax
   0x080483b5 <+17>:    mov    %eax,0x4(%esp)
   0x080483b9 <+21>:    movl   $0x804855c,(%esp)
   0x080483c0 <+28>:    call   0x80482f8 <scanf@plt>
   0x080483c5 <+33>:    lea    -0xd0(%ebp),%eax
   0x080483cb <+39>:    mov    %eax,-0xe0(%ebp)
   0x080483d1 <+45>:    movl   $0x804855f,-0xe4(%ebp)
   0x080483db <+55>:    movl   $0x10,-0xe8(%ebp)
   0x080483e5 <+65>:    cld
   0x080483e6 <+66>:    mov    -0xe0(%ebp),%esi
   0x080483ec <+72>:    mov    -0xe4(%ebp),%edi
   0x080483f2 <+78>:    mov    -0xe8(%ebp),%ecx
   0x080483f8 <+84>:    repz cmpsb %es:(%edi),%ds:(%esi)
   0x080483fa <+86>:    seta   %dl
   0x080483fd <+89>:    setb   %al
   0x08048400 <+92>:    mov    %edx,%ecx
   0x08048402 <+94>:    sub    %al,%cl
   0x08048404 <+96>:    mov    %ecx,%eax
   0x08048406 <+98>:    movsbl %al,%eax
   0x08048409 <+101>:   test   %eax,%eax
   0x0804840b <+103>:   jne    0x8048419 <verify_password+117>
   0x0804840d <+105>:   movl   $0x1,-0xdc(%ebp)
   0x08048417 <+115>:   jmp    0x8048423 <verify_password+127>
   0x08048419 <+117>:   movl   $0x0,-0xdc(%ebp)
   0x08048423 <+127>:   mov    -0xdc(%ebp),%eax
   0x08048429 <+133>:   add    $0xf0,%esp
   0x0804842f <+139>:   pop    %esi
   0x08048430 <+140>:   pop    %edi
   0x08048431 <+141>:   pop    %ebp
   0x08048432 <+142>:   ret
End of assembler dump.
(gdb) x/s 0xf0
0xf0:   <error: Cannot access memory at address 0xf0>
(gdb) x/s 0x804855c
0x804855c:      "%s"
(gdb) x/s 0x804855f
0x804855f:      "AaMilmFS+z11/2J"
(gdb) exit
marcel@MarcelsPC:~/SysProgTasks/task4$ ./simple_login
Enter the correct password:
AaMilmFS+z11/2J
Successful login! Now, we would execute a shell ...
marcel@MarcelsPC:~/SysProgTasks/task4$
```

**Password:**
AaMilmFS+z11/2J

## Buffer  Overflow Vulnerability:
### How does gcc translate function calls to assembly code?
**General functionality:**
The call to a function involves setting up the arguments according to the calling convention, transferring control to the called function, and handling the return value afterward.

1. **Function Prologue**
	- When a function is called, the compiler generates code to set up the function's stack frame
		- allocating space on the stack for local variables via `push`, saving the previous frame pointer, and updating the stack pointer
2. **Parameter Passing**
	- see next question below
3. **Function Body**
	- the actual code for the function is generated based on the C code
		- each statement and expression is translated into a series of assembly instructions
	- local variables are typically accessed using offsets from the stack pointer or base pointer
4. **Function Epilogue**
	- before returning from the function, the compiler generates code to clean up the stack frame
		- restoring the previous frame pointer and deallocating the space for local variables via `pop`
5. **Return Value**
	- see next question below

### How are arguments and return values passed?
- arguments are passed to functions through registers or the stack, depending on the calling convention used
	- if the number of arguments exceeds the available registers, the remaining arguments are typically pushed onto the stack
- the return value is usually stored in a specific register, such as `eax`
	- for more complex return types (e.g., structs), the caller and the callee may follow a predefined convention for passing the return value

### How can the program continue executing where it “left off” when the function call happened?
**General process:**
1. `push ebp`: Saves the previous base pointer on the stack
2. `mov ebp, esp`: Sets up a new base pointer by moving the stack pointer into the base pointer. This establishes the function's stack frame.
3. The function body is executed.
4. `pop ebp`: Restores the previous base pointer.
5. `ret`: Returns from the function. This instruction pops the return address from the stack and transfers control back to the calling function.

### Which standard C-Library functions are vulnerable to buffer overflows and why?
Buffer overflows are a type of vulnerability that can occur when a program writes more data to a buffer than it can hold.
**Possible scenarios:**
1. **No Boundary Checks:**
	- some C-library functions do not perform boundary checks on the size of buffers, leaving it to the programmer to ensure that the destination buffer has enough space for the data being copied
	- i. e.: `strcpy(dest, src)` leads to a buffer overflow if `src` is larger than the `dest` buffer
2. **No Size Parameters:**
	- certain functions do not take a size parameter, so the functions just assume that the destination buffer is large enough to accommodate the data
	- i. e.: `strcat(dest, src)` leads to a buffer overflow if  `src` appended to the content of `dest` is larger than the `dest` buffer
3. **Unsafe String Functions:**
	- some string manipulation functions in the C-library are unsafe because they do not perform bounds checking or ensure null-termination of the destination buffer
	- i. e.: `strncpy(dest, src, size)` may lead to a buffer overflow if `size` is smaller than the length of `src` because then the `dest` buffer will not be terminated with a `null` byte
4. **User Input Handling:**
	- functions that handle user input, especially those that read input from external sources like `gets()` and `scanf()`, can be vulnerable if the input size is not properly validated
	-  i. e.: `gets(buf)` leads to a buffer overflow if the user input is longer than the `buf` buffer

### How to use this knowledge to overwrite the return address of a function?
When a buffer overflow occurs, it can lead to overwriting adjacent memory, including the function's return address.
- the stack typically contains the return address of a function
- the stack also contains the allocated space for the buffer
- by triggering a buffer overflow with a certain length one can overwrite the adjacent parts of the stack including the return address of the function

## How did I find the right return address?
1. Record program with *wrong* password with gdb
2. Record program with *right* password with gdb
3. Find the differences in `main` after the `verify_password` function returned
4. The first difference in addresses was: `0x0804845e` (with wrong PW) vs `0x08048473` (with right PW)
5. Therefore I assumed that I have to overwrite the return address of the `verify_password` function with `0x08048473` to circumvent the authentication check. This turned out to be correct.

## Why is there a segmentation fault after overwriting the return address?
- Overwriting the return address with a buffer overflow will also overwrite everything in between the buffer and the place of the return address on the stack. This most likely leads to a corruption of the stack.
- One would have to edit the exploiting input in between the end of the buffer and the return address in a way that the stack remains intakt.

## What practical countermeasures of contemporary UNIX systems and compilers complicate buffer overflow attacks?
1. **Address Space Layout Randomization (ASLR):**
	- ASLR randomizes the memory addresses of key system components and executable code
	- this makes it more challenging for attackers to predict the location of specific functions or the stack
2. **Data Execution Prevention (DEP):**
	- DEP marks certain areas of memory as non-executable, preventing the execution of code from those regions
3. **Stack Canaries:**
	- Stack canaries are random values placed around the return address on the stack
	- if a buffer overflow attempts to overwrite the return address, it will likely corrupt the canary value
	- the system can then detect this corruption and terminate the program, preventing further exploitation
4. **Non-Executable Stack:**
	- this ensures that the stack memory is marked as non-executable, preventing the execution of code placed on the stack
5. **Safe String Functions:**
	- some compilers provide safe versions of string manipulation functions