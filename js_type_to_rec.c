#include <stdio.h>
#include <string.h>
#include "get_images.h"
void j_type_to_rec(char (*ins)[20][30], rec* rp, unsigned int opcode, unsigned int C);
int find_string_PC(char (*ins)[20][30], char *demand_word, int PC);
void js_func(char (*ins)[20][30], rec* rp, unsigned int PC, char* name, char* v1){
    unsigned int code = 0;
    unsigned int tmp = 0;


    // r type below
    if(strcmp(name, "j") == 0){
        j_type_to_rec(ins, rp, 0x02, find_string_PC(ins, v1, PC));
    }else if(strcmp(name, "jal") == 0){
        printf("JAL!!  C = %d\n", find_string_PC(ins, v1, PC));
        j_type_to_rec(ins, rp, 0x03, find_string_PC(ins, v1, PC));
    }
}

void j_type_to_rec(char (*ins)[20][30], rec* rp, unsigned int opcode, unsigned int C){
    unsigned int num = 0;
    unsigned int tmp;
    printf("J_TYPE_TO_REC!!\n");
    tmp = opcode << 26;
    num += tmp;
    printf("num = %08x\n", num);
    tmp = C << 6;
    num += (tmp>>6);
    printf("num = %08x\n", num);
    int_to_rec(rp, num);
}

int find_string_PC(char (*ins)[20][30], char *demand_word, int PC){
    int i;
    char str[30];
    for(i = 0; i<50; i++){
        strcpy(str, demand_word);
        strcat(str, ":");
        if(strcmp(ins[i][0], str) == 0) return (PC/4 + i);
    }
    return 520;
}
