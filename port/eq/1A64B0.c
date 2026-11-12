#include "m2c_macros.h"

#define AT_F32(p, o) (*(f32 *)((u8 *)(p) + (o)))
#define AT_S32(p, o) (*(s32 *)((u8 *)(p) + (o)))

void *memset(void *dst, s32 c, u32 n);
void func_00129C28(void *dst, void *src);
void Vec3_Normalize(void *dst, void *src);
void EftTrail_SetTextures();
void BtlTaskList_AddTail(void *list, void *cls, void *init);

extern u8 *gEftTrail;
extern u8 *D_003876A0;
extern f32 D_00384E8C;
extern f32 D_00384E90;
extern u8 D_00342688[] __attribute__((section(".data")));
extern u8 D_003426A0[] __attribute__((section(".data")));

/* EftTrail_StartOwned: EftTrail is 0x220 bytes, laid out as in BT3 (include/battle/eft_q.h). */
void EftTrail_StartOwned(u8 kind, s32 objId, void *pos, void *color, void *tbl, f32 width) {
    u8 init[0x220];
    u8 dir[0x10];
    s32 i;

    memset(dir, 0, 0x10);
    memset(init, 0, 0x220);
    AT_F32(dir, 0xC) = 1.0f;
    AT_S32(init, 0x4) = objId;
    *(u8 *)(init + 0x8) = kind;
    AT_S32(init, 0x1B0) = 0x14;
    if (*(s64 *)(D_003876A0 + 0x4D8) & 2) {
        AT_S32(init, 0x1B0) = 8;
    }
    func_00129C28(init + 0x40, pos);
    for (i = 0; i < AT_S32(init, 0x1B0); i++) {
        func_00129C28(init + 0x70 + i * 0x10, pos);
    }
    func_00129C28(init + 0x50, dir);
    Vec3_Normalize(init + 0x50, init + 0x50);
    func_00129C28(init + 0x60, color);
    AT_F32(init, 0xC) = 1.0f;
    AT_F32(init, 0x10) = 1.0f;
    AT_F32(init, 0x14) = D_00384E8C;
    AT_F32(init, 0x18) = D_00384E90;
    AT_F32(init, 0x1C) = width;
    AT_F32(init, 0x20) = width;
    AT_S32(init, 0x24) = -1;
    *(void **)(init + 0x30) = D_003426A0;
    *(void **)(init + 0x0) = tbl;
    AT_S32(init, 0x1B4) = 0;
    AT_S32(init, 0x1B8) = 4;
    EftTrail_SetTextures(init, tbl, 4);
    BtlTaskList_AddTail(*(void **)gEftTrail, D_00342688, init);
}
