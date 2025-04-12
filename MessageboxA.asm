.data
msg db "You can do that ", 0
mytitle db "a comeback " , 0

.code
#externdef MessageBoxA : proc 
main proc :
sub rsp, 28h ; 40 bytes
xor rcx, rcx 
mov rdx, [msg]
mov r8, [mytitle]
xor r9, r9
call MessageBoxA
add rsp, 40 ;  28h  it stands for hexadecimal 
ret 
main endp


end