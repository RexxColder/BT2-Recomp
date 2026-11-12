#include "common.h"

extern void func_00129C28(void *dst, void *src);
extern void func_00129D40(void *dst, void *src);
extern void func_00129B58(void *dst, void *a, void *b);
extern void Vec3_Cross(void *dst, void *a, void *b);
extern void Vec3_Normalize(void *dst, void *src);
extern void func_00129BB8(void *dst, void *src, f32 scale);
extern void func_00129BD0(void *dst, void *src, f32 scale);
extern void Vec3_Add(void *dst, void *a, void *b);
extern void Vec3_Sub(void *dst, void *a, void *b);
extern f32 func_00129CD8(void *a, void *b);
extern s32 func_001294B0(void *out, void *in, s32 n, s32 flag);
extern s32 func_0012C250(u8 *arg0, u8 *arg1, s32 arg2, u8 arg3, u8 arg4, u8 arg5, s64 arg6, s32 arg7);
extern void func_001C5D90(u8 arg0, u8 arg1, u8 arg2, u8 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                          f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6,
                          f32 farg7, u64 arg8);
extern u8 *gBtlCamView;
extern u8 *gEftRibbonMgr;
extern f32 D_00385180;
extern u8 D_0036EFE0[0x40];
extern u8 D_0036F020[0x40];

#define FL(off) (*(f32 *)(sp + (off)))
#define SPLASH(px, py, pz) \
    func_001C5D90(sp[0x1E0], sp[0x1E4], sp[0x1E8], \
                  (u8)(u32)((f32)*(s32 *)(sp + 0x1EC) * fade), (s32)(u32)alphaF, (s32)(u32)alphaF, 0x1000, 1, \
                  (px), (py), (pz), 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, \
                  *(u64 *)(mgr8 + *(s32 *)(obj + 0x58) * 16))

