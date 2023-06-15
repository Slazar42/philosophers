unsigned char reverse_bits(unsigned char b)
{
	unsigned char	r = 0;

    if (128 & b)
        r = r | 1;
    if (64 & b)
        r = r | 2;
    if (32 & b)
        r = r | 4;
    if (16 & b)
        r = r | 8;
    if (8 & b)
        r = r | 16;
    if (4 & b)
        r = r | 32;
    if (2 & b)
        r = r | 64;
    if (1 & b)
        r = r | 128;
    return r;
}
#include<stdio.h>
int main()
{
    printf("%d\n",'c');
    printf("%d\n",reverse_bits('c'));
}
