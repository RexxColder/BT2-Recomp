#include "common.h"

extern u8 *D_003876A0;

s32 func_00100ED0(s32 arg0, s32 arg1, s32 arg2);
s32 func_00100FC8(s32 arg0);
void func_00298240(s32 arg0, void *arg1);
void func_00297A78(s32 arg0, s32 arg1, s32 arg2);
void func_0028BCB0(void);
void func_0028BB60(s32 arg0);
s32 Snd_SpuTransferCheck(void *arg0);
void *memset(void *dst, s32 val, u32 n);

/* 0x00104990: 7-state sound/SPU load sequence. req[0] is the state; req[2..4] are counts; the handles live at st+0x10.. */
s32 func_00104990(s32 *req) {
    u8 *st;

    st = D_003876A0;
    switch (req[0]) {
    case 0:
        *(s32 *)(st + 0x10) = func_00100ED0(0x33D3, 0, 1);
        if (req[2] > 0) {
            *(s32 *)(st + 0x14) = func_00100ED0(req[2], 0, 0);
        }
        if (req[3] > 0) {
            *(s32 *)(st + 0x18) = func_00100ED0(req[3], 0, 0);
        }
        if (req[4] > 0) {
            *(s32 *)(st + 0x1C) = func_00100ED0(req[4], 0, 0);
        }
        func_00100FC8(1);
        req[0] += 1;
        return 0;
    case 1:
        if (func_00100FC8(0) == 0) {
            return 0;
        }
        req[0] += 1;
        /* fall through */
    case 2:
        memset(st + 0x90, 0, 16);
        *(u64 *)(st + 0xA0) = 0;
        *(u64 *)(st + 0xA8) = 0;
        func_00298240(*(s32 *)(st + 0x10), st + 0x90);
        if (req[3] > 0) {
            func_00298240(*(s32 *)(st + 0x18), st + 0xA0);
        }
        if (req[4] > 0) {
            func_00298240(*(s32 *)(st + 0x1C), st + 0xA8);
        }
        func_0028BCB0();
        func_00297A78(0, *(s32 *)(st + 0x10), 0);
        req[0] += 1;
        return 0;
    case 3:
        if (!Snd_SpuTransferCheck(st)) {
            return 0;
        }
        func_0028BB60(*(s32 *)(st + 0x10));
        if (req[2] > 0) {
            func_00297A78(0, *(s32 *)(st + 0x14), 0);
            req[0] = 4;
            return 0;
        }
        if (req[3] > 0) {
            goto l28;
        }
        goto l32;
    case 4:
        if (!Snd_SpuTransferCheck(st)) {
            return 0;
        }
        func_0028BB60(*(s32 *)(st + 0x14));
        if (req[3] <= 0) {
            goto l32;
        }
        goto l28;
    case 5:
        if (!Snd_SpuTransferCheck(st)) {
            return 0;
        }
        func_0028BB60(*(s32 *)(st + 0x18));
        goto l32;
    case 6:
        if (!Snd_SpuTransferCheck(st)) {
            return 0;
        }
        func_0028BB60(*(s32 *)(st + 0x1C));
        req[0] = 6;
        return 1;
    default:
        return 1;
    }

l28:
    func_00297A78(0, *(s32 *)(st + 0x18), 0);
    req[0] = 5;
    return 0;

l32:
    if (req[4] <= 0) {
        return 1;
    }
    func_00297A78(0, *(s32 *)(st + 0x1C), 0);
    req[0] = 6;
    return 0;
}
