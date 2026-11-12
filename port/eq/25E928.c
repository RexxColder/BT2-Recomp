#include "common.h"

extern u8 D_002C3630[] __attribute__((section(".data")));

void Quat_Unpack(void *arg0, u64 arg1);
void Quat_Slerp(void *arg0, void *arg1, void *arg2, f32 farg0);
s32 func_003126C8(void *arg0, void *arg1);

void BtlObjAnim_SamplePosRot(u8 *arg0, f32 *arg1, u8 *arg2, u16 *arg3, f32 farg0) {
    u8 *key;
    u8 *cur;
    u8 *nxt;
    f32 qa[4];
    f32 qb[4];
    f32 t;
    f32 tc;
    f32 tn;
    f32 ratio;
    s32 n;
    s32 idx;
    s32 s2;
    s32 found;
    s32 tcI;
    s32 tnI;

    key = arg0 + 4;
    t = farg0;
    n = *(u16 *)(arg0 + 2);
    if (n == 1) {
        arg1[0] = *(f32 *)(key + 0);
        arg1[1] = *(f32 *)(key + 4);
        arg1[2] = *(f32 *)(key + 8);
        arg1[3] = 1.0f;
        Quat_Unpack(arg2, ((u64)*(u32 *)(key + 0x14) << 32) | *(u32 *)(key + 0x10));
        return;
    }

    idx = *arg3;
    if (idx >= n - 1) {
        idx = 0;
        *arg3 = 0;
    }

search:
    found = 0;
    for (s2 = idx + 1; s2 < n; s2++) {
        cur = key + (s2 - 1) * 0x18;
        nxt = key + s2 * 0x18;
        tcI = *(s32 *)(cur + 0xC);
        tnI = *(s32 *)(nxt + 0xC);
        tc = (f32)(u32)tcI;
        tn = (f32)(u32)tnI;

        if (tc == t) {
            arg1[0] = *(f32 *)(cur + 0);
            arg1[1] = *(f32 *)(cur + 4);
            arg1[2] = *(f32 *)(cur + 8);
            arg1[3] = 1.0f;
            Quat_Unpack(arg2, ((u64)*(u32 *)(cur + 0x14) << 32) | *(u32 *)(cur + 0x10));
            *arg3 = s2 - 1;
            found = 1;
            break;
        }
        if (tc < t && t < tn) {
            ratio = (t - tc) / (f32)((u32)tnI - (u32)tcI);
            arg1[0] = (*(f32 *)(nxt + 0) - *(f32 *)(cur + 0)) * ratio + *(f32 *)(cur + 0);
            arg1[1] = (*(f32 *)(nxt + 4) - *(f32 *)(cur + 4)) * ratio + *(f32 *)(cur + 4);
            arg1[2] = (*(f32 *)(nxt + 8) - *(f32 *)(cur + 8)) * ratio + *(f32 *)(cur + 8);
            arg1[3] = 1.0f;
            Quat_Unpack(qa, ((u64)*(u32 *)(nxt + 0x14) << 32) | *(u32 *)(nxt + 0x10));
            Quat_Unpack(qb, ((u64)*(u32 *)(cur + 0x14) << 32) | *(u32 *)(cur + 0x10));
            Quat_Slerp(arg2, qb, qa, ratio);
            *arg3 = s2 - 1;
            found = 1;
            break;
        }
        if (tn == t) {
            arg1[0] = *(f32 *)(nxt + 0);
            arg1[1] = *(f32 *)(nxt + 4);
            arg1[2] = *(f32 *)(nxt + 8);
            arg1[3] = 1.0f;
            Quat_Unpack(arg2, ((u64)*(u32 *)(nxt + 0x14) << 32) | *(u32 *)(nxt + 0x10));
            *arg3 = s2 - 1;
            found = 1;
            break;
        }
    }

    if (found) {
        return;
    }
    if (*arg3 != 0) {
        *arg3 = 0;
        idx = 0;
        goto search;
    }
    func_003126C8(arg2, D_002C3630);
    func_003126C8(arg1, D_002C3630);
}
