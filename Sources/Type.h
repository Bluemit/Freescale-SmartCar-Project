#ifndef TYPE_H
#define TYPE_H

//common type
typedef volatile unsigned char U8;
typedef volatile unsigned int U16;
typedef volatile unsigned long U32;
typedef volatile signed char S8;
typedef volatile int S16;
typedef volatile long S32;
//typedef volatile long long S64;
typedef volatile unsigned char B2;
typedef unsigned char u8;
typedef unsigned int u16;//int = short
typedef unsigned long u32;
typedef signed char s8;
typedef int s16;
typedef long s32;
//typedef long long s64;
typedef unsigned char b2;

//some common command
#define insert(a,b,c) if ((a)<(b)) a=b;else if ((a)>(c)) a=c;
#define judge_in(a,b,c) (((b)<=(a)&&(a)<=(c))?1:0)
#define insert_in(a,b,c) ((a)<(b)?(b):(a)>(c)?c:a)
#define maxab(a,b) ((a)<(b)?b:a)
#define minab(a,b) ((a)>(b)?b:a)
#define abs0(a) ((a)>0?a:0)
#define abs(a) ((a)>0?a:-(a))

#endif
