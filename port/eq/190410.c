#include "common.h"

s32 BtlTaskList_AddTail(s32 arg0, void *arg1, void *arg2);
void *memset(void *, int, unsigned int);
void *memcpy(void *, const void *, unsigned int);
extern u8 D_00341FE8 __attribute__((section(".data")));
extern u8 *D_003877BC;

/* 0x00190410: builds a 0x40-byte record: arg0, arg1, arg2 at +0/+4/+8, 16 bytes of arg3 at +0x10,
 * 16 bytes of arg4 at +0x20, f12 and f13 at +0x30/+0x34. Returns 0 when D_003877BC, arg0 or arg1 is
 * zero, else BtlTaskList_AddTail(D_003877BC->[0x5588], &D_00341FE8, record). */
s32 func_00190410(s32 arg0, s32 arg1, s32 arg2, u8 *arg3, u8 *arg4, f32 arg5, f32 arg6) {
    u8 rec[0x50];

    memset(rec, 0, 0x40);
    memcpy(rec + 0x10, arg3, 16);
    memcpy(rec + 0x20, arg4, 16);
    if (D_003877BC == NULL || arg0 == 0 || arg1 == 0) {
        return 0;
    }
    *(s32 *)(rec + 0x00) = arg0;
    *(s32 *)(rec + 0x04) = arg1;
    *(s32 *)(rec + 0x08) = arg2;
    *(f32 *)(rec + 0x30) = arg5;
    *(f32 *)(rec + 0x34) = arg6;
    return BtlTaskList_AddTail(*(s32 *)(D_003877BC + 0x5588), &D_00341FE8, rec);
}
