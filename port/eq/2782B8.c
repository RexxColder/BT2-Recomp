#include "common.h"

s32 Dma_BeginDirect(void);
void Dma_EndDirect(s32 arg0);
void TexFile_UploadOne(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00271370(void);

void func_002782B8(s32 arg0, s32 arg1, s32 arg2, s64 arg3) {
    u8 *s6;
    u8 *p;
    u8 *b1;
    u8 *b2;
    u8 *b3;
    u8 *addr0;
    s32 sp0;
    s32 s1;
    s32 s2;
    s32 s3;
    s32 s7;
    s32 a1;
    s32 fp;
    s32 base10;
    s64 s0;
    s64 s4;
    s64 s5;
    s64 a0v;
    s64 a1v;
    s64 w;

    s6 = (u8 *)arg0;
    s1 = arg2 * 16;
    s2 = arg1 * 16;
    s0 = arg3 << 24;

    p = (u8 *)Dma_BeginDirect();
    *(s64 *)(p + 0x0) = ((s64)0x10000000 << 32) | 0x8005;
    *(s64 *)(p + 0x8) = 0xE;
    p += 0x10;
    *(s64 *)(p + 0x0) = 0x44;
    *(s64 *)(p + 0x8) = 0x42;
    p += 0x10;
    *(s64 *)(p + 0x8) = 0x4A;
    *(s64 *)(p + 0x0) = 0;
    p += 0x10;
    *(s64 *)(p + 0x0) = 0x30000;
    *(s64 *)(p + 0x8) = 0x47;
    p += 0x10;
    s0 = s0 | (s64)0x808080;
    *(s64 *)(p + 0x8) = 1;
    *(s64 *)(p + 0x0) = s0;
    p += 0x10;
    *(s64 *)(p + 0x0) = 5;
    *(s64 *)(p + 0x8) = 8;
    s5 = (s64)(s1 + 0x7000);
    s4 = (s64)(0x8000 + s1);
    Dma_EndDirect((s32)(p + 0x10));

    sp0 = s2;
    s7 = 0;
    do {
        s3 = 0;
        s2 = sp0 + 0x7800;
        s1 = sp0 + 0x7000;
        fp = s7 * 4;
        a1 = s3 + fp;
        do {
            s3 += 1;
            addr0 = (u8 *)(s32)(a1 << 6);
            base10 = *(s32 *)(s6 + 0x10);
            TexFile_UploadOne((s32)s6, a1, 0x3000,
                              *(s32 *)((u8 *)(s32)(a1 << 6) + base10 + 0x10) + 0x3000);
            func_00271370();
            p = (u8 *)Dma_BeginDirect();
            *(s64 *)(p + 0x8) = 0x535306;
            *(s64 *)(p + 0x0) = ((s64)0x64000000 << 32) | 0x8001;
            b1 = p + 0x10;
            *(s64 *)(b1 + 0x8) = 0x156;
            a0v = (s64)s1 | ((s64)s5 << 16);
            a1v = (s64)s2 | ((s64)s4 << 16);
            s2 += 0x800;
            addr0 = (u8 *)(s32)((a1 << 6) + base10);
            s1 += 0x800;
            w = *(s64 *)(addr0 + 0x30)
                | ((s64)(*(s32 *)(addr0 + 0x10) + 0x3000) << 37)
                | (((s64)4 << 32) | 0x3000);
            *(s64 *)(b1 + 0x0) = w;
            b2 = b1 + 0x10;
            *(s64 *)(b2 + 0x8) = a0v;
            *(s64 *)(b2 + 0x0) = 0;
            b3 = b2 + 0x10;
            *(s64 *)(b3 + 0x0) = 0x10000800;
            *(s64 *)(b3 + 0x8) = a1v;
            Dma_EndDirect((s32)(b3 + 0x10));
            a1 = s3 + fp;
        } while (s3 < 4);
        s7 += 1;
        s4 += 0x1000;
        s5 += 0x1000;
    } while (s7 < 2);
}
