#include <stdio.h>
#include <string.h>
#include "get_images.h"

void r_type_to_rec(char (*ins)[20][30], rec* rp, unsigned int funct, unsigned int rs, unsigned int rt, unsigned int rd, int C);
void i_type_to_rec(char (*ins)[20][30], rec* rp, unsigned int opcode, unsigned int rs, unsigned int rt, unsigned int C);
int string_to_int(char* str);
int find_string(char (*ins)[20][30], char *demand_word, int cur_num);

void ri_func(char (*ins)[20][30], rec* rp, int cur_num, char* name, char* v1, char* v2, char* v3){
    unsigned int code = 0;
    unsigned int tmp = 0;

    // r type below
    if(strcmp(name, "add") == 0){
        r_type_to_rec(ins, rp, 0x20, string_to_int(v2), string_to_int(v3), string_to_int(v1), 0);
    }else if(strcmp(name, "sub") == 0){
        r_type_to_rec(ins, rp, 0x22, string_to_int(v2), string_to_int(v3), string_to_int(v1), 0);
    }else if(strcmp(name, "and") == 0){
        r_type_to_rec(ins, rp, 0x24, string_to_int(v2), string_to_int(v3), string_to_int(v1), 0);
    }else if(strcmp(name, "or") == 0){
        r_type_to_rec(ins, rp, 0x25, string_to_int(v2), string_to_int(v3), string_to_int(v1), 0);
    }else if(strcmp(name, "xor") == 0){
        r_type_to_rec(ins, rp, 0x26, string_to_int(v2), string_to_int(v3), string_to_int(v1), 0);
    }else if(strcmp(name, "nor") == 0){
        r_type_to_rec(ins, rp, 0x27, string_to_int(v2), string_to_int(v3), string_to_int(v1), 0);
    }else if(strcmp(name, "nand") == 0){
        r_type_to_rec(ins, rp, 0x28, string_to_int(v2), string_to_int(v3), string_to_int(v1), 0);
    }else if(strcmp(name, "slt") == 0){
        r_type_to_rec(ins, rp, 0x2a, string_to_int(v2), string_to_int(v3), string_to_int(v1), 0);
    }else if(strcmp(name, "sll") == 0){
        printf("SLL:  %s %s %d\n", v2, v1, string_to_int(v3));
        r_type_to_rec(ins, rp, 0x00, 0, string_to_int(v2), string_to_int(v1), string_to_int(v3));
    }else if(strcmp(name, "srl") == 0){
        printf("SRL:  %s %s %d\n", v2, v1, string_to_int(v3));
        r_type_to_rec(ins, rp, 0x02, 0, string_to_int(v2), string_to_int(v1), string_to_int(v3));
    }else if(strcmp(name, "sra") == 0){
        printf("SRA:  %s %s %d\n", v2, v1, string_to_int(v3));
        r_type_to_rec(ins, rp, 0x03, 0, string_to_int(v2), string_to_int(v1), string_to_int(v3));
    }else if(strcmp(name, "jr") == 0){
        r_type_to_rec(ins, rp, 0x08, string_to_int(v1), 0, 0, 0);
    }

    // i type below

    else if(strcmp(name, "addi") == 0){
        printf("addi!!   C = %d\n", string_to_int(v3));
        i_type_to_rec(ins, rp, 0x08, string_to_int(v2), string_to_int(v1), string_to_int(v3));
    }else if(strcmp(name, "lw") == 0){
        i_type_to_rec(ins, rp, 0x23, string_to_int(v3), string_to_int(v1), string_to_int(v2));
    }else if(strcmp(name, "lh") == 0){
        i_type_to_rec(ins, rp, 0x21, string_to_int(v3), string_to_int(v1), string_to_int(v2));
    }else if(strcmp(name, "lhu") == 0){
        i_type_to_rec(ins, rp, 0x25, string_to_int(v3), string_to_int(v1), string_to_int(v2));
    }else if(strcmp(name, "lb") == 0){
        i_type_to_rec(ins, rp, 0x20, string_to_int(v3), string_to_int(v1), string_to_int(v2));
    }else if(strcmp(name, "lbu") == 0){
        i_type_to_rec(ins, rp, 0x24, string_to_int(v3), string_to_int(v1), string_to_int(v2));
    }else if(strcmp(name, "sw") == 0){
        i_type_to_rec(ins, rp, 0x2b, string_to_int(v3), string_to_int(v1), string_to_int(v2));
    }else if(strcmp(name, "sh") == 0){
        i_type_to_rec(ins, rp, 0x29, string_to_int(v3), string_to_int(v1), string_to_int(v2));
    }else if(strcmp(name, "sb") == 0){
        i_type_to_rec(ins, rp, 0x28, string_to_int(v3), string_to_int(v1), string_to_int(v2));
    }else if(strcmp(name, "lui") == 0){
        i_type_to_rec(ins, rp, 0x0f, 0, string_to_int(v1), string_to_int(v2));
    }else if(strcmp(name, "andi") == 0){
        i_type_to_rec(ins, rp, 0x0c, string_to_int(v2), string_to_int(v1), string_to_int(v3));
    }else if(strcmp(name, "ori") == 0){
        printf("ori: %s\n", v3);
        i_type_to_rec(ins, rp, 0x0d, string_to_int(v2), string_to_int(v1), string_to_int(v3));
    }else if(strcmp(name, "nori") == 0){
        i_type_to_rec(ins, rp, 0x0e, string_to_int(v2), string_to_int(v1), string_to_int(v3));
    }else if(strcmp(name, "slti") == 0){
        printf("slti: %s %d %s\n", v2, string_to_int(v1), v3);
        i_type_to_rec(ins, rp, 0x0a, string_to_int(v2), string_to_int(v1), string_to_int(v3));
    }else if(strcmp(name, "beq") == 0){
        printf("found_string = %d\n", find_string(ins, v3, cur_num));
        i_type_to_rec(ins, rp, 0x04, string_to_int(v1), string_to_int(v2), find_string(ins, v3, cur_num));
    }else if(strcmp(name, "bne") == 0){
        printf("found_string = %d\n", find_string(ins, v3, cur_num));
        i_type_to_rec(ins, rp, 0x05, string_to_int(v1), string_to_int(v2), find_string(ins, v3, cur_num));
    }
    //special functions below


    else if(strcmp(name, "move") == 0){
        ri_func(ins, rp, cur_num, "add", v1, "zero", v2);
    }else if(strcmp(name, "blt") == 0){
        ri_func(ins, rp, cur_num, "slt", "at", v1, v2);
        ri_func(ins, rp, cur_num, "bne", "at", "zero", v3);
    }
}

