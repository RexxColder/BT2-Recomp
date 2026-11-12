#include "common.h"

extern f32 D_00386348;
extern f32 D_0038634C;
extern f32 D_00386350;
extern f32 D_00386354;
extern f32 D_00386358;
extern f32 D_0038635C;
extern f32 D_00386360;

void *BtlChar_GetPos(s32 arg0);
s32 BtlObjXf_Update(s32 arg0);
void BtlAnim_SetBlend(f32 farg0, s32 arg0);
f32 cosf(f32 farg0);
f32 sinf(f32 farg0);
void func_001F9D78(s32 arg0, s32 arg1);
void func_001F9FB0(s32 arg0, s32 arg1);
s32 func_001FA0A0(s32 arg0, s32 arg1, s32 arg2);
void func_001FA110(s32 arg0, s32 arg1);
void func_001FA360(s32 arg0, f32 farg0);
void func_00208DE8(s32 arg0, s32 arg1, s32 arg2);
void func_00209268(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0, f32 farg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(f32 farg0, s32 arg0, s32 arg1);
void func_00216208(s32 arg0, f32 farg0, f32 farg1);
void func_00216678(s32 arg0);
void func_002177A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_0023F410(s32 arg0);

void func_00227A90(u8 *arg0) {
    s32 sp[4];
    s32 s0;
    s32 v1;
    s32 r1;
    s32 r2;
    f32 t;
    u8 *p;

    if (func_0023F410((s32)arg0) & 0x100) {
        s0 = 0x7E;
    } else if ((*(s32 *)(arg0 + 0x8DC) & 1) == 0) {
        s0 = 0x7E;
    } else {
        s0 = 0x7D;
    }

    v1 = BtlObjXf_Update((s32)arg0);
    if (v1 == 0x40) {
        func_001FA0A0((s32)arg0, 0x41, 1);
    } else if (v1 == 0x41) {
        func_001FA110((s32)arg0, 0);
        if (*(s32 *)(arg0 + 0x8CC) >= 0x1F) {
            BtlAnim_SetBlend(D_00386348, (s32)arg0);
            func_001F9D78((s32)arg0, 0x7D);
        }
    } else if (v1 == 0x7D || v1 == 0x7E) {
        func_001FA360((s32)arg0, 6.0f);
        if (*(s32 *)(arg0 + 0x8C0) < 0xE) {
            if (func_001FA0A0((s32)arg0, s0, 0) != 0) {
                BtlAnim_SetBlend(D_0038634C, (s32)arg0);
                *(s32 *)(arg0 + 0x8DC) = *(s32 *)(arg0 + 0x8DC) ^ 1;
                *(s32 *)(arg0 + 0x8C0) = *(s32 *)(arg0 + 0x8C0) + 1;
            }
        } else {
            func_001F9FB0((s32)arg0, 0);
        }
        r1 = BtlObjXf_Update((s32)arg0);
        r2 = BtlObjXf_Update((s32)arg0);
        func_002177A8((s32)arg0, r1 + 2, r2 + 4, 1);
    }

    func_00215068((s32)arg0, 1, 0xC, D_00386350, 0.5f);
    func_00215E88(D_00386354, (s32)arg0, 7);
    func_00216208((s32)arg0, 0.0f, D_00386358);
    func_00216678((s32)arg0);
    func_002113C0((s32)arg0, 9, 0x200, 1);
    func_002113C0((s32)arg0, 0xD, 8, 1);
    if (func_00211310((s32)arg0, 0, 0x100) != 0) {
        func_002113C0((s32)arg0, 0, 2, 1);
    }
    if (func_00211310((s32)arg0, 0, 1) != 0) {
        func_00208DE8(*(s32 *)(arg0 + 0x1534), (s32)sp, 0x11);
        func_00209268(*(s32 *)(arg0 + 0x1534), (s32)(arg0 + 0xA00), (s32)sp, 0x11,
                      D_0038635C, D_00386360);
        return;
    }

    p = (u8 *)BtlChar_GetPos((s32)arg0);
    t = sinf(*(f32 *)(p + 0xB4));
    *(f32 *)(arg0 + 0xA04) = 0.0f;
    *(f32 *)(arg0 + 0xA00) = t;
    p = (u8 *)BtlChar_GetPos((s32)arg0);
    t = cosf(*(f32 *)(p + 0xB4));
    *(f32 *)(arg0 + 0xA0C) = 0.0f;
    *(f32 *)(arg0 + 0xA08) = t;
}
