#include <stdio.h>
#include <stdlib.h>
#include "function.h"

void I_type_func(unsigned int op, unsigned int rs, unsigned int rt,short int im)
{
    int buff, byte;
    switch(op)
    {
    case 0x08: // addi
        printf("addi\n");
        s[rt] = s[rs] + im;
        OverFlow_add(s[rs],im,s[rt],rt);
        printf("s%d 0x%08x\n", rt, s[rt]);
        break;
    case 0x09: // addiu
        printf("addiu\n");
        s[rt] = s[rs] + im;
        printf("s%d 0x%08x\n", rt, s[rt]);
        break;
    case 0x23: // lw
        printf("lw\n");
        if(Misalignment((s[29]+s[rs]+im)%4)) break;
        if(AddressOverflow(s[29]+s[rs]+im,0)) break;
        s[rt] = d_mem[(s[29]+s[rs]+im)>>2];
        printf("s%d 0x%08x\n", rt, s[rt]);
        break;
    case 0x21: // lh
        printf("lh\n");
        if(Misalignment((s[29]+s[rs]+im)%2)) break;
        if(AddressOverflow(s[29]+s[rs]+im,2)) break;
        buff = d_mem[(s[29]+s[rs]+im)>>2];
        s[rt] = ((s[29]+s[rs]+im)%4==0) ? buff >> 16 : ( (buff&0x0000ffff) << 16) >> 16;
        printf("s%d 0x%08x\n", rt, s[rt]);
        break;
    case 0x25: // lhu
        printf("lhu\n");
        if(Misalignment((s[29]+s[rs]+im)%2)) break;
        if(AddressOverflow(s[29]+s[rs]+im,2)) break;
        buff = d_mem[(s[29]+s[rs]+im)>>2];
        s[rt] = ((s[29]+s[rs]+im)%4==0) ? (buff >> 16) & 0x0000ffff : (buff&0x0000ffff) ;
        printf("s%d = 0x%08x\n", rt, s[rt]);
        break;
    case 0x20: // lb
        printf("lb\n");
        if(AddressOverflow(s[29]+s[rs]+im,3)) break;
        byte = (s[29]+s[rs]+im)%4;
        buff = d_mem[(s[29]+s[rs]+im)>>2];
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
        printf("s%d 0x%08x\n", rt, s[rt]);
        break;
    case 0x24: // lbu
        printf("lbu\n");
        if(AddressOverflow(s[29]+s[rs]+im,3)) break;
        byte = (s[29]+s[rs]+im)%4;
        buff = d_mem[(s[29]+s[rs]+im)>>2];
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
        printf("s%d 0x%08x\n", rt, s[rt]);
        break;
    case 0x2b: // sw
        printf("sw\n");
        if(Misalignment((s[29]+s[rs]+im)%4)) break;
        if(AddressOverflow(s[29]+s[rs]+im,0)) break;
        d_mem[(s[29]+s[rs]+im)>>2] = s[rt];
        break;
    case 0x29: // sh
        printf("sh\n");
        if(Misalignment((s[29]+s[rs]+im)%2)) break;
        if(AddressOverflow(s[29]+s[rs]+im,2)) break;
        buff = d_mem[(s[29]+s[rs]+im)>>2];
        if((s[29]+s[rs]+im)%4==0)
        {
            buff = buff & 0x0000ffff;
            d_mem[(s[29]+s[rs]+im)>>2] = buff | ((s[rt]&0x0000ffff)<<16);
        }
        else
        {
            buff = buff & 0xffff0000;
            d_mem[(s[29]+s[rs]+im)>>2] = buff | ((s[rt]&0x0000ffff));
        }
        break;
    case 0x28: // sb
        printf("sb\n");
        if(AddressOverflow(s[29]+s[rs]+im,3)) break;
        byte = (s[29]+s[rs]+im)%4;
        buff = d_mem[(s[29]+s[rs]+im)>>2];
        switch(byte)
        {
        case 0:
            buff = buff & 0x00ffffff;
            d_mem[(s[29]+s[rs]+im)>>2] = buff | ((s[rt]&0x000000ff)<<24);
            break;
        case 1:
            buff = buff & 0xff00ffff;
            d_mem[(s[29]+s[rs]+im)>>2] = buff | ((s[rt]&0x000000ff)<<16);
            break;
        case 2:
            buff = buff & 0xffff00ff;
            d_mem[(s[29]+s[rs]+im)>>2] = buff | ((s[rt]&0x000000ff)<<8);
            break;
        case 3:
            buff = buff & 0xff00ffff;
            d_mem[(s[29]+s[rs]+im)>>2] = buff | (s[rt]&0x000000ff);
            break;
        }
        break;
    case 0x0f: // lui
        printf("lui\n");
        s[rt] = im << 16;
        printf("s%d 0x%08x\n", rt, s[rt]);
        break;
    case 0x0c: // andi
        printf("andi\n");
        s[rt] = s[rs] & im;
        printf("s%d 0x%08x\n", rt, s[rt]);
        break;
    case 0x0d: // ori
        printf("ori\n");
        s[rt] = s[rs] | im;
        printf("s%d 0x%08x\n", rt, s[rt]);
        break;
    case 0x0e: // nori
        printf("nori\n");
        s[rt] = ~(s[rs] | im);
        printf("s%d 0x%08x\n", rt, s[rt]);
        break;
    case 0x0a: // slti
        printf("slti\n");
        printf("s[rs] = %d , im = %d\n",s[rs],im);
        s[rt] = s[rs] < im ;
        printf("s%d 0x%08x\n", rt, s[rt]);
        break;
    case 0x04: // beq
        printf("beq\n");
        if(s[rs]==s[rt]) PC = PC + 4*im;
        break;
    case 0x05: // bne
        printf("bne\n");
        if(s[rs]!=s[rt]) PC = PC + 4*im;
        break;
    case 0x07: // bgtz
        printf("bgtz\n");
        if(s[rs]>0) PC = PC + 4*im;
        break;
    default:
        printf("No this insturction\n");
        halt = 1;
        break;
    }
    return;
}
