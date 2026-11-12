#include "common.h"

extern u8 *D_00387DA0;
extern s32 D_003777C8 __attribute__((section(".data")));

void func_0026EBC0(s32 arg0, s32 arg1, s32 arg2);
void func_0026F118(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
f32 func_0026F148(s32 arg0, s32 arg1);
void func_002A1340();
void func_002A13E8();
void func_002A1590(s32 arg0);
void func_002A15D0(s32 arg0);
void func_002A15F0(s32 arg0);
void Font_SetShadowOffset(s32 arg0, s32 arg1);
void Font_SetColorRGBA(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void Font_PrintAt(s32 arg0, s32 arg1, s32 arg2);

void func_0029BF08(void) {
    s32 out[6];
    u8 *base;
    u8 *s0;
    s32 b;
    s32 idx;
    s32 pos;
    f32 f20;
    f32 sc;
    f32 fr;
    s32 r;

    base = D_00387DA0;
    if (*(s32 *)(base + 4) != 0) {
        if (*(s32 *)(base + 0x68) >= 0) {
            s0 = base + 8;
            func_0026EBC0((s32)s0, (s32)&D_003777C8, (s32)out);
            if (out[0] >= 0) {
                func_0026F118((s32)s0, (s32)out, (s32)&out[4], (s32)&out[5]);
                f20 = func_0026F148((s32)s0, (s32)out);
                base = D_00387DA0;
                b = *(s32 *)(base + 4);
                idx = (*(s32 *)(base + 0x68) << 2) + b;
                pos = b + (s32)((*(u32 *)((u8 *)idx + 4) >> 2) << 2);
                func_002A1340();
                func_002A1590(1);

                sc = f20 * 128.0f;
                r = (s32)sc;
                fr = sc - (f32)r;
                if (fr > 0.5f || (fr == 0.5f && (r & 1))) {
                    r += 1;
                } else if (fr < -0.5f || (fr == -0.5f && (r & 1))) {
                    r -= 1;
                }
                Font_SetColorRGBA(0xFF, 0xFF, 0xFF, r & 0xFF);
                func_002A15D0(2);
                Font_SetShadowOffset(1, 2);

                sc = f20 * 64.0f;
                r = (s32)sc;
                fr = sc - (f32)r;
                if (fr > 0.5f || (fr == 0.5f && (r & 1))) {
                    r += 1;
                } else if (fr < -0.5f || (fr == -0.5f && (r & 1))) {
                    r -= 1;
                }
                func_002A15F0((r << 24) | 0x202020);
                Font_PrintAt(out[4], out[5], pos);
                func_002A13E8();
            }
        }
    }
}
