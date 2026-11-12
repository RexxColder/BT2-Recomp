#include "common.h"

extern u8 D_0036DAD0[] __attribute__((section(".data")));
extern f32 D_00384188;
extern f32 D_0038418C;
extern f32 D_00384190;
extern f32 D_00384194;
extern f32 D_00384198;
extern f32 D_0038419C;
extern f32 D_003841A0;
extern f32 D_003841A4;
extern f32 D_003841A8;
extern f32 D_003841AC;

s32 rand(void);
f32 BtlCharApi_GetHeight(s32 arg0);
void func_00208AA0(s32 arg0, s32 arg1);
s32 func_00208DE8(s32 arg0, s32 arg1, s32 arg2);
void func_003126C8(f32 *arg0, f32 *arg1);
void func_00312650(void *arg0, void *arg1, void *arg2);
f32 func_0029DFD0(void *arg0);
void func_00312FB0(f32 farg0, void *arg0, void *arg1);
void func_00312680(f32 farg0, void *arg0, void *arg1);
s32 func_001301D0(u8 *arg0, u8 *arg1, u8 b2, u8 b3, u8 b5, s32 w6, s32 w7, u8 b8,
                  f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32 ff, f32 fg, f32 fh,
                  f32 fi, f32 fj, u8 b9);

/* copy of the 0xA0-byte table from the data section (optnone: no memcpy intrinsic on game memory) */
__attribute__((noinline, optnone)) static void table_copy(u8 *d, u8 *s, u32 n) {
    u32 i;
    for (i = 0; i < n; i++) {
        d[i] = s[i];
    }
}

/* Emits bubble effects along 20 segments: each table entry (two s32: start joint, end joint) gives a
   segment from one point to another; every step along it spawns a bubble with probability 1/arg1. */
void EftBubble_EmitBody(s32 arg0, s32 arg1, s32 arg2) {
    u8 sp[0x1C0];
    f32 minStep;
    s32 seg;
    s32 steps;
    s32 i;
    f32 divisor;
    f32 dist;
    f32 rx, ry, rz, rh, rw;
    f32 yaw, scale;
    f32 *table = (f32 *)(sp + 0x20);
    f32 *segEnd = (f32 *)(sp + 0xC0);
    f32 *dir = (f32 *)(sp + 0xF0);
    f32 *segStart = (f32 *)(sp + 0xE0);
    f32 *tmp = (f32 *)(sp + 0x100);

    table_copy(sp + 0x20, D_0036DAD0, 0xA0);
    func_00208AA0(arg0, (s32)(sp + 0xD0));

    minStep = BtlCharApi_GetHeight(arg0) * 0.25f;
    if (minStep < 6.0f) {
        minStep = 6.0f;
    }

    for (seg = 0; seg < 20; seg++) {
        func_00208DE8(arg0, (s32)segEnd, *(s32 *)(sp + 0x20 + 8 * seg));
        func_003126C8((f32 *)(sp + 0xE0), segEnd);
        if (*(s32 *)(sp + 0x24 + 8 * seg) >= 0) {
            func_00208DE8(arg0, (s32)tmp, *(s32 *)(sp + 0x24 + 8 * seg));
            func_00312650(tmp, tmp, segEnd);
            dist = func_0029DFD0(tmp);
            if (minStep < dist) {
                steps = (s32)(dist / minStep + 1.0f);
                func_00312FB0(1.0f / (f32)steps, sp + 0xF0, tmp);
            } else {
                *(f32 *)(sp + 0xF0) = 0.0f;
                steps = 1;
                *(f32 *)(sp + 0xF4) = 0.0f;
                *(f32 *)(sp + 0xF8) = 0.0f;
                *(f32 *)(sp + 0xFC) = 1.0f;
            }
        } else {
            *(f32 *)(sp + 0xF0) = 0.0f;
            steps = 1;
            *(f32 *)(sp + 0xF4) = 0.0f;
            *(f32 *)(sp + 0xF8) = 0.0f;
            *(f32 *)(sp + 0xFC) = 1.0f;
        }

        if (steps > 0) {
            f32 randDiv = D_00384188;
            f32 randScale = D_0038418C;
            f32 offset = D_00384190;

            i = 0;
            do {
                if (rand() % arg1 == 0) {
                    rx = (f32)rand();
                    ry = (f32)rand();
                    rx = (rx / randDiv) * randScale + randScale;
                    ry = (ry / randDiv) * D_00384194 + D_00384198;
                    rz = (f32)rand();
                    rz = (rz / randDiv) * D_0038419C;
                    rh = (f32)rand();
                    rz = rz - offset;
                    rh = (rh / randDiv) * randScale + D_003841A0;
                    rx = rx * (BtlCharApi_GetHeight(arg0) * offset);
                    ry = ry * (BtlCharApi_GetHeight(arg0) * offset);
                    rz = rz * (BtlCharApi_GetHeight(arg0) * offset);
                    scale = (f32)rand();
                    func_00312680((scale / randDiv) * D_003841A4 + D_003841A8, sp + 0x110, sp + 0xD0);
                    *(f32 *)(sp + 0xC0) = segStart[0] + (f32)i * dir[0];
                    *(f32 *)(sp + 0xC8) = segStart[2] + (f32)i * dir[2];
                    *(f32 *)(sp + 0xC4) = segStart[1] + (f32)i * dir[1];
                    yaw = (f32)rand();
                    yaw = (yaw / randDiv) * 360.0f;
                    rw = (f32)rand();
                    rw = (rw / randDiv) * D_003841AC;
                    func_001301D0(sp + 0xC0, sp + 0x110, 0x80, 0x80, 0x80, arg0, arg2, 0,
                                  -8.0f, rx, 128.0f, yaw, rz, 6.0f, rw, ry, 0.25f, rh, 0);
                }
                i++;
            } while (i < steps);
        }
    }
}
