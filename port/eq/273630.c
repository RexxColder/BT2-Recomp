#include "common.h"

extern u8 *D_003876A0;
extern u8 *gBtlStage;

void *memset(void *arg0, s32 arg1, u32 arg2);
void func_00273410(f32 farg0, s32 arg0, s32 arg1);
void func_002746C0(s32 arg0);
s32 func_00276D00(void);

void func_00273630(void) {
    u8 *base5c;
    u8 *s0;
    u8 *s1;
    u8 *s2;
    u8 *a3p;
    u8 *t1p;
    u32 cnt0;
    u32 t2;
    s32 cnt;
    s32 k;
    s32 idx;

    if (*(s64 *)(D_003876A0 + 0x4D8) & 0x2000) {
        return;
    }
    base5c = *(u8 **)(gBtlStage + 0x5C);
    s1 = base5c + *(s32 *)(gBtlStage + 0x2C) * 4;
    s2 = base5c + *(s32 *)(gBtlStage + 0x50) * 4;
    s0 = base5c + *(s32 *)(gBtlStage + 0x24) * 4;
    memset(s1, 0, *(u32 *)(gBtlStage + 0x28));
    if (*(s32 *)(gBtlStage + 8) & 1) {
        return;
    }
    func_00273410(*(f32 *)(gBtlStage + 0x4C), (s32)s2, 1);

    cnt0 = *(u32 *)s0;
    for (t2 = 0; t2 < cnt0; t2++) {
        a3p = base5c + *(s32 *)(s0 + 4) * 4 + (t2 << 5);
        cnt = *(u16 *)a3p;
        if (cnt != 0) {
            t1p = base5c + *(s32 *)(a3p + 4) * 4;
            for (k = 0; k < cnt; k++) {
                idx = *(s32 *)(t1p + 4 * k);
                *(u8 *)(s1 + *(u16 *)(base5c + idx * 4)) = 1;
            }
        }
    }

    if (func_00276D00() == 1) {
        cnt0 = *(u32 *)(s0 + 8);
        for (t2 = 0; t2 < cnt0; t2++) {
            a3p = base5c + *(s32 *)(s0 + 0xC) * 4 + (t2 << 5);
            cnt = *(u16 *)a3p;
            if (cnt != 0) {
                t1p = base5c + *(s32 *)(a3p + 4) * 4;
                for (k = 0; k < cnt; k++) {
                    idx = *(s32 *)(t1p + 4 * k);
                    *(u8 *)(s1 + *(u16 *)(base5c + idx * 4)) = 1;
                }
            }
        }
    }
    func_002746C0((s32)s1);
}
