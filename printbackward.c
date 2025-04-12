#include<stdio.h>
int main(){
         char *p = "qiyana";
         int i = 0 ;
        
        while(*p != 0){
                   p++ ;
                   i++ ;              
                      }
                
                --p ;
        
        while( i > 0 ){
        printf("%c", *p);
        --i ; 
        --p ;               

                      } 
return 0;
          }