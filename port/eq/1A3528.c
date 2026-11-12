#include "common.h"

extern s32 D_0038781C;
extern f32 D_00384E70;

void memset(void *arg0, s32 arg1, s32 arg2);
s32 rand(void);
void Vec3_Add(s32 arg0, s32 arg1, s32 arg2);
void func_00129BD0(s32 arg0, s32 arg1, f32 farg0);
void func_00129B28(s32 arg0, s32 arg1, s32 arg2);
void func_00129D68(s32 arg0, s32 arg1, f32 farg0, f32 farg1);

void func_001A3528(s32 arg0, s32 arg1, s32 arg2) {
    s32 tab[4];
    f32 vtmp[4];
    u8 *node;
    u8 *ent;
    u8 *s0;
    u8 *tp;
    u8 *list;
    s32 idx;
    s32 j;
    s32 flags;
    s32 next;
    s32 prev;
    f32 r;
    f32 f20;
    f32 scale;

    memset(vtmp, 0, 0x10);
    tab[0] = *(s32 *)((u8 *)D_0038781C + 8);
    tab[1] = tab[0] + 0x40;
    list = (u8 *)arg1;
    node = (u8 *)*(s32 *)list;
    if (node == 0) {
        return;
    }

    do {
        if (*(f32 *)(node + 0x08) < *(f32 *)(node + 0x0C)) {
            ent = (u8 *)arg0 + ((s32)node[5] << 7) + 4;
            for (j = 0; j < 4; j++) {
                idx = node[5];
                tp = (u8 *)tab[idx];
                *(f32 *)(node + 0xA0 + 16 * j) = *(f32 *)(tp + 16 * j) * *(f32 *)(node + 0x1C);
                *(s32 *)(node + 0xA4 + 16 * j) = 0;
                *(f32 *)(node + 0xA8 + 16 * j) = *(f32 *)(tp + 16 * j + 8) * *(f32 *)(node + 0x18);
                *(f32 *)(node + 0xAC + 16 * j) = 1.0f;
            }

            func_00129BD0((s32)vtmp, (s32)(node + 0x60), *(f32 *)(node + 0x30));
            s0 = node + 0x40;
            Vec3_Add((s32)s0, (s32)s0, (s32)vtmp);
            Vec3_Add((s32)(node + 0x50), (s32)s0, arg2 + 0x10);
            *(f32 *)(node + 0x5C) = 1.0f;

            flags = *(s32 *)node;
            if (!(flags & 4)) {
                if (*(f32 *)(ent + 0x70) <= *(f32 *)(node + 0x08)) {
                    *(s32 *)(node + 0x9C) = 0;
                    flags |= 4;
                    *(s32 *)node = flags;
                }
            }
            if (!(flags & 8)) {
                if (*(f32 *)(node + 0x14) <= *(f32 *)(node + 0x08)) {
                    f20 = *(f32 *)(node + 0x0C) - *(f32 *)(node + 0x08);
                    flags |= 8;
                    *(s32 *)node = flags;
                    *(f32 *)(node + 0x9C) = -*(f32 *)(node + 0x8C) / f20;
                }
            }

            s0 = node + 0x80;
            if (!(flags & 0x10)) {
                if (*(f32 *)(node + 0x10) <= *(f32 *)(node + 0x08)) {
                    f20 = *(f32 *)(node + 0x0C) - *(f32 *)(node + 0x08);
                    r = (f32)rand() / D_00384E70;
                    *(f32 *)(node + 0x34) = (*(f32 *)(ent + 0x38) + *(f32 *)(ent + 0x3C) * r - *(f32 *)(node + 0x30)) / f20;
                    r = (f32)rand() / D_00384E70;
                    *(f32 *)(node + 0x20) = (*(f32 *)(ent + 0x68) + *(f32 *)(ent + 0x6C) * r - *(f32 *)(node + 0x18)) / f20;
                    r = (f32)rand() / D_00384E70;
                    *(f32 *)(node + 0x24) = (*(f32 *)(ent + 0x50) + *(f32 *)(ent + 0x54) * r - *(f32 *)(node + 0x1C)) / f20;
                    scale = *(f32 *)(arg2 + 4);
                    *(f32 *)(node + 0x34) = *(f32 *)(node + 0x34) * scale;
                    *(f32 *)(node + 0x24) = *(f32 *)(node + 0x24) * scale;
                    *(f32 *)(node + 0x20) = *(f32 *)(node + 0x20) * scale;
                    flags = *(s32 *)node | 0x10;
                    *(s32 *)node = flags;
                }
            }

            func_00129B28((s32)s0, (s32)s0, (s32)(node + 0x90));
            func_00129D68((s32)s0, (s32)s0, 0.0f, 255.0f);
            *(f32 *)(node + 0x08) = *(f32 *)(node + 0x08) + 1.0f;
            *(f32 *)(node + 0x30) = *(f32 *)(node + 0x30) + *(f32 *)(node + 0x34);
            *(f32 *)(node + 0x1C) = *(f32 *)(node + 0x1C) + *(f32 *)(node + 0x24);
            *(f32 *)(node + 0x18) = *(f32 *)(node + 0x18) + *(f32 *)(node + 0x20);
        } else {
            next = *(s32 *)(node + 0x120);
            prev = *(s32 *)(node + 0x124);
            *(s32 *)node = 0;
            if (prev != 0) {
                *(s32 *)((u8 *)prev + 0x120) = next;
            } else {
                *(s32 *)(list + 0) = next;
            }
            if (next != 0) {
                *(s32 *)((u8 *)next + 0x124) = prev;
            } else {
                *(s32 *)(list + 4) = prev;
            }
            *(s32 *)(list + 0x58) -= 1;
        }
        node = (u8 *)*(s32 *)(node + 0x120);
    } while (node != 0);
}
