#include <stdio.h>
#include <stdlib.h>

int s[32], d_mem[2048];

unsigned int PC, LO, HI, i_num, d_num, initial_d;

int bias;

FILE *fp_i, *fp_d, *fp_r, *fp_err;

int cycle, overwriteHL, halt, max_sp, min_sp;

void Initial();

void InitialImf();

void PrintImf();

void Ending();

unsigned int Little2Big(unsigned int i);

unsigned int GetLineN(int n, FILE *fp);

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

int s0_Overwrite(int d);

void OverFlow_add(int s, int t, int d);

void OverFlow_mult(int a, int b, long long int c);

int Misalignment(int i);

int AddressOverflow(int sp, int b);
