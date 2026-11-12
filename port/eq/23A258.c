#include "common.h"

extern f32 D_00386BBC;
extern f32 D_00386BC0;
extern u8 D_002C3630[] __attribute__((section(".data")));

s32 func_00217488(u8 *arg0);
void BattleSide_SetChara(s32 arg0, s32 arg1);
void *BtlChar_GetPos(s32 arg0);
void func_00215E30(f32 farg0, s32 arg0, f32 farg1);
void func_00211828(s32 arg0);
void func_001F9D10(s32 arg0, s32 arg1);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void *func_00202DC0(s32 arg0);
s32 func_00212638(s32 arg0);
void func_00212690(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00208DE8(s32 arg0, s32 arg1, s32 arg2);
void func_003126C8(s32 arg0, s32 arg1);
f32 BtlUtil_WrapAngle(f32 farg0);
f32 BtlCharApi_GetHeight(s32 arg0);
void func_001FC3B0(f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5,
                   s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                   s32 stk0, s32 stk1, s32 stk2, s32 stk3, s32 stk4);

void func_0023A258(u8 *arg0) {
    u8 sp[0x80];
    s32 t;
    f32 f20;
    f32 h;

    t = func_00217488(arg0);
    if (t >= 0x34 && t < 0x37) {
        *(s32 *)(arg0 + 0x8DC) = *(s32 *)(arg0 + 0x8DC) | 1;
    }
    BattleSide_SetChara((s32)arg0, 0x2B);
    *(f32 *)((u8 *)BtlChar_GetPos((s32)arg0) + 0xC0) = 0.0f;
    *(f32 *)((u8 *)BtlChar_GetPos((s32)arg0) + 0xC4) = 0.0f;
    func_00215E30(*(f32 *)((u8 *)BtlChar_GetPos((s32)arg0) + 0x14), (s32)arg0, 0.0f);
    func_00211828((s32)arg0);
    func_001F9D10((s32)arg0, 0x3B);
    func_002113C0((s32)arg0, 9, 0x20, 1);
    *(s32 *)(arg0 + 0x990) = *(s32 *)func_00202DC0((s32)arg0);
    func_00212690((s32)arg0, func_00212638((s32)arg0), (s32)(arg0 + 0x994), 0);
    func_002113C0((s32)arg0, 0xC, 0x20, 0);
    func_002113C0((s32)arg0, 0xC, 0x40, 0);
    func_002113C0((s32)arg0, 0xC, 0x80, 0);
    func_002113C0((s32)arg0, 0xC, 0x100, 0);
    func_002113C0((s32)arg0, 0xC, 0x200, 0);
    func_002113C0((s32)arg0, 0xC, 0x400, 0);
    func_002113C0((s32)arg0, 0xC, 0x800, 0);
    func_00208DE8(*(s32 *)(arg0 + 0x1534), (s32)(sp + 0x30), 3);
    func_003126C8((s32)(sp + 0x40), (s32)(sp + 0x30));
    f20 = BtlUtil_WrapAngle((*(f32 *)((u8 *)BtlChar_GetPos((s32)arg0) + 0xB4) - D_00386BBC) + 0.5f);
    h = BtlCharApi_GetHeight(*(s32 *)(arg0 + 0x1534));
    func_001FC3B0(f20, 0.0f, D_00386BC0, 0.0f, h + h, 0.0f,
                  (s32)arg0, (s32)(sp + 0x30), (s32)D_002C3630, (s32)(sp + 0x40),
                  (s32)D_002C3630, (s32)D_002C3630, (s32)D_002C3630, -1,
                  -1, 3, 3, 1, 0xC5);
}
