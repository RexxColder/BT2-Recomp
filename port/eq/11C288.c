#include "common.h"

extern f32 D_0038405C;
extern f32 D_00384060;
extern f32 D_00384064;

void *memset(void *arg0, s32 arg1, u32 arg2);
void ColCapsule_Set(f32 farg0, s32 arg0, s32 arg1, s32 arg2);
void ColSweep_FromCapsule(s32 arg0, s32 arg1);
void ColBounds_OfCapsule(s32 arg0, s32 arg1);
s32 func_00273248(s32 arg0);
void func_0011CB00(void);
void func_0011CB08(void);
void func_0011C0C0(void);
s32 func_0011CB18(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 StgCol_FirstBit(s64 arg0);
s32 func_00274630(s32 arg0, s32 arg1);
void func_00274338(s32 arg0, s32 arg1);
f32 Vec3_Dist(s32 arg0, s32 arg1);

s32 func_0011C288(u8 *arg0, s32 arg1, s32 arg2) {
    u8 sp[0x100];
    s32 v0 = 0;
    s32 s0;
    s32 s2 = arg2 & 0xFF;
    s32 s4 = arg1 & 0xFF;
    s32 type;
    f32 f;
    u8 *temp_a2;

    if (*(s32 *)(arg0 + 0x80) < 0) {
        return 0;
    }
    memset(sp, 0, 0x90);
    *(s32 *)(sp + 0x80) = (s32)arg0;
    type = *(s32 *)arg0;
    if (type == 0) {
        temp_a2 = *(u8 **)(arg0 + 0xC);
        ColCapsule_Set(*(f32 *)(temp_a2 + 0x10), (s32)(sp + 0xD0), (s32)*(u8 **)(arg0 + 0x10), (s32)temp_a2);
        if (s2 == 0) {
            *(f32 *)(sp + 0xF0) *= *(f32 *)(arg0 + 4);
        }
        ColSweep_FromCapsule((s32)sp, (s32)(sp + 0xD0));
        ColBounds_OfCapsule((s32)(sp + 0xB0), (s32)(sp + 0xD0));
        if (!(*(f32 *)(sp + 0xF0) < *(f32 *)(sp + 0x70))) {
            f = *(f32 *)(sp + 0xF0) + D_0038405C;
        } else {
            f = *(f32 *)(sp + 0x70) + D_00384060;
        }
        *(f32 *)(sp + 0x84) = f;
    } else if (type == 1) {
        temp_a2 = *(u8 **)(arg0 + 0xC);
        ColCapsule_Set(*(f32 *)(temp_a2 + 0x20), (s32)(sp + 0xD0), (s32)(*(u8 **)(arg0 + 0x10) + 0x10),
                       (s32)(temp_a2 + 0x10));
        *(f32 *)(sp + 0xF0) *= *(f32 *)(arg0 + 4);
        ColSweep_FromCapsule((s32)sp, (s32)(sp + 0xD0));
        ColBounds_OfCapsule((s32)(sp + 0xB0), (s32)(sp + 0xD0));
        f = *(f32 *)(sp + 0x70) + D_00384064;
        *(f32 *)(sp + 0x84) = f;
    }

    s0 = func_00273248(*(s32 *)(arg0 + 0x80));
    func_0011CB00();
    if (s2 != 0) {
        func_0011CB08();
    }
    v0 = func_0011CB18((s32)(sp + 0x90), s0, (s32)(sp + 0xB0), (s32)sp, (s32)func_0011C0C0);
    if (v0 != 0) {
        if (sp[0x93] != 0) {
            s32 bit = StgCol_FirstBit(*(s64 *)(sp + 0xA0));
            if (bit >= 0) {
                s32 limit = ((s4 ^ 1) == 0) ? 1 : 0xF423F;
                if (func_00274630(bit, limit) != 0) {
                    func_00274338(bit, (s32)(sp + 0x50));
                    return 0;
                }
            }
        }
        *(s32 *)(arg0 + 0xC8) = *(s32 *)(arg0 + 0xC8) | 1;
        type = *(s32 *)arg0;
        if (type == 1) {
            f = Vec3_Dist((s32)*(u8 **)(arg0 + 0xC), (s32)(arg0 + 0x20));
            *(f32 *)(arg0 + 0xC4) = f;
        } else if (type == 0) {
            f = Vec3_Dist((s32)*(u8 **)(arg0 + 0x10), (s32)(arg0 + 0x20));
            *(f32 *)(arg0 + 0xC4) = f;
        }
        v0 = 1;
    }
    return v0;
}
