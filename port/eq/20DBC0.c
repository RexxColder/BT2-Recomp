#include "common.h"

s32 func_00211310(void *arg0, s32 arg1, s32 arg2);
s32 func_002113C0(void *arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00211328(void *arg0, s32 arg1, s32 arg2);
s32 BtlPad_Test48(void *arg0, s32 arg1);
s32 BtlPad_Test4C(void *arg0, s32 arg1);
f32 func_0020DB08(void *arg0, s32 arg1);
f32 BtlOpp_GetDistance(void *arg0);
void func_0020FC38(void *arg0, s32 arg1);

/* 0x0020DBC0: per-frame pad/edge handler for the object at arg0; 0x1018 is a 0..3 hold counter. */
s32 func_0020DBC0(void *arg0) {
    void *obj;
    s32 v;
    f32 f20;
    f32 dist;

    obj = arg0;
    if (func_00211310(obj, 1, 0x10000) != 0) {
        if (func_00211310(obj, 0, 1) != 0) {
            if (BtlPad_Test48(obj, 0xD) != 0) {
                if (BtlPad_Test4C(obj, 6) != 0) {
                    *(s32 *)((u8 *)obj + 0x1018) = 1;
                }
            }
            if (BtlPad_Test48(obj, 6) != 0) {
                v = *(s32 *)((u8 *)obj + 0x1018);
                if (v > 0) {
                    v += 1;
                    *(s32 *)((u8 *)obj + 0x1018) = v;
                }
                if (!(v < 3)) {
                    func_002113C0(obj, 0, 1, 0);
                }
            } else {
                *(s32 *)((u8 *)obj + 0x1018) = 0;
            }
        } else {
            *(s32 *)((u8 *)obj + 0x1018) = 0;
        }
    }

    v = *(s32 *)((u8 *)obj + 0xB8C);
    if (v > 0) {
        func_002113C0(obj, 0, 1, 0);
        if (func_00211310(obj, 0xA, 0x200) != 0) {
            func_002113C0(obj, 0, 0x10000, 1);
        }
    }
    if (func_00211310(obj, 0xA, 0x80) != 0) {
        func_002113C0(obj, 0, 1, 0);
    }
    func_002113C0(obj, 1, 1, 0);

    if (func_00211310(obj, 1, 0x800) == 0) {
        if (func_00211310(obj, 0, 0x400000) != 0) {
            v = *(s32 *)((u8 *)obj + 0xB8C);
            if (!(v > 0)) {
                v = *(s32 *)((u8 *)obj + 0xB48);
                if (v < 3) {
                    if (func_00211310(obj, 0xA, 0x80) == 0) {
                        f20 = func_0020DB08(obj, 0);
                        dist = BtlOpp_GetDistance(obj);
                        if (dist < f20) {
                            func_002113C0(obj, 1, 1, 1);
                            func_002113C0(obj, 0, 1, 1);
                        }
                    }
                }
            }
        }
    }
    func_002113C0(obj, 1, 0x800, 0);

    if (func_00211310(obj, 0, 1) == 0) {
        if (func_00211328(obj, 0, 1) != 0) {
            func_0020FC38(obj, 0x2D);
        }
    }
    if (func_00211310(obj, 0, 1) != 0) {
        return func_002113C0(obj, 0, 0x10000, 0);
    }
    return 0;
}
