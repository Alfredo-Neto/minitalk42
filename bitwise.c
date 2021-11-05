#include <stdio.h>

# define JORGE 0b01
# define ALEXANDRE 0b10
# define ALFREDO 0b10000000

int main(void)
{
    unsigned int flags = JORGE | ALEXANDRE | ALFREDO; // 32 bits

    // 00000000 00000000 00000000 10000011
    //                            10000000
    
    // 00000000 00000000 00000000 00000001 JORGE
    // 00000000 00000000 00000000 00000010 ALEXANDRE
    // 00000000 00000000 00000000 10000000 ALFREDO

    //  10000011 // flags = flags & ~ALEXANDRE;
    //  11111101 ~
    //  10000001

    //  10000001 // flags = flags | ALEXANDRE;
    //  00000010 original
    //  10000011

    //  if (flags & JORGE) 
    //  10000011 &
    //  00000001
    //  00000001

    flags = flags & ~ALEXANDRE; // 10000001
    flags = flags | ALEXANDRE; // 10000011

    if (flags & JORGE)
        printf("Entrando no primeiro if\n");
    if (flags & ALEXANDRE)
        printf("Entrando no segundo if\n");
    if (flags & ALFREDO)
        printf("Entrando no terceiro if\n");
    
    return 0;
}
