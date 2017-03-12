#include <stdio.h>
#include <stdlib.h>
#include "function.h"

void I_type_func(unsigned int op, unsigned int rs, unsigned int rt,short int im)
{
    int buff, byte;
    switch(op)
    {
    case 0x08: // addi
        if(s0_Overwrite(rt)) break;
        s[rt] = s[rs] + im;
        OverFlow_add(s[rs],im,s[rt],rt);
        break;
    case 0x09: // addiu
        if(s0_Overwrite(rt)) break;
        s[rt] = s[rs] + im;
        break;
    case 0x23: // lw
        s0_Overwrite(rt);
        AddressOverflow(initial_d+s[rs]+im,4);
        if(Misalignment( (s[rs]+im) %4 )) break;
        s[rt] = d_mem[(initial_d+s[rs]+im)/4];
        break;
    case 0x21: // lh
        s0_Overwrite(rt);
        AddressOverflow(initial_d+s[rs]+im,2);
        if(Misalignment( (s[rs]+im) % 2)) break;
        buff = d_mem[(initial_d+s[rs]+im)/4];
        s[rt] = ((initial_d+s[rs]+im)%4==0) ? buff >> 16 : ( (buff&0x0000ffff) << 16) >> 16;
        break;
    case 0x25: // lhu
        s0_Overwrite(rt);
        AddressOverflow(initial_d+s[rs]+im,2);
        if(Misalignment((s[rs]+im)%2)) break;
        buff = d_mem[(initial_d+s[rs]+im)/4];
        s[rt] = ((initial_d+s[rs]+im)%4==0) ? (buff >> 16) & 0x0000ffff : (buff&0x0000ffff) ;
        break;
    case 0x20: // lb
        s0_Overwrite(rt);
        if(AddressOverflow(initial_d+s[rs]+im,1)) break;
        byte = (initial_d+s[rs]+im)%4;
        buff = d_mem[(initial_d+s[rs]+im)/4];
        switch(byte)
        {
        case 0:
            s[rt] = (buff & 0xff000000) >> 24;
            break;
        case 1:
            s[rt] = ( (buff & 0x00ff0000) << 8 ) >> 24;
            break;
        case 2:
            s[rt] = ( (buff & 0x0000ff00) << 16) >> 24;
            break;
        case 3:
            s[rt] = ((buff & 0x000000ff) << 24) >> 24;
            break;
        }
        break;
    case 0x24: // lbu
        s0_Overwrite(rt);
        if(AddressOverflow(initial_d+s[rs]+im,1)) break;
        byte = (initial_d+s[rs]+im)%4;
        buff = d_mem[(initial_d+s[rs]+im)/4];
        switch(byte)
        {
        case 0:
            s[rt] = (buff >> 24) & 0x000000ff;
            break;
        case 1:
            s[rt] = (buff & 0x00ff0000) >> 16;
            break;
        case 2:
            s[rt] = (buff & 0x0000ff00) >> 8;
            break;
        case 3:
            s[rt] = buff & 0x000000ff;
            break;
        }
        break;
    case 0x2b: // sw
        AddressOverflow(initial_d+s[rs]+im,4);
        if(Misalignment((s[rs]+im)%4)) break;
        d_mem[(initial_d+s[rs]+im)/4] = s[rt];
        break;
    case 0x29: // sh
        AddressOverflow(initial_d+s[rs]+im,2);
        if(Misalignment((s[rs]+im)%2)) break;
        buff = d_mem[(initial_d+s[rs]+im)/4];
        if((initial_d+s[rs]+im)%4==0)
        {
            buff = buff & 0x0000ffff;
            d_mem[(initial_d+s[rs]+im)/4] = buff | ((s[rt]&0x0000ffff)<<16);
        }
        else
        {
            buff = buff & 0xffff0000;
            d_mem[(initial_d+s[rs]+im)/4] = buff | ((s[rt]&0x0000ffff));
        }
        break;
    case 0x28: // sb
        if(AddressOverflow(initial_d+s[rs]+im,1)) break;
        byte = (initial_d+s[rs]+im)%4;
        buff = d_mem[(initial_d+s[rs]+im)/4];
        switch(byte)
        {
        case 0:
            buff = buff & 0x00ffffff;
            d_mem[(initial_d+s[rs]+im)/4] = buff | ((s[rt]&0x000000ff)<<24);
            break;
        case 1:
            buff = buff & 0xff00ffff;
            d_mem[(initial_d+s[rs]+im)/4] = buff | ((s[rt]&0x000000ff)<<16);
            break;
        case 2:
            buff = buff & 0xffff00ff;
            d_mem[(initial_d+s[rs]+im)/4] = buff | ((s[rt]&0x000000ff)<<8);
            break;
        case 3:
            buff = buff & 0xff00ffff;
            d_mem[(initial_d+s[rs]+im)/4] = buff | (s[rt]&0x000000ff);
            break;
        }
        break;
    case 0x0f: // lui
        if(s0_Overwrite(rt)) break;
        s[rt] = im << 16;
        break;
    case 0x0c: // andi
        if(s0_Overwrite(rt)) break;
        s[rt] = s[rs] & im;
        break;
    case 0x0d: // ori
        if(s0_Overwrite(rt)) break;
        s[rt] = s[rs] | im;
        break;
    case 0x0e: // nori
        if(s0_Overwrite(rt)) break;
        s[rt] = ~(s[rs] | im);
        break;
    case 0x0a: // slti
        if(s0_Overwrite(rt)) break;
        s[rt] = s[rs] < im ;
        break;
    case 0x04: // beq
        if(s[rs]==s[rt]) PC = PC + 4*im;
        break;
    case 0x05: // bne
        if(s[rs]!=s[rt]) PC = PC + 4*im;
        break;
    case 0x07: // bgtz
        if(s[rs]>0) PC = PC + 4*im;
        break;
    default:
        fprintf(fp_r,"illegal instruction found at 0x0%8X\n",PC);
        halt = 1;
        break;
    }
    s[0] = 0;
    return;
}
