#include "common.h"

void *func_002A4108(s32 arg0);
void func_002A1340();
void func_002A12B0(void *arg0);
void func_002A13E8();
s32 Gsc_GetString(void);
void Font_PrintAt(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_003B0C34 __attribute__((section(".data")));

s32 func_002A7838(s32 arg0, s32 *arg1) {
    void *temp;
    s32 str;

    if (arg0 == 0) {
        *arg1 = 0;
        return 0;
    }
    if (arg0 == 1) {
        return 0;
    }
    if (arg0 == 2) {
        if (*arg1 != 0) {
            return 1;
        }
        if (D_003B0C34 & 0x4000) {
            *arg1 = 1;
        }
        return 0;
    }
    if (arg0 == 3) {
        temp = func_002A4108(arg0);
        func_002A1340();
        func_002A12B0(temp);
        str = Gsc_GetString();
        Font_PrintAt(*(s32 *)((u8 *)temp + 0x50), *(s32 *)((u8 *)temp + 0x54), str);
        func_002A13E8();
        return 0;
    }
    return 0;
}
