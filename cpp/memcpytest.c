#include <stdio.h>
#include <stdlib.h>

int main() {
   char s[10] = "hakan";
   char p[10];
 
   memcpy(p,s,2);
   p[2]='\0';
   printf("%s\n",p);
   return 0;
}
