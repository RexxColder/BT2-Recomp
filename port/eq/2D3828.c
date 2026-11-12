#include "common.h"

extern u8 D_0037A5A0[];
extern u8 *D_00346E88;
extern s32 D_00346E84;
extern u8 *D_00346E90;
extern u8 *D_00346E94;

void *memset(void *arg0, s32 arg1, s32 arg2);
char *strcpy(char *arg0, char *arg1);
s32 strlen(char *arg0);

void func_002D3828(void) {
    u8 buf[0x120];
    s32 i;

    for (i = 0; i < 0x100; i++) {
        buf[i] = D_0037A5A0[i];
    }
    for (i = 0; i < 0x12; i++) {
        buf[0x100 + i] = D_0037A5A0[0x100 + i];
    }
    if (D_00346E88 != NULL) {
        memset(D_00346E88, 0, D_00346E84);
        D_00346E90 = D_00346E88;
        strcpy((char *)D_00346E88, (char *)buf);
        D_00346E94 = D_00346E90 + strlen((char *)buf);
        D_00346E90 = D_00346E94;
    }
}
