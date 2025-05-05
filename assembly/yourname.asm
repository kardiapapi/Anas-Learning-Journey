section .data
  prompt db "hello cowboy whats ur name? ", 10, 0
  hero   db ", you are a hero ", 0
  newline db 10

section .bss
  name_buffer resb 32

section .text

  global _start
_start:
 mov rax, 1
 mov rdi, 1
 mov rsi, prompt
 mov rdx, 27
 syscall
 
 mov rax, 0
 mov rdi, 0
 mov rsi, name_buffer
 mov rdx,32
 syscall

 mov r8, rax   ; this is important for lemght rax holds the number of bytes read, and we store it in r8 to use later.

 mov rax, 1
 mov rdi, 1
 mov rsi, hero
 mov rdx, 16
syscall

mov rax, 1
 mov rdi, 1
 mov rsi, name_buffer
 mov rdx, r8
 syscall
 
 mov rax, 1
 mov rdi, 1
 mov rsi, newline
 mov rdx, 1
 syscall

 mov rax, 60
 xor rdi, rdi
 syscall
; this code is just to print something like for example asking user for their name then answering them including their name 