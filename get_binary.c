#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "get_images.h"

void my_strcpy(char* s1, char* s2){
    int i;
    for(i = 0; i < strlen(s2); i++){
        s1[i] = s2[i];
    }
    s1[i] = '\0';
}
void get_binary(int instruct_num){

    int i, j;

    int PC = 0;
    int sp = 0;

    rec iimage_bin;
    rec dimage_bin;

    FILE* iimage = fopen("iimage.bin", "wb");
    FILE* dimage = fopen("dimage.bin", "wb");

    FILE* input = fopen("middle_file.txt", "r+");

    printf("PC value(in hex): ");
    scanf("%x", &PC);
    int_to_rec(&iimage_bin, PC);
    fwrite(&iimage_bin,sizeof(rec),1,iimage);
    int_to_rec(&iimage_bin, instruct_num);
    fwrite(&iimage_bin,sizeof(rec),1,iimage);

    printf("$sp value(in hex): ");
    scanf("%x", &sp);
    int_to_rec(&dimage_bin, sp);
    fwrite(&dimage_bin,sizeof(rec),1,dimage);

    int dimage_num = -1;
    printf("How many words in dimage (0~256): ");
    scanf("%d", &dimage_num);

    while(dimage_num<0 || dimage_num>256){
        printf("Enter a number between 0 and 256, or dimage.bin will be larger than 1k!\n");
        printf("How many words in dimage (0~256): ");
        scanf("%d", &dimage_num);
    }

    int tmp_num;
    int_to_rec(&dimage_bin, dimage_num);
    fwrite(&dimage_bin,sizeof(rec),1,dimage);

    FILE* dimage_gen = fopen("dimage_gen.txt", "r");
    if(dimage_gen == 0){
        printf("can't open dimage_gen!!\n");
        return;
    }
    for(i = 0; i < dimage_num; i++){
        fscanf(dimage_gen, "%x", &tmp_num);
        printf("%x\n", tmp_num);
        int_to_rec(&dimage_bin, tmp_num);
        fwrite(&dimage_bin,sizeof(rec),1,dimage);
    }


    char str[30];
    char ins[500][20][30];
    int is_not_end;
    is_not_end = fscanf(input, "%s", str);

    for(i = 0; is_not_end != -1 && is_not_end != 0; i++){
        for(j = 1; strcmp(str, "@") != 0 && j < 5; j++){
            if(str[strlen(str)-1] == ':'){
                j = j-1;
            }
            strcpy(ins[i][j], str);
            is_not_end = fscanf(input, "%s", str);
            printf("%s ", str);
        }
        is_not_end = fscanf(input, "%s", str);
    }


    for(i = 0; i < instruct_num; i++){
        if(strcmp(ins[i][1], "j") == 0 || strcmp(ins[i][1], "jal") == 0){
            printf("JS_FUNC:   PC = 0x%08x, v1 = %s, v2 = %s\n", PC, ins[i][1], ins[i][2]);
            js_func(ins, &iimage_bin, PC, ins[i][1], ins[i][2]);
            fwrite(&iimage_bin,sizeof(rec),1,iimage);
        }else if(strcmp(ins[i][1], "halt") == 0){
            iimage_bin.a = 0xff;
            iimage_bin.b = 0xff;
            iimage_bin.c = 0xff;
            iimage_bin.d = 0xff;
            fwrite(&iimage_bin,sizeof(rec),1,iimage);

        }else{
            printf("i = %d\n", i);
            ri_func(ins, &iimage_bin, i, ins[i][1], ins[i][2], ins[i][3], ins[i][4]);
            fwrite(&iimage_bin,sizeof(rec),1,iimage);
        }
    }
    fclose(iimage);
    fclose(dimage);
    fclose(input);
}




