#include "common.h"

void *memset(void *, int, unsigned int);
void *memcpy(void *, const void *, unsigned int);
s32 BtlTaskList_AddTail(s32 arg0, void *arg1, void *arg2);
extern u8 *D_003877B8;
extern u8 D_00341FB8 __attribute__((section(".data")));

/* 0x0018DF28 (EftQuad_CreateEx in BT3): builds a 0x38-byte quad record: def at +0, def2 at +4, tex at +8, 16 bytes
 * of pos at +0x10, 16 bytes of dir at +0x20, size (f12) at +0x30, life (f13) at +0x34. Returns 0 when the manager
 * D_003877B8, def or def2 is NULL; else BtlTaskList_AddTail(*(D_003877B8 + 0x9688), &D_00341FB8, record). */
s32 EftQuad_CreateEx(u8 *def, u8 *def2, u8 *tex, u8 *pos, u8 *dir, f32 size, f32 life) {
    u8 rec[0x50];

    memset(rec, 0, 0x40);
    memcpy(rec + 0x10, pos, 16);
    memcpy(rec + 0x20, dir, 16);
    if (D_003877B8 == NULL) {
        return 0;
    }
    if (def == NULL) {
        return 0;
    }
    if (def2 == NULL) {
        return 0;
    }
    *(s32 *)(rec + 0x00) = (s32)def;
    *(s32 *)(rec + 0x04) = (s32)def2;
    *(s32 *)(rec + 0x08) = (s32)tex;
    *(f32 *)(rec + 0x30) = size;
    *(f32 *)(rec + 0x34) = life;
    return BtlTaskList_AddTail(*(s32 *)(D_003877B8 + 0x9688), &D_00341FB8, rec);
}
