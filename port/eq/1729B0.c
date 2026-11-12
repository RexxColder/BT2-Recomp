#include "m2c_macros.h"

void *func_001F3758(void *arg0);
s32 EftShot_TestBits(s32 objId, s32 mask);
void *func_00172978(void *arg0);
void Vec3_Sub(void *a0, void *a1, void *a2);
void Vec3_Normalize(void *a0, void *a1);
s32 func_00191600(void *arg0);
s32 func_00191728(s32 arg0);
void EftTechEvt_RequestRestart(s32 arg0);

/* Five-slot shot table at unit+0xAB0 (8 bytes a slot, value at +4): a slot whose value is no longer live
 * is cleared; returns 1 when any slot is still live. When the unit's shot bit test passes and no flag
 * is set, a message built from the unit is sent (vector from the unit's +0x70 minus +0x40, normalized). */
s32 EftTech_UpdateShots(u8 *arg0) {
    u8 frame[0x70];
    u8 *ret;
    u8 *u;
    u8 *p;
    u8 *s3;
    u8 *ent;
    s32 s4;
    s32 s5;
    s32 k;

    ret = func_001F3758(arg0);
    u = *(u8 **)(arg0 + 0x38);
    s4 = *(s32 *)((u8 *)ret + 0x38);
    s5 = 0;
    ent = u + 0xAB0;

    if ((*(u32 *)u & 1) == 0) {
        p = *(u8 **)(u + 0xA0);
        if (EftShot_TestBits(*(s32 *)p, 4)) {
            s3 = func_00172978(u);
            if (s3 != NULL) {
                Vec3_Sub(frame, u + 0x70, u + 0x40);
                Vec3_Normalize(frame, frame);
                *(f32 *)(frame + 0xC) = 1.0f;
                *(u8 **)(frame + 0x40) = p;
                *(s32 *)(frame + 0x44) = s4;
                *(u8 **)(frame + 0x48) = u + 0x850;
                *(u8 **)(frame + 0x4C) = u + 0x70;
                *(u8 **)(frame + 0x50) = frame;
                *(s32 *)(frame + 0x54) = *(s32 *)(u + 0xAAC);
                *(s32 *)(frame + 0x58) = 5;
                *(s32 *)(frame + 0x5C) = 2;
                *(s32 *)(frame + 0x60) = 1;
                *(f32 *)(frame + 0x64) = 1.0f;
                *(f32 *)(frame + 0x68) = *(f32 *)(u + 0x14);
                *(s32 *)(frame + 0x6C) = 0;
                for (k = 0; k < 0x30; k += 4) {
                    *(u32 *)(frame + 0x10 + k) = *(u32 *)(frame + 0x40 + k);
                }
                *(s32 *)(s3 + 4) = func_00191600(frame + 0x10);
                *(s32 *)(u + 0xAAC) = *(s32 *)(u + 0xAAC) + 1;
                *(u32 *)u = *(u32 *)u | 0x80;
            }
            EftTechEvt_RequestRestart(*(s32 *)p);
        }
    }

    for (k = 4; k >= 0; k--) {
        if (func_00191728(*(s32 *)(ent + 4)) == 0) {
            *(s32 *)(ent + 4) = 0;
        } else {
            s5 = 1;
        }
        ent += 8;
    }
    return s5;
}
