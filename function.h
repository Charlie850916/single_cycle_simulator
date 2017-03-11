#include <stdio.h>
#include <stdlib.h>

int s[32], d_mem[1024];

unsigned int PC, LO, HI, i_num, d_num;

FILE *fp_i, *fp_d;

int overwriteHL, halt;

void Initial();

void Ending();

unsigned int Little2Big(unsigned int i); //function done

unsigned int GetLineN(int n, FILE *fp); //function done

unsigned int GetOpcode(unsigned int i);

unsigned int Get_rs(unsigned int i);

unsigned int Get_rt(unsigned int i);

unsigned int Get_rd(unsigned int i);

unsigned int Get_C(unsigned int i);

unsigned int Get_func(unsigned int i);

short int Get_i(unsigned int i);

int Get_addr(unsigned int i);

void R_type_func(unsigned int s,unsigned int t,unsigned int d,unsigned int C,unsigned int func);

void I_type_func(unsigned int op, unsigned int s, unsigned int t,short int im);

void WriteZero();

void OverFlow_add(int s, int t, int d, int p);

void OverFlow_sub(int s, int t, int d, int p);

void OverFlow_mult(int a, int b, int HI);

int Misalignment(int i);

int AddressOverflow(int i, int b);
