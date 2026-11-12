#include "common.h"

extern f32 D_003876EC;
extern void *memcpy(void *dst, const void *src, u32 n);
void ColBox_GetCenter(u8 *box, u8 *out);
void StgGround_ExtendBoxDown(u8 *box);
s32 BtlStage_FindZoneNear(s32 zone, u8 *center);
s32 func_00273248(s32 arg0);
void func_0011CB00(void);
void func_0011CB18(u8 *res, s32 zone, u8 *box, u8 *ctx, void *cb);
void StgGround_Cb(void);

/* 0x0011C948 (StgGround_Probe, BT3 C as guide): out (when set) +4 = D_003876EC; center of the box; box copy (0x18 bytes)
 * extended down; ctx = {out, minY}; zone = func_00273248(BtlStage_FindZoneNear(zone, center)); func_0011CB00();
 * func_0011CB18(res, zone, box, ctx, StgGround_Cb). */
void StgGround_Probe(s32 arg0, u8 *arg1, u8 *arg2, f32 arg3) {
    u8 ctx[8];
    u8 box[0x18];
    u8 res[0x20];
    u8 center[0x10];
    s32 z;

    if (arg2 != 0) {
        *(f32 *)(arg2 + 4) = D_003876EC;
    }
    ColBox_GetCenter(arg1, center);
    memcpy(box, arg1, 0x18);
    StgGround_ExtendBoxDown(box);
    *(s32 *)ctx = (s32)arg2;
    *(f32 *)(ctx + 4) = arg3;
    z = func_00273248(BtlStage_FindZoneNear(arg0, center));
    func_0011CB00();
    func_0011CB18(res, z, box, ctx, StgGround_Cb);
}
