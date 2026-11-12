#include "common.h"

void func_002767A8(void *arg0);
void Vu0Screen_StoreMtx(void *arg0);
void func_0029E2E0(void *arg0, void *arg1, void *arg2);
extern void *gBtlCamView;

void func_0027E9F0(void *arg0) {
    u8 frame[0x80];
    u8 *s1;
    f32 f50;
    f32 f54;
    f32 f58;
    f32 x;
    f32 y;
    s32 v0;
    s32 a0;
    s32 a1;
    s32 a2;
    s32 temp_v0;

    s1 = (u8 *)arg0;
    if (s1[0x500] == 0) {
        return;
    }
    if (s1[0x501] == 0) {
        *(s32 *)(s1 + 0x504) = *(s32 *)(s1 + 0x514);
        a1 = *(s32 *)(s1 + 0x520);
        *(s32 *)(s1 + 0x50C) = a1;
    } else {
        func_002767A8(frame + 0x40);
        Vu0Screen_StoreMtx(frame);
        func_0029E2E0(frame + 0x50, frame, frame + 0x40);
        f50 = *(f32 *)(frame + 0x50);
        f54 = *(f32 *)(frame + 0x54);
        f58 = *(f32 *)(frame + 0x58);
        x = f50 - 1792.0f;
        y = f54 - 1824.0f;

        if (0.0f < f58
            && (f32)*(s32 *)((u8 *)gBtlCamView + 0x200) <= x
            && x <= (f32)(*(s32 *)((u8 *)gBtlCamView + 0x204) + 1)
            && (f32)*(s32 *)((u8 *)gBtlCamView + 0x208) <= y
            && y <= (f32)(*(s32 *)((u8 *)gBtlCamView + 0x20C) + 1)) {
            temp_v0 = *(s32 *)(s1 + 0x504);
            if (*(u32 *)(s1 + 0x510) < 2U) {
                a2 = *(s32 *)(s1 + 0x514);
                a1 = *(s32 *)(s1 + 0x520);
                v0 = temp_v0 + a1;
                *(u32 *)(s1 + 0x510) = 1U;
                *(s32 *)(s1 + 0x504) = v0;
                if (a2 < v0) {
                    *(s32 *)(s1 + 0x504) = a2;
                    *(u32 *)(s1 + 0x510) = 2U;
                }
            } else {
                a0 = *(s32 *)(s1 + 0x518);
                a1 = *(s32 *)(s1 + 0x520);
                v0 = temp_v0 - a1;
                *(s32 *)(s1 + 0x504) = v0;
                if (v0 < a0) {
                    *(s32 *)(s1 + 0x504) = a0;
                }
            }
        } else {
            a0 = *(s32 *)(s1 + 0x51C);
            v0 = *(s32 *)(s1 + 0x504) - 1;
            *(u32 *)(s1 + 0x510) = 0U;
            *(s32 *)(s1 + 0x504) = v0;
            if (v0 < a0) {
                *(s32 *)(s1 + 0x504) = a0;
            }
            a1 = *(s32 *)(s1 + 0x520);
            *(s32 *)(s1 + 0x50C) = a1;
        }
    }
    if (s1[0x503] != 0) {
        *(s32 *)(s1 + 0x50C) = *(s32 *)(s1 + 0x520);
        *(s32 *)(s1 + 0x504) = *(s32 *)(s1 + 0x514);
    }
    s1[0x503] = 0;
}
