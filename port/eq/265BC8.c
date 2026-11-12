#include "common.h"

extern u8 *D_003876A0;
extern u8 *D_00387A40;

s32 BtlStage_IsReady(void);
void func_002605A0(u8 *arg0, s32 arg1);
void func_002673F0(u8 *arg0);
void func_002667F8(u8 *arg0);
void func_00266838(u8 *arg0);
void func_00266908(u8 *arg0);
void func_00269400(u8 *arg0);

void func_00265BC8(void) {
    u8 *base;
    u8 *s0;
    u8 *s1;
    s32 i;
    s32 off;

    if (*(s64 *)(D_003876A0 + 0x4D8) & 3) {
        if (BtlStage_IsReady() == 0) {
            return;
        }
    }

    base = D_00387A40;
    if (*(s32 *)(base + 4) > 0) {
        i = 0;
        off = 0;
        do {
            s0 = (u8 *)*(s32 *)base + off;
            off += 0x18580;
            s1 = s0 + 0xAF0;
            *(s32 *)(s1 + 8) = 0;
            func_002605A0(s0, 2);
            func_002673F0(s0);
            func_002667F8(s0);
            func_00266838(s0);
            func_00266908(s0);
            if (*(s32 *)s1 & 0x10) {
                func_00269400(s0);
            }
            i++;
            base = D_00387A40;
        } while (i < *(s32 *)(base + 4));
    }

    base = D_00387A40;
    if (*(s32 *)(base + 0xC) > 0) {
        i = 0;
        off = 0;
        do {
            s0 = (u8 *)*(s32 *)(base + 8) + off;
            off += 0x1520;
            s1 = s0 + 0xAF0;
            *(s32 *)(s1 + 8) = 0;
            if (*(s32 *)(s0 + 0xC) != 0) {
                func_002605A0(s0, 2);
                func_002673F0(s0);
                func_002667F8(s0);
                func_00266838(s0);
                func_00266908(s0);
                if (*(s32 *)s1 & 0x10) {
                    func_00269400(s0);
                }
            }
            i++;
            base = D_00387A40;
        } while (i < *(s32 *)(base + 0xC));
    }
}
