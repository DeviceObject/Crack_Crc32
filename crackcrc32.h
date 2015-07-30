//
//  crackcrc32.h
//  CrackCrc32
//
//  Created by PassP on 7/30/15.
//  Copyright (c) 2015 PassP. All rights reserved.
//

#ifndef __CrackCrc32__crackcrc32__
#define __CrackCrc32__crackcrc32__

#include <stdio.h>

#endif /* defined(__CrackCrc32__crackcrc32__) */


typedef struct  _THREAD_PARAMTERS
{
    int calc_length;
}THREAD_PARAMTERS,*PTHREAD_PARAMTERS;

typedef struct _CRACK_THREAD_INFO
{
    char *szDat;
    int thread_count;
    int check_crc32;
    pthread_t thread[64];
    THREAD_PARAMTERS ThreadParamters[0x500];
}CRACK_THREAD_INFO,*PCRACK_THREAD_INFO;

