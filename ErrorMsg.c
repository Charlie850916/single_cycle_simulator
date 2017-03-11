#include <stdio.h>
#include <stdlib.h>
#include "function.h"

void OverFlow_add(int s, int t, int d, int p)
{
    if( (s>0 && t>0 && d<=0) || (s<0 && t<0 && d>=0) ) printf("s%d number overflow!\n",p);
    return;
}

void OverFlow_sub(int s, int t, int d, int p)
{
    if( (s>0 && t<0 && d<=0) || (s<0 && t>0 && d>=0) ) printf("s%d number overflow!\n",p);
    return;
}

void OverFlow_mult(int a, int b, long long int c)
{
    if( ( (a>0 && b>0) || (a<0 && b<0) ) && c <= 0) printf("HI-LO number overflow!\n");
    if( ( (a>0 && b<0) || (a<0 && b>0) ) && c >= 0) printf("HI-LO number overflow!\n");
    return;
}

int Misalignment(int i)
{
    if( i!=0 )
    {
        halt = 1;
        printf("Misalignment Error\n");
        return 1;
    }
    return 0;
}

int AddressOverflow(int i, int b)
{
    if( i>(1023*4+b) || i<0 )
    {
        halt = 1;
        printf("Address Overflow\n");
        return 1;
    }
    return 0;
}
