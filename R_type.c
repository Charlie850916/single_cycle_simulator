#include <stdio.h>
#include <stdlib.h>
#include "function.h"

void R_type_func(unsigned int rs, unsigned int rt, unsigned int rd, unsigned int C, unsigned int func)
{
    switch(func)
    {
    case 0x20: // add
        printf("add\n");
        s[rd] = s[rs] + s[rt];
        printf("s%d 0x%08x\n", rd, s[rd]);
        OverFlow_add(s[rs], s[rt], s[rd], rd);
        break;
    case 0x21: // addu
        printf("addu\n");
        s[rd] = s[rs] + s[rt];
        printf("s%d 0x%08x\n", rd, s[rd]);
        break;
    case 0x22: // sub
        printf("sub\n");
        s[rd] = s[rs] - s[rt];
        printf("s%d 0x%08x\n", rd, s[rd]);
        OverFlow_sub(s[rs], s[rt], s[rd], rd);
        break;
    case 0x24: // and
        printf("and\n");
        s[rd] = (s[rs] & s[rt]);
        printf("s%d 0x%08x\n", rd, s[rd]);
        break;
    case 0x25: // or
        printf("or\n");
        s[rd] = (s[rs] | s[rt]);
        printf("s%d 0x%08x\n", rd, s[rd]);
    case 0x26: // xor
        printf("xor\n");
        s[rd] = (s[rs] ^ s[rt]);
        printf("s%d 0x%08x\n", rd, s[rd]);
    case 0x27: // nor
        printf("nor\n");
        s[rd] = ~(s[rs] | s[rt]);
        printf("s%d 0x%08x\n", rd, s[rd]);
        break;
    case 0x28: // nand
        printf("nand\n");
        s[rd] = ~(s[rs] & s[rt]);
        printf("s%d 0x%08x\n", rd, s[rd]);
        break;
    case 0x2a: // slt
        printf("slt\n");
        s[rd] = (s[rs] < s[rt]);
        printf("s%d 0x%08x\n", rd, s[rd]);
        break;
    case 0x00: // sll
        printf("sll\n");
        s[rd] = s[rt] << C;
        printf("s%d 0x%08x\n", rd, s[rd]);
        break;
    case 0x02: // srl
        printf("srl\n");
        s[rd] = ( (s[rt] >> C) & 0x7fffffff );
        printf("s%d 0x%08x\n", rd, s[rd]);
        break;
    case 0x03: // sra
        printf("sra\n");
        s[rd] = s[rt] >> C;
        printf("s%d 0x%08x\n", rd, s[rd]);
        break;
    case 0x08: // jr
        printf("jr\n");
        PC = s[rs];
        break;
    case 0x18: // mult
        if(overwriteHL) printf("HI-LO overwrite\n");
        printf("mult\n");
        long long a, b, c, c1 ,c2;
        a = s[rs];
        b = s[rt];
        c = a*b;
        c1 = c >> 32;
        c2 = c & 0x00000000ffffffff ;
        HI = c1;
        LO = c2 ;
        printf("HI 0x%08x\n", HI);
        printf("LO 0x%08x\n", LO);
        OverFlow_mult(s[rs],s[rt],HI);
        overwriteHL = 1;
        break;
    case 0x19: // multu
        if(overwriteHL) printf("HI-LO overwrite\n");
        printf("multu\n");
        long long a_u, b_u, c_u, c1_u, c2_u;
        a_u = ( s[rs] & 0x00000000ffffffff);
        b_u = ( s[rt] & 0x00000000ffffffff);
        c_u = a_u * b_u;
        c1_u = c_u >>32;
        c2_u = c_u & 0x00000000ffffffff ;
        HI = c1_u;
        LO = c2_u ;
        printf("HI 0x%08x\n", HI);
        printf("LO 0x%08x\n", LO);
        overwriteHL = 1;
        break;
    case 0x10: // mfhi
        s[rd] = HI;
        printf("s%d 0x%08x\n", rd, s[rd]);
        overwriteHL = 0;
        break;
    case  0x12: // mflo
        s[rd] = LO;
        printf("s%d 0x%08x\n", rd, s[rd]);
        overwriteHL = 0;
        break;
    }
    return;
}
