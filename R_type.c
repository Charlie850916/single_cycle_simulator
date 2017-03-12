#include <stdio.h>
#include <stdlib.h>
#include "function.h"

void R_type_func(unsigned int rs, unsigned int rt, unsigned int rd, unsigned int C, unsigned int func)
{
    switch(func)
    {
    case 0x20: // add
        if(s0_Overwrite(rd)) break;
        s[rd] = s[rs] + s[rt];
        OverFlow_add(s[rs], s[rt], s[rd], rd);
        break;
    case 0x21: // addu
        if(s0_Overwrite(rd)) break;
        s[rd] = s[rs] + s[rt];
        break;
    case 0x22: // sub
        if(s0_Overwrite(rd)) break;
        s[rd] = s[rs] - s[rt];
        OverFlow_sub(s[rs], s[rt], s[rd], rd);
        break;
    case 0x24: // and
        if(s0_Overwrite(rd)) break;
        s[rd] = (s[rs] & s[rt]);
        break;
    case 0x25: // or
        if(s0_Overwrite(rd)) break;
        s[rd] = (s[rs] | s[rt]);
        break;
    case 0x26: // xor
        if(s0_Overwrite(rd)) break;
        s[rd] = (s[rs] ^ s[rt]);
        break;
    case 0x27: // nor
        if(s0_Overwrite(rd)) break;
        s[rd] = ~(s[rs] | s[rt]);
        break;
    case 0x28: // nand
        if(s0_Overwrite(rd)) break;
        s[rd] = ~(s[rs] & s[rt]);
        break;
    case 0x2a: // slt
        if(s0_Overwrite(rd)) break;
        s[rd] = (s[rs] < s[rt]);
        break;
    case 0x00: // sll
        if(s0_Overwrite(rd)) break;
        s[rd] = s[rt] << C;
        break;
    case 0x02: // srl
        if(s0_Overwrite(rd)) break;
        s[rd] = ( (s[rt] >> C) & 0x7fffffff );
        break;
    case 0x03: // sra
        if(s0_Overwrite(rd)) break;
        s[rd] = s[rt] >> C;
        break;
    case 0x08: // jr
        PC = s[rs];
        break;
    case 0x18: // mult
        if(overwriteHL) fprintf(fp_err ,"In cycle %d: Overwrite HI-LO registers\n", cycle);
        long long a, b, c, c1 ,c2;
        a = s[rs];
        b = s[rt];
        c = a*b;
        c1 = c >> 32;
        c2 = c & 0x00000000ffffffff ;
        HI = c1;
        LO = c2 ;
        OverFlow_mult(s[rs],s[rt],c);
        overwriteHL = 1;
        break;
    case 0x19: // multu
        if(overwriteHL) fprintf(fp_err ,"In cycle %d: Overwrite HI-LO registers\n", cycle);
        long long a_u, b_u, c_u, c1_u, c2_u;
        a_u = ( s[rs] & 0x00000000ffffffff);
        b_u = ( s[rt] & 0x00000000ffffffff);
        c_u = a_u * b_u;
        c1_u = c_u >>32;
        c2_u = c_u & 0x00000000ffffffff ;
        HI = c1_u;
        LO = c2_u ;
        overwriteHL = 1;
        break;
    case 0x10: // mfhi
        if(s0_Overwrite(rd)) break;
        s[rd] = HI;
        overwriteHL = 0;
        break;
    case  0x12: // mflo
        if(s0_Overwrite(rd)) break;
        s[rd] = LO;
        overwriteHL = 0;
        break;
    }
    return;
}
