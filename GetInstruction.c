#include <stdio.h>
#include <stdlib.h>
#include "function.h"

unsigned int GetLineN(int n, FILE *fp)
{
    fpos_t pos = n;
    unsigned int buff;

    fsetpos(fp,&pos);
    fread(&buff,sizeof(unsigned int),1,fp);

    return Little2Big(buff);
}

unsigned int Little2Big(unsigned int i)
{
    unsigned int b0,b1,b2,b3;

    b0 = (i & 0x000000ff) << 24u;
    b1 = (i & 0x0000ff00) << 8u;
    b2 = (i & 0x00ff0000) >> 8u;
    b3 = (i & 0xff000000) >> 24u;

    return b0 | b1 | b2 | b3;
}
