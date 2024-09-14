%include "io.inc"

section .data
    str1 db "Hello", 0
    str2 db "World!", 0

section .text
global main
main:
    mov ebp, esp; for correct debugging
    ;write your code here
    PRINT_STRING str1
    NEWLINE
    PRINT_STRING str2
    NEWLINE
    xor eax, eax
    ret