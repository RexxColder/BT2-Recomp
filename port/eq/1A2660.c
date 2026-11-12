#include "common.h"

extern f32 D_00384E68;

s32 rand(void);
void func_00129B28(u8 *a0, u8 *a1, u8 *a2);
void func_00129D68(u8 *arg0, u8 *arg1, f32 arg2, f32 arg3);

/* Particle update: walks the live list at head (head[0] first, head[1] tail, head[22] count),
   advances each node, and unlinks the ones whose age reached their life. */
void func_001A2660(u8 *base, s32 *head, u8 *cfg) {
    u8 *node;
    u8 *next;
    u8 *prev;
    u8 *em;
    u8 *vec;
    s32 flags;
    f32 age;
    f32 life;
    f32 span;
    f32 ratio;

    node = (u8 *)head[0];
    while (node != NULL) {
        age = *(f32 *)(node + 0x8);
        life = *(f32 *)(node + 0xC);

        if (age < life) {
            em = base + ((s32)node[5] << 7) + 4;
            flags = *(s32 *)node;

            if ((flags & 4) == 0 && *(f32 *)(em + 0x70) <= age) {
                *(s32 *)(node + 0x9C) = 0;
                flags |= 4;
                *(s32 *)node = flags;
            }

            if ((flags & 8) == 0 && *(f32 *)(node + 0x14) <= age) {
                span = life - age;
                flags |= 8;
                *(s32 *)node = flags;
                *(f32 *)(node + 0x9C) = -*(f32 *)(node + 0x8C) / span;
            }

            if ((flags & 0x10) == 0 && *(f32 *)(node + 0x10) <= age) {
                span = life - age;
                ratio = (f32)rand() / D_00384E68;
                flags |= 0x10;
                *(s32 *)node = flags;
                *(f32 *)(node + 0x24) =
                    ((*(f32 *)(em + 0x50) + *(f32 *)(em + 0x54) * ratio) * *(f32 *)(cfg + 0x4) -
                     *(f32 *)(node + 0x1C)) / span;
            }

            vec = node + 0x80;
            func_00129B28(vec, vec, node + 0x90);
            func_00129D68(vec, vec, 0.0f, 255.0f);

            *(f32 *)(node + 0x1C) = *(f32 *)(node + 0x1C) + *(f32 *)(node + 0x24);
            if (*(f32 *)(node + 0x1C) < 0.0f) {
                *(f32 *)(node + 0x1C) = 0.0f;
            }
            *(f32 *)(node + 0x8) = *(f32 *)(node + 0x8) + 1.0f;
        } else {
            *(s32 *)node = 0;
            prev = *(u8 **)(node + 0x124);
            next = *(u8 **)(node + 0x120);
            if (prev != NULL) {
                *(u8 **)(prev + 0x120) = next;
            } else {
                head[0] = (s32)next;
            }
            if (next != NULL) {
                *(u8 **)(next + 0x124) = prev;
            } else {
                head[1] = (s32)prev;
            }
            head[22] = head[22] - 1;
        }

        node = *(u8 **)(node + 0x120);
    }
}
