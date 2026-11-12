#include "common.h"

void *BtlChar_GetPos(s32 arg0);
s32 BtlObjXf_Update(s32 arg0);
f32 func_00209730(s32 arg0, s32 arg1);
void func_00210FD0(s32 arg0, s32 arg1);
s32 func_00312650(s32 arg0, s32 arg1, s32 arg2);
void func_00312638(s32 arg0, s32 arg1, s32 arg2);
void func_002118F0(s32 arg0, s32 arg1);
void func_002113C0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00216550(u8 *arg0);
void func_00215068(u8 *a0, s32 a1, s32 a2, f32 fMax, f32 fScale);
void func_00215E88(s32 a0, u32 a1);
s32 func_001F9D78(s32 arg0, s32 arg1);
void func_00206958(s32 arg0, s32 arg1);
s32 func_001F9FB0(u8 *arg0, s32 arg1);
s32 func_001FA0A0(s32 a0, s32 a1, s32 a2);
f32 func_001FA318(s32 arg0);
s32 func_001FA2E0(s32 arg0);
void func_001FA380(u8 *arg0, f32 arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_00217BD0(u8 *arg0);
void func_00216208(f32 farg0, f32 farg1, s32 arg0);
extern f32 D_00385EB4;
extern f32 D_00385EB8;
extern f32 D_00385EBC;
extern f32 D_00385EC0;
extern f32 D_00385EC4;
extern f32 D_00385EC8;
extern f32 D_00385ECC;

/* 0x0021F098: 4-state character action (state at +0x8C0, counter at +0x8C4, param at +0x8C8). */
void func_0021F098(u8 *self) {
    s32 *state = (s32 *)(self + 0x8C0);
    s32 *count = (s32 *)(self + 0x8C4);
    s32 *param = (s32 *)(self + 0x8C8);
    u8 sp[0x30];
    s32 obj = (s32)(u32)self;
    s32 posA;
    s32 posB;
    s32 anim;
    s32 grounded;
    f32 f20;
    f32 f21;

    switch (*state) {
    case 0:
        func_001F9FB0(self, 0);
        *count = *count + 1;
        if (*count >= 2) {
            func_002113C0(self, 9, 0x4000, 1);
        }
        if (*count < 4) {
            return;
        }
        *count = 0;
        *state = *state + 1;
        return;
    case 1:
        func_00209730(*(s32 *)(self + 0x1534), (s32)(u32)&sp[0]);
        func_00210FD0(obj, (s32)(u32)&sp[0x10]);
        func_00312650((s32)(u32)&sp[0x20], (s32)(u32)&sp[0x10], (s32)(u32)&sp[0]);
        posA = (s32)(u32)BtlChar_GetPos(obj);
        posB = (s32)(u32)BtlChar_GetPos(obj);
        func_00312638(posA, posB, (s32)(u32)&sp[0x20]);
        func_002118F0(obj, (s32)(u32)&sp[0x10]);
        func_002113C0(self, 3, 0x1000, 1);
        func_002113C0(self, 3, 0x800, 1);
        func_002113C0(self, 9, 0x4000, 1);
        break;
    case 2:
        func_00216550(self);
        func_00215068(self, 1, 9, D_00385EB4, 1.0f);
        func_00215E88(obj, 3);
        func_002113C0(self, 3, 0x800, 1);
        func_002113C0(self, 9, 0x4000, 1);
        func_001F9D78(obj, *param);
        func_00206958(obj, 0x4000);
        break;
    case 3:
        grounded = 1;
        anim = BtlObjXf_Update(obj);
        f20 = D_00385EB8;
        f21 = D_00385EBC;
        switch (anim - 0x68) {
        case 0:
        case 3:
        case 6:
        case 9:
        case 12:
            func_001FA0A0(obj, BtlObjXf_Update(obj) + 2, 0);
            *(f32 *)(self + 0x9B0) = 1.0f;
            if (func_001FA318(obj) < 0.5f) {
                func_002113C0(self, 9, 0x4000, 1);
            }
            if (func_001FA2E0(obj) != 0) {
                func_002113C0(self, 14, 0x40, 1);
            }
            break;
        case 2:
        case 5:
        case 8:
        case 11:
        case 14:
            func_001F9FB0(self, 0);
            *(s32 *)(self + 0x8DC) = *(s32 *)(self + 0x8DC) | 1;
            func_001FA380(self, 2.0f);
            if (func_00211310(obj, 4, 2) != 0) {
                f20 = 0.0f;
                *(f32 *)((u8 *)BtlChar_GetPos(obj) + 0xC0) = f20;
            }
            if (func_00211310(obj, 4, 0xC) != 0) {
                f20 = 0.0f;
                f21 = D_00385EC0;
                grounded = 0;
                if (func_00217BD0(self) != 0) {
                    *(f32 *)((u8 *)BtlChar_GetPos(obj) + 0xC0) = f20;
                }
            }
            break;
        default:
            break;
        }
        if (grounded != 0) {
            func_00215068(self, 1, 9, D_00385EC4, 1.0f);
        } else {
            func_00215068(self, 5, 12, D_00385EC8, 0.5f);
        }
        func_00215E88(obj, 3);
        func_00216208(f20, f21, obj);
        return;
    default:
        return;
    }
    /* states 1 and 2 share the tail */
    func_002113C0(self, 14, 0x20, 1);
    func_002113C0(self, 15, 0x20, 1);
    func_002113C0(self, 1, 0x20000, 1);
    *state = *state + 1;
}
