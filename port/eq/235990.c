#include "common.h"

extern void BtlMove_BrakeVertical(void *arg0);
extern s32 BtlObjXf_Update(void *arg0);
extern void func_001F9D78(void *arg0, s32 arg1);
extern s32 func_001F9FB0(void *arg0, s32 arg1);
extern void func_001FA0A0(void *arg0, s32 arg1, s32 arg2);
extern s32 func_001FA2E0(void *arg0);
extern s32 func_001FA3A8(s32 arg0);
extern void func_00206958(void *arg0, s64 arg1);
extern void func_00206EA0(void *arg0);
extern void func_00206FE0(void *arg0, s32 arg1);
extern void func_00207068(void *arg0);
extern void func_002071B0(void *arg0, s32 arg1);
extern s32 func_00210DD8(void *arg0);
extern void *func_00211288(s32 arg0);
extern s32 func_00211310(void *arg0, s32 arg1, s32 arg2);
extern void func_002113C0(void *arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_00211828(void *arg0);
extern void func_00211F08(void *arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_00212320(s32 arg0);
extern s32 func_00212560(void *arg0);
extern void func_00215068(void *arg0, s32 arg1, s32 arg2, f32 f12, f32 f13);
extern void func_00215E88(void *arg0, s32 arg1, f32 f12);
extern void func_00216208(void *arg0, f32 f12, f32 f13);
extern void func_00216770(void *arg0);
extern s32 func_00240F78(void *arg0, s32 arg1);
extern s32 func_002411E0(void *arg0, s32 arg1);
extern f32 D_003869C4;
extern f32 D_003869C8;

void func_00235990(void *arg0) {
    s32 s2;
    s32 s1;
    s32 s3;
    void *a0;
    u8 *s0;
    s32 t;

    s0 = arg0;
    s2 = func_00212320(arg0);
    s1 = func_00212560(s0);
    s3 = func_001FA3A8(BtlObjXf_Update(s0)) & 0x10;
    if (s3 == 0) {
        a0 = s0;
    } else {
        a0 = func_00211288(func_00210DD8(s0));
    }
    if (func_00240F78(a0, s2) == 0xA7) {
        *(s32 *)(s0 + 0x8DC) = *(s32 *)(s0 + 0x8DC) | 2;
    }
    if ((func_001FA2E0(s0) != 0) && (s1 != 0)) {
        if (s3 != 0) {
            func_00211F08(s0, s2, s1, 0);
        } else {
            func_00211F08(s0, s2, s1, 1);
        }
        func_002113C0(s0, 1, 0x20000, 1);
    }
    if (s1 != *(s32 *)(s0 + 0xA7C)) {
        t = *(s32 *)(s0 + 0xA74);
        if (*(s32 *)(s0 + 0x8DC) & 2) {
            if (s1 < (t - 1)) {
                func_001FA0A0(s0, BtlObjXf_Update(s0) + 1, 0);
            } else {
                if ((func_001FA2E0(s0) != 0) && (s3 == 0)) {
                    func_002113C0(s0, 0xC, 0x8000, 1);
                    func_002113C0(s0, 0xC, 0x10000, 0);
                    func_002113C0(s0, 0xC, 0x20000, 0);
                    func_002113C0(s0, 0xC, 0x40000, 0);
                    func_002113C0(s0, 0xC, 0x80000, 0);
                    func_00211828(s0);
                }
                if (func_001F9FB0(s0, 0) != 0) {
                    if (s3 != 0) {
                        *(s32 *)(s0 + 0x8DC) = *(s32 *)(s0 + 0x8DC) | 1;
                    } else if (func_00211310(s0, 0xC, 0x10000) != 0) {
                        *(s32 *)(s0 + 0x8DC) = *(s32 *)(s0 + 0x8DC) | 1;
                    } else {
                        func_002113C0(s0, 9, 0x10000, 1);
                    }
                }
            }
        } else if (s1 >= (t - 1)) {
            if (func_001F9FB0(s0, 0) != 0) {
                *(s32 *)(s0 + 0x8DC) = *(s32 *)(s0 + 0x8DC) | 1;
                if (*(s32 *)(s0 + 0xA80) >= 0) {
                    func_00206EA0(s0);
                    if ((*(s32 *)(s0 + 0xA80) >= 0) && (*(s32 *)(s0 + 0xA7C) < s1)) {
                        if (func_001FA2E0(s0) != 0) {
                            func_00206FE0(s0, (s1 - *(s32 *)(s0 + 0xA7C)) + 0x1B0);
                        }
                        if (func_002411E0(s0, s2) & 0x10000) {
                            func_002071B0(s0, 0);
                        }
                        func_00207068(s0);
                    }
                }
            } else {
                if ((*(s32 *)(s0 + 0xA80) >= 0) && (*(s32 *)(s0 + 0xA7C) < s1)) {
                    if (func_001FA2E0(s0) != 0) {
                        func_00206FE0(s0, (s1 - *(s32 *)(s0 + 0xA7C)) + 0x1B0);
                    }
                    if (func_002411E0(s0, s2) & 0x10000) {
                        func_002071B0(s0, 0);
                    }
                    func_00207068(s0);
                }
            }
        } else {
            func_001FA0A0(s0, BtlObjXf_Update(s0) + 1, 0);
            if ((*(s32 *)(s0 + 0xA80) >= 0) && (*(s32 *)(s0 + 0xA7C) < s1)) {
                if (func_001FA2E0(s0) != 0) {
                    func_00206FE0(s0, (s1 - *(s32 *)(s0 + 0xA7C)) + 0x1B0);
                }
                if (func_002411E0(s0, s2) & 0x10000) {
                    func_002071B0(s0, 0);
                }
                func_00207068(s0);
            }
        }
    } else if ((func_001F9FB0(s0, 0) != 0) && (func_00211310(s0, 0xC, 0x2000) != 0)) {
        if (*(s32 *)(s0 + 0xA80) >= 0) {
            func_002113C0(s0, 0xC, 0x4000, 1);
        }
        func_001F9D78(s0, BtlObjXf_Update(s0) + 1);
    }

    func_00215068(s0, 5, 0xD, D_003869C4, 1.0f);
    func_00215E88(s0, 6, 1.0f);
    func_00216208(s0, 0.0f, D_003869C8);
    if ((s3 != 0) || (s1 < (*(s32 *)(s0 + 0xA74) - 1))) {
        BtlMove_BrakeVertical(s0);
    } else if (func_002411E0(s0, s2) & 0x1000) {
        func_00216770(s0);
    } else {
        BtlMove_BrakeVertical(s0);
    }
    func_002113C0(s0, 9, 0x200, 1);
    func_002113C0(s0, 1, 0x40, 1);
    func_002113C0(s0, 3, 0x800, 1);
    func_002113C0(s0, 3, 0xE, 1);
    func_002113C0(s0, 0xD, 8, 1);
    func_002113C0(s0, 0xD, 0x10, 1);
    func_002113C0(s0, 0xD, 1, 1);
    func_002113C0(s0, 9, 0x200000, 1);
    func_002113C0(s0, 1, 0x800000, 1);
    func_00206958(s0, (s64)0x8000 << 29);
    func_002113C0(s0, 0xF, 0x100000, 1);
    func_002113C0(s0, 1, 0x100000, 1);
    if (func_001FA2E0(s0) != 0) {
        func_002113C0(s0, 2, 0x400, 1);
    }
    if (s3 != 0) {
        func_002113C0(s0, 6, 2, 1);
        func_002113C0(s0, 6, 4, 1);
        func_002113C0(s0, 1, 0x1000, 1);
    } else {
        func_002113C0(s0, 5, 0x20, 1);
        func_002113C0(s0, 1, 0x2000, 1);
    }
    *(f32 *)(s0 + (s1 * 4) + 0xA94) = *(f32 *)(*(u8 **)(s0 + 0x1530) + 0xBE0);
}
