Aufruf zum Finden des Passworts:
```bash
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


Passwort:
AaMilmFS+z11/2J

Segmentation Fault bei:
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
210 Zeichen


Ablauf falsches PW:
0x08048444
0x08048450
0x080483af
0x080483c5
..........
0x08048419	%
0x08048429	%
..........
0x08048458
..........
0x0804845e	%
0x0804846a	%
..........
0x08048489


080483a4 <verify_password>:
 80483a4:       55                      push   %ebp
 80483a5:       89 e5                   mov    %esp,%ebp
 80483a7:       57                      push   %edi
 80483a8:       56                      push   %esi
 80483a9:       81 ec f0 00 00 00       sub    $0xf0,%esp
[3]80483af:       8d 85 30 ff ff ff       lea    -0xd0(%ebp),%eax
 80483b5:       89 44 24 04             mov    %eax,0x4(%esp)
 80483b9:       c7 04 24 5c 85 04 08    movl   $0x804855c,(%esp)
 80483c0:       e8 33 ff ff ff          call   80482f8 <scanf@plt>
[4]80483c5:       8d 85 30 ff ff ff       lea    -0xd0(%ebp),%eax
 80483cb:       89 85 20 ff ff ff       mov    %eax,-0xe0(%ebp)
 80483d1:       c7 85 1c ff ff ff 5f    movl   $0x804855f,-0xe4(%ebp)
 80483d8:       85 04 08
 80483db:       c7 85 18 ff ff ff 10    movl   $0x10,-0xe8(%ebp)
 80483e2:       00 00 00
 80483e5:       fc                      cld
 80483e6:       8b b5 20 ff ff ff       mov    -0xe0(%ebp),%esi
 80483ec:       8b bd 1c ff ff ff       mov    -0xe4(%ebp),%edi
 80483f2:       8b 8d 18 ff ff ff       mov    -0xe8(%ebp),%ecx
 80483f8:       f3 a6                   repz cmpsb %es:(%edi),%ds:(%esi)
 80483fa:       0f 97 c2                seta   %dl
 80483fd:       0f 92 c0                setb   %al
 8048400:       89 d1                   mov    %edx,%ecx
 8048402:       28 c1                   sub    %al,%cl
 8048404:       89 c8                   mov    %ecx,%eax
 8048406:       0f be c0                movsbl %al,%eax
 8048409:       85 c0                   test   %eax,%eax
 804840b:       75 0c                   jne    8048419 <verify_password+0x75>
 804840d:       c7 85 24 ff ff ff 01    movl   $0x1,-0xdc(%ebp)
 8048414:       00 00 00
 8048417:       eb 0a                   jmp    8048423 <verify_password+0x7f>
[5]8048419:       c7 85 24 ff ff ff 00    movl   $0x0,-0xdc(%ebp)
 8048420:       00 00 00
 8048423:       8b 85 24 ff ff ff       mov    -0xdc(%ebp),%eax
[6]8048429:       81 c4 f0 00 00 00       add    $0xf0,%esp
 804842f:       5e                      pop    %esi
 8048430:       5f                      pop    %edi
 8048431:       5d                      pop    %ebp
 8048432:       c3                      ret

08048433 <main>:
 8048433:       8d 4c 24 04             lea    0x4(%esp),%ecx
 8048437:       83 e4 f0                and    $0xfffffff0,%esp
 804843a:       ff 71 fc                push   -0x4(%ecx)
 804843d:       55                      push   %ebp
 804843e:       89 e5                   mov    %esp,%ebp
 8048440:       51                      push   %ecx
 8048441:       83 ec 24                sub    $0x24,%esp
[1]8048444:       c7 04 24 6f 85 04 08    movl   $0x804856f,(%esp)
 804844b:       e8 b8 fe ff ff          call   8048308 <puts@plt>
[2]8048450:       e8 4f ff ff ff          call   80483a4 <verify_password>
 8048455:       89 45 f8                mov    %eax,-0x8(%ebp)
[3]8048458:       83 7d f8 00             cmpl   $0x0,-0x8(%ebp)
 804845c:       75 15                   jne    8048473 <main+0x40>
[4]804845e:       c7 04 24 8b 85 04 08    movl   $0x804858b,(%esp)
 8048465:       e8 9e fe ff ff          call   8048308 <puts@plt>
[5]804846a:       c7 45 e8 01 00 00 00    movl   $0x1,-0x18(%ebp)
 8048471:       eb 13                   jmp    8048486 <main+0x53>
 8048473:       c7 04 24 98 85 04 08    movl   $0x8048598,(%esp)
 804847a:       e8 89 fe ff ff          call   8048308 <puts@plt>
 804847f:       c7 45 e8 00 00 00 00    movl   $0x0,-0x18(%ebp)
 8048486:       8b 45 e8                mov    -0x18(%ebp),%eax
[6]8048489:       83 c4 24                add    $0x24,%esp
 804848c:       59                      pop    %ecx
 804848d:       5d                      pop    %ebp
 804848e:       8d 61 fc                lea    -0x4(%ecx),%esp
 8048491:       c3                      ret



Ablauf richtiges PW:
0x08048444
0x08048450
0x080483af
0x080483c5
..........
0x0804840d	%
0x08048429	%
..........
0x08048458
..........
0x08048473	%
0x0804847f	%
..........
0x08048489


080483a4 <verify_password>:
 80483a4:       55                      push   %ebp
 80483a5:       89 e5                   mov    %esp,%ebp
 80483a7:       57                      push   %edi
 80483a8:       56                      push   %esi
 80483a9:       81 ec f0 00 00 00       sub    $0xf0,%esp
[3]80483af:       8d 85 30 ff ff ff       lea    -0xd0(%ebp),%eax
 80483b5:       89 44 24 04             mov    %eax,0x4(%esp)
 80483b9:       c7 04 24 5c 85 04 08    movl   $0x804855c,(%esp)
 80483c0:       e8 33 ff ff ff          call   80482f8 <scanf@plt>
[4]80483c5:       8d 85 30 ff ff ff       lea    -0xd0(%ebp),%eax
 80483cb:       89 85 20 ff ff ff       mov    %eax,-0xe0(%ebp)
 80483d1:       c7 85 1c ff ff ff 5f    movl   $0x804855f,-0xe4(%ebp)
 80483d8:       85 04 08
 80483db:       c7 85 18 ff ff ff 10    movl   $0x10,-0xe8(%ebp)
 80483e2:       00 00 00
 80483e5:       fc                      cld
 80483e6:       8b b5 20 ff ff ff       mov    -0xe0(%ebp),%esi
 80483ec:       8b bd 1c ff ff ff       mov    -0xe4(%ebp),%edi
 80483f2:       8b 8d 18 ff ff ff       mov    -0xe8(%ebp),%ecx
 80483f8:       f3 a6                   repz cmpsb %es:(%edi),%ds:(%esi)
 80483fa:       0f 97 c2                seta   %dl
 80483fd:       0f 92 c0                setb   %al
 8048400:       89 d1                   mov    %edx,%ecx
 8048402:       28 c1                   sub    %al,%cl
 8048404:       89 c8                   mov    %ecx,%eax
 8048406:       0f be c0                movsbl %al,%eax
 8048409:       85 c0                   test   %eax,%eax
 804840b:       75 0c                   jne    8048419 <verify_password+0x75>
[5]804840d:       c7 85 24 ff ff ff 01    movl   $0x1,-0xdc(%ebp)
 8048414:       00 00 00
 8048417:       eb 0a                   jmp    8048423 <verify_password+0x7f>
 8048419:       c7 85 24 ff ff ff 00    movl   $0x0,-0xdc(%ebp)
 8048420:       00 00 00
 8048423:       8b 85 24 ff ff ff       mov    -0xdc(%ebp),%eax
[6]8048429:       81 c4 f0 00 00 00       add    $0xf0,%esp
 804842f:       5e                      pop    %esi
 8048430:       5f                      pop    %edi
 8048431:       5d                      pop    %ebp
 8048432:       c3                      ret

08048433 <main>:
 8048433:       8d 4c 24 04             lea    0x4(%esp),%ecx
 8048437:       83 e4 f0                and    $0xfffffff0,%esp
 804843a:       ff 71 fc                push   -0x4(%ecx)
 804843d:       55                      push   %ebp
 804843e:       89 e5                   mov    %esp,%ebp
 8048440:       51                      push   %ecx
 8048441:       83 ec 24                sub    $0x24,%esp
[1]8048444:       c7 04 24 6f 85 04 08    movl   $0x804856f,(%esp)
 804844b:       e8 b8 fe ff ff          call   8048308 <puts@plt>
[2]8048450:       e8 4f ff ff ff          call   80483a4 <verify_password>
 8048455:       89 45 f8                mov    %eax,-0x8(%ebp)
[3]8048458:       83 7d f8 00             cmpl   $0x0,-0x8(%ebp)
 804845c:       75 15                   jne    8048473 <main+0x40>
 804845e:       c7 04 24 8b 85 04 08    movl   $0x804858b,(%esp)
 8048465:       e8 9e fe ff ff          call   8048308 <puts@plt>
 804846a:       c7 45 e8 01 00 00 00    movl   $0x1,-0x18(%ebp)
 8048471:       eb 13                   jmp    8048486 <main+0x53>
[4]8048473:       c7 04 24 98 85 04 08    movl   $0x8048598,(%esp)
 804847a:       e8 89 fe ff ff          call   8048308 <puts@plt>
[5]804847f:       c7 45 e8 00 00 00 00    movl   $0x0,-0x18(%ebp)
 8048486:       8b 45 e8                mov    -0x18(%ebp),%eax
[6]8048489:       83 c4 24                add    $0x24,%esp
 804848c:       59                      pop    %ecx
 804848d:       5d                      pop    %ebp
 804848e:       8d 61 fc                lea    -0x4(%ecx),%esp
 8048491:       c3                      ret