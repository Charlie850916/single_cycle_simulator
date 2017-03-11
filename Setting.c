#include <stdio.h>
#include <stdlib.h>
#include "function.h"

void Initial()
{
    int i;

    fp_i = fopen("iimage.bin", "rb");
    fp_d = fopen("dimage.bin", "rb");

    HI = 0x0000000;
    LO = 0x0000000;
    for(i=0 ; i<32 ; i++) s[i] = 0x00000000;
    for(i=0 ; i<1024 ; i++) d_mem[i] = 0x00000000;
    PC = GetLineN(0x00, fp_i);
    i_num = GetLineN(0x04, fp_i);
    s[29] = GetLineN(0x00, fp_d);
    d_num = GetLineN(0x04, fp_d);
    for(i=0 ; i<d_num ; i++) d_mem[(s[29]>>2)+i] = GetLineN((i<<2)+8, fp_d);
    overwriteHL = 0;
    halt = 0;

    return;
}

void Ending()
{
    fclose(fp_i);
    fclose(fp_d);
    return;
}
