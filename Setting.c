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
    for(i=0 ; i<2048 ; i++) d_mem[i] = 0x00000000;
    PC = GetLineN(0x00, fp_i);
    i_num = GetLineN(0x04, fp_i);
    initial_d = GetLineN(0x00, fp_d);
    d_num = GetLineN(0x04, fp_d);
    s[29] = initial_d;
    for(i=0 ; i<d_num ; i++) d_mem[(s[29]/4)+i] = GetLineN((i*4)+8, fp_d);
    overwriteH = 0;
    overwriteL = 0;
    max_sp = initial_d;
    min_sp = initial_d;
    halt = 0;

    return;
}

void Ending()
{
    fclose(fp_i);
    fclose(fp_d);
    return;
}
