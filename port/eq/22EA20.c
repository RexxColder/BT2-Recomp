#include "common.h"

#define PTR(p, off) (*(u8 **)((u8 *)(p) + (off)))
#define W32(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define F32(p, off) (*(f32 *)((u8 *)(p) + (off)))
#define U8(p, off) (*(u8 *)((u8 *)(p) + (off)))

extern f32 D_0038674C;
extern f32 D_00386750;
extern f32 D_00386754;
extern f32 D_00386758;
extern f32 D_0038675C;

s32 func_00211310(u8 *obj, s32 arg1, s32 arg2);
s32 func_00211328(u8 *obj, s32 arg1, s32 arg2);
s32 func_00212820(u8 *obj);
s32 func_00212878(u8 *obj);
u8 *BtlMember_GetActiveGauge(u8 *obj);
s32 func_0023D1E0(u8 *obj, s32 arg1);
f32 func_00217330(u8 *obj);
s32 BtlAnim_SetBlend(u8 *obj, f32 farg0);

s32 func_0022EA20(u8 *obj) {
    f32 f0;
    s32 s1;
    u8 *g;

    if (func_00211310(obj, 0, 4) == 0 && func_00211328(obj, 0, 4) == 0
        && !(W32(PTR(obj, 0x1530), 0xE54) & 0x20) && func_00211310(obj, 0, 0x100) == 0) {
        f0 = func_00217330(obj);
        if (F32(PTR(obj, 0x1530), 0xFAC) * D_0038674C < f0) {
            BtlAnim_SetBlend(obj, D_00386750);
            return 0x21;
        }
    }

    if (func_00212820(obj) != 0) {
        if (W32(obj, 0x8CC) >= 0x5B) {
            BtlAnim_SetBlend(obj, D_00386754);
            return (func_00211310(obj, 0, 0x100) == 0) ? 0x22 : 0x26;
        }
        g = BtlMember_GetActiveGauge(obj);
        if (U8(g, 0x29) == 0 || W32(obj, 0xB94) <= 0) {
            s1 = func_0023D1E0(obj, 0);
            if (s1 != -1) {
                BtlAnim_SetBlend(obj, D_00386758);
                return s1;
            }
        }
    }

    if (W32(obj, 0xB74) > 0) {
        return 0xAA;
    }
    if (W32(obj, 0x8DC) & 1) {
        if (func_00211310(obj, 0, 0x400000) != 0) {
            return 0x33;
        }
    }
    if (func_00212878(obj) == 0) {
        return -1;
    }
    if (func_00211310(obj, 0, 0x40) == 0) {
        return -1;
    }
    if (func_00212820(obj) == 0) {
        return -1;
    }
    BtlAnim_SetBlend(obj, D_0038675C);
    return 0x26;
}
