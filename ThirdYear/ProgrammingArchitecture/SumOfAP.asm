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
    
    PRINT_STRING "a1 = "
    PRINT_DEC 4, [a1]
    NEWLINE
    PRINT_STRING "d = "
    PRINT_DEC 4, [d]
    NEWLINE
    PRINT_STRING "n = "
    PRINT_DEC 4, [n]
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
    mov eax, [n] ; eax = n
    imul eax, ebx ; eax = n * ebx
    shr eax, 1 ; sum = eax/2
    mov [sum], eax
    
    PRINT_STRING "Sum = "
    PRINT_DEC 4, [sum] ; Print the result
    NEWLINE
    
    ; Negate the value of sum and print
    mov eax, [sum]      ; Load sum into eax
    neg eax             ; Negate eax (two's complement)
    PRINT_STRING "Negated Sum = "
    PRINT_DEC 4, eax    ; Print directly from eax
    NEWLINE

    ; Bitwise NOT of sum and print
    mov eax, [sum]      ; Load sum into eax
    not eax             ; Bitwise NOT (invert all bits)
    PRINT_STRING "Bitwise NOT of Sum = "
    PRINT_DEC 4, eax    ; Print directly from eax
    NEWLINE

    ; Add with carry (ADC) and print
    mov eax, [sum]      ; Load sum into eax
    add eax, 10         ; Add 10 to eax
    adc eax, 1          ; Add carry (CF) to eax
    PRINT_STRING "Sum + 10 + Carry = "
    PRINT_DEC 4, eax    ; Print directly from eax
    NEWLINE

    ; Subtract with borrow (SBB) and print
    mov eax, [sum]      ; Load sum into eax
    sub eax, 5          ; Subtract 5 from eax
    sbb eax, 1          ; Subtract borrow (CF) from eax
    PRINT_STRING "Sum - 5 - Borrow = "
    PRINT_DEC 4, eax    ; Print directly from eax
    NEWLINE

    ; Rotate left (ROL) by 2 bits and print
    mov eax, [sum]      ; Load sum into eax
    rol eax, 2          ; Rotate eax left by 2 bits
    PRINT_STRING "Sum Rol 2 = "
    PRINT_DEC 4, eax    ; Print directly from eax
    NEWLINE

    ; Rotate right (ROR) by 3 bits and print
    mov eax, [sum]      ; Load sum into eax
    ror eax, 3          ; Rotate eax right by 3 bits
    PRINT_STRING "Sum Ror 3 = "
    PRINT_DEC 4, eax    ; Print directly from eax
    NEWLINE
    
    ; Shift Right (SHR) by 1 and print
    mov eax, [sum]      ; Load sum into eax
    shr eax, 1          ; Shift eax right by 1 bit
    PRINT_STRING "Sum SHR 1 = "
    PRINT_DEC 4, eax    ; Print directly from eax
    NEWLINE

    ; Exchange `sum` with another value (42) and print
    mov eax, [sum]      ; Load sum into eax
    mov ebx, 42         ; Load another value into ebx
    xchg eax, ebx       ; Exchange eax and ebx
    PRINT_STRING "Sum Exchanged with 42 = "
    PRINT_DEC 4, eax    ; Print directly from eax
    NEWLINE

    ; Test if the highest bit is set
    mov eax, [sum]      ; Load sum into eax
    test eax, 0x80000000 ; Test the highest bit (sets flags but no result stored)
    PRINT_STRING "Highest Bit Set = "
    jz .bit_not_set      ; Jump if zero flag is set (highest bit is not set)
    PRINT_STRING "Yes (1)"
    jmp .end_bit_test
.bit_not_set:
    PRINT_STRING "No (0)"
.end_bit_test:
    NEWLINE

    ; Compare sum with 100 and print result
    mov eax, [sum]      ; Load sum into eax
    cmp eax, 100        ; Compare sum with 100
    PRINT_STRING "Sum > 100 = "
    ja .greater         ; Jump if above (unsigned comparison)
    PRINT_STRING "No (0)"
    jmp .end_compare
.greater:
    PRINT_STRING "Yes (1)"
.end_compare:
    NEWLINE

    ; Push and Pop operations
    mov eax, [sum]      ; Load sum into eax
    push eax            ; Push eax onto the stack
    pop eax             ; Pop it back into eax
    PRINT_STRING "Pushed and Popped Sum = "
    PRINT_DEC 4, eax    ; Print directly from eax
    NEWLINE


    ; Exit
    xor eax, eax ; Set eax to 0 (return value)
    ret