void r_type_to_rec(char (*ins)[20][30], rec* rp, unsigned int funct, unsigned int rs, unsigned int rt, unsigned int rd, int C){
    unsigned int num = 0;
    unsigned int tmp;
    tmp = funct << 32-6;
    num += tmp >> 32-6;
    tmp = C << 32-5;
    tmp = tmp >> 21;
    num += tmp;
    tmp = rd << 11;
    num += tmp;
    tmp = rt << 16;
    num += tmp;
    tmp = rs << 21;
    num += tmp;
    int_to_rec(rp, num);
}
void i_type_to_rec(char (*ins)[20][30], rec* rp, unsigned int opcode, unsigned int rs, unsigned int rt, unsigned int C){
    unsigned int num = 0;
    unsigned int tmp;
    printf("opcode = %06x\n", opcode);
    tmp = C << 16;
    num += (tmp >> 16);
    printf("num = %08x\n", num);
    printf("rt = %08x\n", rt);
    tmp = rt << 16;
    num += tmp;
    printf("num = %08x\n", num);
    tmp = rs << 21;
    num += tmp;
    printf("num = %08x\n", num);
    tmp = opcode << 26;
    printf("tmp = %08x\n", tmp);
    printf("num = %08x\n", num);
    num += tmp;
    int_to_rec(rp, num);
    printf("%x\n", num);
    printf("%x %x %x %x\n", rp->a, rp->b, rp->c, rp->d);
}

