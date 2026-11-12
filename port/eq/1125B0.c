#include "common.h"

s32 func_0010B078(void);
s32 func_0010B080(void);
void func_00112B28(s32 arg0);
void func_0029D548(void);
void func_00113598(void *a);
s32 BtlObjVis_GetView(s32 arg0);
s32 func_00111B50(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3);
void func_00111B10(s32 arg0);
void func_001140A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_0029D580(s32 arg0);
f32 func_00111FE8(s32 arg0, u8 *arg1, s32 arg2);
f32 func_00111D00(s32 arg0, u8 *arg1, s32 arg2);
f32 func_001122D8(s32 arg0, u8 *arg1, s32 arg2);
extern u8 D_003876E0[] __attribute__((section(".data")));

/* 0x001125B0: per-frame setup of the two-unit table at base (from func_0010B078) with 168-byte rows (+0xF70 vector,
   +0xF7C handle, +0xF80 running value). Row 0 gets a 8.0 or 504.0 x value and a 108.0 y value; the view loop
   draws into a 0xC00-byte buffer (func_00111B50 / func_00111B10, and func_001140A8 for row 1); the last two loops
   add the func_00111FE8 / func_00111D00 / func_001122D8 results onto the running value (the last loop starts
   from +32.0 per row). Returns 0. */
s32 func_001125B0(void) {
    u8 v23[0xC00];
    u8 v24[8];
    u8 *base;
    u8 *g;
    u8 *p;
    s32 i;
    s32 view;
    f32 r;

    base = (u8 *)func_0010B078();
    g = (u8 *)func_0010B080();
    __builtin_memcpy(v24, D_003876E0, 8);
    func_00112B28(*(s32 *)(g + 4));

    p = base + 3952;
    for (i = 0; i < 2; i++) {
        *(f32 *)(p + 0xC) = (i != 0) ? 504.0f : 8.0f;
        *(f32 *)(p + 0x10) = 108.0f;
        p += 168;
    }

    p = base + 3952;
    for (i = 0; i < 2; i++) {
        func_0029D548();
        *(f32 *)(v24 + 4) = 78.0f;
        func_00113598((void *)v24);
        view = BtlObjVis_GetView(i);
        if (func_00111B50(v23, p, view, i)) {
            if (i == 1) {
                func_001140A8((s32)v23, 1, 1, 0, 2);
            }
            func_00111B10((s32)v23);
        }
        p += 168;
        func_0029D580(1);
    }

    p = base;
    for (i = 0; i < 2; i++) {
        func_0029D548();
        func_00113598((void *)(p + 0xF7C));
        view = BtlObjVis_GetView(i);
        r = func_00111FE8((i == 0), p + 0xF70, (view == 0));
        *(f32 *)(p + 0xF80) = *(f32 *)(p + 0xF80) + r;
        func_0029D580(1);
        p += 168;
    }

    p = base;
    for (i = 0; i < 2; i++) {
        func_0029D548();
        func_00113598((void *)(p + 0xF7C));
        view = BtlObjVis_GetView(i);
        r = func_00111D00((i == 0), p + 0xF70, (view == 0));
        *(f32 *)(p + 0xF80) = *(f32 *)(p + 0xF80) + r;
        func_0029D580(1);
        p += 168;
    }

    p = base;
    for (i = 0; i < 2; i++) {
        *(f32 *)(p + 0xF80) = *(f32 *)(p + 0xF80) + 32.0f;
        func_0029D548();
        func_00113598((void *)(p + 0xF7C));
        view = BtlObjVis_GetView(i);
        r = func_001122D8((i == 0), p + 0xF70, view);
        *(f32 *)(p + 0xF80) = *(f32 *)(p + 0xF80) + r;
        func_0029D580(1);
        p += 168;
    }
    return 0;
}
