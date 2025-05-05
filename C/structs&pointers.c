#include<stdio.h>
struct stats{
       char name[20];
       int goals ;

};
int main() {
          struct stats player1={"lamine zamal",25} ;
          struct stats *playerptr = &player1 ;
          playerptr->goals += 2 ;
          printf("player name : %s \n", playerptr -> name ) ;
          printf("player goals : %d \n" , playerptr -> goals ) ;
    return 0 ; 
} 
