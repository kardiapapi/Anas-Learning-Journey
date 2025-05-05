


section .data
    msg db "hello cowboy", 10 
    len equ $ - msg

section .text
    global _start

_start:
    ; Write syscall
    mov rax, 1          
    mov rdi, 1          
    mov rsi, msg        
    mov rdx, len        
    syscall

    ; Exit syscall
    mov rax, 60         
    mov rdi, 0          
    syscall