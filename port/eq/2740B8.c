#include "common.h"

void func_002768A8(s32 arg0, u32 arg1);
extern u8 *gBtlStage;

#define STG ((s32)gBtlStage)
#define SET_BIT0(idx) (*(u16 *)(*(s32 *)(STG + 0x5C) + (idx) * 4 + 2) = (u16)(*(u16 *)(*(s32 *)(STG + 0x5C) + (idx) * 4 + 2) | 1))
#define CLR_BIT0(idx) (*(u16 *)(*(s32 *)(STG + 0x5C) + (idx) * 4 + 2) = (u16)(*(u16 *)(*(s32 *)(STG + 0x5C) + (idx) * 4 + 2) & 0xFFFE))

void func_002740B8(s32 arg0) {
    s32 e;
    s32 v;
    u32 s1;

    e = *(s32 *)(STG + 0x5C) + *(s32 *)(STG + 0x48) * 4;
    if (arg0 == 1) {
        s1 = 0;
        if (*(u32 *)(STG + 0x44) != 0) {
            do {
                v = *(s32 *)(e + 0x0C);
                if (v != 0) {
                    CLR_BIT0(v);
                }
                v = *(s32 *)(e + 0x14);
                if (v != 0) {
                    CLR_BIT0(v);
                }
                v = *(s32 *)(e + 0x1C);
                if (v != 0) {
                    CLR_BIT0(v);
                }
                v = *(s32 *)(e + 0x10);
                if (v != 0) {
                    SET_BIT0(v);
                }
                v = *(s32 *)(e + 0x18);
                if (v != 0) {
                    SET_BIT0(v);
                }
                v = *(s32 *)(e + 0x20);
                if (v != 0) {
                    SET_BIT0(v);
                }
                *(s32 *)(e + 0x00) = arg0;
                s1 += 1;
                *(s32 *)(e + 0x30) = 0;
                *(s32 *)(e + 0x08) = 0;
                e += 0x50;
            } while (s1 < *(u32 *)(STG + 0x44));
        }
    } else {
        s1 = 0;
        if (*(u32 *)(STG + 0x44) != 0) {
            do {
                v = *(s32 *)(e + 0x0C);
                if (v != 0) {
                    SET_BIT0(v);
                }
                v = *(s32 *)(e + 0x14);
                if (v != 0) {
                    SET_BIT0(v);
                }
                v = *(s32 *)(e + 0x1C);
                if (v != 0) {
                    SET_BIT0(v);
                }
                v = *(s32 *)(e + 0x10);
                if (v != 0) {
                    CLR_BIT0(v);
                }
                v = *(s32 *)(e + 0x18);
                if (v != 0) {
                    CLR_BIT0(v);
                }
                v = *(s32 *)(e + 0x20);
                if (v != 0) {
                    CLR_BIT0(v);
                }
                *(s32 *)(e + 0x00) = arg0;
                *(s32 *)(e + 0x30) = 0;
                func_002768A8(e, s1);
                s1 += 1;
                e += 0x50;
            } while (s1 < *(u32 *)(STG + 0x44));
        }
    }
}
