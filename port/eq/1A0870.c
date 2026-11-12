#include "common.h"

extern s32 D_00387808;
extern f32 D_00384E0C;
extern void *memset(void *dst, s32 c, u32 n);
extern void *memcpy(void *dst, const void *src, u32 n);

s32 BtlScene_IsTimeStopped(void);
void func_001A0390(u8 *arg0, s32 arg1, f32 farg0);
void func_00181760(s32 arg0, void *arg1);
void func_001817F8(s32 arg0, s32 arg1);
void func_00181828(void **arg0, f32 farg0);
void func_001E7178(void *arg0);
void Vec4_Set(void *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
s32 EftPtcl3_Create(s32 arg0);
void EftPtcl3_SetType(s32 arg0, s32 arg1);
void func_00129C28(s32 arg0, s32 arg1);

/* 0x001A0870 (per-frame update of an effect owner). Skipped while the scene is time-stopped. The owner is at obj+0x38
 * (fields: 0x24 float timer, 0x28 flags (4 = particle created, 8 = attached), 0x34 particle, 0x40 u16 phase, 0x42 s16
 * step, 0x44 counter). Each step: the first and 0x21st ticks call func_001A0390; the particle is created once (flag 4)
 * from a 0x50-byte parameter block; while the flag 8 is clear, a 0x14-byte message is sent with func_00181760 and
 * func_001817F8 and the records of the table at (*(obj+0x398)) get their fields set; the tail updates the timer and
 * phase. */
void func_001A0870(u8 *obj) {
    u8 frame[0xA0];
    u8 *s1;
    u8 *s3;
    u8 *msg;
    u8 *rec;
    s32 flags;
    s32 cnt;
    s32 count;
    s32 h;
    s32 i;
    s32 ptcl;
    f32 f0;

    if (BtlScene_IsTimeStopped() != 0) {
        return;
    }

    s1 = *(u8 **)(obj + 0x38);
    s3 = (u8 *)(D_00387808 + 8);

    cnt = *(s32 *)(s1 + 0x44) + 1;
    *(s32 *)(s1 + 0x44) = cnt;
    if (cnt == 1 || cnt == 0x21) {
        h = *(s16 *)(s1 + 0x42);
        if (h == 1) {
            f0 = 1.0f;
        } else {
            f0 = *(f32 *)(s1 + 0x24);
        }
        func_001A0390(obj, (s32)f0, (f32)h);
        *(u16 *)(s1 + 0x42) = (u16)(*(u16 *)(s1 + 0x42) + 1);
    }

    flags = *(s32 *)(s1 + 0x28);
    if ((flags & 4) == 0) {
        *(s32 *)(frame + 0x50) = 0;
        f0 = *(f32 *)(s1 + 0x24) * 1.5f;
        *(f32 *)(frame + 0x54) = f0;
        memset(frame + 0x60, 0, 0x10);
        memset(frame + 0x70, 0, 0x10);
        *(s32 *)(frame + 0x80) = 1;
        *(s32 *)(frame + 0x84) = (s32)(s3 + 0x228);
        *(s32 *)(frame + 0x88) = *(s32 *)(s3 + 0x338) + 0x164;
        *(s32 *)(frame + 0x8C) = *(s32 *)(s3 + 0x33C) + 0x50;
        *(s32 *)(frame + 0x90) = *(s32 *)s1;
        memcpy(frame, frame + 0x50, 0x50);

        func_00129C28((s32)(frame + 0x10), (s32)(s1 + 0x10));
        Vec4_Set(frame + 0x20, 0.0f, -1.0f, 0.0f, 1.0f);
        ptcl = EftPtcl3_Create((s32)frame);
        *(s32 *)(s1 + 0x34) = ptcl;
        EftPtcl3_SetType(ptcl, 2);
        flags |= 4;
        *(s32 *)(s1 + 0x28) = flags;
    }

    if ((flags & 8) == 0) {
        msg = frame + 0x50;
        *(u8 *)(msg + 0) = 2;
        *(s32 *)(msg + 4) = *(s32 *)s1;
        *(s32 *)(msg + 8) = 0;
        *(s32 *)(msg + 0xC) = *(s32 *)(s3 + 0x398);
        *(s32 *)(msg + 0x10) = (s32)(s3 + 0x348);

        count = *(s32 *)(*(u8 **)(s3 + 0x398) + 0x2D0);
        for (i = 0; i < count; i++) {
            rec = *(u8 **)(s3 + 0x398) + i * 0x30;
            *(f32 *)(rec + 0x10) = 2.0f;
            *(u8 *)(rec + 0x2C) = 10;
            *(u8 *)(rec + 0x2B) = 0x60;
        }

        func_00181760((s32)(s1 + 0x38), msg);
        func_001817F8((s32)(s1 + 0x38), (s32)(s1 + 0x10));
        *(s32 *)(s1 + 0x28) = *(s32 *)(s1 + 0x28) | 8;
    }

    func_00181828((void **)(s1 + 0x38), *(f32 *)(s1 + 0x24));
    func_001E7178(s1 + 0x2C);
    func_001E7178(s1 + 0x30);

    *(f32 *)(s1 + 0x24) = *(f32 *)(s1 + 0x24) + D_00384E0C;
    *(u16 *)(s1 + 0x40) = (u16)((*(u16 *)(s1 + 0x40) + 1) & 7);
}
