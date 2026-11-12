#include "common.h"

s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void BattleSide_SetChara(s32 arg0, s32 arg1);
void func_002113C0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
void *BtlChar_GetPos(s32 arg0);
void func_002765A8(s32 arg0, u8 *arg1, u8 *arg2, s32 arg3);
s32 func_00210DD8(s32 arg0);
f32 func_00273000(void);
f32 tanf(f32 farg0);
f32 sinf(f32 farg0);
f32 cosf(f32 farg0);
f32 func_0029DFD0(s32 arg0);
void sceVu0Normalize(void *arg0, void *arg1);
f32 func_00272FA8(void);
f32 func_002086B0(s32 arg0);
void func_00211898(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
f32 func_00273048(void);
f32 BtlCharApi_GetHeight(s32 arg0);
void func_00276700(u8 *arg0, u8 *arg1);
s32 func_001FC3B0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                  s32 arg8, s32 arg9, s32 arg10, s32 arg11, s32 arg12,
                  f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5);
extern s32 D_002C3630[] __attribute__((section(".data")));
extern f32 D_00386B50;
extern f32 D_00386B54;
extern f32 D_00386B58;
extern f32 D_00386B5C;
extern f32 D_00386B60;
extern f32 D_00386B64;
extern f32 D_00386B68;
extern f32 D_00386B6C;

/* 0x00239750: set up a camera move (func_001FC3B0) that looks at the target character's position. */
s32 func_00239750(u8 *self) {
    f32 srcPos[4];  /* sp 0x30 */
    f32 dstPos[4];  /* sp 0x40 */
    f32 camPos[4];  /* sp 0x50 */
    f32 dir[4];     /* sp 0x60 */
    f32 camBase[4]; /* sp 0x70 */
    u8 matBuf[16];  /* sp 0x80 */
    s32 obj = (s32)(u32)self;
    s32 table = (s32)(u32)D_002C3630;
    s32 target = *(s32 *)(self + 0x1534);
    f32 refY;
    f32 t;
    f32 lim;
    f32 len;
    f32 height;
    u8 *pos;

    BattleSide_SetChara(obj, func_00211310(obj, 0, 0x100) != 0 ? 0xE9 : 0xE7);
    func_002113C0(self, 12, 1, 0);
    func_002113C0(self, 12, 4, 0);
    func_002113C0(self, 12, 8, 0);
    func_002113C0(self, 12, 0x10, 0);
    *(s32 *)((u8 *)BtlChar_GetPos(obj) + 0xC0) = 0;
    *(s32 *)((u8 *)BtlChar_GetPos(obj) + 0xC4) = 0;
    func_002113C0(self, 16, 0x80000, 1);
    func_002113C0(self, 9, 0x10000000, 1);
    func_002765A8(target, (u8 *)srcPos, (u8 *)dir, 0);
    func_002765A8(func_00210DD8(obj), (u8 *)dstPos, (u8 *)dir, 0);
    refY = func_00273000();
    dir[0] = srcPos[0] - dstPos[0];
    dir[2] = srcPos[2] - dstPos[2];
    t = -tanf(D_00386B50);
    dir[1] = t * __builtin_sqrtf(dir[0] * dir[0] + dir[2] * dir[2]);
    if (func_0029DFD0((s32)(u32)dir) < D_00386B54) {
        t = D_00386B58;
        *(s32 *)&dir[0] = 0;
        dir[1] = -sinf(t);
        dir[2] = cosf(t);
    } else {
        sceVu0Normalize(dir, dir);
    }
    t = (refY - srcPos[1]) / dir[1];
    if (t > 300.0f) {
        t = 300.0f;
    }
    camPos[1] = srcPos[1] + dir[1] * t;
    camPos[0] = srcPos[0] + dir[0] * t;
    camPos[2] = srcPos[2] + dir[2] * t;
    lim = func_00272FA8();
    lim = lim - func_002086B0(target);
    len = __builtin_sqrtf(camPos[0] * camPos[0] + camPos[2] * camPos[2]);
    if (lim < len) {
        lim = lim / len;
        camPos[2] = camPos[2] * lim;
        camPos[0] = camPos[0] * lim;
    }
    func_00211898(obj, (s32)(u32)camPos, table, (s32)(u32)camPos);
    pos = (u8 *)BtlChar_GetPos(obj);
    if (*(f32 *)(pos + 4) < func_00273048()) {
        height = BtlCharApi_GetHeight(*(s32 *)(self + 0x1534)) * 1.5f;
        return func_001FC3B0(self, table, table, table, table, table, table, 3,
                             3, 3, 3, 60, 0xC5,
                             0.0f, D_00386B5C, D_00386B60, D_00386B64,
                             height, BtlCharApi_GetHeight(*(s32 *)(self + 0x1534)) * 0.5f);
    }
    func_00276700((u8 *)camBase, matBuf);
    camBase[1] = camBase[1] - 5.0f;
    return func_001FC3B0(self, (s32)(u32)camBase, table, (s32)(u32)camBase, table, (s32)(u32)camBase, table, -1,
                         -1, -1, -1, 60, 0xC5,
                         0.0f, D_00386B68, D_00386B6C, 0.0f,
                         100.0f, 0.0f);
}
