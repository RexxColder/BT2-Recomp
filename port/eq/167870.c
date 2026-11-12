#include "common.h"

#define LD32(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define LU8(p, off) (*(u8 *)((u8 *)(p) + (off)))
#define LDF(p, off) (*(f32 *)((u8 *)(p) + (off)))

s32 func_0014EFA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
s32 func_0014F2B8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_001513D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                   s32 arg8, s32 arg9, f32 farg0);

/* 0x00167870: walks the 16 slots of the table at *arg2 (0x110 bytes each, count byte at +0) of the object at
 * arg1+0x38. For every entry, arg3 (low byte) selects func_0014F2B8 or func_0014EFA8 (with the object's flag
 * bits 1 and 4); a non-zero result (2 when the object's flag 0x100 is set) is passed on to func_001513D0. */
void func_00167870(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 obj;
    s32 s6;
    s32 s2;
    s32 flag;
    s32 off;
    s32 idx;
    s32 k;
    s32 rec;
    s32 v;
    s32 w;

    flag = arg3 & 0xFF;
    obj = LD32(arg1, 0x38);
    s6 = LD32(obj, 0xB0);
    s2 = obj + 0xB4;

    off = 0;
    for (idx = 0; idx < 16; idx++) {
        rec = LD32(arg2, 0) + off;
        if (LU8(rec, 0) != 0) {
            for (k = 0; k < LU8(rec, 0); k++) {
                w = LD32(obj, 0);
                if (flag != 0) {
                    v = func_0014F2B8(arg2, s2, idx, k);
                } else {
                    v = func_0014EFA8(arg0, arg2, s2, idx, k, w & 0x1, w & 0x4);
                }
                if (LD32(obj, 0) & 0x100) {
                    v = 2;
                }
                if (v != 0) {
                    func_001513D0(s6, arg2, s2, obj + 0x860, obj + 0x80, obj + 0x30, idx, k, k, v,
                                  LDF(obj, 0x18));
                }
            }
        }
        off += 0x110;
    }
}
