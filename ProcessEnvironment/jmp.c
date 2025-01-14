#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>

jmp_buf jump_buffer;

void function2() {
    printf("Inside function2\n");
    longjmp(jump_buffer, 1); // 跳转回 setjmp，返回值为 1
    printf("This will not be printed\n");
}

void function1() {
    printf("Inside function1\n");
    function2();
    printf("This will also not be printed\n");
}

int main() {
    if (setjmp(jump_buffer) == 0) {
        printf("First call to setjmp\n");
        function1();
    } else {
        printf("Returned from longjmp with value %d\n", 1);
    }

    return 0;
}