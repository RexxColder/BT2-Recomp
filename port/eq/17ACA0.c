#include "common.h"

extern u8 *gEftAuraPool;
extern u8 *gEftAuraPrm;
extern u8 *D_0038777C;

void func_00129C28();
void func_00129B58(u8 *arg0, u8 *arg1, u8 *arg2);
void func_00129BD0(u8 *arg0, u8 *arg1, f32 arg2);
void func_00129B28(u8 *arg0, u8 *arg1, u8 *arg2);
void func_00129D68(u8 *arg0, u8 *arg1, f32 arg2, f32 arg3);
void EftAura_TurnFlame(u8 *arg0, u8 *arg1, f32 arg2);
void EftAura_AccelFlame(u8 *arg0, f32 arg1);
void Vec3_Add(u8 *arg0, u8 *arg1, u8 *arg2);
f32 EftAura_GetFlameSize(u8 *arg0, s32 arg1, s32 arg2);
f32 EftAura_GetFlameStretch(u8 *arg0, s32 arg1, s32 arg2);
s32 EftAura_SpawnFlames(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);

void func_0017ACA0(u8 *arg0, s32 arg1, f32 farg) {
    u8 frame[0x50];
    u8 *link;
    u8 *node;
    u8 *s0;
    s32 flags;
    s32 b9;
    s32 v1;
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f3;
    f32 f20;

    link = gEftAuraPool + 0x14;
    node = *(u8 **)link;
    while (node != 0) {
        if (*(u8 *)(node + 7) != arg1) {
            link = node + 0xC0;
            goto next;
        }
        f0 = *(f32 *)(node + 0x10);
        if (!(0.0f < f0)) {
            goto B0B0;
        }

        /* TRUE branch: 0 < life, type matches */
        b9 = *(u8 *)(node + 9);
        ((void (*)(u8 *, u8 *, f32))func_00129C28)(frame + 0x10, arg0 + (b9 << 4) + 0x90, farg);
        func_00129C28(frame, frame + 0x10);
        v1 = *(s32 *)(D_0038777C + b9 * 12 + 0x414);
        if (v1 >= 0) {
            func_00129C28(frame + 0x20, arg0 + (b9 << 4) + 0x1D0);
            func_00129B58(frame + 0x30, frame + 0x20, frame + 0x10);
            func_00129BD0(frame + 0x40, frame + 0x30, *(f32 *)(node + 0x34));
            func_00129B28(frame, frame, frame + 0x40);
        }
        func_00129B28(frame, frame, node + 0x40);

        s0 = node + 0xB0;
        f20 = *(f32 *)(node + 0x10) / *(f32 *)(node + 0x14);
        EftAura_TurnFlame(node, frame, f20);
        EftAura_AccelFlame(node, f20);
        func_00129BD0(frame + 0x40, node + 0x80, *(f32 *)(node + 0x30) + *(f32 *)(arg0 + 0x40));
        Vec3_Add(s0, s0, frame + 0x40);
        func_00129B28(node + 0x50, frame, s0);

        *(f32 *)(node + 0x5C) = 1.0f;
        f2 = *(f32 *)(node + 0x1C) + *(f32 *)(node + 0x24);
        f3 = *(f32 *)(node + 0x20) + *(f32 *)(node + 0x28);
        *(f32 *)(node + 0x1C) = f2;
        *(f32 *)(node + 0x20) = f3;
        if (f2 < 0.0f) {
            *(s32 *)(node + 0x1C) = 0;
        }
        if (f3 < 0.0f) {
            *(s32 *)(node + 0x20) = 0;
        }

        flags = *(s32 *)node;
        if (!(flags & 8)) {
            f0 = *(f32 *)(node + 0x10) / *(f32 *)(node + 0x14);
            f2 = *(f32 *)(gEftAuraPrm + 4);
            f0 = 1.0f - f0;
            if (f2 < f0) {
                f0 = (EftAura_GetFlameSize(node, arg1, 2) - *(f32 *)(node + 0x1C)) / *(f32 *)(node + 0x10);
                *(f32 *)(node + 0x24) = f0;
                f0 = EftAura_GetFlameStretch(node, arg1, 2);
                f0 = (f0 - *(f32 *)(node + 0x20)) / *(f32 *)(node + 0x10);
                flags = flags | 8;
                *(s32 *)node = flags;
                *(f32 *)(node + 0x28) = f0;
            }
        }

        if (!(flags & 1)) {
            f1 = *(f32 *)(node + 0x14) - *(f32 *)(node + 0x10);
            f0 = *(f32 *)(gEftAuraPrm + 0x2C);
            if (f0 <= f1) {
                *(s32 *)(node + 0x7C) = 0;
                flags = flags | 1;
                *(s32 *)node = flags;
            }
        }

        if (!(flags & 2)) {
            f1 = *(f32 *)(node + 0x10);
            f0 = *(f32 *)(gEftAuraPrm + 0x30);
            if (f1 <= f0) {
                f1 = f1 + 1.0f;
                f2 = *(f32 *)(arg0 + 0x40C);
                f0 = *(f32 *)(node + 0x6C);
                flags = flags | 2;
                *(s32 *)node = flags;
                f0 = f0 - f2;
                f1 = 1.0f / f1;
                f0 = f0 * f1;
                f0 = -f0;
                *(f32 *)(node + 0x7C) = f0;
                s0 = node + 0x60;
            }
        }

        func_00129B28(s0, s0, node + 0x70);
        func_00129D68(s0, s0, 0.0f, 1.0f);

        f0 = *(f32 *)(node + 0x10) - 1.0f;
        f1 = *(f32 *)(node + 0xC);
        *(f32 *)(node + 0x10) = f0;
        if (!(f0 <= f1)) {
            link = node + 0xC0;
            goto next;
        }

        flags = *(s32 *)node;
        if (!(flags & 0x10)) {
            f0 = (EftAura_GetFlameSize(node, arg1, 3) - *(f32 *)(node + 0x1C)) / *(f32 *)(node + 0x10);
            *(f32 *)(node + 0x24) = f0;
            f0 = EftAura_GetFlameStretch(node, arg1, 3);
            f0 = (f0 - *(f32 *)(node + 0x20)) / *(f32 *)(node + 0x10);
            flags = flags | 0x10;
            *(s32 *)node = flags;
            *(f32 *)(node + 0x28) = f0;
        }

        /* B070 */
        link = node + 0xC0;
        if (flags & 4) {
            goto next;
        }
        if (!(flags & 0x800)) {
            if (EftAura_SpawnFlames(arg0, arg1, b9, 1) != 0) {
                *(s32 *)node = *(s32 *)node | 4;
            }
            goto next;
        }
        *(s32 *)node = flags | 4;
        goto next;

    B0B0:
        flags = *(s32 *)node;
        if (flags & 4) {
            *(u8 **)link = *(u8 **)(node + 0xC0);
            *(u8 **)(node + 0xC0) = *(u8 **)(gEftAuraPool + 0x10);
            *(u8 **)(gEftAuraPool + 0x10) = node;
            *(s32 *)(arg0 + 0x38) = *(s32 *)(arg0 + 0x38) - 1;
            goto next;
        }
        if (EftAura_SpawnFlames(arg0, arg1, *(u8 *)(node + 9), 1) == 0) {
            goto next;
        }
        *(s32 *)node = *(s32 *)node | 4;

    next:
        node = *(u8 **)link;
    }
}
