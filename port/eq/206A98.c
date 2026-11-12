#include "common.h"
#include "m2c_macros.h"

extern f32 D_00385950;

s32 func_0025FBE8(void *a0, s64 a1);
s32 BtlObjXf_Update(void *a0);
s32 func_001FA3A8(s32 a0);
s32 func_00210000(void *a0, s32 a1);
void func_002102B0(void *a0, s32 a1, f32 farg0, f32 farg1);
s32 func_00101608(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0);
void func_00267550(void *a0, s32 a1, s32 a2);
void func_003126C8(void *a0, void *a1);
s32 rand(void);

void func_00206A98(void *arg0, void *arg1) {
    u8 sp[0x10];
    void *s0 = arg0;
    void *s2 = arg1;
    s32 s1;
    s32 v;

    if (func_0025FBE8(s0, 0x2000000) != 0) {
        M2C_FIELD(s0, s32 *, 0xAF0) = M2C_FIELD(s0, s32 *, 0xAF0) & ~2;
    }
    if (func_0025FBE8(s0, 0x4000000) != 0) {
        M2C_FIELD(s0, s32 *, 0xAF0) = M2C_FIELD(s0, s32 *, 0xAF0) | 2;
    }
    if (func_0025FBE8(s0, 0x20) != 0) {
        M2C_FIELD(s0, s32 *, 0xAF0) = M2C_FIELD(s0, s32 *, 0xAF0) | 0x20;
    }
    if (func_0025FBE8(s0, 0x40) != 0) {
        M2C_FIELD(s0, s32 *, 0xAF0) = M2C_FIELD(s0, s32 *, 0xAF0) & ~0x20;
    }
    if (func_0025FBE8(s0, (s64)0x8000 << 28) != 0) {
        M2C_FIELD(s0, s32 *, 0xAF0) = M2C_FIELD(s0, s32 *, 0xAF0) | 0x40;
    }
    if (func_0025FBE8(s0, (s64)0x8000 << 29) != 0) {
        M2C_FIELD(s0, s32 *, 0xAF0) = M2C_FIELD(s0, s32 *, 0xAF0) & ~0x40;
    }
    func_003126C8(sp, (u8 *)s0 + 0x9A0);
    if (func_0025FBE8(s0, 0x10) != 0) {
        func_00210000(sp, (rand() % 3) + 0x28);
    }
    if (func_0025FBE8(s0, 0x10000000) != 0) {
        func_00210000(sp, 0x1E);
    }
    func_0025FBE8(s0, 0x20000000);
    func_0025FBE8(s0, 0x40000000);
    if (func_0025FBE8(s0, (s64)0x8000 << 20) != 0) {
        func_00210000(sp, 0x20);
    }
    if (func_0025FBE8(s0, (s64)0x8000 << 21) != 0) {
        func_00210000(sp, 0x4D);
    }
    if (func_0025FBE8(s0, (s64)0x8000 << 22) != 0) {
        func_00210000(sp, 0x25);
    }
    if (func_0025FBE8(s0, (s64)0x8000 << 23) != 0) {
        func_00210000(sp, 0x33);
    }
    if (func_0025FBE8(s0, (s64)0x8000 << 25) != 0) {
        func_00210000(sp, 0x30);
    }
    if (func_0025FBE8(s0, (s64)0x8000 << 32) != 0) {
        func_00210000(sp, 0x48);
    }
    if (func_0025FBE8(s0, (s64)0x8000 << 16) != 0) {
        v = rand();
        func_002102B0(sp, v % 2, 200.0f, D_00385950);
    }

    s1 = -1;
    v = func_001FA3A8(BtlObjXf_Update(s2));
    s1 = (v & 0x20000000) ? 0x53 : -1;
    s1 = (v & 0x40000000) ? 0x55 : s1;
    s1 = (v & 0x04000000) ? 0x57 : s1;
    s1 = (v & 0x08000000) ? 0x59 : s1;
    s1 = (v & 0x10000000) ? 0x5B : s1;
    if (s1 >= 0) {
        if (func_0025FBE8(s0, 0x8000) != 0) {
            func_00101608(M2C_FIELD(s2, s32 *, 0x1534), M2C_FIELD(M2C_FIELD(s2, void **, 0x1530), s32 *, 4), s1, 0, 0);
        }
        if (func_0025FBE8(s0, (s64)0x8000 << 24) != 0) {
            func_00101608(M2C_FIELD(s2, s32 *, 0x1534), M2C_FIELD(M2C_FIELD(s2, void **, 0x1530), s32 *, 4), s1 + 1, 0, 0);
        }
    }

    if (BtlObjXf_Update(s2) == 0x1B6) {
        s1 = (func_0025FBE8(s0, 0x8000) != 0) ? 0x62 : -1;
        s1 = (func_0025FBE8(s0, (s64)0x8000 << 24) != 0) ? 0x63 : s1;
        if (s1 >= 0) {
            func_00101608(M2C_FIELD(s2, s32 *, 0x1534), M2C_FIELD(s0, s32 *, 4), s1, 0, 0);
            func_00267550(s0, 2, s1);
        }
    }
}
