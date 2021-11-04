#include <stdio.h>

int main(int argc, char const *argv[])
{
   int decimal = 0;
   int binary;
   int base = 1;
   int rem;
   int num;

   printf("Digite um numero binario: ");
   scanf("%d", &binary);

   num = binary;
   while (binary != 0)
   {
       rem = binary % 10; // 0 //rem == 1
       decimal = decimal + rem * base; // decimal == 1 + 1 * 128 = 65 // 01000001
       binary = binary / 10; // 01000001 / 10 == 0
       base = base * 2; // base == 128
   }
   printf("Decimal equivalente: %c", decimal);
   
    return 0;
}
