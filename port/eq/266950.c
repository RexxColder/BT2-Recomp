#include "common.h"

#define LD32(p, off) (*(s32 *)((u8 *)(p) + (off)))

s32 func_00266938(s32 arg0);
s32 rand(void);

extern u8 D_00344800[] __attribute__((section(".data")));
extern u8 D_00344840[] __attribute__((section(".data")));
extern u8 D_00344880[] __attribute__((section(".data")));
extern u8 D_003448C0[] __attribute__((section(".data")));
extern u8 D_00344900[] __attribute__((section(".data")));
extern u8 D_00344940[] __attribute__((section(".data")));
extern u8 D_00344980[] __attribute__((section(".data")));
extern u8 D_003449C0[] __attribute__((section(".data")));

/* 0x00266950: picks one of four jaw key tables at random for the face (+0x2C): the table group depends on flag
 * 0x400000 of the model (*(obj+0x44)). Random index 0, 1, 2 selects the first three tables, others the fourth. */
void BtlObjFace_PickJawKeys(s32 arg0, s32 arg1) {
    u32 tab; /* integer address: a pointer switch becomes a pointer table, not lowerable with 4-byte pointers */
    s32 r;

    if (func_00266938(arg0) == 0) {
        return;
    }

    if (LD32(LD32(arg0, 0x44), 0) & 0x400000) {
        r = rand() % 4;
        switch (r) {
        case 0:
            tab = (u32)D_00344900;
            break;
        case 1:
            tab = (u32)D_00344940;
            break;
        case 2:
            tab = (u32)D_00344980;
            break;
        default:
            tab = (u32)D_003449C0;
            break;
        }
    } else {
        r = rand() % 4;
        switch (r) {
        case 0:
            tab = (u32)D_00344800;
            break;
        case 1:
            tab = (u32)D_00344840;
            break;
        case 2:
            tab = (u32)D_00344880;
            break;
        default:
            tab = (u32)D_003448C0;
            break;
        }
    }
    LD32(arg1, 0x2C) = tab;
}
