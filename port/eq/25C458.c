#include "m2c_macros.h"

extern u8 *D_003876A0;
void func_003126C8(void *a0, void *a1);
s32 BtlStage_FindZoneNear(s32 arg0, void *arg1);
s32 StgCol_TraceSphere(s32 obj, void *seg, void *hitPos, f32 *t, u8 *unk);

/* BT3 BtlCam_TraceStage (src/battle/btl_cam.c). The segment from..to is tested against the stage zones of both
 * ends; when the two ends are in different zones the first zone is tried, then the second. Vec4 is 16 bytes. */
s32 BtlCam_TraceStage(void *out, void *from, void *to, f32 *frac, s32 *hitObj) {
    u8 fr[0xB0];
    void *a;
    void *b;
    void *seg;
    void *hitPos;
    u8 *unk;
    f32 *tp;
    f32 f;
    s32 objA;
    s32 objB;
    s32 obj;
    s32 ret;

    a = fr;
    b = fr + 0x10;
    seg = fr + 0x20;
    hitPos = fr + 0x50;
    unk = fr + 0x60;
    tp = (f32 *)(fr + 0xA0);

    func_003126C8(out, from);
    if ((*(u64 *)(D_003876A0 + 0x4D8) & 0x2000) != 0) {
        if (frac != NULL) {
            *frac = 1.0f;
        }
        return 0;
    }
    func_003126C8(a, to);
    func_003126C8(b, from);
    objA = BtlStage_FindZoneNear(-1, a);
    objB = BtlStage_FindZoneNear(-1, b);
    func_003126C8(seg, a);
    func_003126C8(fr + 0x30, b);
    *(f32 *)(fr + 0x40) = 2.0f;

    if (objA != objB) {
        obj = objA;
        if (StgCol_TraceSphere(obj, seg, hitPos, tp, unk) != 0) {
            func_003126C8(out, hitPos);
            ret = 1;
            f = *tp;
        } else {
            obj = objB;
            if (StgCol_TraceSphere(obj, seg, hitPos, tp, unk) != 0) {
                func_003126C8(out, hitPos);
                ret = 1;
                f = *tp;
            } else {
                ret = 0;
                f = 1.0f;
            }
        }
    } else {
        obj = objA;
        if (StgCol_TraceSphere(obj, seg, hitPos, tp, unk) != 0) {
            func_003126C8(out, hitPos);
            ret = 1;
            f = *tp;
        } else {
            f = 1.0f;
            ret = 0;
        }
    }
    if (frac != NULL) {
        *frac = f;
    }
    if (hitObj != NULL) {
        *hitObj = obj;
    }
    return ret;
}
