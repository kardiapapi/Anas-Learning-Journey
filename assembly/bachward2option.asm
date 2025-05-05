section .data
    prompt db "Enter a word: ", 0 
    prompt_len equ $ - prompt     

section .bss
    input resb 100                
    input_len equ $ - input       

section .text
    global _start

_start:
    
    mov rax, 1                     
    mov rdi, 1                     
    lea rsi, [prompt]              
    mov rdx, prompt_len            
    syscall

    mov rax, 0                     
    mov rdi, 0                     
    lea rsi, [input]               
    mov rdx, input_len             
    syscall

    ; Save the length of the input
    mov r8, rax                    
    dec r8                        

    ; Reverse the input string
    lea rsi, [input]               
    lea rdi, [input + r8 - 1]      

reverse_loop:
    cmp rsi, rdi                  
    jge print_reversed             

    ; Swap characters
    mov al, [rsi]                  
    mov bl, [rdi]                  
    mov [rsi], bl                  
    mov [rdi], al                
    ; Move pointers
    inc rsi                       
    dec rdi                        
    jmp reverse_loop               

print_reversed:
    ; Print the reversed string
    mov rax, 1                     
    mov rdi, 1                     
    lea rsi, [input]               
    mov rdx, r8                    
    syscall

    ; Print a newline
    mov rax, 1                     
    mov rdi, 1                     
    lea rsi, [0x0A]             ; new line optional depends on what u want as output
    mov rdx, 1                     
    syscall

    
    mov rax, 60                  
    xor rdi, rdi                   
    syscall

