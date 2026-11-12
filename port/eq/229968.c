#include "common.h"

s32 func_00211310(void *arg0, s32 arg1, s32 arg2);
f32 func_00240D50(void *arg0, s32 arg1);
f32 func_00207E90(void *arg0);
s32 BtlObjXf_Update(void *arg0);
s32 func_001FA110(void *arg0, s32 arg1);
void *BtlChar_GetPos(void *arg0);
void func_001F9D78(void *arg0, s32 arg1);
s32 BtlAnim_SetBlend(void *arg0, f32 arg1);
s32 func_00206958(void *arg0, s64 arg1);
f32 func_00217360(void *arg0);
s32 func_00212878(void);
void func_001F9FB0(void *arg0, s32 arg1);
s32 func_001FA1D0(void *arg0, f32 arg1);
s32 func_0023F440(void *arg0);
void func_0020D048(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void func_0020D240(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
s32 func_0023F410(void *arg0);
s32 func_0020FC38(void *arg0, s32 arg1);
void func_00215068(void *arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4);
void func_00215E88(void *arg0, s32 arg1, f32 arg2);
void func_00216208(void *arg0, f32 arg1, f32 arg2);
s32 func_00216678(void *arg0);
void func_0020D7E8(void *arg0, f32 arg1, f32 arg2);
s32 func_002113C0(void *arg0, s32 arg1, s32 arg2, s32 arg3);
u8 *BtlMember_GetActiveGauge(void *arg0);

extern f32 D_00386440;
extern f32 D_00386444;
extern f32 D_00386448;
extern f32 D_0038644C;
extern f32 D_00386450;
extern f32 D_00386454;
extern f32 D_00386458;
extern f32 D_0038645C;
extern f32 D_00386460;

s32 func_00229968(u8 *arg0) {
    u8 *ctx;
    s32 r;
    s32 v;
    s32 a1;
    f32 f0;
    f32 f20;
    f32 f21;
    f32 f22;
    u8 *pos;
    u8 *g;

    ctx = arg0;
    r = func_00211310(ctx, 1, 2);
    a1 = (r != 0) ? 0xE : 0xD;
    f20 = func_00240D50(ctx, a1);
    f0 = func_00207E90(ctx);
    f21 = f20 * f0;
    f22 = D_00386440;
    v = BtlObjXf_Update(ctx);

    if (v == 0x2D) {
        goto L2A58;
    }
    if (v < 0x2E) {
        if (v == 0x2C) {
            goto L2A00;
        }
        goto L2C00;
    }
    if (v == 0x2E) {
        goto L2B08;
    }
    goto L2C00;

L2A00:
    func_001FA110(ctx, 0);
    pos = BtlChar_GetPos(ctx);
    f0 = *(f32 *)(pos + 0xC4);
    if (0.0f <= f0) {
        func_001F9D78(ctx, 0x2D);
        BtlAnim_SetBlend(ctx, D_00386444);
    }
    func_00206958(ctx, (s64)0x8000 << 28);
    goto L2C00;

L2A58:
    func_001FA110(ctx, 0);
    f0 = func_00217360(ctx);
    if (!(f0 < 3.0f)) {
        if (func_00211310(ctx, 0, 4) == 0) {
            goto L2C00;
        }
    }
    /* L2A94 */
    if (func_00212878() == 0) {
        goto L2AD8;
    }
    if (func_00211310(ctx, 0, 0x8000) != 0) {
        goto L2AD8;
    }
    g = *(u8 **)(ctx + 0x1530);
    if (!(*(f32 *)(g + 0xE64) < -10.0f)) {
        goto L2C00;
    }
    /* falls to L2AD4 */
L2AD8:
    func_001F9D78(ctx, 0x2E);
    BtlAnim_SetBlend(ctx, D_00386448);
    func_00206958(ctx, (s64)0x8000 << 20);
    goto L2C00;

L2B08:
    f22 = D_0038644C;
    func_001F9FB0(ctx, 1);
    if (func_001FA1D0(ctx, f22) == 0) {
        goto L2BF8;
    }
    if (func_0023F440(ctx) == 4) {
        f20 = 100.0f;
        f21 = 1000.0f;
        pos = BtlChar_GetPos(ctx);
        func_0020D240(pos, f20, f21, D_00386450, f22);
        pos = BtlChar_GetPos(ctx);
        func_0020D048(pos, f20, f21, 3.0f, D_00386454);
        func_0020FC38(ctx, 0x25);
        func_00206958(ctx, (s64)0x8000 << 23);
        goto L2BF8;
    }
    /* L2BB8 */
    if ((func_0023F410(ctx) & 0x8000) != 0) {
        func_0020FC38(ctx, 0xB);
    } else {
        func_0020FC38(ctx, 0x33);
    }
    func_00206958(ctx, (s64)0x8000 << 20);

L2BF8:
    f21 = 0.0f;
    f22 = D_00386458;

L2C00:
    f20 = D_0038645C;
    func_00215068(ctx, 5, 0xC, D_00386460, f20);
    func_00215E88(ctx, 2, f20);
    func_00216208(ctx, f21, f22);
    func_00216678(ctx);
    func_0020D7E8(ctx, 20.0f, 50.0f);
    func_002113C0(ctx, 9, 0x1000, 1);
    func_002113C0(ctx, 1, 0x40, 1);
    g = BtlMember_GetActiveGauge(ctx);
    if (*(u8 *)(g + 0x29) == 0) {
        return 0;
    }
    return func_002113C0(ctx, 6, 8, 1);
}
