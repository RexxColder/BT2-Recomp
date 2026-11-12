#include "common.h"

u8 *func_0028BAA8(s32 arg0);
void func_0028BC08(s32 arg0);
void func_00297580(s32 arg0, s32 arg1);
void *memset(void *arg0, s32 arg1, u32 arg2);
s32 sceSifAllocIopHeap(s32 arg0);
void sceSdRemoteInit(void);
void sceSdRemoteCallbackInit(s32 arg0);
extern u8 *D_00387ED0;

void func_00297908(void) {
    u8 *temp_v0;

    temp_v0 = func_0028BAA8(0x74);
    D_00387ED0 = temp_v0;
    memset(temp_v0, 0, 0x74);
    *(s32 *)(D_00387ED0 + 0x6C) = sceSifAllocIopHeap(0x81800);
    *(s32 *)(D_00387ED0 + 0x64) = -1;
    func_0028BC08(-1);
    sceSdRemoteInit();
    sceSdRemoteCallbackInit(5);
    func_00297580(1, 0x4000);
}
