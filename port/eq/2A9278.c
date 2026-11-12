#include "common.h"

s32 func_0025FBE8(u8 *a0, s64 a1);
u8 *func_00269A40(u8 *a0, s32 a1);
void func_003126C8(void *a0, u8 *a1);
void func_002A8D90(void *a0, void *a1, void *a2);
void func_00297FE0(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0);
s32 rand(void);

void func_002A9278(u8 *arg0) {
    s32 sp[8];
    u8 *v;
    u8 *t958;
    s32 r;
    u32 u;
    s32 a1;

    v = func_00269A40(arg0, 0x11);
    if (v != NULL) {
        func_003126C8(sp, v + 0x30);
    } else {
        v = func_00269A40(arg0, 0);
        if (v != NULL) {
            func_003126C8(sp, v + 0x30);
        } else {
            func_003126C8(sp, arg0 + 0x9A0);
        }
    }
    func_002A8D90(sp, &sp[4], &sp[5]);

    if (func_0025FBE8(arg0, 0x10) != 0) {
        func_00297FE0(1, (rand() % 3) + 0x28, sp[4], sp[5], 0);
    }
    if (func_0025FBE8(arg0, 0x10000000) != 0) {
        func_00297FE0(1, 0x1E, sp[4], sp[5], 0);
    }
    if (func_0025FBE8(arg0, 0x20000000) != 0) {
        u = (u32)rand();
        func_00297FE0(1, (s32)(u - (((s32)(u + (u >> 0x1F)) >> 1) * 2)), sp[4], sp[5], 0);
    }
    if (func_0025FBE8(arg0, 0x40000000) != 0) {
        func_00297FE0(1, (rand() % 3) + 6, sp[4], sp[5], 0);
    }
    if (func_0025FBE8(arg0, (s64)0x8000 << 20) != 0) {
        func_00297FE0(1, 0x20, sp[4], sp[5], 0);
    }
    if (func_0025FBE8(arg0, (s64)0x8000 << 21) != 0) {
        func_00297FE0(1, 0x4D, sp[4], sp[5], 0);
    }
    if (func_0025FBE8(arg0, (s64)0x8000 << 22) != 0) {
        func_00297FE0(1, 0x25, sp[4], sp[5], 0);
    }
    if (func_0025FBE8(arg0, (s64)0x8000 << 23) != 0) {
        t958 = *(u8 **)(arg0 + 0x958);
        a1 = 0x33;
        if (t958 != NULL) {
            a1 = ((*(s32 *)(t958 + 0x30)) & 0x8000) ? 0xB : 0x33;
        }
        func_00297FE0(1, a1, sp[4], sp[5], 0);
    }
    if (func_0025FBE8(arg0, (s64)0x8000 << 25) != 0) {
        t958 = *(u8 **)(arg0 + 0x958);
        a1 = 0x30;
        if (t958 != NULL) {
            a1 = ((*(s32 *)(t958 + 0x30)) & 0x8000) ? 0xB : 0x30;
        }
        func_00297FE0(1, a1, sp[4], sp[5], 0);
    }
    if (func_0025FBE8(arg0, (s64)0x8000 << 32) != 0) {
        func_00297FE0(1, 0x48, sp[4], sp[5], 0);
    }
    if (func_0025FBE8(arg0, (s64)0x8000 << 33) != 0) {
        func_00297FE0(1, 0x12, sp[4], sp[5], 0);
    }
    if (func_0025FBE8(arg0, (s64)0x8000 << 34) != 0) {
        func_00297FE0(1, 0x18, sp[4], sp[5], 0);
    }
    if (func_0025FBE8(arg0, (s64)0x8000 << 35) != 0) {
        func_00297FE0(1, 0x2C, sp[4], sp[5], 0);
    }
    if (func_0025FBE8(arg0, (s64)0x8000 << 36) != 0) {
        func_00297FE0(1, 0x1F, sp[4], sp[5], 0);
    }
    if (func_0025FBE8(arg0, (s64)0x8000 << 37) != 0) {
        func_00297FE0(1, 0x31, sp[4], sp[5], 0);
    }
    if (func_0025FBE8(arg0, (s64)0x8000 << 38) != 0) {
        u = (u32)rand();
        func_00297FE0(1, (s32)(u - (((s32)(u + (u >> 0x1F)) >> 1) * 2)) + 4, sp[4], sp[5], 0);
    }
    if (func_0025FBE8(arg0, (s64)0x8000 << 16) != 0) {
        u = (u32)rand();
        func_00297FE0(2, (s32)(u - (((s32)(u + (u >> 0x1F)) >> 1) * 2)), sp[4], sp[5], 0);
    }
}
