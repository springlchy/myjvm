#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>
#include "constants.h"

#define READ_U1(fp, dest) fread(dest, 1, 1, fp)
#define READ_U2(fp, dest) \
READ_U1(fp, dest+1);\
READ_U1(fp, dest)

#define READ_U4(fp, dest) \
READ_U2(fp, dest+2);\
READ_U2(fp, dest)

#define READ_U8(fp, dest) \
READ_U4(fp, dest+4); \
READ_U4(fp, dest)

char readByte(FILE *fp)
{
    char c;
    READ_U1(fp, &c);
    return c;
}

uchar readU1(FILE *fp)
{
    uchar uc;
    READ_U1(fp, &uc);
    return uc;
}

short readShort(FILE *fp)
{
    char uc2[2];
    READ_U2(fp, uc2);
    return *(short*)&uc2[0];
}

ushort readUShort(FILE *fp)
{
    uchar uc2[2];
    READ_U2(fp, uc2);
    return *(ushort*)&uc2[0];
}

float readFloat(FILE *fp)
{
    char uc4[4];
    READ_U4(fp, uc4);
    return *(float*)&uc4;
}

uint readUInt(FILE *fp)
{
    uchar uc4[4];
    READ_U4(fp, uc4);
    return *(uint*)&uc4;
}

int readInt(FILE *fp)
{
    char uc4[4];
    READ_U4(fp, uc4);
    return *(int*)&uc4;
}

long readLong(FILE *fp)
{
    char uc8[8];
    READ_U8(fp, uc8);
    return *(long*)&uc8;
}
double readDouble(FILE *fp)
{
    char uc8[8];
    READ_U8(fp, uc8);
    return *(double*)&uc8;
}

void readBytes(FILE *fp, uchar dest[], uint len)
{
    fread(dest, len, 1, fp);
}

void displayHex(uchar s[], int len)
{
    ushort i=0;
    printf("0x");
    while(i < len) {
        printf("%02X ", s[i]);
        i++;
    }
}

#endif
