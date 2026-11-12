#include "common.h"

s32 BtlTaskList_AddTail(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_00387820;
extern u8 D_00342418[] __attribute__((section(".data")));

typedef struct {
    s64 w[8];
} EftChainBlock;

/* Copies the 0x40-byte block at arg0 to the stack and adds it to the task list D_00342418 (list head D_00387820). */
void EftChain_Create(void *arg0) {
    EftChainBlock blk = *(EftChainBlock *)arg0;

    BtlTaskList_AddTail(D_00387820, (s32)D_00342418, (s32)&blk);
}