int find_string(char (*ins)[20][30], char *demand_word, int cur_num){
    int i;
    char str[30];
    for(i = 0; i<50; i++){
        strcpy(str, demand_word);
        strcat(str, ":");
        if(strcmp(ins[i][0], str) == 0) return (i - cur_num - 1);
    }
    return 520;
}

int string_to_int(char* str){
    int i;
    int neg = 1;
    int advance = 0;
    int tmp;
    if(strcmp(str, "zero") == 0) {
        return 0;
    }else if(strcmp(str, "at") == 0) {
        return 1;
    }else if(strcmp(str, "v0") == 0) {
        return 2;
    }else if(strcmp(str, "v1") == 0) {
        return 3;
    }else if(strcmp(str, "a0") == 0) {
        return 4;
    }else if(strcmp(str, "a1") == 0) {
        return 5;
    }else if(strcmp(str, "a2") == 0) {
        return 6;
    }else if(strcmp(str, "a3") == 0) {
        return 7;
    }else if(strcmp(str, "t0") == 0) {
        return 8;
    }else if(strcmp(str, "t1") == 0) {
        return 9;
    }else if(strcmp(str, "t2") == 0) {
        return 10;
    }else if(strcmp(str, "t3") == 0) {
        return 11;
    }else if(strcmp(str, "t4") == 0) {
        return 12;
    }else if(strcmp(str, "t5") == 0) {
        return 13;
    }else if(strcmp(str, "t6") == 0) {
        return 14;
    }else if(strcmp(str, "t7") == 0) {
        return 15;
    }else if(strcmp(str, "s0") == 0) {
        return 16;
    }else if(strcmp(str, "s1") == 0) {
        return 17;
    }else if(strcmp(str, "s2") == 0) {
        return 18;
    }else if(strcmp(str, "s3") == 0) {
        return 19;
    }else if(strcmp(str, "s4") == 0) {
        return 20;
    }else if(strcmp(str, "s5") == 0) {
        return 21;
    }else if(strcmp(str, "s6") == 0) {
        return 22;
    }else if(strcmp(str, "s7") == 0) {
        return 23;
    }else if(strcmp(str, "t8") == 0) {
        return 24;
    }else if(strcmp(str, "t9") == 0) {
        return 25;
    }else if(strcmp(str, "k0") == 0) {
        return 26;
    }else if(strcmp(str, "k1") == 0) {
        return 27;
    }else if(strcmp(str, "gp") == 0) {
        return 28;
    }else if(strcmp(str, "sp") == 0) {
        return 29;
    }else if(strcmp(str, "fp") == 0) {
        return 30;
    }else if(strcmp(str, "ra") == 0) {
        return 31;
    }


    if(str[0] == '-'){
        printf("NEGATIVE!!\n");
        neg = -1;
        advance = 1;
    }
    int num = 0;
    if(str[0+advance] == '0' && (str[1+advance] == 'x' || str[1+advance] == 'X')){
        for(i = 2+advance; str[i] != '\0'; i++){
            if(str[i] == 'a' || str[i] == 'A') tmp = 10;
            else if(str[i] == 'b' || str[i] == 'B') tmp = 11;
            else if(str[i] == 'c' || str[i] == 'C') tmp = 12;
            else if(str[i] == 'd' || str[i] == 'D') tmp = 13;
            else if(str[i] == 'e' || str[i] == 'E') tmp = 14;
            else if(str[i] == 'f' || str[i] == 'F') tmp = 15;
            else tmp = str[i] - '0';
            num *= 16;
            num += tmp;
        }
    }
    else{
        for(i = advance; str[i] != '\0'; i++){
            num *= 10;
            num += str[i] - '0';
        }
    }
    return num*neg;
}
