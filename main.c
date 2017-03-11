#include <stdio.h>
#include <stdlib.h>
#include "function.h"

int main()
{
    unsigned int IS, opcode, rs, rt, rd, C, func, addr;
    short int im;
    int cycle, inital_PC;

    Initial();
    if(fp_i==NULL || fp_d==NULL) return -1;

    inital_PC = PC;
    cycle = 1;
    printf("0x%08X\n",PC);
    printf("0x%08X\n",i_num);
    printf("0x%08X\n",s[29]);
    int i;
    for(i=0;i<1024;i++) if(d_mem[i]!=0) printf("d%d = 0x%08X\n", i , d_mem[i]);

    while(!halt)
    {
        printf("In cycle %d\n",cycle);
        IS = GetLineN((PC-inital_PC)+8,fp_i);
        printf("IS = 0x%08X\n",IS);
        opcode = GetOpcode(IS);
        switch(opcode)
        {
        case 0x00: // R_type
            rs = Get_rs(IS);
            rt = Get_rt(IS);
            rd = Get_rd(IS);
            C = Get_C(IS);
            func = Get_func(IS);
            PC = PC + 4;
            R_type_func(rs,rt,rd,C,func);
            break;
        case 0x02: // j
            printf("j\n");
            addr = Get_addr(IS);
            PC = ((PC+4)&0xf0000000) | (addr<<2);
            break;
        case 0x03: // jal
            printf("jal\n");
            addr = Get_addr(IS);
            s[31] = PC + 4;
            PC = ((PC+4)&0xf0000000) | (addr<<2);
            printf("s31 = 0x%08X\n",s[31]);
            break;
        case 0x3f: // halt
            halt = 1;
            break;
        default: // I_type
            rs = Get_rs(IS);
            rt = Get_rt(IS);
            im = Get_i(IS);
            I_type_func(opcode,rs,rt,im);
            PC = PC + 4;
            break;
        }
        printf("PC = 0x%08x\n\n", PC);
        cycle++;
        if(s[29]>max_sp) max_sp = s[29];
        if(s[29]<min_sp) min_sp = s[29];
        if(max_sp - min_sp > 1024 * 4) halt = 1;
        if (GetLineN(PC-inital_PC+8,fp_i) == 0xffffffff) halt = 1;
        if (  (PC-inital_PC)  > 4*(i_num-1) ) halt = 1;
    }

    Ending();
    return 0;
}
