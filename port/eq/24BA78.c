#include "common.h"

#define GS_CSR        ((volatile u64 *)0x12001000)
#define GS_DISPFB1    ((volatile u64 *)0x12000070)
#define GS_DISPLAY1   ((volatile u64 *)0x12000080)
#define GS_DISPFB2    ((volatile u64 *)0x12000090)
#define GS_DISPLAY2   ((volatile u64 *)0x120000A0)
#define GS_EXTWRITE   ((volatile u64 *)0x120000D0)

extern f32 D_00386D6C;
extern u8 *D_00387F2C;
extern u8 D_003B0B00[];

s32 sceDmaGetChan(s32 arg0);
void sceDmaSend(s32 arg0, u8 *arg1);
void sceGsSyncPath(s32 arg0, s32 arg1);
void FlushCache(s32 arg0);
void *memset(void *s, s32 c, u32 n);

void func_0024B800(void);
void func_002B6208(u8 *arg0);
s32 func_002B30E0(u8 *arg0);
s32 func_0028BAA8(s32 arg0);
u8 *func_002B4038(u8 *arg0);
u8 *func_001013B0(void);
void func_002B88C0(u8 *arg0, u8 *arg1);
void func_002B6E50(u8 *arg0, s32 arg1);
void func_002B7BD8(void);
s32 func_0028BDA0(void);
void func_002B4FD0(u8 *arg0, u8 *arg1);
void func_0024B980(u8 *arg0, s32 arg1, s32 arg2);
void func_002B58F0(u8 *arg0);
s32 func_002B8328(u8 *arg0);
void func_002EF218(s32 arg0);
void func_002B45D8(u8 *arg0);
void func_002B65C0(void);
void func_0028BB60(s32 arg0);
void func_0024B898(void);

void func_0024BA78(s32 arg0) {
    u8 sp[0x1F0];
    u8 *s3;
    u8 *obj;
    u8 *v49_0;
    s32 s0;
    s32 s1;
    s32 s2;
    s32 s4;
    s32 v1;
    s32 r1;
    s32 r2;
    s32 ret;
    s32 chan;
    s32 a1v;
    s32 x;
    s32 y;
    s64 s6;

    s6 = 0x001BF9FF02000000LL;
    s1 = arg0;
    s2 = 0x80;
    s4 = 1;

    chan = sceDmaGetChan(2);
    *(s32 *)(sp + 0x1E0) = chan;
    func_0024B800();

    memset(sp + 0x100, 0, 0x20);
    *(f32 *)(sp + 0x100) = D_00386D6C;
    *(s32 *)(sp + 0x104) = 1;
    *(s32 *)(sp + 0x108) = 0;
    *(s32 *)(sp + 0x10C) = 0;
    *(s32 *)(sp + 0x1E4) = 0x12000000;
    func_002B6208(sp + 0x100);

    memset(sp + 0x120, 0, 0x30);
    *(s32 *)(sp + 0x124) = 0x005B8D80;
    *(s32 *)(sp + 0x128) = 0x280;
    *(s32 *)(sp + 0x12C) = 0x1E0;
    *(s32 *)(sp + 0x130) = 2;
    *(s32 *)(sp + 0x140) = 0;
    *(s32 *)(sp + 0x1E4) |= 0xA0;
    *(s32 *)(sp + 0x120) = 1;
    *(s32 *)(sp + 0x134) = 1;
    r1 = func_002B30E0(sp + 0x120);
    *(s32 *)(sp + 0x13C) = r1;
    r2 = func_0028BAA8(r1);
    *(s32 *)(sp + 0x138) = r2;
    s3 = func_002B4038(sp + 0x120);
    func_002B88C0(s3, func_001013B0());
    func_002B6E50(s3, arg0);
    s1 = 2;

    for (;;) {
        func_002B7BD8();
        func_0028BDA0();
        s0 = (s32)((*GS_CSR >> 13) & 1);
        if (s0 == 0) {
            func_002B4FD0(s3, sp + 0x150);
            v49_0 = *(u8 **)(sp + 0x150);
            if (v49_0 != NULL) {
                func_0024B980(v49_0, *(s32 *)(sp + 0x15C), *(s32 *)(sp + 0x160));
                func_002B58F0(s3);
            }
        }
        obj = D_00387F2C;
        x = *(s32 *)(obj + 0x10A0);
        y = *(s32 *)(obj + 0x109C);
        *GS_DISPFB2 = 0x1000;
        *GS_DISPLAY2 = ((s64)(y * 4 + 0x27C) | ((s64)(x * 2 + 0x32) << 12) | s6);
        *GS_DISPFB1 = 0x1000;
        *GS_DISPLAY1 = ((s64)(y * 4 + 0x27C) | ((s64)(x * 2 + 0x33) << 12) | s6);
        *GS_EXTWRITE = 0;

        if (s0 == 0) {
            a1v = (s2 < 0x81) ? s2 : 0x80;
            *(u64 *)(sp + 0x00) = 0;
            *(u64 *)(sp + 0x08) = 0;
            *(u64 *)(sp + 0x80) = 0;
            *(u64 *)(sp + 0x88) = 0;
            *(u32 *)(sp + 0x6C) = a1v;
            *(u32 *)(sp + 0x4C) = a1v;
            *(u64 *)(sp + 0x10) = 0x1000000000000001ULL;
            *(u64 *)(sp + 0x20) = 68;
            *(u32 *)(sp + 0x00) = 0x10000007;
            *(u64 *)(sp + 0x28) = 66;
            *(u64 *)(sp + 0x30) = 0x4023400000008001ULL;
            *(u64 *)(sp + 0x38) = 16705;
            *(u64 *)(sp + 0x18) = 14;
            *(u32 *)(sp + 0x50) = 1792;
            *(u32 *)(sp + 0x54) = 1824;
            *(u32 *)(sp + 0x70) = 2304;
            *(u32 *)(sp + 0x74) = 2272;
            *(u32 *)(sp + 0x80) = 0x70000000;
            *(u32 *)(sp + 0x40) = 0;
            *(u32 *)(sp + 0x44) = 0;
            *(u32 *)(sp + 0x48) = 0;
            *(u32 *)(sp + 0x58) = 16;
            *(u32 *)(sp + 0x5C) = 0;
            *(u32 *)(sp + 0x60) = 0;
            *(u32 *)(sp + 0x64) = 0;
            *(u32 *)(sp + 0x68) = 0;
            *(u32 *)(sp + 0x78) = 16;
            *(u32 *)(sp + 0x7C) = 0;
            FlushCache(0);
            sceDmaSend(chan, sp);
            sceGsSyncPath(0, 0);
        }

        ret = func_002B8328(s3);
        v1 = *(s32 *)(D_003B0B00 + 0x134);
        if ((u32)(ret - 3) < 2) {
            s4 = 2;
        }
        if ((v1 & 8) != 0) {
            s4 = 2;
        }
        if (s2 >= 0x91) {
            break;
        }

        {
            s32 vnew;
            vnew = s2 + 8;
            if (s4 == 1) {
                if (s2 != 0) {
                    s2 -= 8;
                }
                vnew = s2 + 8;
            }
            if (s4 == 2) {
                s2 = vnew;
            }
            func_002EF218(1);
        }
    }

    func_002B45D8(s3);
    func_002B65C0();
    if (*(s32 *)(sp + 0x138) != 0) {
        func_0028BB60(*(s32 *)(sp + 0x138));
        *(s32 *)(sp + 0x138) = 0;
    }
    func_0024B898();
}
