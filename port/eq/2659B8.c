#include "common.h"

void func_00260620(s32 arg0);
extern u8 *D_003876A0;
extern u8 *D_00387A40;

void func_002659B8(void) {
    s32 i;
    s32 off;
    u8 *elem;

    i = 0;
    if (*(s32 *)(D_00387A40 + 4) > 0) {
        off = 0;
        do {
            elem = (u8 *)(*(s32 *)D_00387A40 + off);
            off += 0x18580;
            if ((*(s64 *)(D_003876A0 + 0x4D8) & 0x100) == 0) {
                func_00260620((s32)elem);
                *(s32 *)(elem + 0xE54) = *(s32 *)(elem + 0xE50);
                *(s32 *)(elem + 0xE50) = 0;
            }
            i += 1;
        } while (i < *(s32 *)(D_00387A40 + 4));
    }

    i = 0;
    if (*(s32 *)(D_00387A40 + 0xC) > 0) {
        off = 0;
        do {
            elem = (u8 *)(*(s32 *)(D_00387A40 + 8) + off);
            off += 0x1520;
            *(s32 *)(elem + 0xAF8) = 0;
            if (*(s32 *)(elem + 0xC) != 0 && !(*(s64 *)(D_003876A0 + 0x4D8) & 0x100)) {
                func_00260620((s32)elem);
                *(s32 *)(elem + 0xE54) = *(s32 *)(elem + 0xE50);
                *(s32 *)(elem + 0xE50) = 0;
            }
            i += 1;
        } while (i < *(s32 *)(D_00387A40 + 0xC));
    }
}
