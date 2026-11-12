#include "common.h"

void BattleSide_SetChara(void *arg0, s32 arg1);
s32 func_00212320(void *arg0);
u8 *BtlChar_GetPos(void *arg0);
void func_002113C0(void *arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_002411E0(void *arg0, s32 arg1);
s32 func_002412A0(void *arg0, s32 arg1, s32 arg2);
s32 func_00211310(void *arg0, s32 arg1, s32 arg2);
s32 BtlObjAnim_QueryEvent(void *arg0, s64 arg1, s32 arg2, s32 arg3);
s32 func_00203C58(void *arg0, s64 arg1, s32 arg2);
void func_00210868(void *arg0, void *arg1);
void func_00215E30(void *arg0, f32 farg0, f32 farg1);
void func_00210FD0(void *arg0, void *arg1);
void func_002118F0(void *arg0, void *arg1);
void BtlAnim_SetNoBlend(void *arg0);
s32 func_00217488(void *arg0);

void func_00233A90(u8 *arg0) {
    u8 sp[0x20] __attribute__((aligned(8)));
    s32 v;
    s32 a1v;
    s32 s1;
    s32 s2;
    s32 v1;
    s32 t;

    v = func_00217488(arg0);
    if (v == 0xCE) {
        a1v = 0x153;
    } else if (v == 0xCF) {
        a1v = 0x175;
    } else if (v == 0xCD) {
        a1v = 0x131;
    } else {
        a1v = 0;
    }
    BattleSide_SetChara(arg0, a1v);
    s2 = func_00212320(arg0);
    *(s32 *)(BtlChar_GetPos(arg0) + 0xC0) = 0;
    *(s32 *)(BtlChar_GetPos(arg0) + 0xC4) = 0;
    func_002113C0(arg0, 7, 0x20, 1);

    if (!(func_002411E0(arg0, s2) & 0x08000000)) {
        s1 = func_002412A0(arg0, s2, 0);
        if ((func_00211310(arg0, 0, 0x800) != 0) && (s2 != 4)) {
            s1 = s1 + s1 / 5;
        }
        *(s32 *)(arg0 + 0x9C8) = s1;
        *(s32 *)(arg0 + 0x9C4) = s1;
        v = BtlObjAnim_QueryEvent(*(void **)(arg0 + 0x1530), (s64)0x8000 << 18, 0, 2);
        *(s32 *)(arg0 + 0x9D0) = v;
        *(s32 *)(arg0 + 0x9D4) = 0x8000;
        *(s32 *)(arg0 + 0x9CC) = *(s32 *)(arg0 + 0x9C4) / (v + 5);

        if (s2 == 2) {
            *(s32 *)(arg0 + 0x9D4) = 0x8200;
        } else if (s2 == 3) {
            *(s32 *)(arg0 + 0x9D4) = 0x8400;
        } else if (s2 == 4) {
            *(s32 *)(arg0 + 0x9D4) = 0x8800;
        }

        if (func_00203C58(arg0, 0x08000000, 3) != 0) {
            *(s32 *)(arg0 + 0x9D4) = *(s32 *)(arg0 + 0x9D4) | 1;
        }
        v1 = *(s32 *)(arg0 + 0x9CC);
        t = v1 % 10;
        if (t != 0) {
            *(s32 *)(arg0 + 0x9CC) = (v1 - t) + 0xA;
        }
    }

    if (func_002411E0(arg0, s2) & 0x40) {
        func_00210868(arg0, sp + 0x10);
        func_00215E30(arg0, *(f32 *)(sp + 0x14), 0.0f);
        func_002113C0(arg0, 7, 0x100, 1);
        func_00210FD0(arg0, sp);
        func_002118F0(arg0, sp);
        func_002113C0(arg0, 3, 0x1000, 1);
        func_002113C0(arg0, 1, 0x20000, 1);
        BtlAnim_SetNoBlend(arg0);
    }
    *(s32 *)(arg0 + 0xA30) = 0;
}
