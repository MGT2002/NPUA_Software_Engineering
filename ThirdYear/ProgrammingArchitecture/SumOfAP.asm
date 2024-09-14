%include "io.inc"

section .bss
    a1 resd 1           ; Reserve space for the first term 
    d  resd 1           ; Reserve space for the common difference
    n  resd 1           ; Reserve space for the number of terms
    sum resd 1          ; Reserve space for the sum
    ;resd 1 doubleword(4byte)

section .text
global main

print_all:
    ;mov ebp, esp
    
    PRINT_DEC 4, [a1]
    NEWLINE
    PRINT_DEC 4, [d]
    NEWLINE
    PRINT_DEC 4, [n]
    NEWLINE
    PRINT_DEC 4, [sum]
    NEWLINE
    
    ret

main:
    mov ebp, esp       ; Set up the stack frame

    ; Get input for the first term (a1)
    GET_DEC 4, eax     ; Read first term into eax
    mov [a1], eax      ; Store the first term in memory

    ; Get input for the common difference (d)
    GET_DEC 4, eax     ; Read common difference into eax
    mov [d], eax       ; Store the common difference in memory

    ; Get input for the number of terms (n)
    GET_DEC 4, eax     ; Read number of terms into eax
    mov [n], eax       ; Store the number of terms in memory
    
    call print_all

    ; Load values into registers for calculation
    mov eax, [a1]      ; Load a1 into eax
    mov ebx, [d]       ; Load d into ebx
    mov ecx, [n]       ; Load n into ecx

    ; Calculate (n - 1) * d
    dec ecx            ; ecx = n - 1
    imul ebx, ecx      ; ebx = (n - 1) * d
    
    ; Calculate 2 * a1
    shl eax, 1         ; eax = 2 * a1
    
    ; Add 2 * a1 + (n - 1) * d
    add eax, ebx ; eax = 2 * a1 + (n - 1) * d    
    mov [sum], eax ;sum = eax
    
    ; Calculate sum = n * (2 * a1 + (n - 1) * d)
    mov ebx, [sum] ; ebx = 2*a1+(n-1)*d
    imul eax, ebx ; eax = n/2 * ebx
    mov [sum], eax ; sum = eax
    
    ;Sum = Sum/2
    mov eax, [sum]
    shr eax, 1
    mov [sum], eax
    
    ; Print the result
    PRINT_DEC 4, [sum] ; Print the result
    NEWLINE

    ; Exit
    xor eax, eax ; Set eax to 0 (return value)
    ret