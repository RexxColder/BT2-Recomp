#include "m2c_macros.h"

extern u8 *gBtlStage;
u32 func_00272E98(void *arg0, void *arg1, s32 arg2, void *arg3);

/* Zone lookup: record arg0 of the zone table (64-byte records at count*4 after the index list) is tested
 * against point arg1 (x at 0, y at 8). A zone with its box hit returns its own index; a parent zone whose
 * children are listed (count at +8, first index at +0xC) returns the first child that hits. Otherwise the
 * slow path func_00272E98 runs. */
u32 BtlStage_FindZoneNear(s32 arg0, f32 *arg1) {
    u8 *base;
    u8 *recs;
    u8 *e;
    u8 *c;
    s32 *list;
    s32 n;
    s32 i;
    f32 px;
    f32 py;
    f32 lx;
    f32 ly;
    f32 hx;
    f32 hy;
    s32 a2v;
    u32 r;

    base = *(u8 **)(gBtlStage + 0x5C);
    recs = base + *(s32 *)(gBtlStage + 0x3C) * 4;
    a2v = arg0;
    if (arg0 >= 0 && (u32)arg0 < (u32)*(s32 *)(gBtlStage + 0x38)) {
        e = recs + (arg0 << 6);
        px = arg1[0];
        py = arg1[2];
        lx = *(f32 *)(e + 0x20) - *(f32 *)(e + 0x30);
        ly = *(f32 *)(e + 0x28) - *(f32 *)(e + 0x38);
        hx = *(f32 *)(e + 0x20) + *(f32 *)(e + 0x30);
        hy = *(f32 *)(e + 0x28) + *(f32 *)(e + 0x38);
        if (hx < px || hy < py || px < lx || py < ly) {
            a2v = (s32)e;
            list = (s32 *)(base + *(s32 *)(e + 0xC) * 4);
            n = *(s32 *)(e + 0x8);
            for (i = 0; i < n; i++) {
                c = recs + list[i] * 64;
                lx = *(f32 *)(c + 0x20) - *(f32 *)(c + 0x30);
                ly = *(f32 *)(c + 0x28) - *(f32 *)(c + 0x38);
                hx = *(f32 *)(c + 0x20) + *(f32 *)(c + 0x30);
                hy = *(f32 *)(c + 0x28) + *(f32 *)(c + 0x38);
                if (!(hx < px) && !(hy < py) && !(px < lx) && !(py < ly)) {
                    return (u32)list[i];
                }
            }
        } else {
            return (u32)arg0;
        }
    }
    r = func_00272E98(arg1, arg1, a2v, recs);
    return (r == 0xFFFFFFFFu) ? 0 : r;
}
