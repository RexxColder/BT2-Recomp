#include "common.h"

#define PTR(v) ((u8 *)(s32)(v))
#define LD32(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define LH(p, off) (*(s16 *)((u8 *)(p) + (off)))

s32 BtlCharApi_ObjTestAttr(s32 arg0, s32 arg1);

/* 0x00174A70: flag word (0x200..0x4000) for an object. Without the flag at +0x18 of arg0 the object record
 * (*arg0) is tested with BtlCharApi_ObjTestAttr for each bit; with it, arg1 (+0x14 of arg0) is compared with
 * the six halfwords of the table arg2 at +0x3E..+0x48. */
s32 func_00174A70(s32 arg0, s32 arg1, s32 arg2) {
    u8 *p;
    u8 *s0;
    u8 *q;
    s32 obj;
    s32 s1;
    s32 a1v;

    p = PTR(arg0);
    s1 = 0;
    if (*(u8 *)(p + 0x18) == 0) {
        s0 = PTR(LD32(p, 0));
        obj = LD32(s0, 0);
        if (BtlCharApi_ObjTestAttr(obj, 0x200) != 0) {
            s1 = 0x200;
        }
        if (BtlCharApi_ObjTestAttr(obj, 0x400) != 0) {
            s1 |= 0x400;
        }
        if (BtlCharApi_ObjTestAttr(obj, 0x800) != 0) {
            s1 |= 0x800;
        }
        if (BtlCharApi_ObjTestAttr(obj, 0x1000) != 0) {
            s1 |= 0x1000;
        }
        if (BtlCharApi_ObjTestAttr(obj, 0x2000) != 0) {
            s1 |= 0x2000;
        }
        if (BtlCharApi_ObjTestAttr(obj, 0x4000) != 0) {
            s1 |= 0x4000;
        }
        return s1;
    }

    /* the table comes from *(*arg0 + 0x20) (asm 0x174A90: lw a2,32(s0) in the delay slot), not from arg2 */
    q = PTR(LD32(PTR(LD32(p, 0)), 0x20));
    a1v = LD32(p, 0x14);
    if (a1v == LH(q, 0x3E)) {
        s1 = 0x200;
    }
    if (a1v == LH(q, 0x40)) {
        s1 |= 0x400;
    }
    if (a1v == LH(q, 0x42)) {
        s1 |= 0x800;
    }
    if (a1v == LH(q, 0x44)) {
        s1 |= 0x1000;
    }
    if (a1v == LH(q, 0x46)) {
        s1 |= 0x2000;
    }
    if (a1v == LH(q, 0x48)) {
        s1 |= 0x4000;
    }
    return s1;
}
