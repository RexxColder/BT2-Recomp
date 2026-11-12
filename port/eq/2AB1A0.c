#include "common.h"

extern s32 D_003876A0;
extern s32 D_00387F2C;
extern s32 D_003B26B0;

s32 func_00100ED0(s32 arg0, s32 arg1, s32 arg2);
s32 func_00100FC8(s32 arg0);
void func_00298240(s32 arg0, s32 arg1);
void func_0028BCB0(void);
void func_00297A78(s32 arg0, s32 arg1, s32 arg2);
s32 Snd_SpuTransferCheck(void);
void func_0028BB60(s32 arg0);

/* Sound-bank load sequencer: a1[0] is the step. Steps 0..2 pick the bank ids, start the transfers and
 * prepare the mix buffers; steps 3..5 wait for the SPU transfers and kick the next one. Returns 1 when
 * the load is complete (or on an unknown step). */
s32 func_002AB1A0(s32 *a1) {
    s32 A = D_003876A0;
    s32 *rec;
    s32 v7;
    s32 v8;
    s32 v11;
    s32 v12;
    s32 v13;
    s32 v15;
    s32 result;

    switch (*a1) {
    case 0:
        *(s32 *)(A + 0x10) = func_00100ED0(0x33D3, 0, 1);
        rec = (s32 *)a1[5];
        if (rec[9] != 0) {
            rec[10] = rec[9];
        } else {
            rec[9] = 13269;
            rec[10] = 13269;
        }
        v7 = rec[10];
        a1[2] = v7;
        if (v7 > 0) {
            *(s32 *)(A + 0x14) = func_00100ED0(v7, *(s32 *)(A + 0x14), 0);
        }
        if (rec[11] != 0) {
            v8 = D_00387F2C;
            if (D_003B26B0 == 1) {
                s32 q = (rec[11] - 44219) / 9;
                s32 alt = q + 43939;
                s32 pick = q + 44079;
                if ((*(s32 *)(v8 + 4104) & 1) == 0) {
                    pick = alt;
                }
                rec[12] = pick;
                goto step0_tail;
            }
        } else {
            v8 = D_00387F2C;
        }
        v12 = 44079;
        if ((*(s32 *)(v8 + 4104) & 1) == 0) {
            v12 = 43939;
        }
        rec[12] = v12;

step0_tail:
        v13 = rec[12];
        rec[13] = v13;
        a1[3] = v13;
        if (v13 > 0) {
            *(s32 *)(A + 0xC) = func_00100ED0(v13, *(s32 *)(A + 0xC), 0);
        }
        func_00100FC8(1);
        *a1 = *a1 + 1;
        return 0;

    case 1:
        result = func_00100FC8(0);
        if (result == 0) {
            return result;
        }
        *a1 = *a1 + 1;
        goto step2;

    case 2:
step2:
        __builtin_memset((void *)(A + 0x90), 0, 16);
        *(s64 *)(A + 0xA0) = 0;
        *(s64 *)(A + 0xA8) = 0;
        func_00298240(*(s32 *)(A + 0x10), A + 0x90);
        if (a1[3] > 0) {
            func_00298240(*(s32 *)(A + 0xC), A + 0xA0);
        }
        func_0028BCB0();
        func_00297A78(0, *(s32 *)(A + 0x10), 0);
        *a1 = *a1 + 1;
        return 0;

    case 3:
        if (Snd_SpuTransferCheck() == 0) {
            return 0;
        }
        func_0028BB60(*(s32 *)(A + 0x10));
        if (a1[2] > 0) {
            func_00297A78(0, *(s32 *)(A + 0x14), 0);
            *a1 = 4;
            return 0;
        }
        v15 = a1[3];
        goto wait_done;

    case 4:
        if (Snd_SpuTransferCheck() == 0) {
            return 0;
        }
        v15 = a1[3];
        goto wait_done;

    case 5:
        return Snd_SpuTransferCheck() != 0;

    default:
        return 1;
    }

wait_done:
    if (v15 <= 0) {
        return 1;
    }
    func_00297A78(0, *(s32 *)(A + 0xC), 0);
    *a1 = 5;
    return 0;
}
