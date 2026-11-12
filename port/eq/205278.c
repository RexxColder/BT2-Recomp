#include "common.h"

extern u8 D_0036F8B0[];
extern void *memcpy(void *dst, const void *src, u32 n);
extern f32 sinf(f32 x);
extern f32 cosf(f32 x);
s32 func_0023F298(u8 *a0);
s32 func_0023F410(u8 *a0);
s32 func_0023F2B8(u8 *a0);
s32 BattleResult_GetFlags(u8 *a0);
s32 BtlChar_FrameMod(s32 a0);
void BtlOpp_GetTargetPos(u8 *a0, void *a1);
f32 func_00210D10(u8 *a0);
u8 *BtlChar_GetPos(u8 *a0);
f32 BtlCharApi_GetHeight(u8 *a0);
void func_001A5EF0(s32 a0, void *a1, u8 *a2);
s32 BtlObjAnim_MaskToNode(s32 a0);
void func_00208DE8(u8 *a0, void *a1, s32 a2);
void func_00312680(void *a0, void *a1, f32 f12);
void func_00312638(void *a0, void *a1, void *a2);
f32 sceVu0InnerProduct(void *a0, void *a1);
void func_0020FC38(u8 *a0, s32 a1);

void BtlFx_TriggerObjReq1D(u8 *arg0) {
    u8 sp[0x80];
    f32 *f0p = (f32 *)sp;
    f32 *f10 = (f32 *)(sp + 0x10);
    f32 *f40 = (f32 *)(sp + 0x40);
    f32 *f50 = (f32 *)(sp + 0x50);
    f32 *f60 = (f32 *)(sp + 0x60);
    u32 *tbl = (u32 *)(sp + 0x20);
    u64 s3;
    s32 s2 = -1, s4 = -1, s5, s0;
    u32 a2, a0;
    s32 a1;
    f32 f20, f0, f1;
    u8 *pos;

    s3 = *(u64 *)(arg0 + 0x338);
    if (s3 & 0x200000) {
        s5 = 0;
        switch (func_0023F298(arg0)) {
        case 1: s4 = 0; break;
        case 2: s4 = 1; break;
        case 3: s4 = 2; break;
        case 6: s4 = 4; break;
        case 7: s4 = 5; break;
        case 8: s4 = 6; break;
        case 11:
            s4 = 0xB;
            if (!(func_0023F410(arg0) & 0x80)) s4 = 0xA;
            break;
        case 13: s4 = 0xF; break;
        case 15: s4 = 0x10; break;
        case 16: s4 = 0x11; break;
        default: break;
        }
        s0 = func_0023F2B8(arg0);
        if (func_0023F410(arg0) & 0x40) {
            u64 v = *(u64 *)(*(u8 **)(arg0 + 0x1530) + 0xAF0);
            s5 = 1;
            if ((~v) & 0x22) s5 = 0;
            if (BattleResult_GetFlags(arg0) & 0x2000) s5 = 0;
        }
        if (s5) {
            s2 = 0x4D;
            if (s0 >= 5) s2 = 0x36;
        } else {
            switch (s0) {
            case 1: s2 = BtlChar_FrameMod(2) + 2; break;
            case 2: s2 = 0x19; break;
            case 3: s2 = 0x22; break;
            case 4: s2 = 0x45; break;
            case 5: s2 = BtlChar_FrameMod(2) + 9; break;
            case 6: s2 = 0x25; break;
            case 7: s2 = 0x26; break;
            case 8: s2 = 0x27; break;
            case 9: s2 = 0x49; break;
            case 10: s2 = 0x4E; break;
            case 11: s2 = 0x50; break;
            case 12: s2 = 0x4F; break;
            default: break;
            }
        }
    }
    if (s3 & 0x400000) {
        s4 = 8;
        if (func_0023F2B8(arg0) < 5) s2 = BtlChar_FrameMod(2) + 4;
        else s2 = BtlChar_FrameMod(2) + 0xC;
    }
    if (s3 & 0x2000000) {
        s4 = 0xD;
        s2 = 0x24;
    }
    if (s3 & 0x10000000) {
        s4 = 9;
        s2 = 0x42;
    }
    if (s3 & 0x4000000) {
        if (func_0023F298(arg0) < 6) {
            s4 = 3;
            s2 = BtlChar_FrameMod(2) + 0xC;
        } else {
            s4 = 7;
            s2 = 0x24;
        }
    }
    if (s4 >= 0) {
        if (s3 & 0xE0000000ULL) {
            BtlOpp_GetTargetPos(arg0, f10);
            f20 = func_00210D10(arg0);
            pos = BtlChar_GetPos(arg0);
            f0 = sinf(*(f32 *)(pos + 0xB4));
            f0p[0] = f10[0] - f0 * f20;
            pos = BtlChar_GetPos(arg0);
            f0p[1] = *(f32 *)(pos + 4);
            f20 = func_00210D10(arg0);
            pos = BtlChar_GetPos(arg0);
            f0 = cosf(*(f32 *)(pos + 0xB4));
            f0p[3] = 1.0f;
            f0p[2] = f10[2] - f0 * f20;
            if (s3 & 0x40000000) {
                f0 = BtlCharApi_GetHeight(*(u8 **)(arg0 + 0x1534));
                f0p[1] = f0p[1] - f0 * 0.5f;
            } else if (s3 & 0x80000000ULL) {
                f0 = BtlCharApi_GetHeight(*(u8 **)(arg0 + 0x1534));
                f0p[1] = f0p[1] - f0;
            }
            func_001A5EF0(s4 & 0xFF, sp, *(u8 **)(arg0 + 0x1534));
        } else {
            memcpy(tbl, D_0036F8B0, 0x20);
            a2 = *(u32 *)(*(u8 **)(arg0 + 0x1530) + 0xD6C);
            a0 = a2 & tbl[0];
            if (!a0) {
                for (a1 = 1; a1 < 8; a1++) {
                    a0 = a2 & tbl[a1];
                    if (a0) break;
                }
                if (!a0) {
                    a0 = a2 & 1;
                    if (!a0) {
                        for (a1 = 1; a1 < 19; a1++) {
                            a0 = a2 & (1u << a1);
                            if (a0) break;
                        }
                        if (!a0) goto done;
                    }
                }
            }
            func_00208DE8(*(u8 **)(arg0 + 0x1534), f40, BtlObjAnim_MaskToNode(a0));
            pos = BtlChar_GetPos(arg0);
            f50[0] = sinf(*(f32 *)(pos + 0x14));
            f50[1] = 0;
            pos = BtlChar_GetPos(arg0);
            f50[2] = cosf(*(f32 *)(pos + 0x14));
            func_00312680(sp + 0x70, f50, 5.0f);
            pos = BtlChar_GetPos(arg0);
            func_00312638(f60, pos, sp + 0x70);
            f0 = -sceVu0InnerProduct(f50, f60);
            f50[3] = f0;
            f0 = sceVu0InnerProduct(f50, f40);
            f1 = f50[3];
            f0 = f0 + f1;
            if (f0 < 0.0f) {
                func_00312680(sp + 0x70, f50, -f0);
                func_00312638(f40, f40, sp + 0x70);
            }
            f40[3] = 1.0f;
            func_001A5EF0(s4 & 0xFF, f40, *(u8 **)(arg0 + 0x1534));
        }
    }
done:
    if (s2 >= 0) func_0020FC38(arg0, s2);
}
