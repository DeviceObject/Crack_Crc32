//
//  crc32.h
//  CrackCrc32
//
//  Created by PassP on 7/30/15.
//  Copyright (c) 2015 PassP. All rights reserved.
//

#ifndef __CrackCrc32__crc32__
#define __CrackCrc32__crc32__

#include <stdio.h>

#endif /* defined(__CrackCrc32__crc32__) */


void crc32Init(unsigned int *pCrc32);
void crc32Update(unsigned int *pCrc32, const char *pData, unsigned int uSize);
void crc32Finish(unsigned int *pCrc32);