/* Ribbon strip renderer (variant of 1E9B80 with a node chain at node+0x40). */
void func_001C6278(s32 unused, u8 *obj, u8 *flags) {
    u8 sp[0x480];   /* el original reserva 0x450 (regs guardados desde 0x400) */
    u8 *mgr8;
    u8 *node;
    u8 *next;
    s32 i = 0;
    s32 first = 1;
    s32 skip;
    s32 k;
    f32 step, uA = 1.0f, uB, uC, alpha;

    mgr8 = gEftRibbonMgr + 8;
    __builtin_memcpy(sp + 0x10, D_0036EFE0, 0x40);
    __builtin_memcpy(sp + 0x50, D_0036F020, 0x40);
    func_00129C28(sp + 0xF0, gBtlCamView + 0x1F0);
    step = -1.0f / (f32)*(s32 *)(obj + 0x64);
    uB = step + 1.0f;
    uC = uB;
    if (!(*(s32 *)(obj + 0x50) & 0x20)) {
        for (k = 0; k < 4; k++) {
            func_00129C28(sp + 0x130 + k * 16, sp + 0x10 + k * 16);
        }
    } else {
        for (k = 0; k < 4; k++) {
            func_00129C28(sp + 0x130 + k * 16, sp + 0x50 + k * 16);
        }
    }
    func_00129C28(sp + 0x170, obj + 0xA0);
    func_00129D40(sp + 0x1E0, sp + 0x170);
    alpha = *(f32 *)(obj + 0x74) + *(f32 *)(obj + 0x74);
    node = *(u8 **)obj;
    if (node == 0) {
        return;
    }
    next = *(u8 **)(node + 0x40);
    for (;;) {
        if (next != 0) {
            u8 *p0 = node + 0x10;
            u8 *p1 = next + 0x10;
            u8 *s3 = sp + 0xD0;
            u8 *s2 = sp + 0xE0;

            skip = 0;
            func_00129B58(sp + 0x100, p1, p0);
            func_00129B58(sp + 0x120, p0, sp + 0xF0);
            Vec3_Cross(sp + 0x100, sp + 0x100, sp + 0x120);
            Vec3_Normalize(sp + 0x100, sp + 0x100);
            func_00129BB8(sp + 0x180, sp + 0x100, *(f32 *)(obj + 0x74));
            if (first) {
                Vec3_Add(sp + 0x90, p0, sp + 0x180);
                first = 0;
                FL(0x9C) = 1.0f;
                Vec3_Sub(sp + 0xA0, p0, sp + 0x180);
                FL(0xAC) = 1.0f;
            } else {
                if (func_00129CD8(sp + 0x100, sp + 0x110) < 0.0f) {
                    func_00129BD0(sp + 0x180, sp + 0x180, -1.0f);
                    func_00129BD0(sp + 0x100, sp + 0x100, -1.0f);
                }
                if (*flags != 1) {
                    if (func_00129CD8(sp + 0x100, sp + 0x110) < D_00385180) {
                        f32 fade, alphaF;

                        skip = 1;
                        FL(0x190) = (*(f32 *)p0 + *(f32 *)p1) * 0.5f;
                        FL(0x194) = (*(f32 *)(node + 0x14) + *(f32 *)(next + 0x14)) * 0.5f;
                        FL(0x198) = (*(f32 *)(node + 0x18) + *(f32 *)(next + 0x18)) * 0.5f;
                        fade = 1.0f - (f32)(i / *(s32 *)(obj + 0x64));
                        alphaF = alpha * fade;
                        SPLASH(*(f32 *)(node + 0x10), *(f32 *)(node + 0x14), *(f32 *)(node + 0x18));
                        SPLASH(FL(0x190), FL(0x194), FL(0x198));
                        SPLASH(*(f32 *)(next + 0x10), *(f32 *)(next + 0x14), *(f32 *)(next + 0x18));
                    }
                }
                func_00129C28(sp + 0x90, s3);
                func_00129C28(sp + 0xA0, s2);
            }

            Vec3_Add(sp + 0xB0, p1, sp + 0x180);
            Vec3_Sub(sp + 0xC0, p1, sp + 0x180);
            FL(0xBC) = 1.0f;
            FL(0xCC) = 1.0f;
            func_00129C28(sp + 0xD0, sp + 0xB0);
            func_00129C28(sp + 0xE0, sp + 0xC0);
            func_00129C28(sp + 0x110, sp + 0x100);

            if (!skip) {
                s32 depth;
                s32 j;

                func_001294B0(sp + 0x1A0, sp + 0x90, 4, 1);
                depth = (*(s32 *)(sp + 0x1A8) + *(s32 *)(sp + 0x1D8) +
                         (*(s32 *)(sp + 0x1C8) + *(s32 *)(sp + 0x1B8))) >> 10;
                FL(0x140) = uA;
                FL(0x130) = uA;
                FL(0x150) = uB;
                FL(0x160) = uB;
                for (j = 0; j < 2; j++) {
                    u8 *tri = sp + 0x90 + j * 16;
                    u8 *uv = sp + 0x130 + j * 16;

                    func_00129C28(sp + 0x1F0, tri);
                    func_00129C28(sp + 0x200, tri + 0x10);
                    func_00129C28(sp + 0x210, tri + 0x20);
                    func_00129C28(sp + 0x280, uv);
                    func_00129C28(sp + 0x290, uv + 0x10);
                    func_00129C28(sp + 0x2A0, uv + 0x20);
                    func_00129C28(sp + 0x310, sp + 0x170);
                    func_00129C28(sp + 0x320, sp + 0x170);
                    func_00129C28(sp + 0x330, sp + 0x170);
                    func_0012C250(sp + 0x1F0, gBtlCamView + 0x100, 1, 0, 0, 0,
                                  *(s64 *)(obj + 8 + *(u8 *)(node + 4) * 8 + 0x140), depth);
                }
            }
        }
        uA = uC;
        uB = uB + step;
        if (!(i < *(s32 *)(obj + 0x64) - 2)) {
            uB = 0.0f;
        }
        i++;
        node = next;
        if (node == 0) {
            break;
        }
        uC = step + uC;
        next = *(u8 **)(node + 0x40);
    }
}
