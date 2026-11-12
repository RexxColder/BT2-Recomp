#include "common.h"

extern u8 *func_001F3758(s32 arg0);
extern s32 BtlScene_IsCharStopped(u8 *arg0);
extern void func_00152530(u8 *arg0, u8 *arg1);
extern s32 EftShot_TestBits(u8 *arg0, s32 arg1);
extern void func_00208DE8(u8 *arg0, void *arg1, s32 arg2);
extern void func_00129C28(void *arg0, void *arg1);
extern void func_0012D3A0(u8 *arg0, u8 *arg1, u8 *arg2);
extern f32 func_0020A068(u8 *arg0);
extern s32 func_0012D488(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3);
extern u8 *func_00165618(u8 *arg0);
extern s32 func_00191600(void *arg0);
extern void EftTechEvt_RequestRestart(u8 *arg0);
extern void func_0027BCC0(u8 *arg0, u8 *arg1, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);
extern void func_002837C0(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0);
extern void func_00283800(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0);
extern void func_00283840(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0);
extern void func_00283770(s32 a0, u8 *a1, s32 a2);
extern s32 func_00191728(s32 arg0);
extern void func_00151FB0(u8 *arg0);
extern void func_00165488(u8 *arg0, u8 *task, u8 *scene, s32 arg3);
extern s32 func_00152200(u8 *arg0, u8 *arg1);
extern s32 BtlTask_SetDead(u8 *task);
extern void func_00152930(u8 *arg0, u8 *arg1);
extern void func_001652C0(u8 *task);

extern f32 D_003847A8;
extern f32 D_003847AC;
extern f32 D_003847B0;
extern f32 D_003847B4;

