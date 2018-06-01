#include<stdio.h>

void *orig_stack_pointer;

void blow_stack() {
    blow_stack();
}

int main() {
    __asm__("movl %esp, orig_stack_pointer");

    blow_stack();
    return 0;
}
/*
 会出现段错误，我们要调试
(gdb) r
Starting program: /home/home/misc-code/setrlimit

Program received signal SIGSEGV, Segmentation fault.
blow_stack () at setrlimit.c:4
4       blow_stack();
(gdb) print (void *)$esp
$1 = (void *) 0xffffffffff7ff000
(gdb) print (void *)orig_stack_pointer
$2 = (void *) 0xffffc800
(gdb) print 0xffffc800-0xff7ff000
$3 = 8378368    // Current Process Stack Size is 8M
*/
