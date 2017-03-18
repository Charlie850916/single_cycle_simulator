#include <stdio.h>
#include <stdlib.h>
#include "function.h"

void I_type_func(unsigned int op, unsigned int rs, unsigned int rt,short int im)
{
    int buff, byte;
    switch(op)
    {
    case 0x08: // addi
        s0_Overwrite(rt);
        OverFlow_add(s[rs],im,s[rt]+im);
        s[rt] = s[rs] + im;
        break;
    case 0x09: // addiu
        if(s0_Overwrite(rt)) break;
        s[rt] = s[rs] + im;
        break;
    case 0x23: // lw
        s0_Overwrite(rt);
        OverFlow_add(s[rs],im,s[rs]+im);
        if(AddressOverflow(s[rs]+im,4))
        {
            Misalignment( (s[rs]+im) %4 );
            break;
        }
        if(Misalignment( (s[rs]+im) %4 )) break;
        s[rt] = (d_mem[bias+initial_d+s[rs]+im]<<24) | (d_mem[bias+initial_d+s[rs]+im+1] << 16) | (d_mem[bias+initial_d+s[rs]+im+2] << 8) | (d_mem[bias+initial_d+s[rs]+im+3]);
        break;
    case 0x21: // lh
        s0_Overwrite(rt);
        OverFlow_add(s[rs],im,s[rs]+im);
        if(AddressOverflow(s[rs]+im,2))
        {
            Misalignment((s[rs]+im)%2);
            break;
        }
        if(Misalignment( (s[rs]+im) % 2)) break;
        s[rt] = (d_mem[bias+initial_d+s[rs]+im]<<24>>16) | (d_mem[bias+initial_d+s[rs]+im+1]);
        break;
    case 0x25: // lhu
        s0_Overwrite(rt);
        OverFlow_add(s[rs],im,s[rs]+im);
        if(AddressOverflow(s[rs]+im,2))
        {
            Misalignment((s[rs]+im)%2);
            break;
        }
        if(Misalignment((s[rs]+im)%2)) break;
        s[rt] =  (d_mem[bias+initial_d+s[rs]+im]<<8) | (d_mem[bias+initial_d+s[rs]+im+1]);
        break;
    case 0x20: // lb
        s0_Overwrite(rt);
        OverFlow_add(s[rs],im,s[rs]+im);
        if(AddressOverflow(s[rs]+im,1)) break;
        s[rt] = d_mem[bias+initial_d+s[rs]+im] << 24 >> 24;
        break;
    case 0x24: // lbu
        s0_Overwrite(rt);
        OverFlow_add(s[rs],im,s[rs]+im);
        if(AddressOverflow(s[rs]+im,1)) break;
        s[rt] = d_mem[bias+initial_d+s[rs]+im] ;
        break;
    case 0x2b: // sw
        OverFlow_add(s[rs],im,s[rs]+im);
        if(AddressOverflow(s[rs]+im,4))
        {
            Misalignment((s[rs]+im)%4);
            break;
        }
        if(Misalignment((s[rs]+im)%4)) break;
        d_mem[bias+initial_d+s[rs]+im] = (s[rt] >> 24) & 0x000000ff ;
        d_mem[bias+initial_d+s[rs]+im+1] = (s[rt] >> 16) & 0x000000ff ;
        d_mem[bias+initial_d+s[rs]+im+2] = (s[rt] >> 8) & 0x000000ff ;
        d_mem[bias+initial_d+s[rs]+im+3] = s[rt] & 0x000000ff ;
        break;
    case 0x29: // sh
        OverFlow_add(s[rs],im,s[rs]+im);
        if(AddressOverflow(s[rs]+im,2))
        {
            Misalignment((s[rs]+im)%2);
            break;
        }
        if(Misalignment((s[rs]+im)%2)) break;
        d_mem[bias+initial_d+s[rs]+im] = (s[rt] >> 8) & 0x000000ff ;
        d_mem[bias+initial_d+s[rs]+im+1] = s[rt] & 0x000000ff ;
        break;
    case 0x28: // sb
        OverFlow_add(s[rs],im,s[rs]+im);
        if(AddressOverflow(s[rs]+im,1)) break;
        d_mem[bias+initial_d+s[rs]+im] = s[rt] & 0x000000ff ;
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
        OverFlow_add(PC+4,4*im,PC+4+4*im);
        if(s[rs]==s[rt]) PC = PC + 4*im;
        break;
    case 0x05: // bne
        OverFlow_add(PC+4,4*im,PC+4+4*im);
        if(s[rs]!=s[rt]) PC = PC + 4*im;
        break;
    case 0x07: // bgtz
        OverFlow_add(PC+4,4*im,PC+4+4*im);
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
