#include <prog2.h>

int fibnacci(int no)
{
   int a=1,b=1;

   while(a< no)
   {
     int temp = a;
     a=b;
     b=temp+b;
   }

   return a;
}
