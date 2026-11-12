#include "common.h"

extern f32 sinf(f32 x);
extern s32 func_00126598(s32 arg0);
extern void func_00129D40(void *dst, void *src);
extern void func_00129C28(void *dst, void *src);
extern void func_00129C50(void *dst, void *mtx, void *src);
extern void func_00129B58(void *dst, void *a, void *b);
extern void Vec3_Cross(void *dst, void *a, void *b);
extern void Vec3_Normalize(void *dst, void *src);
extern void func_00129BD0(void *dst, void *src, f32 scale);
extern void Vec3_Add(void *dst, void *a, void *b);
extern void Vec3_Sub(void *dst, void *a, void *b);
extern f32 func_00129CD8(void *a, void *b);
extern s32 func_001294B0(void *out, void *in, s32 n, s32 flag);
extern void func_001EA808(u8 arg0, u8 arg1, u8 arg2, u8 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                          f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6,
                          f32 farg7, u8 forceFar, u64 arg8);
extern s32 func_0012C250(u8 *arg0, u8 *arg1, s32 arg2, u8 arg3, u8 arg4, u8 arg5, s64 arg6, s32 arg7);
extern s32 func_0012C9E8(u8 *arg0, u8 *arg1, s64 *arg2, s32 arg3, s32 arg4);
extern u8 *gBtlCamView;
extern f32 D_003856C8;
extern f32 D_003856CC;
extern u8 D_00387900[8];
extern u8 D_0036F260[0x40];

#define FL(off) (*(f32 *)(sp + (off)))
#define SPLASH(px, py, pz) \
    func_001EA808(sp[0x50], sp[0x54], sp[0x58], sp[0x5C], (s32)(u32)len, (s32)(u32)len, 0x1000, \
                  *(s32 *)(*(u8 **)obj + 0x94), (px), (py), (pz), 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, \
                  (u8)useFar, *(u64 *)(*(u8 **)(obj + 0x128) + *(s32 *)(obj + 0x11C) * 16))

