//
//  main.c
//  CrackCrc32
//
//  Created by PassP on 7/27/15.
//  Copyright (c) 2015 PassP. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include "crc32.h"
#include "crackcrc32.h"

int CrackCrc32(char *szbuf,int nSize)
{
    return 0;
}

int main(int argc, const char * argv[])
{
    FILE *fpHdr = 0;
    long size = 0,tmp_size = 0;
    long items = 0;
    CRACK_THREAD_INFO crack_thread_info;
    
    memset(&crack_thread_info,0,sizeof(CRACK_THREAD_INFO));
    
    if (argc == 2) {
        if (0 != argv[1]) {
            fpHdr = fopen(argv[1], "r");
            if (0 == fpHdr) {
                printf("main(): open file failed.\r\n");
                return -1;
            }
            fseek(fpHdr, 0, SEEK_END);
            size = ftell(fpHdr);
            if (0 == size) {
                printf("main(): get file size error.\r\n");
                fclose(fpHdr);
                return -1;
            }
            tmp_size = size;
            crack_thread_info.szDat = (char *)malloc(size);
            if (0 == crack_thread_info.szDat) {
                printf("main(): malloc buf failed.\r\n");
                fclose(fpHdr);
                return -1;
            }
            memset(crack_thread_info.szDat, 0, size);
            if (0 == fread(crack_thread_info.szDat, size, items, fpHdr)) {
                printf("main(): read file error.\r\n");
                free((void *)crack_thread_info.szDat);
                fclose(fpHdr);
                return -1;
            }
            tmp_size -= 0x08;
            crack_thread_info.check_crc32 = *(long *)((long)crack_thread_info.szDat + tmp_size);
            if (0 > crack_thread_info.check_crc32) {
                do {
                    crack_thread_info.ThreadParamters[crack_thread_info.thread_count].calc_length = \
                    size;
                    crack_thread_info.thread[crack_thread_info.thread_count] = \
                    pthread_create(&crack_thread_info.thread[crack_thread_info.thread_count], , <#void *(*)(void *)#>, <#void *restrict#>)
                } while (tmp_size != 0);
            }
        }
    }else {
        printf("main(): argv,paramters error.\r\n");
    }
    return 0;
}
