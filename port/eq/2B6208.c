#include "common.h"

void Rand_Range(void *arg0);
void func_002BC1E8(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2, s32 t3,
                   s32 s9, s32 s10, s32 s11, s32 s12);
void func_002B7768(void);
void func_002ED220(s32 arg0);
void func_00304660(void);
void BtlGame_Term(void);
void func_00305410(void);
s32 func_002BD478(void);
void func_002B6700(s32 arg0);
void func_002B6420(s32 *arg0);
s32 func_002B6750(s32 arg0);
void func_002B6558(s32 *arg0);
void func_00300898(void);
void func_003007D0(void *arg0, s32 arg1);
void func_002B9378(void);
void func_002B63C0(s32 *arg0);
void *memset(void *, s32, u32);
extern u8 BtlAiPick_Random[] __attribute__((section(".data")));
extern s32 D_00345340 __attribute__((section(".data")));
extern s32 D_00345344 __attribute__((section(".data")));
extern s32 D_00346C04 __attribute__((section(".data")));
extern u8 D_00378690[] __attribute__((section(".data")));
extern u8 D_00378730[] __attribute__((section(".data")));
extern u8 D_00378758[] __attribute__((section(".data")));
extern u8 D_00378780[] __attribute__((section(".data")));
extern u8 *D_0038BBC0 __attribute__((section(".data")));

void func_002B6208(void *arg0) {
    s32 sp[8];
    u8 *s0;
    f32 f0;
    f32 v;
    s32 i;
    f32 d;

    if (arg0 == NULL) {
        Rand_Range(D_00378730);
        return;
    }
    s0 = (u8 *)arg0;
    memset(sp, 0, 0x20);
    f0 = *(f32 *)s0;
    *(f32 *)&sp[0] = f0;
    D_0038BBC0 = D_00378690;
    sp[5] = *(s32 *)(s0 + 0x14);
    sp[4] = *(s32 *)(s0 + 0x10);
    sp[6] = *(s32 *)(s0 + 0x18);
    sp[3] = *(s32 *)(s0 + 0xC);
    sp[2] = *(s32 *)(s0 + 0x8);
    sp[1] = *(s32 *)(s0 + 0x4);
    sp[7] = *(s32 *)(s0 + 0x1C);
    func_002BC1E8(sp[5], sp[6], sp[4], sp[3], sp[2], sp[1], sp[7], 0,
                  sp[0], sp[2], sp[4], sp[6]);
    func_002B7768();
    sp[2] = (sp[2] - 2 < 0) ? 0 : sp[2] - 2;
    if (D_00345340 == 0) {
        func_002ED220(D_00345340);
        func_00304660();
        BtlGame_Term();
        func_00305410();
        if (func_002BD478() != 0) {
            func_002B6700(-0x65);
            Rand_Range(D_00378758);
        }
        func_002B6420(sp);
        D_00346C04 = 0;
        v = *(f32 *)&sp[0] * 1000.0f + 0.5f;
        i = (s32)v;
        d = v - (f32)i;
        if (d > 0.5f || (d == 0.5f && (i & 1))) {
            i += 1;
        } else if (d < -0.5f || (d == -0.5f && (i & 1))) {
            i -= 1;
        }
        if (func_002B6750(i) != 0) {
            Rand_Range(D_00378780);
        }
        D_00345344 = 1;
        func_002B6558(sp);
        func_00300898();
        func_003007D0(BtlAiPick_Random, 0);
        func_002B9378();
        func_002B63C0(sp);
    }
    D_00345340 += 1;
}
