#include "common.h"

#define W(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define F(p, o) (*(f32 *)((u8 *)(p) + (o)))

extern f32 D_00384F74;
extern f32 D_00384F78;
extern f32 D_00384F7C;
extern f32 D_00384F80;
extern f32 D_00384F84;
extern f32 D_00384F88;

extern void func_00129C28(u8 *dst, u8 *src);
extern void Vec4_Set(u8 *dst, f32 x, f32 y, f32 z, f32 w);
extern void Mtx_StoreIdentity(u8 *m);
extern void Mtx_RotateX(f32 ang, u8 *dst, u8 *src);
extern void Mtx_RotateY(f32 ang, u8 *dst, u8 *src);
extern void Mtx_MulVec4(u8 *dst, u8 *mtx, u8 *vec);
extern void Vec3_Scale(u8 *dst, u8 *src, f32 s);
extern void Vec3_Sub(u8 *dst, u8 *a, u8 *b);
extern void Vec3_Add(u8 *dst, u8 *a, u8 *b);
extern void Vec3_Normalize(u8 *dst, u8 *src);
extern f32 Vec3_Dot(u8 *a, u8 *b);
extern void Vec3_Add4(u8 *dst, u8 *a, u8 *b, u8 *c, u8 *d);
extern s32 rand(void);

/* (rand/D - rand/D) with the first rand taken first */
#define RDIFF(a, b) ((f32)(a) / D_00384F74 - (f32)(b) / D_00384F74)

/* Updates the linked list of trail points (node next at +0x60) of an effect: refreshes each node's position and
   velocity per the mode in obj[0x38][0x38][1] (1: first/last-node init with a rotated random offset, 2: random
   walk of cfg[0x60] direction, else drift by cfg+0x60), then recomputes the node's 0x40 and 0x50 vectors,
   clamps alpha and fades the last nodes. */