/* Per-frame update of a battle effect task: advances the state byte (task+1) through its 6 phases, spawns blasts, ticks the screen flash and the 10 child slots. */
s32 func_00165758(u8 *task) {
    u8 sp[0x70 + 4];
    u8 *scene;
    u8 *fx;
    u8 *ctx;
    u8 *fxbase;
    u8 *vec;
    u8 *mtxs;
    u8 *obj;
    u8 *slot;
    s32 advance = 0;
    s32 anyAlive = 0;
    s32 busy;
    s32 flags;
    s32 res;
    s32 i;
    s32 t0, t1, t2;
    f32 f;

    scene = *(u8 **)(func_001F3758(0) + 0x38);
    fx = *(u8 **)(task + 0x38);
    ctx = *(u8 **)(fx + 0xB0);
    res = BtlScene_IsCharStopped(*(u8 **)ctx);
    if (res != 0) return res;
    vec = fx + 0x860;
    func_00152530(ctx, vec);

    if ((*(u32 *)fx & 0x80) == 0) {
        if (EftShot_TestBits(*(u8 **)ctx, 2)) {
            task[1] = 0;
            *(u32 *)fx |= 0x80;
        } else if (EftShot_TestBits(*(u8 **)ctx, 4)) {
            task[1] = 2;
            *(u32 *)fx |= 0x80;
        }
    }

    if ((*(u32 *)fx & 0x80) != 0 && task[1] < 6) {
        switch (task[1]) {
        case 0:
            if (EftShot_TestBits(*(u8 **)ctx, 2)) {
                s32 v = *(s32 *)(fx + 0x870);
                *(s32 *)(fx + 4) = v;
                func_00208DE8(*(u8 **)ctx, sp, v);
                func_00129C28(fx + 0x40, sp);
                func_0012D3A0(fx + 0x30, fx + 0x40, *(u8 **)ctx);
                task[1] = 1;
            }
            break;
        case 2:
            f = func_0020A068(*(u8 **)ctx);
            *(f32 *)(fx + 0x1C) = f;
            *(f32 *)(fx + 0x18) = *(f32 *)(fx + 0x14) * (f + 1.0f);
            func_00208DE8(*(u8 **)ctx, sp, *(s32 *)(fx + 4));
            func_00129C28(fx + 0x40, sp);
            if (EftShot_TestBits(*(u8 **)ctx, 0x40)) {
                s32 v = *(s32 *)(fx + 0x9B0);
                *(s32 *)(fx + 0xC) = v;
                func_00208DE8(*(u8 **)ctx, sp, v);
                func_00129C28(fx + 0x60, sp);
                *(u32 *)fx |= 0x40;
            }
            if (EftShot_TestBits(*(u8 **)ctx, 4)) {
                s32 v = *(s32 *)(fx + 0x8B0);
                *(s32 *)(fx + 8) = v;
                func_00208DE8(*(u8 **)ctx, sp, v);
                func_00129C28(fx + 0x50, sp);
                func_00129C28(fx + 0x70, fx + 0x50);
                func_00129C28(fx + 0x80, fx + 0x70);
                task[1] = 3;
            }
            break;
        case 4:
            func_00208DE8(*(u8 **)ctx, sp, *(s32 *)(fx + 8));
            func_00129C28(fx + 0x50, sp);
            if (EftShot_TestBits(*(u8 **)ctx, 8)) {
                *(u32 *)fx |= 9;
                task[1] = 5;
            }
            break;
        default:
            advance = 1;
            break;
        }
    }

    if (EftShot_TestBits(*(u8 **)ctx, 4)) {
        u8 *blast;
        func_0012D488(ctx, fx + 0x30, fx + 0x70, *(u8 **)ctx);
        blast = func_00165618(fx);
        if (blast != NULL) {
            u8 *pk = sp + 0x10;
            u8 *src = sp + 0x40;
            *(u8 **)(src + 0x00) = ctx;
            *(u8 **)(src + 0x04) = scene;
            *(u8 **)(src + 0x08) = vec;
            *(u8 **)(src + 0x0C) = fx + 0x70;
            *(u8 **)(src + 0x10) = fx + 0x30;
            *(s32 *)(src + 0x14) = *(s32 *)(fx + 0xAB0);
            *(s32 *)(src + 0x18) = 0xA;
            *(s32 *)(src + 0x1C) = 2;
            *(s32 *)(src + 0x20) = 1;
            *(s32 *)(src + 0x24) = 0;
            *(f32 *)(src + 0x28) = *(f32 *)(fx + 0x18);
            *(f32 *)(src + 0x2C) = *(f32 *)(*(u8 **)(ctx + 0x24) + 8);
            __builtin_memcpy(pk, src, 0x30);
            *(s32 *)(blast + 4) = func_00191600(pk);
            *(s32 *)(fx + 0xAB0) = *(s32 *)(fx + 0xAB0) + 1;
        }
        EftTechEvt_RequestRestart(*(u8 **)ctx);
        if ((*(u32 *)fx & 0x200) != 0) {
            func_0027BCC0(*(u8 **)ctx, fx + 0x70, D_003847AC, 10.0f, 50.0f, 15.0f, D_003847A8);
            func_0027BCC0(*(u8 **)ctx, fx + 0x70, D_003847A8, 10.0f, 30.0f, 20.0f, D_003847B0);
            *(f32 *)(fx + 0x24) = 15.0f;
            *(f32 *)(fx + 0x20) = 1.0f;
        }
    }

    if ((*(u32 *)fx & 0x200) != 0) {
        f = *(f32 *)(fx + 0x20);
        t0 = (s32)(f * 8.0f);
        t1 = (s32)(f * 32.0f);
        t2 = (s32)(f * 128.0f);
        func_002837C0(0, 0x80, 0x80, 0x80, t0 & 0xFF);
        func_00283800(0, 0x80, 0x80, 0x80, t1 & 0xFF);
        func_00283840(0, 0x80, 0x80, 0x80, t2 & 0xFF);
        func_00283770(0, fx + 0x30, 0);
        f = *(f32 *)(fx + 0x24);
        if (f <= 0.0f) {
            f = *(f32 *)(fx + 0x20);
            if (0.0f < f) {
                f = f - D_003847B4;
                *(f32 *)(fx + 0x20) = f;
                if (f < 0.0f) {
                    *(f32 *)(fx + 0x20) = 0.0f;
                }
            }
        } else {
            *(f32 *)(fx + 0x24) = f - 1.0f;
        }
    }

    slot = fx + 0xAB4;
    for (i = 9; i >= 0; i--) {
        if (func_00191728(*(s32 *)(slot + 4)) != 0) {
            anyAlive = 1;
        } else {
            *(s32 *)(slot + 4) = 0;
        }
        slot += 8;
    }

    mtxs = fx + 0xB4;
    if (EftShot_TestBits(*(u8 **)ctx, 0x80)) {
        flags = *(s32 *)fx;
        if ((flags & 8) == 0) {
            *(s32 *)fx = flags | 4;
        }
        *(s32 *)fx = *(s32 *)fx | 1;
    }
    func_00151FB0(mtxs);
    func_00165488(*(u8 **)ctx, task, scene, 0);
    busy = func_00152200(scene, mtxs) != 0;
    if (advance) {
        task[1] = task[1] + 1;
    }
    flags = *(s32 *)fx;
    if (anyAlive == 0 && busy == 0) {
        if ((flags & 2) != 0) {
            return BtlTask_SetDead(task);
        }
    }
    if ((flags & 1) != 0) {
        res = flags | 2;
        *(s32 *)fx = res;
        return res;
    }
    res = *(s32 *)(*(u8 **)(ctx + 0x20) + 0x30) & 1;
    if (res == 0) return res;
    res = flags & 0x10;
    if (res == 0) return res;
    func_00152930(scene, mtxs);
    func_001652C0(task);
    return res;
}
