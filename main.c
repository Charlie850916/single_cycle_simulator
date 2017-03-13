#include <stdio.h>
#include <stdlib.h>
#include "function.h"

int main()
{
    unsigned int IS, opcode, addr;
    int inital_PC;

    Initial();
    if(fp_i==NULL || fp_d==NULL) return -1;

    inital_PC = PC;

    cycle = 1;

    while(!halt)
    {
        IS = GetLineN(PC-inital_PC+8,fp_i);
        fprintf(fp_r,"cycle %d\n",cycle);
        opcode = GetOpcode(IS);
        switch(opcode)
        {
        case 0x00: // R_type
            PC = PC + 4;
            R_type_func(Get_rs(IS),Get_rt(IS),Get_rd(IS),Get_C(IS),Get_func(IS));
            break;
        case 0x02: // j
            addr = Get_addr(IS);
            PC = ((PC+4)&0xf0000000) | (addr<<2);
            break;
        case 0x03: // jal
            addr = Get_addr(IS);
            s[31] = PC + 4;
            PC = ((PC+4)&0xf0000000) | (addr<<2);
            break;
        case 0x3f: // halt
            halt = 1;
            break;
        default: // I_type
            I_type_func(opcode,Get_rs(IS),Get_rt(IS),Get_i(IS));
            PC = PC + 4;
            break;
        }
        cycle++;
        PrintImf();
        if(GetOpcode(GetLineN(PC-inital_PC+8,fp_i))==0x3f) halt = 1;
    }

    Ending();
    return 0;
}
