#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "get_images.h"


void int_to_rec(rec* rp, int num){
    unsigned int tmp;

    tmp = num << 24;
    rp->d = tmp >> 24;

    tmp = num << 16;
    rp->c = tmp >> 24;

    tmp = num << 8;
    rp->b = tmp >> 24;

    rp->a = num >> 24;
}

void get_input(){

    FILE* input;
    char file_name[5];

    FILE* output = fopen("middle_file.txt", "w");

    input = fopen("new.S", "r");


    if(input == 0){
        printf("can't open\n");
        return ;
    }

    int get;
    int blank = 0;
    int instruct_num = 0;


    get = fgetc(input);
    while(get != EOF){

        while(get == ' ' || get == '\t' || get == '$' || get == '(' || get == ')' || get == ',' ){
            get = fgetc(input);
            blank = 1;
        }
        if(get == '#'){
            get = fgetc(input);
            while(get != '\n') get = fgetc(input);
            fputc(get, input);
        }
        if(get == '\n') {
            instruct_num++;
            fprintf(output, " @"); // @ denote '\n'
        }

        (blank == 1)? fprintf(output, " %c", get): fprintf(output, "%c", get);
        blank = 0;
        get = fgetc(input);



    }

    fclose(input);
    fclose(output);
    get_binary(instruct_num);
}
