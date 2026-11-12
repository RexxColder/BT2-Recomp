#include "common.h"

s32 BtlTaskList_AddTail(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_003878EC;
extern u8 D_003434F0[] __attribute__((section(".data")));

typedef struct {
    s64 w[8];
} TaskBlock;

/* Copies the 0x40-byte block at arg0 to the stack and adds it to the task list D_003434F0 (list head D_003878EC). */
void func_001E66A0(void *arg0) {
    TaskBlock blk = *(TaskBlock *)arg0;

    BtlTaskList_AddTail(D_003878EC, (s32)D_003434F0, (s32)&blk);
}
