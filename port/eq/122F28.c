#include "common.h"

void func_00121938(s32 arg0);
void func_00121B68(s32 arg0);
void func_00122498(s32 *arg0);
void func_00122EC0(u8 *arg0, s32 arg1, s32 arg2);
void func_001227D8(u8 *arg0);
void func_00122738(s32 arg0);
void func_001229F0(u8 *arg0);
void func_00122B98(void *arg0);
s32 func_00122638(s32 arg0);
s32 EftObj_UpdateMtx(s32 id);
s32 func_001FA3A8(s32 arg0);
s32 func_00208DE8(s32 arg0, u8 *arg1, s32 arg2);
void func_003126C8(void *arg0, void *arg1);
s32 func_00123CD8(s32 arg0, u8 *arg1, u8 *arg2);

s32 func_00122F28(u8 *arg0) {
    u8 sp9[16];
    u8 sp10[16];
    u8 *cur;
    u8 *st;
    s32 result;
    s32 mode;
    s32 draw;
    s32 updated;
    s32 k;

    cur = arg0 + 0xBE0;
    st = arg0 + 0xFE0;

    result = *(s32 *)(arg0 + 0xBE4);
    if (result <= 0 || result == 1) {
        return result;
    }

    if (*(s32 *)cur != *(s32 *)st) {
        func_00122EC0(arg0, *(s32 *)(st + 0x18), *(s32 *)(st + 0x1C));
    }
    func_00121938((s32)arg0);
    func_00121B68((s32)arg0);
    func_00122498((s32 *)arg0);

    mode = *(s32 *)(st + 0x2C);
    if (mode == 1) {
        func_001227D8(arg0);
    } else if (mode >= 2) {
        if (mode == 2) {
            func_001229F0(arg0);
        } else if (mode == 3) {
            func_00122B98(arg0);
        }
    } else if (mode == 0) {
        func_00122738((s32)arg0);
    }
    result = *(s32 *)(cur + 0xC);

    draw = 0;
    if (result != 0) {
        draw = func_00122638((s32)arg0) != 0;
        if (*(s32 *)(arg0 + 0x14) != 0) {
            *(s32 *)(st + 0x48) = 0;
        } else {
            for (k = 0; k < 4; k++) {
                if ((u8)(arg0[0x10 + k] + 0xBF) >= 0x7F) {
                    break;
                }
            }
            if (k < 4) {
                *(s32 *)(st + 0x48) = 0;
            } else {
                *(s32 *)(st + 0x48) = *(s32 *)(st + 0x48) + 1;
                if (*(s32 *)(st + 0x48) >= 0x1F) {
                    draw = 1;
                }
            }
        }

        updated = EftObj_UpdateMtx((s32)arg0);
        if (func_001FA3A8(updated) & 0x10) {
            draw = 1;
        }
        if (*(u8 *)(st + 0x6) != 0) {
            draw = 1;
        }
        if (*(s32 *)(st + 0x4C) >= 91) {
            draw = 1;
        }
    }

    if (draw != 0) {
        func_00208DE8(*(s32 *)arg0, sp9, 17);
        func_003126C8(sp10, st + 0x90);
        return func_00123CD8((s32)arg0, sp9, sp10);
    }
    return 0;
}
