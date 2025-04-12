.data
  letprint db "hello cowboy" , 10

.text
global _start
_start:

      mov rsi, letprint
      xor rcx, rcx 
lenghtcount
      cmp byte [rsi+rcx], 0
      je prints
      inc rcx
      jge lenghtcount

prints

    mov rax, 1
    mov rdi, 1
    mov rsi, hadak
    mov rdx, rcx
syscall
exit

  mov rax, 60
  xor rdi, rdi
syscall