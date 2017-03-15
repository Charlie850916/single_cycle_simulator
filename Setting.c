#include <stdio.h>
#include <stdlib.h>
#include "function.h"

int s_p[32];

unsigned int LO_p, HI_p;

void Initial()
{
    int i,buff;

    fp_i = fopen("iimage.bin", "rb");
    fp_d = fopen("dimage.bin", "rb");
    fp_r = fopen("snapshot.rpt", "wb");
    fp_err = fopen("errop_dump.rpt", "wb");

    HI = 0x0000000;
    LO = 0x0000000;
    HI_p = 0x00000000;
    LO_p = 0x00000000;

    for(i=0 ; i<32 ; i++)
    {
        s[i] = 0x00000000;
        s_p[i] = 0x00000000;
    }

    for(i=0 ; i<2048 ; i++) d_mem[i] = 0;

    PC = GetLineN(0x00, fp_i);
    i_num = GetLineN(0x04, fp_i);
    initial_d = GetLineN(0x00, fp_d);
    d_num = GetLineN(0x04, fp_d);

    s[29] = initial_d;
    s_p[29] = initial_d;

    bias = 1023 - initial_d;

    for(i=0 ; i<d_num ; i++)
    {
        buff = ( GetLineN(i*4+8, fp_d) ) ;
        d_mem[1023+i*4] = (buff >> 24) & 0x000000ff;
        d_mem[1023+i*4+1] = (buff >> 16) & 0x000000ff;
        d_mem[1023+i*4+2] = (buff >> 8) & 0x000000ff;
        d_mem[1023+i*4+3] = buff & 0x000000ff;
    }

    overwriteHL = 0;
    halt = 0;

    InitialImf();

    return;
}

void Ending()
{
    fclose(fp_i);
    fclose(fp_d);
    fclose(fp_r);
    fclose(fp_err);
    return;
}

void InitialImf()
{
    int i;
    fprintf(fp_r,"cycle 0\n");
    for(i=0 ; i<32 ; i++)
    {
        fprintf(fp_r,"$%02d: 0x%08X\n", i, s[i]);
    }
    fprintf(fp_r,"$HI: 0x%08X\n", HI);
    fprintf(fp_r,"$LO: 0x%08X\n", LO);
    fprintf(fp_r,"PC: 0x%08X\n", PC);
    fprintf(fp_r,"\n\n");
    return;
}

void PrintImf()
{
    int i;
    fprintf(fp_r,"cycle %d\n",cycle);
    for(i=0 ; i<32 ; i++)
    {
        if( s[i]!=s_p[i] )
        fprintf(fp_r,"$%02d: 0x%08X\n", i, s[i]);
        s_p[i] = s[i];
    }
    if(HI!=HI_p)
    {
        fprintf(fp_r,"$HI: 0x%08X\n", HI);
        HI_p = HI;
    }
    if(LO!=LO_p)
    {
        fprintf(fp_r,"$LO: 0x%08X\n", LO);
        LO_p = LO;
    }
    fprintf(fp_r,"PC: 0x%08X\n",PC);
    fprintf(fp_r,"\n\n");
    return;
}
