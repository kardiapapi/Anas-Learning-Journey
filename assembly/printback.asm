section .data
 salut db "hello gimme a word ?, " , 10 , 0

section .bss
 Userinput resb 32
 deb resb 1

section .text:
global _start
_start:
   mov rax, 1
    mov rdi, 1
    mov rsi, salut
    mov rdx, 23
syscall

   mov rax, 0
    mov rdi, 0
    mov rsi, Userinput
    mov rdx, 32
syscall
   mov r9, rax  
   dec r9
   mov r8, r9 
   
.printback: 
      
     cmp r8, 0
      jl .exit

     movzx rax, byte [Userinput + r8]

         mov [deb], rax
         mov rsi, deb
         mov rdx, 1
syscall
    dec r8
    jmp .printback
 
    
.exit:

    mov rax, 60
    xor rdi, rdi
syscall
