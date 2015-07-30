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
#include <unistd.h>
#include "crc32.h"
#include "crackcrc32.h"

CRACK_THREAD_INFO crack_thread_info;

void *crack_crc32(void *arg){
    
    PTHREAD_PARAMTERS pthread_paramters = 0;
    long current_length = 0;
    unsigned long crc32 = 0;
    
    pthread_paramters = arg;
    crc32 = crack_thread_info.check_crc32;
    
    for (long i = pthread_paramters->calc_length;i >= 0;i--)
    {
        for (long j = 0;j <= i;j++)
        {
            current_length = i;
            
            crc32Init(&crc32);
            crc32Update(&crc32,(char*)((long)crack_thread_info.szDat + j),current_length - j);
            crc32Finish(&crc32);
            sleep(1);
            if (crc32 == 0 || crc32 == 0xFFFFFFFF)
            {
                continue;
            }
            printf("ThreadCount:  %08lx\tOffset:  %08lx\tLength:  %08lx\tCrc32:  %08lx\tCrc32Check:  %08lx\r\n", \
                   crack_thread_info.thread_count,j,current_length - j,crc32,0xFFFFFFFF ^ crc32);
            if (crack_thread_info.check_crc32 == ((long)0xFFFFFFFF ^ crc32))
            {
                printf("Finder,Start Offset:   %08lx\t\t,End Offset:   %08lx\r\n",j,i);
            }
            
        }
    }
    return 0;
}

int main(int argc, const char * argv[])
{
    FILE *fpHdr = 0;
    long size = 0,tmp_size = 0;
    long items = 0;
    int isthread_success = 0;
    void *res = 0;
    int n_status = 0;
    
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
                    crack_thread_info.ThreadParamters[crack_thread_info.thread_count].calc_length = size;
                    isthread_success = pthread_create(&crack_thread_info.thread[crack_thread_info.thread_count], 0, crack_crc32, &crack_thread_info.ThreadParamters[crack_thread_info.thread_count]);
                    if (0 == isthread_success) {
                        crack_thread_info.thread_count++;
                        if (tmp_size < 0x5000) {
                            break;
                        }
                        tmp_size -= 0x5000;
                        if (crack_thread_info.thread_count >= 64) {
                            break;
                        }
                    }
                } while (tmp_size != 0);
                for (int i; i < crack_thread_info.thread_count; i++) {
                    n_status = pthread_join(crack_thread_info.thread[i], &res);
                    if (n_status != 0) {
                        printf("main(): pthread_join failed,thread id:%08lx",(unsigned long)crack_thread_info.thread[i]);
                    }
                }
            }
            
        }
        fclose(fpHdr);
        free(crack_thread_info.szDat);
    }else {
        printf("main(): argv,paramters error.\r\n");
    }
    
    return 0;
}