/* Ribbon/trail renderer: walks the node list at obj+0x180 and draws a quad strip between consecutive nodes. */
void func_001E9B80(u8 *obj) {
    u8 sp[0x360];
    f32 seg[2];
    u8 *camPos = obj + 0x50;
    u8 *node;
    s32 i = 0;
    s32 first = 1;
    s32 useFar = 0;
    f32 step, len;

    __builtin_memset(sp + 0x110, 0, 0x10);
    __builtin_memset(sp + 0x120, 0, 0x10);
    __builtin_memset(sp + 0x130, 0, 0x10);
    __builtin_memset(sp + 0x140, 0, 0x10);
    __builtin_memcpy(sp + 0x150, D_0036F260, 0x40);
    __builtin_memset(sp + 0x190, 0, 0x1B0);
    __builtin_memcpy(seg, D_00387900, 8);

    if (*(u16 *)(obj + 0x124) & 0x20) {
        if (!func_00126598(*(s32 *)(obj + 0x120))) {
            return;
        }
        useFar = 1;
    }

    step = -1.0f / (f32)*(s32 *)(obj + 0x114);
    seg[1] = seg[0] + step;
    func_00129D40(sp + 0x50, obj + 0x50);
    len = (*(f32 *)(obj + 0xFC) * 18.0f) * *(f32 *)(obj + 0xC4);
    func_00129C28(sp + 0x120, gBtlCamView + 0x1F0);

    node = *(u8 **)(obj + 0x180);
    if (node == 0) {
        return;
    }
    do {
        u8 *next = *(u8 **)(node + 0x18);
        f32 ang = ((f32)i / (f32)*(s32 *)(obj + 0x110)) * D_003856C8;
        s32 skip = 0;

        *(s32 *)(sp + 0x5C) = (s32)(*(f32 *)(obj + 0x5C) * sinf(ang));
        if (next != 0) {
            s32 j;

            func_00129C50(sp + 0x100, obj + 0x10, node);
            func_00129C50(sp + 0x110, obj + 0x10, next);
            func_00129B58(sp + 0x60, sp + 0x110, sp + 0x100);
            func_00129B58(sp + 0x70, sp + 0x100, sp + 0x120);
            Vec3_Cross(sp + 0x80, sp + 0x70, sp + 0x60);
            Vec3_Normalize(sp + 0x80, sp + 0x80);
            func_00129BD0(sp + 0x130, sp + 0x80, *(f32 *)(obj + 0xFC) * *(f32 *)(obj + 0xC4));

            if (first) {
                Vec3_Add(sp + 0xA0, sp + 0x100, sp + 0x130);
                Vec3_Sub(sp + 0xB0, sp + 0x100, sp + 0x130);
                first = 0;
                FL(0xBC) = 1.0f;
                FL(0xAC) = 1.0f;
            } else {
                if (func_00129CD8(sp + 0x80, sp + 0x90) < 0.0f) {
                    func_00129BD0(sp + 0x80, sp + 0x80, -1.0f);
                    func_00129BD0(sp + 0x130, sp + 0x130, -1.0f);
                }
                if (*(u16 *)(obj + 0x124) & 0x100) {
                    if (func_00129CD8(sp + 0x80, sp + 0x90) < D_003856CC) {
                        if (0.0f < *(f32 *)(node + 0x10)) {
                            FL(0x140) = (FL(0x100) + FL(0x110)) * 0.5f;
                            FL(0x144) = (FL(0x104) + FL(0x114)) * 0.5f;
                            FL(0x148) = (FL(0x108) + FL(0x118)) * 0.5f;
                            FL(0x14C) = 1.0f;
                            SPLASH(FL(0x100), FL(0x104), FL(0x108));
                            SPLASH(FL(0x140), FL(0x144), FL(0x148));
                            SPLASH(FL(0x110), FL(0x114), FL(0x118));
                        }
                        skip = 1;
                    }
                }
                func_00129C28(sp + 0xA0, sp + 0xE0);
                func_00129C28(sp + 0xB0, sp + 0xF0);
            }

            Vec3_Add(sp + 0xC0, sp + 0x110, sp + 0x130);
            Vec3_Sub(sp + 0xD0, sp + 0x110, sp + 0x130);
            FL(0xDC) = 1.0f;
            FL(0xCC) = 1.0f;
            func_00129C28(sp + 0xE0, sp + 0xC0);
            func_00129C28(sp + 0xF0, sp + 0xD0);
            func_00129C28(sp + 0x90, sp + 0x80);

            if (!skip) {
                s32 depth;

                func_001294B0(sp + 0x10, sp + 0xA0, 4, 1);
                depth = (*(s32 *)(sp + 0x18) + *(s32 *)(sp + 0x48) +
                         (*(s32 *)(sp + 0x38) + *(s32 *)(sp + 0x28))) >> 10;
                FL(0x160) = seg[0];
                FL(0x180) = seg[1];
                FL(0x150) = seg[0];
                FL(0x170) = seg[1];
                for (j = 0; j < 2; j++) {
                    u8 *tri = sp + 0xA0 + j * 16;
                    u8 *uv = sp + 0x150 + j * 16;

                    func_00129C28(sp + 0x190, tri);
                    func_00129C28(sp + 0x1A0, tri + 0x10);
                    func_00129C28(sp + 0x1B0, tri + 0x20);
                    func_00129C28(sp + 0x220, uv);
                    func_00129C28(sp + 0x230, uv + 0x10);
                    func_00129C28(sp + 0x240, uv + 0x20);
                    func_00129C28(sp + 0x2B0, camPos);
                    func_00129C28(sp + 0x2C0, camPos);
                    func_00129C28(sp + 0x2D0, camPos);
                    if (useFar) {
                        func_0012C9E8(sp + 0x190, gBtlCamView + 0x100,
                                      (s64 *)(*(u8 **)(obj + 0x128) + *(s32 *)(obj + 0x118) * 16),
                                      *(s32 *)(*(u8 **)obj + 0x94), 0xFFFFFF);
                    } else {
                        func_0012C250(sp + 0x190, gBtlCamView + 0x100, *(s32 *)(*(u8 **)obj + 0x94), 0, 0, 0,
                                      *(s64 *)(obj + 0x170 + *(s32 *)(obj + 0x118) * 8), depth);
                    }
                }
            }
        }
        seg[0] = seg[0] + step;
        seg[1] = seg[1] + step;
        if (!(i < *(s32 *)(obj + 0x114) - 2)) {
            seg[1] = 0;
        }
        i++;
        node = next;
    } while (node != 0);
}
