#include "common.h"

extern f32 D_00385B40;
extern f32 D_00385B44;
extern f32 D_00385B48;
extern f32 D_00385B4C;

s32 BtlObjXf_Update(u8 *a0);
s32 func_002174B8(u8 *a0);
s32 func_00211310(u8 *a0, s32 a1, s32 a2);
s32 func_001FA0A0(u8 *a0, s32 a1, s32 a2);
void BtlAnim_SetBlend(u8 *a0, f32 farg0);
void func_001F9FB0(u8 *a0, s32 a1);
f32 func_001FA308(u8 *a0);
s32 BtlObjAnim_QueryEvent(s32 a0, s32 a1, s32 a2, s32 a3);
void func_002113C0(u8 *a0, s32 a1, s32 a2, s32 a3);
void func_00215068(u8 *a0, s32 a1, s32 a2, f32 farg0, f32 farg1);
void func_00215E88(u8 *a0, s32 a1, f32 farg0);
void func_00216208(u8 *a0, f32 farg0, f32 farg1);
void func_00216678(u8 *a0);

/* 0x00218A38: switch on BtlObjXf_Update's result (0..76, jump table jtbl_0036FB30).
 * Cases 0/50 -> block B38, 67-75 -> A78, 71/76 -> AD8, everything else -> the default tail. */
void func_00218A38(u8 *arg0) {
    s32 idx;
    s32 r;
    s32 r2;
    f32 f20;

    idx = BtlObjXf_Update(arg0);
    if ((u32)idx < 0x4D) {
        switch (idx) {
        case 0:
        case 50:
            func_001F9FB0(arg0, 1);
            func_002113C0(arg0, 5, 0x800, 1);
            goto default_tail;
        case 67:
        case 68:
        case 69:
        case 70:
        case 72:
        case 73:
        case 74:
        case 75:
            r = func_002174B8(arg0);
            if (r == -1) {
                r = func_00211310(arg0, 0, 2);
                r2 = func_001FA0A0(arg0, (r == 0) ? 0 : 0x32, 0);
                if (r2 != 0) {
                    BtlAnim_SetBlend(arg0, D_00385B40);
                }
                goto b1c;
            }
            func_001F9FB0(arg0, 0);
            goto b1c;
        case 71:
        case 76:
            func_001F9FB0(arg0, 0);
            f20 = func_001FA308(arg0);
            r = BtlObjAnim_QueryEvent(*(s32 *)(arg0 + 0x1530), 2, 0, 1);
            if (f20 < (f32)r) {
                goto b1c;
            }
            goto default_tail;
        default:
            break;
        }
    }
    goto default_tail;

b1c:
    func_002113C0(arg0, 3, 0x40000, 1);

default_tail:
    func_00215068(arg0, 5, 0xC, D_00385B44, 0.5f);
    func_00215E88(arg0, 2, D_00385B48);
    func_00216208(arg0, 0.0f, D_00385B4C);
    func_00216678(arg0);
    func_002113C0(arg0, 9, 0x200, 1);
    func_002113C0(arg0, 5, 1, 1);
    r = func_00211310(arg0, 0, 0x100);
    if (r != 0) {
        func_002113C0(arg0, 0, 2, 1);
    }
}
