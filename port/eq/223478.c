#include "common.h"

s32 BtlAnim_SetBlend(void *arg0, f32 arg1);
s32 func_00203310(void *arg0, s32 arg1, s32 arg2);
s32 func_00203888(void *arg0, s32 arg1, s32 arg2);
void func_0020D048(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void func_0020D240(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
s32 func_00211310(void *arg0, s32 arg1, s32 arg2);
s32 func_002113C0(void *arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00212820(void *arg0);
s32 func_00218540(void *arg0, f32 arg1);
s32 func_00218560(void *arg0, f32 arg1);
s32 func_0023F410(void *arg0);
s32 func_0023FB58(void *arg0);
void *BtlChar_GetPos(void *arg0);

extern f32 D_003860B0;
extern f32 D_003860B4;
extern f32 D_003860B8;
extern f32 D_003860BC;
extern f32 D_003860C0;
extern f32 D_003860C4;
extern f32 D_003860C8;
extern f32 D_003860CC;
extern f32 D_003860D0;
extern f32 D_003860D4;

s32 func_00223478(u8 *arg0) {
    u8 *ctx;
    s32 r;
    s32 cnt;
    f32 f20;
    f32 f21;
    u8 *p;

    ctx = arg0;
    cnt = *(s32 *)(ctx + 0x8C0) - 1;
    *(s32 *)(ctx + 0x8C0) = cnt;
    if (cnt < 0) {
        if (func_00212820(ctx) != 0) {
            BtlAnim_SetBlend(ctx, D_003860B0);
            return 0x26;
        }
    }

    f20 = D_003860B4;
    r = func_00218540(ctx, f20);
    if (r == 0) {
        /* L223648 */
        r = func_00218560(ctx, D_003860B4);
        if (r == 0) {
            return -1;
        }
        p = *(u8 **)(ctx + 0x1530);
        if (*(s32 *)(p + 0xED0) & 0x40) {
            if (func_00212820(ctx) == 0) {
                return 0xA9;
            }
            return 0x9B;
        }
        if (D_003860C8 < (f32)*(s32 *)(ctx + 0x8CC)) {
            if (func_00212820(ctx) == 0) {
                goto tailB;
            }
            if (func_00211310(ctx, 1, 0x80000) != 0) {
                goto tailB;
            }
            if (func_00211310(ctx, 1, 0x4000) != 0) {
                func_00203888(ctx, func_0023FB58(ctx), 0);
                return 0x2A;
            }
            if (func_00211310(ctx, 1, 0x8000) == 0) {
                goto tailB;
            }
            func_00203888(ctx, func_0023FB58(ctx), 0);
            if (func_00211310(ctx, 0, 1) != 0) {
                return 0x2C;
            }
            return 0x2A;
        }
        goto tailB;
    }

    /* r != 0 */
    if (D_003860B8 < (f32)*(s32 *)(ctx + 0x8CC)) {
        if (func_00212820(ctx) == 0) {
            goto tailA;
        }
        if (func_00211310(ctx, 1, 0x80000) != 0) {
            goto tailA;
        }
        if (func_00211310(ctx, 1, 0x4000) != 0) {
            func_00203888(ctx, func_0023FB58(ctx), 0);
            goto after;
        }
        if (func_00211310(ctx, 1, 0x8000) == 0) {
            goto tailA;
        }
        func_00203888(ctx, func_0023FB58(ctx), 0);
        if (func_00211310(ctx, 0, 1) != 0) {
            return 0x2B;
        }
after:
        /* L2359C */
        r = func_0023F410(ctx);
        return (r & 0x1000) ? 0x27 : 0x29;
    }

tailA:
    /* L235BC, 0x1F4 path */
    f21 = 100.0f;
    func_00203310(ctx, 0x1F4, 0);
    f20 = 1000.0f;
    func_002113C0(ctx, 6, 0x10, 1);
    func_0020D048(BtlChar_GetPos(ctx), f21, f20, 3.0f, D_003860BC);
    func_0020D240(BtlChar_GetPos(ctx), f21, f20, D_003860C0, D_003860C4);
    *(s32 *)((u8 *)BtlChar_GetPos(ctx) + 0xC0) = 0;
    return 0xA8;

tailB:
    /* L223754, 0x258 path */
    f21 = 100.0f;
    func_00203310(ctx, 0x258, 0);
    f20 = 1000.0f;
    func_002113C0(ctx, 6, 0x10, 1);
    func_0020D048(BtlChar_GetPos(ctx), f21, f20, 3.0f, D_003860CC);
    func_0020D240(BtlChar_GetPos(ctx), f21, f20, D_003860D0, D_003860D4);
    return 0xA9;
}
