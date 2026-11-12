#include "common.h"

#define W(p, off) (*(s32 *)((u8 *)(p) + (off)))

s32 BtlScene_IsCharStopped(s32 arg0);
void BtlTask_SetDead(void *arg0);
void EftChain2_SetPos(s32 arg0, void *arg1);
void EftChain2_Stop(s32 arg0);
void EftPtcl3_SetDir(s32 arg0, void *arg1);
void EftPtcl3_SetPos(s32 arg0, void *arg1);
void EftPtcl3_Stop(s32 arg0);
void func_001CC9E8(s32 arg0);
void func_001CCAC8(s32 arg0, void *arg1);
void func_001CCB20(s32 arg0, void *arg1);
void func_00208DE8(s32 arg0, void *arg1, s32 arg2);
s32 func_0020AC48(s32 arg0);

void func_001ADC78(u8 *arg0) {
    u8 *s1, *s3, *s4;
    s32 v1, i, e;

    s1 = *(u8 **)(arg0 + 0x38);
    if (BtlScene_IsCharStopped(W(s1, 0x10)) == 0) {
        s3 = s1 + 0x30;
        s4 = s1 + 0x40;
        func_00208DE8(W(s1, 0x10), s3, W(s1, 0x14));
        for (i = 0; i < 3; i++) {
            e = W(s1, 0x50 + 4 * i);
            EftPtcl3_SetPos(e, s3);
            EftPtcl3_SetDir(e, s4);
        }
        EftChain2_SetPos(W(s1, 0x60), s3);
        func_001CCAC8(W(s1, 0x5C), s3);
        func_001CCB20(W(s1, 0x5C), s4);
        if (func_0020AC48(W(s1, 0x10)) == 0) {
            W(s1, 0x20) = W(s1, 0x20) | 1;
        }
    }
    v1 = W(s1, 0x20);
    if (v1 & 2) {
        BtlTask_SetDead(arg0);
        return;
    }
    if (v1 & 1) {
        for (i = 0; i < 3; i++) {
            e = W(s1, 0x50 + 4 * i);
            EftPtcl3_Stop(e);
            W(s1, 0x50 + 4 * i) = 0;
        }
        EftChain2_Stop(W(s1, 0x60));
        W(s1, 0x60) = 0;
        func_001CC9E8(W(s1, 0x5C));
        W(s1, 0x5C) = 0;
        W(s1, 0x20) = W(s1, 0x20) | 2;
    }
}
