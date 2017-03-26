#include <stdio.h>
#include <stdlib.h>
#include "function.h"

int main()
{
    unsigned int IS, opcode, addr;
    int initial_PC;

    Initial();

    initial_PC = PC;

    cycle = 1;

    while(!halt)
    {
        if(PC>=initial_PC) IS = GetLineN(PC-initial_PC+8,fp_i);
        else IS = 0x00000000;
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
        if(!halt) PrintImf();
        cycle++;
    }

    Ending();
    return 0;
}
