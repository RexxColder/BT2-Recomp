#include "common.h"

s32 func_00217488(void *arg0);
s32 func_00211310(void *arg0, s32 arg1, s32 arg2);
s32 func_00210E18(void *arg0);
s32 BtlPad_Test48(void *arg0, s32 arg1);
s32 BtlPad_Test4C(void *arg0, s32 arg1);
u8 *BtlMember_GetActiveGauge(void *arg0);
s32 func_0023FC98(void *arg0);
s32 func_00208738(void *arg0, s32 arg1);
s32 func_0023D410(void *arg0, s32 arg1, s32 arg2);
s32 BtlAnim_SetBlend(void *arg0, f32 arg1);
s32 func_002113C0(void *arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_002174D8(void *arg0, s32 arg1);
f32 func_001FA318(void *arg0);
s32 func_002174B8(void *arg0);
s32 func_0023C710(void *arg0);

extern f32 D_00385C68;
extern f32 D_00385C6C;
extern f32 D_00385C70;
extern f32 D_00385C74;
extern f32 D_00385C78;
extern f32 D_00385C7C;
extern f32 D_00385C80;
extern f32 D_00385C84;
extern f32 D_00385C88;

s32 func_0021B048(u8 *arg0) {
    u8 *ctx;
    s32 v;
    s32 s1;
    s32 r;
    u8 *g;
    f32 f0;

    ctx = arg0;
    v = func_00217488(ctx);
    if (v == 0x76) {
        goto c76;
    }
    if (v < 0x77) {
        if (v == 0x5D) {
            goto c5D;
        }
        goto L348;
    }
    if (v == 0x7B) {
        goto c7B;
    }
    if (v == 0x7C) {
        goto c7C;
    }
    goto L348;

c5D:
    if (func_00211310(ctx, 0, 0x800) == 0) {
        goto L348;
    }
    if (func_00210E18(ctx) != 0x99) {
        goto L348;
    }
    if (BtlPad_Test48(ctx, 7) == 0) {
        goto L348;
    }
    if (BtlPad_Test4C(ctx, 1) == 0) {
        goto L348;
    }
    g = BtlMember_GetActiveGauge(ctx);
    if (*(u8 *)(g + 0x2C) != 0) {
        goto L348;
    }
    v = func_0023FC98(ctx);
    s1 = -1;
    if (v == 1) {
        s1 = 2;
    } else if (v == 2) {
        s1 = 3;
    }
    if (s1 < 0) {
        goto L348;
    }
    if (func_00208738(*(u8 **)(ctx + 0x1534), s1) == 0) {
        goto L348;
    }
    s1 = func_0023D410(ctx, s1, 1);
    if (s1 == -1) {
        goto L348;
    }
    BtlAnim_SetBlend(ctx, D_00385C68);
    func_002113C0(ctx, 7, 0x20000, 1);
    return s1;

c76:
    if (func_00211310(ctx, 4, 2) == 0) {
        goto L348;
    }
    if (BtlPad_Test4C(ctx, 0) != 0) {
        func_002174D8(ctx, 0x77);
    }
    f0 = func_001FA318(ctx);
    if (!(D_00385C6C < f0)) {
        goto L348;
    }
    f0 = func_001FA318(ctx);
    if (!(f0 < D_00385C70)) {
        goto L348;
    }
    if (func_002174B8(ctx) == -1) {
        goto L348;
    }
    BtlAnim_SetBlend(ctx, D_00385C74);
    return func_002174B8(ctx);

c7B:
    if (func_00211310(ctx, 4, 2) == 0) {
        goto L348;
    }
    if (BtlPad_Test4C(ctx, 1) != 0) {
        func_002174D8(ctx, 0x7C);
    }
    f0 = func_001FA318(ctx);
    if (!(D_00385C78 < f0)) {
        goto L348;
    }
    if (func_002174B8(ctx) == -1) {
        goto L348;
    }
    BtlAnim_SetBlend(ctx, D_00385C7C);
    return func_002174B8(ctx);

c7C:
    if (func_00211310(ctx, 4, 2) == 0) {
        goto L348;
    }
    if (BtlPad_Test4C(ctx, 0) != 0) {
        func_002174D8(ctx, 0x7D);
    }
    f0 = func_001FA318(ctx);
    if (!(D_00385C80 < f0)) {
        goto L348;
    }
    if (func_002174B8(ctx) == -1) {
        goto L348;
    }
    BtlAnim_SetBlend(ctx, D_00385C84);
    return func_002174B8(ctx);

L348:
    r = func_00211310(ctx, 2, 1);
    if (r == 0) {
        return -1;
    }
    BtlAnim_SetBlend(ctx, D_00385C88);
    if (func_00217488(ctx) == 0x5D) {
        g = BtlMember_GetActiveGauge(ctx);
        *(s32 *)(g + 0x1C) = 0;
        *(s32 *)(ctx + 0xA34) = 0x3C;
    }
    return func_0023C710(ctx);
}
