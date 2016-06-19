#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "get_images.h"

int dimage_gen(){
    FILE* fp;
    fp = fopen("dimage_gen.txt", "w");
    time_t t;
    srand((unsigned) time(&t));
    int i;
    int mod;
    for(i = 0; i < 256; i++){
        fprintf(fp, "%08x\n", rand()%0xffffffff);
    }
    fclose(fp);

}
