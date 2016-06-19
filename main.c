#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "get_images.h"
#define INST_NUM 500
#define MEM_NUM 5000
unsigned int PC;
int reg[32];
int mem[MEM_NUM];

void show_reg(FILE* output,unsigned int cycle);//show cycle, reg[], and PC
void show_mem();//show mem


int main(){

    //define snapshot
    dimage_gen();
    get_input();
    return 0;
}



void show_reg(FILE* output, unsigned int cycle){
    fprintf(output, "cycle %d\n", cycle);
    int i;
    for(i = 0 ; i < 32; i++){
        fprintf(output, "$%02d: 0x%08X\n", i, reg[i]);
    }
    fprintf(output, "PC: 0x%08X\n\n\n", PC);
}

void show_mem(){
    //printf("Memory:\n");
    //int i;
    //for(i = 0 ; i < MEM_NUM; i++){
    //    printf("$%2d: 0x%08x\n", i, mem[i]);
    //}
}
