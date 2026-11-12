#include "common.h"

extern u8 *D_00387A40;
extern u8 *gScrWarp;

s32 rand(void);
s32 func_0025E068(void);
s32 StgRigid_Create(s32 arg0, u8 *arg1, f32 farg0);
void StgRigid_LaunchSpin(s32 arg0, s32 arg1, s32 arg2);
void StgRigid_GetMatrix(u8 *arg0, s32 arg1);
void func_0025E0B8(s32 arg0, u8 *arg1, u8 *arg2);
void func_00260B58(u8 *arg0, u8 *arg1);
void func_00265AC8(u8 *arg0, s32 arg1);
void func_0026A240(u8 *arg0, f32 *arg1);

/* Spawns one shock-wave slot from gScrWarp+0x40 when it is free (count >= 8, or a 1-in-8 roll
 * for smaller counts), then sets its colour by count for counts 8..11. The asm returns a stale v0
 * on every path; the only caller (0x00274BA8) never reads v0, so this is void. */
void func_002425D8(s32 arg0, s32 arg1, s32 arg2) {
    u8 *s2;
    u8 *base;
    u8 *v10;
    s32 id;
    s32 h;
    s32 idx;
    f32 col[4];

    if (gScrWarp == NULL) {
        return;
    }
    s2 = NULL;
    if (*(s32 *)(gScrWarp + 0x40) == 0) {
        s2 = gScrWarp + 0x40;
    }
    if (s2 == NULL) {
        return;
    }

    if ((u32)*(s32 *)(s2 + 0x10) >= 8 || (rand() & 7) == 0) {
        id = func_0025E068();
        *(s32 *)(s2 + 0x8) = id;
        if (id < 0) {
            return;
        }
        h = StgRigid_Create(arg0, s2 + 0x60, 2.25f);
        *(s32 *)(s2 + 0xC) = h;
        if (h < 0) {
            return;
        }

        base = *(u8 **)(D_00387A40 + 0x8);
        func_0025E0B8(*(s32 *)(s2 + 0x8), base + 5408 * *(s32 *)(s2 + 0x8), gScrWarp + 4);
        StgRigid_LaunchSpin(*(s32 *)(s2 + 0xC), arg1, arg2);
        StgRigid_GetMatrix(s2 + 0x20, *(s32 *)(s2 + 0xC));

        base = *(u8 **)(D_00387A40 + 0x8);
        v10 = base + 5408 * *(s32 *)(s2 + 0x8);
        func_00260B58(v10, s2 + 0x20);

        idx = *(s32 *)(s2 + 0x10) - 1;
        if ((u32)idx >= 7 && (u32)idx < 11) {
            if (idx == 7) {
                col[0] = 0.0f;
                col[1] = 255.0f;
                col[2] = 78.0f;
                col[3] = 70.0f;
            } else if (idx == 8) {
                col[0] = 0.0f;
                col[1] = 255.0f;
                col[2] = 246.0f;
                col[3] = 70.0f;
            } else if (idx == 9) {
                col[0] = 255.0f;
                col[1] = 246.0f;
                col[2] = 0.0f;
                col[3] = 70.0f;
            } else {
                col[0] = 179.0f;
                col[1] = 0.0f;
                col[2] = 1.0f;
                col[3] = 70.0f;
            }
            func_00265AC8(v10, 6);
            func_0026A240(v10, col);
        }
        *(s32 *)s2 = 1;
    }
}
