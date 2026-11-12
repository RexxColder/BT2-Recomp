#include "common.h"

s32 Dma_BeginDirect(void);
void Dma_EndDirect(s32 arg0);
void TexFile_UploadOne(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00271370(void);

#define SD(p, o, v) (*(s64 *)((u8 *)(p) + (o)) = (v))

void func_00277E70(u8 *arg0, s32 arg1, s64 arg2) {
    s64 s0;
    s64 s1;
    s64 s2;
    s64 s5;
    s64 s6;
    s64 s7;
    s64 fp;
    s64 a0;
    s64 a1;
    s64 v0;
    s64 v1;
    s32 s3;
    s32 sp0;
    s32 p10;
    u8 *p;
    u8 *q;
    u8 *tmp;

    s5 = 0;
    s7 = 0x7000;
    fp = 0x8000;
    s0 = (s64)((u64)arg2 << 24);
    s1 = (s64)(s32)((u32)arg1 << 4);
    p = (u8 *)(s32)Dma_BeginDirect();
    SD(p, 0, ((s64)0x10000000 << 32) | 0x8005);
    SD(p, 8, 0xE);
    p += 0x10;
    SD(p, 0, 0x44);
    SD(p, 8, 0x42);
    p += 0x10;
    SD(p, 0, 0);
    SD(p, 8, 0x4A);
    p += 0x10;
    SD(p, 0, 0x30000);
    SD(p, 8, 0x47);
    p += 0x10;
    s0 = s0 | 0x808080;
    SD(p, 8, 1);
    SD(p, 0, s0);
    p += 0x10;
    SD(p, 0, 5);
    SD(p, 8, 8);
    p += 0x10;
    Dma_EndDirect((s32)p);
    sp0 = (s32)s1;

    do {
        s3 = 0;
        s6 = (s64)((s32)s5 << 2);
        s2 = (s64)sp0 + 0x7800;
        s1 = (s64)sp0 + 0x7000;
        a1 = s6;
        do {
            s3 += 1;
            s0 = (s64)((s32)a1 << 6);
            tmp = (u8 *)(s32)(s0 + *(s32 *)(arg0 + 0x10));
            TexFile_UploadOne((s32)arg0, (s32)a1, 0x3000, *(s32 *)(tmp + 0x10) + 0x3000);
            func_00271370();
            q = (u8 *)(s32)Dma_BeginDirect();
            a0 = s7 << 16;
            SD(q, 8, 0x535306);
            SD(q, 0, ((s64)0x64000000 << 32) | 0x8001);
            q += 0x10;
            a0 = s1 | a0;
            p10 = *(s32 *)(arg0 + 0x10);
            a1 = s2 | (fp << 16);
            s2 += 0x800;
            s0 = (s64)(s32)(s0 + p10);
            SD(q, 8, 0x156);
            v0 = *(s32 *)((u8 *)(s32)s0 + 0x10);
            s1 += 0x800;
            v1 = *(s64 *)((u8 *)(s32)s0 + 0x30);
            v0 = (s64)(s32)(v0 + 0x3000);
            v1 = v1 | (v0 << 37);
            v0 = ((s64)4 << 32) | 0x3000;
            v1 = v1 | v0;
            SD(q, 0, v1);
            q += 0x10;
            SD(q, 8, a0);
            SD(q, 0, 0);
            q += 0x10;
            SD(q, 0, 0x10000800);
            SD(q, 8, a1);
            Dma_EndDirect((s32)(q + 0x10));
            a1 = s3 + s6;
        } while (s3 < 4);
        s5 += 1;
        fp += 0x1000;
        s7 += 0x1000;
    } while (s5 < 2);
}
