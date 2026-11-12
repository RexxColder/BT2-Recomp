#include "common.h"

f32 sceVu0InnerProduct(void *arg0, void *arg1);
void sceVu0InterVector(f32 arg0, void *arg1, void *arg2, void *arg3);
void func_003126C8(void *arg0, void *arg1);
void func_00312650(void *arg0, void *arg1, void *arg2, s32 arg3);

s32 func_001ED2D8(u8 *arg0, s32 arg1, u8 *arg2) {
    u8 sp[0x200];
    s32 *flags;
    s32 k;
    s32 nflag;
    s32 i;
    s32 j;
    s32 cnt;
    u8 *s3;
    u8 *vi;
    u8 *vj;
    u8 *tmp;
    f32 d;
    f32 ip0;
    f32 ip1;
    f32 f20;
    f32 f21;

    flags = (s32 *)(sp + 0x1C0);
    tmp = sp + 0x1B0;
    *(s32 *)(sp + 0x1F0) = arg1;
    f20 = 0.0f;
    nflag = 0;

    for (k = 0; k < arg1; k++) {
        vi = arg2 + k * 0x10;
        d = sceVu0InnerProduct(arg0, vi) + *(f32 *)(arg0 + 0xC);
        flags[k] = (d < f20) ? 1 : 0;
        nflag += (d < f20) ? 1 : 0;
    }

    if (nflag == 0) {
        return arg1;
    }
    if (arg1 == nflag) {
        return 0;
    }

    *(s32 *)(sp + 0x1F4) = 0;
    s3 = sp;
    for (i = 0; i < arg1; i++) {
        j = (i + 1 < arg1) ? (i + 1) : 0;
        vi = arg2 + i * 0x10;
        if (flags[i] == 0) {
            cnt = *(s32 *)(sp + 0x1F4) + 1;
            *(s32 *)(sp + 0x1F4) = cnt;
            func_003126C8(s3, vi);
            func_003126C8(s3 + 0x90, vi + 0x90);
            func_003126C8(s3 + 0x120, vi + 0x120);
            s3 += 0x10;
            if (flags[j] != 0) {
                cnt = *(s32 *)(sp + 0x1F4) + 1;
                *(s32 *)(sp + 0x1F4) = cnt;
                vj = arg2 + j * 0x10;
                func_00312650(tmp, vi, vj, cnt);
                ip0 = sceVu0InnerProduct(arg0, vi);
                ip1 = sceVu0InnerProduct(arg0, tmp);
                f20 = (ip0 + *(f32 *)(arg0 + 0xC)) / ip1;
                f21 = 1.0f - f20;
                sceVu0InterVector(f21, s3, vi, vj);
                sceVu0InterVector(f21, s3 + 0x90, vi + 0x90, vj + 0x90);
                sceVu0InterVector(f21, s3 + 0x120, vi + 0x120, vj + 0x120);
                s3 += 0x10;
            }
        } else {
            if (flags[j] == 0) {
                cnt = *(s32 *)(sp + 0x1F4) + 1;
                *(s32 *)(sp + 0x1F4) = cnt;
                vj = arg2 + j * 0x10;
                func_00312650(tmp, vi, vj, cnt);
                ip0 = sceVu0InnerProduct(arg0, vi);
                ip1 = sceVu0InnerProduct(arg0, tmp);
                f20 = (ip0 + *(f32 *)(arg0 + 0xC)) / ip1;
                f21 = 1.0f - f20;
                sceVu0InterVector(f21, s3, vi, vj);
                sceVu0InterVector(f21, s3 + 0x90, vi + 0x90, vj + 0x90);
                sceVu0InterVector(f21, s3 + 0x120, vi + 0x120, vj + 0x120);
                s3 += 0x10;
            }
        }
    }

    {
        u8 *dst = arg2;
        s32 b;
        for (b = 0; b < 0x1B0; b++) {
            dst[b] = sp[b];
        }
    }
    return *(s32 *)(sp + 0x1F4);
}
