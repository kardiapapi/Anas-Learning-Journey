#include<windows.h>
#include<stdio.h>

int main (){
 HMODULE crazy = GetModuleHandleA(0);
 IMAGE_DOS_HEADER *dosP = (IMAGE_DOS_HEADER*)crazy ;
 printf("dosP value: 0x%p\n", *dosP);
 IMAGE_NT_HEADERS  *ntP = (IMAGE_NT_HEADERS*)((char*)crazy+ dosP->e_lfanew) ; // dosP->e_lfanew =128 accessing to a specific memory location ointed at in that struct
 printf("dosP value2: 0x%p\n", dosP->e_lfanew);
 
 printf( "EXE dial darkom : 0x%p\n", crazy) ; // printing 0x%p = base pointer in hexadecimal
printf("code section: 0x%p\n", (char*)crazy+ ntP->OptionalHeader .BaseOfCode) ;
printf("haahowa ntp : 0x%p\n", ntP->OptionalHeader .BaseOfCode);
printf("chou had ntp: 0x%d\n", *ntP);


return 0 ;
}                         