void func_001B1380(u8 *obj, u8 *cfg) {
    u8 sp[0x80];
    u8 *node;
    u8 *next;
    u8 *objst;
    u8 *st;
    u8 *pos;
    u8 *vel;
    u8 *dir;
    f32 idx;
    f32 x;
    f32 y;
    f32 len;
    s32 n = 0;
    s32 r0;
    s32 r1;
    s32 mode;

    objst = *(u8 **)(obj + 0x38);
    node = *(u8 **)cfg;
    if (node == NULL) {
        return;
    }
    st = *(u8 **)(objst + 0x38);
    dir = cfg + 0x60;
    for (;;) {
        idx = (f32)n;
        next = *(u8 **)(node + 0x60);
        if (idx < F(cfg, 0xC)) {
            W(node, 0) = W(node, 0) | 2;
        } else {
            W(node, 0) = W(node, 0) & ~2;
        }
        pos = node + 0x20;
        vel = node + 0x30;
        if (W(cfg, 8) & 2) {
            mode = st[1];
            if (mode == 1) {
                if (next == NULL) {
                    func_00129C28(sp + 0x40, pos);
                    Vec4_Set(sp + 0x60, 0.0f, 0.0f, 1.0f, 1.0f);
                    Mtx_StoreIdentity(sp);
                    Mtx_RotateX(F(cfg, 0x28), sp, sp);
                    Mtx_RotateY(F(cfg, 0x2C), sp, sp);
                    Mtx_MulVec4(sp + 0x60, sp, sp + 0x60);
                    Vec3_Scale(pos, sp + 0x60, F(node, 0xC));
                    F(node, 0x2C) = 1.0f;
                    Vec3_Sub(sp + 0x50, sp + 0x40, pos);
                    F(sp, 0x5C) = 1.0f;
                    len = __builtin_sqrtf(Vec3_Dot(sp + 0x50, sp + 0x50));
                    F(node, 0x10) = len * F(st, 0x54);
                    r0 = rand(); r1 = rand();
                    F(node, 0x30) = F(node, 0x10) * RDIFF(r0, r1);
                    r0 = rand(); r1 = rand();
                    F(node, 0x34) = F(node, 0x10) * RDIFF(r0, r1);
                    r0 = rand(); r1 = rand();
                    F(node, 0x3C) = 1.0f;
                    F(node, 0x38) = F(node, 0x10) * RDIFF(r0, r1);
                    x = F(cfg, 0x28) + F(cfg, 0x30);
                    F(cfg, 0x28) = x;
                    if (D_00384F7C <= x) {
                        F(cfg, 0x28) = x - D_00384F78;
                    } else if (x <= D_00384F80) {
                        F(cfg, 0x28) = x + D_00384F78;
                    }
                    y = F(cfg, 0x2C) + F(cfg, 0x34);
                    F(cfg, 0x2C) = y;
                    if (D_00384F84 <= y) {
                        F(cfg, 0x2C) = y - D_00384F78;
                    } else if (y <= D_00384F88) {
                        F(cfg, 0x2C) = y + D_00384F78;
                    }
                } else {
                    func_00129C28(pos, next + 0x20);
                    func_00129C28(vel, next + 0x30);
                }
            } else if (mode == 2) {
                if (next != NULL) {
                    func_00129C28(pos, next + 0x20);
                    func_00129C28(vel, next + 0x30);
                } else {
                    Vec4_Set(dir, 0.0f, -1.0f, 0.0f, 1.0f);
                    r0 = rand(); r1 = rand();
                    F(dir, 0) = F(dir, 0) + F(st, 0x58) * RDIFF(r0, r1);
                    r0 = rand(); r1 = rand();
                    F(cfg, 0x68) = F(cfg, 0x68) + F(st, 0x58) * RDIFF(r0, r1);
                    Vec3_Normalize(dir, dir);
                    Vec3_Scale(dir, dir, F(cfg, 0x40));
                    r0 = rand();
                    Vec3_Scale(dir, dir, F(st, 0x5C) + F(st, 0x60) * ((f32)r0 / D_00384F74));
                    Vec3_Add(pos, pos, dir);
                    r0 = rand(); r1 = rand();
                    F(node, 0x30) = F(node, 0x10) * RDIFF(r0, r1);
                    r0 = rand(); r1 = rand();
                    F(node, 0x34) = F(node, 0x10) * RDIFF(r0, r1);
                    r0 = rand(); r1 = rand();
                    F(node, 0x3C) = 1.0f;
                    F(node, 0x38) = F(node, 0x10) * RDIFF(r0, r1);
                }
            } else {
                Vec3_Add(pos, pos, cfg + 0x60);
                r0 = rand(); r1 = rand();
                F(node, 0x30) = F(node, 0x10) * RDIFF(r0, r1);
                r0 = rand(); r1 = rand();
                F(node, 0x34) = F(node, 0x10) * RDIFF(r0, r1);
                r0 = rand(); r1 = rand();
                F(node, 0x3C) = 1.0f;
                F(node, 0x38) = F(node, 0x10) * RDIFF(r0, r1);
            }
        }
        Vec3_Add4(node + 0x40, objst + 0x10, cfg + 0x50, pos, vel);
        F(node, 0x4C) = 1.0f;
        func_00129C28(node + 0x50, cfg + 0x80);
        F(node, 0x5C) = F(node, 0x5C) * F(cfg, 0x3C);
        if (255.0f < F(node, 0x5C)) {
            F(node, 0x5C) = 255.0f;
        }
        mode = st[1];
        if (mode == 0 || mode == 3) {
            f32 life = F(cfg, 0xC);

            if (life - 1.0f <= idx) {
                F(node, 0x5C) = F(node, 0x5C) * 0.0f;
            } else if (life - 2.0f <= idx) {
                F(node, 0x5C) = F(node, 0x5C) * 0.5f;
            }
        }
        n++;
        node = *(u8 **)(node + 0x60);
        if (node == NULL) {
            break;
        }
    }
}
